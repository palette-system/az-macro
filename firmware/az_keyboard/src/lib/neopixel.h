#ifndef neopixel_h
#define neopixel_h

#include <Adafruit_NeoPixel.h>


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
        Adafruit_NeoPixel *rgb_led; // RGB_LEDオブジェクト
        Neopixel();   // コンストラクタ
        void begin(short data_pin, short row_size, short col_size); // LED制御初期化
        void set_led_num(int8_t key, int8_t val);
        void set_key_matrix(int8_t key, int8_t val);
        void set_led_buf(int8_t key_id, int8_t set_num);
        void rgb_led_loop_exec(void);
};

#endif
