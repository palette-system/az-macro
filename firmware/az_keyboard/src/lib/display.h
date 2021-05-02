#ifndef display_h
#define display_h


#include "Arduino.h"
#include "Arduino_ST7789_my.h"


// クラスの定義
class Display
{
    public:
        Arduino_ST7789 *_tft; // st7789オブジェクト
        int  _option_type; // オプションのタイプ
	    short _width; // 液晶のサイズ幅
	    short _height; // 液晶のサイズ高さ
        Display();   // コンストラクタ
        void begin(Arduino_ST7789 *tft_obj, int option_type); // 初期化
        void view_full_image(uint8_t *image_data); // 画面いっぱいに画像を表示する
	    void viewBMPspi_head(); // データを流し込んで画像を表示する(ヘッダ)
	    void viewBMPspi_data(uint8_t *wbuf, int wsize); // データを流し込んで画像を表示する(データ)
        void view_standby_image();
        void open_movie(); // 起動ムービー
        void loop_exec(); // 定期処理
};

#endif
