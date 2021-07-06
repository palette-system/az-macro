#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <Adafruit_NeoPixel.h>


#include "src/lib/Arduino_ST7789_my.h"
#include "src/image/az_66jp_img.h"
#include "index_bin.h"
#include "image.h"



// 液晶 オブジェクト
Arduino_ST7789 *tft; // st7789オブジェクト

// RGBLED
#define RGBLED_LENGTH   70
#define RGBLED_PIN   14
Adafruit_NeoPixel *rgb_led; // RGB_LEDオブジェクト
int rgbled_index;
int rgbled_step;

// キー用IOピン
#define  ROW_LENGTH   5
#define  COL_LENGTH   14
#define  KEY_LENGTH   70
int row_pin[] = {35, 34, 39, 36, 23};
int col_pin[] = {1, 3, 19, 18, 5, 4, 0, 2, 15, 32, 33, 27, 12, 13};


// サーモ表示用のボタンの位置
const uint8_t az66jp_key_position[70][2] PROGMEM = {
  {4, 4}, {8, 19}, {10, 35}, {14, 51}, {5, 67}, {20, 4}, {28, 19}, {32, 35}, {40, 51}, {24, 67},
  {36, 4}, {43, 19}, {47, 35}, {55, 51}, {0, 0}, {51, 4}, {59, 19}, {63, 35}, {71, 51}, {0, 0},
  {67, 4}, {75, 19}, {79, 35}, {87, 51}, {87, 67}, {83, 4}, {91, 19}, {95, 35}, {103, 51}, {106, 67},
  {99, 4}, {107, 19}, {111, 35}, {119, 51}, {125, 67}, {115, 4}, {123, 19}, {127, 35}, {135, 51}, {0, 0},
  {131, 4}, {139, 19}, {143, 35}, {151, 51}, {144, 67}, {147, 4}, {155, 19}, {159, 35}, {167, 51}, {163, 67},
  {163, 4}, {171, 19}, {175, 35}, {182, 51}, {179, 67}, {179, 4}, {186, 19}, {190, 35}, {198, 51}, {195, 67},
  {195, 4}, {202, 19}, {206, 35}, {0, 0}, {210, 67}, {210, 4}, {226, 4}, {224, 27}, {220, 51}, {226, 67}
};

// 既に押したことがあるボタンかどうか
uint8_t  key_oncheck[KEY_LENGTH];

// 無線LANのサーバー設定
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);


// IP アドレスデータを表示用の文字列にする
String toStringIp(IPAddress ip) {
    String res = "";
    for (int i = 0; i < 3; i++) {
        res += String((ip >> (8 * i)) & 0xFF) + ".";
    }
    res += String(((ip >> 8 * 3)) & 0xFF);
    return res;
}

//無効リクエストはすべてESP32に向ける
void captivePortal() {
    server.sendHeader("Location", "http://"+toStringIp(WiFi.softAPIP())+"/", true);
    server.send(302, "text/plain", "");
    server.client().stop();
}


// wifi 初期処理
void start_wifi() {
    int i, j;
    char text_buf[255];
    
    //無線LAN接続AP(アクセスポイント)モード
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("az-66jp", "");

    // DNSサーバー起動
    IPAddress myIP = WiFi.softAPIP();
    dnsServer.start(DNS_PORT, "*", myIP); // 全ドメインを自分に向ける
    ESP_LOGD(LOG_TAG, "server ip : %S", toStringIp(myIP));

    // メインページ
    server.on("/", []() {
        server.send(200, "text/html", index_bin);
    });
    // OTA 用updater
    server.on("/firmware_update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        delay(2000);
        ESP.restart();
    }, []() {
        // ファイルを受け取ってファームウェアを更新
        HTTPUpload& upload = server.upload();
        if (upload.status == UPLOAD_FILE_START) {
            ESP_LOGD(LOG_TAG, "Update: file start %s\n", upload.filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                // Update.printError(Serial);
            }
            tft->fillRect(0, 92,  240, 43, WHITE);
            tft->viewBMP(6, 100, 190, 26, (uint8_t *)firm_write_now_txt_img, 10); // ファームウェア書込み中
            
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            /* flashing firmware to ESP*/
            ESP_LOGD(LOG_TAG, "Update: write %D\n", upload.currentSize);
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                // Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            ESP_LOGD(LOG_TAG, "Update: end\n");
            if (Update.end(true)) { //true to set the size to the current progress
                ESP_LOGD(LOG_TAG, "Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
                // Update.printError(Serial);
            }
        }
    });
    // httpサーバーそれ以外のページ
    server.onNotFound([]() {
        ESP_LOGD(LOG_TAG, "onNotFound: %S", server.uri().c_str());
        // メインページにリダイレクト
        server.sendHeader("Location", "http://"+toStringIp(WiFi.softAPIP())+"/", true);
        server.send(302, "text/plain", "");
        server.client().stop();
    });
    // httpサーバー起動
    server.begin();
}

// RGBLED用のループ
void led_loop() {
    int i;
    rgbled_step++;
    if (rgbled_step < 5) return;
    rgbled_step = 0;
    rgbled_index++;
    if (rgbled_index > 66) return;
    for (i=0; i<RGBLED_LENGTH; i++) {
        if (i < rgbled_index) {
            rgb_led->setPixelColor(i, rgb_led->Color(0, 0, 1));
        } else {
            rgb_led->setPixelColor(i, rgb_led->Color(0, 0, 0));
        }
    }
    rgb_led->show();
}

// キー入力をスキャンして液晶に表示
void key_scan() {
    int i, j, s, n;
    n = 0;
    // マトリックス入力の取得
    for (i=0; i<COL_LENGTH; i++) {
        // 対象のcolピンのみ lowにする
        for (j=0; j<COL_LENGTH; j++) {
            if (i == j) { s = 0; } else { s = 1; }
            digitalWrite(col_pin[j], s);
        }
        delayMicroseconds(50);
        // row の分キー入力チェック
        for (j=0; j<ROW_LENGTH; j++) {
            if (!az66jp_key_position[n][0]) {
                n++;
                continue;
            }
            if (!digitalRead(row_pin[j])) {
                tft->fillRect(az66jp_key_position[n][0] - 1, az66jp_key_position[n][1] + 9,  12, 12, BLUE);
                key_oncheck[n] = 1;
            } else if (key_oncheck[n]) {
                tft->fillRect(az66jp_key_position[n][0] - 1, az66jp_key_position[n][1] + 9,  12, 12, 0x667f);
            } else {
                tft->fillRect(az66jp_key_position[n][0] - 1, az66jp_key_position[n][1] + 9,  12, 12, WHITE);
            }
            n++;
        }
    }
}



void setup() {
    int i;
    // 液晶初期化
    tft = new Arduino_ST7789(26, 25, 21, 22, -1);
    tft->init(240, 135);
    tft->setRotation(1);
    delay(100);
    tft->fillRect(0, 0,  240, 10, WHITE);
    tft->fillRect(0, 92,  240, 43, WHITE);
    tft->viewBMP(0, 10, 240, 82, (uint8_t *)az_66jp_plate_img, 10);
    tft->viewBMP(6, 100, 166, 26, (uint8_t *)switch_chack_now_txt_img, 10); // スイッチチェック中
    // RBGLED初期化
    rgbled_index = 0;
    rgbled_step = 0;
    rgb_led = new Adafruit_NeoPixel(RGBLED_LENGTH, RGBLED_PIN, NEO_GRB + NEO_KHZ400);
    for (i=0; i<RGBLED_LENGTH; i++) {
        rgb_led->setPixelColor(i, rgb_led->Color(0, 0, 0));
    }
    rgb_led->show();
    // キー用初期化
    for (i=0; i<COL_LENGTH; i++) {
        pinMode(col_pin[i], OUTPUT_OPEN_DRAIN);
    }
    for (i=0; i<ROW_LENGTH; i++) {
        pinMode(row_pin[i], INPUT_PULLUP);
    }
    for (i=0; i<KEY_LENGTH; i++) {
        key_oncheck[i] = 0;
    }
    // 設定モード開始
    start_wifi();
}


// ループ処理本体
void loop() {
    // dnsサーバー定期処理
    dnsServer.processNextRequest();
    // httpサーバー定期処理
    server.handleClient();
    // キー入力をスキャンして液晶に表示
    key_scan();
    // RGBLEDチェック用
    led_loop();
    delay(50);
}
