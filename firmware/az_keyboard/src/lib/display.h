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
	int dakagi_last_view;
        Display();   // コンストラクタ
        void begin(Arduino_ST7789 *tft_obj, int option_type); // 初期化
        void view_full_image(uint8_t *image_data); // 画面いっぱいに画像を表示する
        void view_int(uint16_t x, uint16_t y, int v); // 数字を表示する
	void view_dakagi(int vint); // 打鍵数表示
	    void viewBMPspi_head(); // データを流し込んで画像を表示する(ヘッダ)
	    void viewBMPspi_data(uint8_t *wbuf, int wsize); // データを流し込んで画像を表示する(データ)
        void view_black(); // 画面全体黒い画面表示
        void view_standby_image(); // 待ち受け画面表示
        void view_setting_mode(); // 設定モード画面表示
        void view_save(); // 保存中表示
        void view_wifi_conn(); // WiFi接続中画面表示
        void view_webhook(); // Webhook中表示
        void open_movie(); // 起動ムービー
        void loop_exec(); // 定期処理
};

#endif
