#include "Arduino.h"
#include "display.h"

#include "../../az_common.h"
#include "../image/gimp_image.h"
#include "../image/tanoshii.h"
#include "../image/wificonn1.h"
#include "../image/wificonn2.h"


int view_index = 0;
int loop_index = 0;


unsigned long last_n;


// コンストラクタ
Display::Display() {
}


// LED制御初期化
void Display::begin(Arduino_ST7789 *tft_obj, int option_type) {
    view_index = 0;
	loop_index = 0;
	_option_type = option_type;
    this->_tft = tft_obj;
	if (_option_type == 3) {
		// AZ-Macro用135x240
		this->_tft = new Arduino_ST7789(26, 25, 27, 12, -1);
		this->_width = 135;
		this->_height = 240;
		this->_tft->init(135, 240);
		this->_tft->setRotation(2);
		
	} else if (_option_type == 4) {
		// AZ-66JP用135x240
		this->_tft = new Arduino_ST7789(26, 25, 21, 22, -1);
		this->_width = 240;
		this->_height = 135;
		this->_tft->init(135, 240);
		this->_tft->setRotation(2);
	}
    this->_tft->fillScreen(WHITE);
    this->_tft->setTextSize(1);
    this->_tft->setTextColor(WHITE);
    last_n = millis();
}

// 画面いっぱいに画像を表示する
void Display::view_full_image(uint8_t *image_data) {
	this->_tft->viewBMP(0, 0, this->_width, this->_height, image_data, 10);
}

// 待ち受け画像表示
void Display::view_standby_image() {

}

// データを流し込んで画像を表示する(ヘッダ)
void Display::viewBMPspi_head() {
	this->_tft->viewBMPspi_head(0, 0, this->_width, this->_height);
}
// データを流し込んで画像を表示する(データ)
void Display::viewBMPspi_data(uint8_t *wbuf, int wsize) {
	this->_tft->viewBMPspi_data(wbuf, wsize);
}


// 起動ムービー(AZ-Macro用)
#ifdef KEYBOARD_AZMACRO
void Display::open_movie() {
	int i;
      // 楽しいを形に…
      this->_tft->fillScreen(WHITE);
      delay(1000);
      for (i=0; i<=10; i++) {
        this->_tft->viewBMP(17, 84, 100, 20, (uint8_t *)tanoshi_1_img, i);
        this->_tft->viewBMP(29, 120, 77, 20, (uint8_t *)tanoshi_2_img, i);
        delay(100);
      }
      delay(1500);
      for (i=10; i>=0; i--) {
        this->_tft->viewBMP(17, 84, 100, 20, (uint8_t *)tanoshi_1_img, i);
        this->_tft->viewBMP(29, 120, 77, 20, (uint8_t *)tanoshi_2_img, i);
        delay(100);
      }
      delay(1000);
      
    for (i=0; i<=10; i++) {
        this->_tft->viewBMP(26, 29, 82, 135, (uint8_t *)logo_tate_1_img, i);
        this->_tft->viewBMP(7, 180, 122, 17, (uint8_t *)logo_tate_2_img, i);
        delay(100);
    }
    delay(3000);
    for (i=10; i>=0; i--) {
        this->_tft->viewBMP(26, 29, 82, 135, (uint8_t *)logo_tate_1_img, i);
        this->_tft->viewBMP(7, 180, 122, 17, (uint8_t *)logo_tate_2_img, i);
        delay(100);
    }
    delay(1000);
	this->_tft->viewBMPFile(0,0,this->_width, this->_height, "/stimg.dat");
}
#endif


// 起動ムービー(AZ-66JP用)
#ifdef KEYBOARD_AZ66JP
void Display::open_movie() {
	int i;
      // 楽しいを形に…
      this->_tft->fillScreen(WHITE);
      delay(1000);
      for (i=0; i<=10; i++) {
        this->_tft->viewBMP(40, 54, 161, 20, (uint8_t *)tanoshii, i);
        delay(100);
      }
      delay(1500);
      for (i=10; i>=0; i--) {
        this->_tft->viewBMP(40, 54, 161, 20, (uint8_t *)tanoshii, i);
        delay(100);
      }
      delay(1000);
      
    for (i=0; i<=10; i++) {
        this->_tft->viewBMP(0, 0, 240, 135, (uint8_t *)gimp_image, i);
        delay(100);
    }
    delay(3000);
    for (i=10; i>=0; i--) {
        this->_tft->viewBMP(0, 0, 240, 135, (uint8_t *)gimp_image, i);
        delay(100);
    }
    delay(1000);
	this->_tft->viewBMPFile(0,0,this->_width, this->_height, "/stimg.dat");
    delay(10000);
}
#endif


// 定期処理
void Display::loop_exec() {
    unsigned long n;
    n = millis();
	this->_tft->fillRect(4, 4,  80, 20, BLACK);
	// this->_tft->fillRect(0, 0,  240, 135, BLACK);
    this->_tft->setCursor(4, 4);
    this->_tft->printf("[%D]", (n - last_n));
	loop_index++;
	last_n = n;
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

