#include "Arduino.h"
#include "neopixel.h"


// コンストラクタ
Neopixel::Neopixel() {
	this->_data_pin = -1;
	this->_led_length = -1;
	this->_row_size = -1;
	this->_col_size = -1;
}


// LED制御初期化
void Neopixel::begin(short data_pin, short row_size, short col_size, int *select_layer) {
    int i;
    this->_data_pin = data_pin;
    this->_led_length = (row_size * col_size);
    this->_row_size = row_size;
    this->_col_size = col_size;
	this->_select_layer_no = select_layer;
    this->led_buf = new int8_t[this->_led_length];
    for (i=0; i<this->_led_length; i++) { this->led_buf[i] = 0; }
    this->led_num = new int8_t[this->_led_length];
    for (i=0; i<this->_led_length; i++) { this->led_num[i] = -1; }
    this->key_matrix = new int8_t[this->_led_length];
    for (i=0; i<this->_led_length; i++) { this->key_matrix[i] = -1; }
    this->select_key_cler();
    // RGB_LEDピン用の初期化
    if (this->_data_pin >= 0 && this->_led_length > 0) {
        this->rgb_led = new Adafruit_NeoPixel(this->_led_length, this->_data_pin, NEO_GRB + NEO_KHZ400);
        for (i=0; i<this->_led_length; i++) {
            this->rgb_led->setPixelColor(i, this->rgb_led->Color(0, 0, 0));
        }
    	this->rgb_led->show();
    }
}

// LED番号のリストのデータを受け取る
void Neopixel::set_led_num(int8_t key, int8_t val) {
    this->led_num[key] = val;
}

// キーマトリックスのデータを受け取る
void Neopixel::set_key_matrix(int8_t key, int8_t val) {
    this->key_matrix[key] = val;
}

// 指定したキーにアクション番号を入れる
void Neopixel::set_led_buf(int8_t key_id, int8_t set_num) {
    if (this->_data_pin < 0 || this->_led_length <= 0) return;
    int i;
    for (i=0; i<this->_led_length; i++) {
        if (this->key_matrix[i] == key_id) {
            this->led_buf[i] = set_num;
            return;
        }
    }
}


// 選択キークリア
void Neopixel::select_key_cler() {
	int i;
	for (i=0; i<NEO_SELECT_KEY_MAX; i++) {
		this->select_key[i].layer_id = -1;
		this->select_key[i].key_num = 0;
	}
}


// 選択キーを追加
void Neopixel::select_key_add(int8_t layer_id, uint8_t key_num) {
	int i;
	for (i=0; i<NEO_SELECT_KEY_MAX; i++) {
		if (this->select_key[i].layer_id >= 0) continue;
		this->select_key[i].layer_id = layer_id;
		this->select_key[i].key_num = key_num;
	}
}


// 選択キーを点灯
void Neopixel::select_key_show() {
	int i;
	for (i=0; i<NEO_SELECT_KEY_MAX; i++) {
		if (this->select_key[i].layer_id < 0 || *this->_select_layer_no != this->select_key[i].layer_id) continue;
		this->rgb_led->setPixelColor(this->led_num[this->select_key[i].key_num], this->rgb_led->Color(80, 0, 0));
	}
}



//    2
//  3 1 4
//    5

//    6
//  7   8
//    9

// RGB_LEDを制御する定期処理
void Neopixel::rgb_led_loop_exec(void) {
    // RGB_LED の設定が無ければ何もしない
    if (this->_data_pin < 0 || this->_led_length <= 0) return;
    int i, j, k, l, m;
    int csize = this->_col_size;
    int rsize = this->_row_size;
    int rmax = this->_led_length - this->_col_size;
    int cmax = csize - 1;
    int8_t read_buf[this->_led_length];
    // led_bufの値をコピーしておいて作業はread_bufのデータをもとにled_bufを書き換える
    for (i=0; i<this->_led_length; i++) {
        read_buf[i] = this->led_buf[i];
    }
    for (i=0; i<this->_led_length; i++) {
            if (read_buf[i] == 1) {
                // 上下左右に作る
                if (i >= csize) this->led_buf[i - csize] = 2; // 上
                if (i < rmax) this->led_buf[i + csize] = 5; // 下
                if ((i % csize) > 0) this->led_buf[i - 1] = 3; // 左
                if ((i % csize) < cmax) this->led_buf[i + 1] = 4; // 右
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 2) {
                // 上、右に作る
                if (i >= csize) this->led_buf[i - csize] = 2; // 上
                if ((i % csize) < cmax) this->led_buf[i + 1] = 8; // 右
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 3) {
                // 左、上に作る
                if ((i % csize) > 0) this->led_buf[i - 1] = 3; // 左
                if (i >= csize) this->led_buf[i - csize] = 6; // 上
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 4) {
                // 右、下に作る
                if ((i % csize) < cmax) this->led_buf[i + 1] = 4; // 右
                if (i < rmax) this->led_buf[i + csize] = 9; // 下
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 5) {
                // 下、左に作る
                if (i < rmax) this->led_buf[i + csize] = 5; // 下
                if ((i % csize) > 0) this->led_buf[i - 1] = 7; // 左
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 6) {
                // 上に作る
                if (i >= csize) this->led_buf[i - csize] = 6; // 上
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 7) {
                // 左に作る
                if ((i % csize) > 0) this->led_buf[i - 1] = 7; // 左
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 8) {
                // 右に作る
                if ((i % csize) < cmax) this->led_buf[i + 1] = 8; // 右
                this->led_buf[i] = 10;
            } else if (read_buf[i] == 9) {
                // 下に作る
                if (i < rmax) this->led_buf[i + csize] = 9; // 下
                this->led_buf[i] = 10;
            } else if (read_buf[i] > 9) {
                // それ以外は消す
                this->led_buf[i] = 0;
            }
    }
    // LEDを点灯
    for (i=0; i<this->_led_length; i++) {
        this->rgb_led->setPixelColor(i, this->rgb_led->Color(0, 0, 0));
    }
    for (i=0; i<this->_led_length; i++) {
        if (this->led_buf[i] && this->key_matrix[i] >= 0) {
            m = 30;
            if (led_buf[i] >= 6 && led_buf[i] <= 10) m = 5;
            this->rgb_led->setPixelColor(this->led_num[this->key_matrix[i]], this->rgb_led->Color(0, 0, m));
        }
    }
	// 選択キーを点灯
	this->select_key_show();
	// LEDにデータを送る
    this->rgb_led->show();
}


