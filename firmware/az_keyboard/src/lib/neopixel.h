#ifndef neopixel_h
#define neopixel_h

#include <Adafruit_NeoPixel.h>



// 常に光らせるキー最大数
#define  NEO_SELECT_KEY_MAX  8

// 常に光らせるキー
struct neo_select_key {
	int8_t layer_id; // レイヤー
	uint8_t key_num; // キーの番号
};


// クラスの定義
class Neopixel
{
    public:
        short _data_pin; // データピン
        short _led_length; // 接続LED数
        short _row_size; // マトリックス縦サイズ
        short _col_size; // マトリックス横サイズ
        int8_t *led_buf;
        int8_t *led_num;
        int8_t *key_matrix;
        int *_select_layer_no;
        neo_select_key select_key[NEO_SELECT_KEY_MAX]; // 
        Adafruit_NeoPixel *rgb_led; // RGB_LEDオブジェクト
        Neopixel();   // コンストラクタ
        void begin(short data_pin, short row_size, short col_size, int *select_layer); // LED制御初期化
        void set_led_num(int8_t key, int8_t val);
        void set_key_matrix(int8_t key, int8_t val);
        void set_led_buf(int8_t key_id, int8_t set_num);
        void select_key_cler();
        void select_key_add(int8_t layer_id, uint8_t key_num);
        void select_key_show();
        void rgb_led_loop_exec(void);
};

#endif
