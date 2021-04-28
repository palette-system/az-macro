#include "Arduino.h"
#include "display.h"

#include "../image/gimp_image.h"
#include "../image/tanoshii.h"
#include "../image/wificonn1.h"
#include "../image/wificonn2.h"


int view_index = 0;
int loop_index = 0;



// コンストラクタ
Display::Display() {
}



// LED制御初期化
void Display::begin(Arduino_ST7789 *tft_obj) {
    view_index = 0;
	loop_index = 0;
    this->_tft = tft_obj;
    this->_tft->setTextSize(2);
    this->_tft->setTextColor(WHITE);
}

// 定期処理
void Display::loop_exec() {
	this->_tft->fillRect(4, 4,  80, 20, BLACK);
	// this->_tft->fillRect(0, 0,  240, 135, BLACK);
    this->_tft->setCursor(4, 4);
    this->_tft->printf("[%D]", loop_index);
	loop_index++;
    /*
    delay(200);
    while (1) {
      // 楽しいを形に…
      tft->fillScreen(WHITE);
      delay(1000);
      for (i=0; i<=10; i++) {
        tft->viewBMP(40, 54, 161, 20, (uint8_t *)tanoshii, i);
        delay(100);
      }
      delay(1500);
      for (i=10; i>=0; i--) {
        tft->viewBMP(40, 54, 161, 20, (uint8_t *)tanoshii, i);
        delay(100);
      }
      delay(1000);
      
    for (i=0; i<=10; i++) {
        tft->viewBMP(0, 0, 240, 135, (uint8_t *)gimp_image, i);
        delay(100);
    }
    delay(3000);
    for (i=10; i>=0; i--) {
        tft->viewBMP(0, 0, 240, 135, (uint8_t *)gimp_image, i);
        delay(100);
    }
    delay(1000);
    for (i=0; i<=20; i++) {
        tft->viewBMP(0, 0, 240, 135, (uint8_t *)wifi_conn_1, 10);
        delay(500);
        tft->viewBMP(0, 0, 240, 135, (uint8_t *)wifi_conn_2, 10);
        delay(500);
    }
    delay(3000);
    tft->fillScreen(WHITE);
    tft->setTextSize(2);
    tft->setTextColor(BLACK);
    tft->setCursor(4, 4);
    tft->print("AZ-60JIS\n");
    delay(1000);
    tft->setCursor(4, 24);
    tft->print("WiFi : on\n");
    delay(1000);
    tft->setCursor(4, 44);
    tft->print("Layer : 1\n");
    delay(1000);
    delay(10000);
    
    }
    */
}

