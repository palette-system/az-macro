#include <Wire.h>
#include <BleMouse.h>

BleMouse bleMouse;


#define  MTCH6301_I2C_ADDR      0x25
#define  MTCH6301_MODE_GESTURE  0x01
#define  MTCH6301_MODE_TOUCH    0x02
#define  TOUCH_MAX  11


// 今押されているマウスボタン情報
struct touch_data {
    short data_type; // 0 = 離された , 1 = タッチ中
    short move_x; // 開始位置からの移動距離　X座標
    short move_y; // 開始位置からの移動距離　Y座標
    short move_count; // 移動した回数
    short last_x; // 最後に取得したX座標
    short last_y; // 最後に取得したY座標
    uint32_t start_time; // タッチし始めた
    uint32_t last_time; // 最後に取得した時間
};

touch_data touch_list[TOUCH_MAX];


bool mtch_reset(); // タッチセンサリセット
bool mtch_begin(uint8_t rx_count, uint8_t tx_count, uint8_t set_mode); // タッチセンサ開始処理
uint8_t mtch_command(uint8_t * cmd); // コマンド実行

uint32_t last_time = 0; // 最後にデータを受信した時間
int last_x = 0; // 最後に受信した座標 X
int last_y = 0; // 最後に受信した座標 Y
uint8_t boot_mode = 0; // 起動モード MTCH6301_MODE_GESTURE = ジェスチャー  /  MTCH6301_MODE_TOUCH = タッチ


// タッチセンサリセット
bool mtch_reset() {
    int i;
    Serial.printf("reset\n");
    digitalWrite(27, 0);
    delay(5);
    digitalWrite(27, 1);
    delay(5);
    while (digitalRead(12)) {
        Serial.printf(".");
        delay(5);
    }
    Serial.printf("\n");
    // タッチデータリセット
    for (i=0; i<TOUCH_MAX; i++) {
        touch_list[i].data_type = 0;
        touch_list[i].move_x = 0;
        touch_list[i].move_y = 0;
        touch_list[i].move_count = 0;
        touch_list[i].last_x = 0;
        touch_list[i].last_y = 0;
        touch_list[i].start_time = 0;
        touch_list[i].last_time = 0;
    }
    return true;
}

// タッチセンサ開始
bool mtch_begin(uint8_t rx_count, uint8_t tx_count, uint8_t set_mode) {
    int i, r;
    uint8_t cmd[8];
    boot_mode = set_mode;

    // MTCH6301に接続できるか確認
    while (true) {
        Wire.beginTransmission(MTCH6301_I2C_ADDR);
        r = Wire.endTransmission();
        if (r == 0) break; // 接続出来たらOK
        Serial.printf(".");
        delay(100);
    }
    Serial.printf("\n");

    // ピンの情報など初期レジスタ設定

    // touch stop
    cmd[0] = 0x01; cmd[1] = 0x01;
    r = mtch_command(cmd);
    // RX
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0x00; cmd[3] = 0x01; cmd[4] = rx_count;
    r = mtch_command(cmd);
    // TX
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0x00; cmd[3] = 0x02; cmd[4] = tx_count;
    r = mtch_command(cmd);
    // マルチタッチの許容数
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0x30; cmd[3] = 0x07; cmd[4] = 0x00;
    r = mtch_command(cmd);
    // touch config  81 = enabled   01 = disabled
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0xF0; cmd[3] = 0x07; cmd[4] = 0x01;
    if (boot_mode & MTCH6301_MODE_TOUCH) cmd[4] = 0x81;
    r = mtch_command(cmd);
    // gesture config  81 = enabled   01 = disabled
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0xF0; cmd[3] = 0x09; cmd[4] = 0x01;
    if (boot_mode & MTCH6301_MODE_GESTURE) cmd[4] = 0x81;
    r = mtch_command(cmd);
    // status config  81 = enabled   01 = disabled
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0xF0; cmd[3] = 0x0A; cmd[4] = 0x01;
    r = mtch_command(cmd);
    // pen down timer  0 - 10
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0x30; cmd[3] = 0x05; cmd[4] = 0x09;
    r = mtch_command(cmd);
    // pen up timer  0 - 10
    cmd[0] = 0x04; cmd[1] = 0x15; cmd[2] = 0x30; cmd[3] = 0x06; cmd[4] = 0x09;
    r = mtch_command(cmd);
    // start touch pad
    cmd[0] = 0x01; cmd[1] = 0x00;
    r = mtch_command(cmd);
    // touch request
    cmd[0] = 0x01; cmd[1] = 0x14;
    r = mtch_command(cmd);
    
    // 完了
    return true;
}


// コマンド実行
uint8_t mtch_command(uint8_t * cmd) {
    uint8_t i, r, s;

    // コマンド実行前に MTCH6301 が送りたいデータがあれば全て空読みしておく
    if (boot_mode & MTCH6301_MODE_GESTURE) {
        i = 3;
    } else if (boot_mode & MTCH6301_MODE_TOUCH) {
        i = 6;
    } else {
        i = 1;
    }
    while (digitalRead(12)) {
        r = Wire.requestFrom(MTCH6301_I2C_ADDR, i);
        while (Wire.available()) Serial.printf("r: %02X\n", Wire.read());
    }

    // コマンド送信
    Serial.printf("mtch_command\n");
    Serial.printf("write:");
    Wire.beginTransmission(MTCH6301_I2C_ADDR);
    s = cmd[0];
    Wire.write(cmd[0]);
    Serial.printf(" %02X", cmd[0]);
    for (i=1; i<s+1; i++) {
        Wire.write(cmd[i]);
        Serial.printf(" %02X", cmd[i]);
    }
    i = Wire.endTransmission(false);
    Serial.printf("\n");
    delay(10);

    // 結果受信
    r = 5;
    if (cmd[1] == 0x00) r = 5;
    if (cmd[1] == 0x01) r = 5;
    if (cmd[1] == 0x14) r = 5;
    if (cmd[1] == 0x15) r = 5;
    if (cmd[1] == 0x16) r = 5;
    if (cmd[1] == 0x83) r = 9;
    Wire.requestFrom(MTCH6301_I2C_ADDR, r, true);
    Serial.printf("read:");
    i = 0;
    while (Wire.available()) {
        s = Wire.read();
        Serial.printf(" %02X", s);
        i++;
    }
    Serial.printf("\n");
    delay(5);
    return i;
}


void mtch_get_toutch() {
    int e, i, r, s, x, y;
    int move_x, move_y;
    uint8_t read_buf[16];
    uint32_t touch_id;
    uint32_t touch_pen;
    uint32_t now_time;
    uint32_t time_i;
    uint32_t down_time;

    // バッファクリア
    for (i=0; i<16; i++) {
      read_buf[i] = 0x00;
    }

    // INT が H になるまで待つ
    while (!digitalRead(12)) {
      delay(5);
    }

    // データの受信
    if (boot_mode & MTCH6301_MODE_GESTURE) {
        i = 3;
    } else if (boot_mode & MTCH6301_MODE_TOUCH) {
        i = 6;
    } else {
        return;
    }
    r = Wire.requestFrom(MTCH6301_I2C_ADDR, i);
    if (r == 0) {
        return;
    }

    i = 0;
    while (Wire.available()) {
        read_buf[i] = Wire.read();
        i++;
        if (i > r) break;
    }
    // 一応空になるまでread
    while (Wire.available()) Wire.read();

    touch_id = ( read_buf[1] >> 3 ) & 0x0F;
    touch_pen = read_buf[1] & 0x01;
    x = 0;
    y = 0;
    if (touch_id >= TOUCH_MAX) return;
    // 前のタッチからの経過秒数を取得(ミリ秒)
    now_time = millis();
    if (touch_list[touch_id].last_time) {
        time_i = now_time - touch_list[touch_id].last_time;
    } else {
        time_i = 0;
    }
    if (boot_mode & MTCH6301_MODE_TOUCH) {
        x = (read_buf[2] & 0x7F) + ((read_buf[3] & 0x1F) << 7 );
        y = (read_buf[4] & 0x7F) + ((read_buf[5] & 0x1F) << 7 );
        move_x = x - touch_list[touch_id].last_x;
        move_y = y - touch_list[touch_id].last_y;
    }
    // タッチ終わりの時タッチ時間が120ミリ秒以下ならクリック
    if (touch_pen == 0) {
        down_time = now_time - touch_list[touch_id].start_time;
        if (touch_list[touch_id].move_count < 5 && down_time > 20 && down_time < 110) {
            bleMouse.click(MOUSE_LEFT);
        }
        Serial.printf("Down: %D  %D  %D  \n", touch_id, down_time, touch_list[touch_id].move_count);
        touch_list[touch_id].last_time = 0;
        return;
    }
    if (x > 3950 || x < 3000) return;
    if (y < 700) return;
    // 前のタッチから200ミリ秒経っていたら開始と判定して何もしない
    if (time_i <= 0 || time_i > 200) {
        touch_list[touch_id].data_type = touch_pen;
        touch_list[touch_id].move_x = 0;
        touch_list[touch_id].move_y = 0;
        touch_list[touch_id].move_count = 0;
        touch_list[touch_id].last_x = x;
        touch_list[touch_id].last_y = y;
        touch_list[touch_id].start_time = now_time;
        touch_list[touch_id].last_time = now_time;
        return;
    }
    if (move_x > 160 || move_x < -160 || move_y > 160 || move_y < -160) return;
    if (boot_mode & MTCH6301_MODE_GESTURE) {
        Serial.printf("read: %02X %02X %02X  t: %D\n", read_buf[0], read_buf[1], read_buf[2], time_i);
    } else if (boot_mode & MTCH6301_MODE_TOUCH) {
        // Serial.printf("read: %02X %02X %02X %02X %02X %02X [ %D , %D]  t: %D\n", read_buf[0], read_buf[1], read_buf[2], read_buf[3], read_buf[4], read_buf[5], (last_x - x), (last_y - y), time_i);
        Serial.printf("%D, %D    %D,%D    %D,%D\n", touch_id, touch_pen, move_x, move_y, x, y);
        bleMouse.move((move_y / 5), ((move_x / 3) * -1), 0);
    }
    touch_list[touch_id].last_x = x;
    touch_list[touch_id].last_y = y;
    touch_list[touch_id].move_count++;
    touch_list[touch_id].last_time = now_time;
    delay(5);
}


void setup()
{
    // I2C
    Wire.begin(26, 25); // SCL = 22  .  SDA = 21
    Wire.setClock(100000); // 100kHz

    // Serial
    Serial.begin(115200);
    while (!Serial);

    // IOピン
    pinMode(12, INPUT); // INT
    pinMode(27, OUTPUT); // RESET

    // MTCH6301 リセット
    mtch_reset();

    // MTCH6301 初期化
    // mtch_begin(0x05, 0x04, MTCH6301_MODE_GESTURE); // ジェスチャーモード
    mtch_begin(0x05, 0x04, MTCH6301_MODE_TOUCH); // タッチモード

    // bleマウス初期化
    bleMouse.begin();
    
    // 一応
    delay(50);
}

void loop()
{
    // touch read loop
    mtch_get_toutch();
    delay(5);
}
