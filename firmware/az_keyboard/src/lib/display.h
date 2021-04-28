#ifndef display_h
#define display_h

#include "Arduino.h"
#include "Arduino_ST7789_my.h"


// クラスの定義
class Display
{
    public:
        Arduino_ST7789 *_tft; // st7789オブジェクト
        Display();   // コンストラクタ
        void begin(Arduino_ST7789 *tft_obj); // 初期化
        void loop_exec(); // 定期処理
};

#endif
