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
		this->_tft->init(240, 135);
		this->_tft->setRotation(1);
	}
    this->_tft->fillScreen(WHITE);
    this->_tft->setTextSize(1);
    this->_tft->setTextColor(WHITE);
    last_n = millis();
	this->dakagi_last_view = -1;
}

// 画面いっぱい黒い画面
void Display::view_black() {
    this->_tft->fillScreen(BLACK);
}

// 画面いっぱいに画像を表示する
void Display::view_full_image(uint8_t *image_data) {
	this->_tft->viewBMP(0, 0, this->_width, this->_height, image_data, 10);
}

// 数字を表示
void Display::view_int(uint16_t x, uint16_t y, int v) {
	char s[12];
	uint8_t *set_img;
	int i;
	sprintf(s, "%D", v);
	i = 0;
	while (i < 12 && s[i] && x < this->_width) {
		if (s[i] == 0x30) set_img = (uint8_t *)int_0_img;
		if (s[i] == 0x31) set_img = (uint8_t *)int_1_img;
		if (s[i] == 0x32) set_img = (uint8_t *)int_2_img;
		if (s[i] == 0x33) set_img = (uint8_t *)int_3_img;
		if (s[i] == 0x34) set_img = (uint8_t *)int_4_img;
		if (s[i] == 0x35) set_img = (uint8_t *)int_5_img;
		if (s[i] == 0x36) set_img = (uint8_t *)int_6_img;
		if (s[i] == 0x37) set_img = (uint8_t *)int_7_img;
		if (s[i] == 0x38) set_img = (uint8_t *)int_8_img;
		if (s[i] == 0x39) set_img = (uint8_t *)int_9_img;
		this->_tft->viewBMP(x, y, 16, 22, set_img, 10);
		x += 16;
		i++;
	}
	
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
      // 楽しいをカタチに…
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
}
// 設定モード画面表示
void Display::view_setting_mode() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(26, 50, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(18, 160, 98, 25, (uint8_t *)setting_title_img, 10);
}
// 保存中画面表示
void Display::view_save() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(26, 50, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(29, 160, 76, 25, (uint8_t *)save_img, 10);
}
// wifi 接続中
void Display::view_wifi_conn() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(19, 46, 97, 82, (uint8_t *)wifi_icon_img, 10);
    this->_tft->viewBMP(13, 160, 109, 25, (uint8_t *)wifi_conn_img, 10);
}
// Webhook中
void Display::view_webhook() {
    this->_tft->fillRect(0, 210,  135, 240, WHITE);
    this->_tft->viewBMP(10, 212, 116, 25, (uint8_t *)webhook_img, 10);
}
// 打鍵数を表示
void Display::view_dakagi(int vint) {
	if (this->dakagi_last_view == common_cls.key_count_total) return;
	// this->_tft->fillRect(0, 210,  135, 30, WHITE);
	this->_tft->viewBMP(5, 215, 57, 25, (uint8_t *)dakagi_img, 10);
	this->view_int(65, 217, common_cls.key_count_total);
	this->dakagi_last_view = common_cls.key_count_total;
}
// 暗記中
void Display::view_ankey_now() {
    this->_tft->fillRect(0, 0,  135, 240, WHITE);
    this->_tft->viewBMP(20, 20, 95, 86, (uint8_t *)ankey_icon_img, 10);
    this->_tft->viewBMP(30, 135, 75, 25, (uint8_t *)ankinow_img, 10);
}
// 暗記入力
void Display::view_ankey_input() {
    this->_tft->fillRect(0, 0,  135, 240, WHITE);
    this->_tft->viewBMP(20, 20, 95, 86, (uint8_t *)ankey_icon_img, 10);
    this->_tft->viewBMP(30, 55, 75, 25, (uint8_t *)nyuryokunow_img, 10);
}

// 待ち受け画像表示
void Display::view_standby_image() {
    this->_tft->viewBMPFile(0,0, 135, 210, "/stimg.dat");
	this->_tft->fillRect(0, 210,  135, 30, WHITE);
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
}
// 設定モード画面表示
void Display::view_setting_mode() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(20, 24, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(124, 55, 98, 25, (uint8_t *)setting_title_img, 10);
}
// 保存中画面表示
void Display::view_save() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(20, 24, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(124, 55, 76, 25, (uint8_t *)save_img, 10);
}
// wifi 接続中
void Display::view_wifi_conn() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(10, 27, 97, 82, (uint8_t *)wifi_icon_img, 10);
    this->_tft->viewBMP(120, 55, 109, 25, (uint8_t *)wifi_conn_img, 10);
}
// Webhook中
void Display::view_webhook() {
    this->_tft->fillRect(0, 105,  240, 135, WHITE);
    this->_tft->viewBMP(10, 27, 97, 82, (uint8_t *)wifi_icon_img, 10);
    this->_tft->viewBMP(116, 107, 116, 25, (uint8_t *)webhook_img, 10);
}
// 暗記中
void Display::view_ankey_now() {
    this->_tft->fillRect(0, 0,  240, 135, WHITE);
    this->_tft->viewBMP(20, 25, 95, 86, (uint8_t *)ankey_icon_img, 10);
    this->_tft->viewBMP(135, 55, 75, 25, (uint8_t *)ankinow_img, 10);
}
// 暗記入力
void Display::view_ankey_input() {
    this->_tft->fillRect(0, 0,  240, 135, WHITE);
    this->_tft->viewBMP(20, 25, 95, 86, (uint8_t *)ankey_icon_img, 10);
    this->_tft->viewBMP(135, 55, 75, 25, (uint8_t *)nyuryokunow_img, 10);
}

// 打鍵数を表示
void Display::view_dakagi(int vint) {
	if (this->dakagi_last_view == common_cls.key_count_total) return;
	// this->_tft->fillRect(0, 210,  135, 30, WHITE);
	this->_tft->viewBMP(5, 105, 57, 25, (uint8_t *)dakagi_img, 10);
	this->view_int(70, 107, common_cls.key_count_total);
	this->dakagi_last_view = common_cls.key_count_total;
}

// 待ち受け画像表示
void Display::view_standby_image() {
    this->_tft->viewBMPFile(0,0, 240, 135, "/stimg.dat");
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
}

#endif


// 定期処理
void Display::loop_exec() {
    unsigned long n;
    n = millis();
	// this->_tft->fillRect(4, 4,  80, 40, BLACK);
	// this->_tft->fillRect(0, 0,  240, 135, BLACK);
    this->_tft->setCursor(4, 4);
	this->_tft->setTextSize(3);
    // this->_tft->printf("[%D]", (n - last_n));
	this->view_dakagi(loop_index);
	loop_index++;
	if (loop_index > 9999) loop_index = 0;
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

