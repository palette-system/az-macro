#include "Arduino.h"
#include "display.h"

#include "../../az_common.h"
#include "../image/gimp_image.h"
#include "../image/tanoshii.h"
#include "../image/wificonn1.h"
#include "../image/wificonn2.h"





// コンストラクタ
Display::Display() {
}


// 液晶制御初期化
void Display::begin(Arduino_ST7789 *tft_obj, int option_type) {
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
	this->_info_spot = 0;
	this->dakagi_last_view = -1;
	this->_wait_index = 0;
	this->_stimg_load_flag = 0;
	this->_thermo_flag = 0;
	this->_qr_flag = 0;
	this->_last_view_type = 255;
	this->_last_view_info = 255;
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

// サーモグラフモードをON/OFF切り替える
void Display::view_dakagi_thermo_on() {
	if (this->_thermo_flag) {
		this->_thermo_flag = 0;
		this->_qr_flag = 0;
		this->view_type = DISP_TYPE_STANDBY;
	} else {
		this->_thermo_flag = 1;
		this->_qr_flag = 0;
		this->view_type = DISP_TYPE_DKTHERM;
	}
}

// QRコードモードをON/OFF切り替える
void Display::view_dakagi_qr_on() {
	if (this->_qr_flag) {
		this->_qr_flag = 0;
		if (this->_thermo_flag) {
			this->view_type = DISP_TYPE_DKTHERM;
		} else {
			this->view_type = DISP_TYPE_STANDBY;
		}
	} else {
		this->_qr_flag = 1;
		this->view_type = DISP_TYPE_DKQRCOD;
	}
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
	this->_last_view_type = DISP_TYPE_SETTING;
}
// 保存中画面表示
void Display::view_save() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(26, 50, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(29, 160, 76, 25, (uint8_t *)save_img, 10);
	this->_last_view_type = DISP_TYPE_SAVENOW;
}
// wifi 接続中
void Display::view_wifi_conn() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(19, 46, 97, 82, (uint8_t *)wifi_icon_img, 10);
    this->_tft->viewBMP(13, 160, 109, 25, (uint8_t *)wifi_conn_img, 10);
	this->_last_view_type = DISP_TYPE_WIFICNN;
}
// Webhook中
void Display::view_webhook() {
    this->_tft->fillRect(0, 210,  135, 30, WHITE);
    this->_tft->viewBMP(10, 212, 116, 25, (uint8_t *)webhook_img, 10);
	this->_last_view_type = DISP_TYPE_WEBFOOK;
}
// 暗記中
void Display::view_ankey_now() {
}
// 打鍵数を表示
void Display::view_dakagi() {
	// 最後に表示したInfoが打鍵数で最後に表示した打鍵数が今の打鍵数と一緒なら何もしない
	if (this->_last_view_info == 1 && this->dakagi_last_view == common_cls.key_count_total) return;
	// 最後に表示したInfoが空か、打鍵でなければInfoを空にする
	if (this->_last_view_info != 0 && this->_last_view_info != 1) {
		this->_tft->fillRect(0, 210,  135, 30, WHITE);
	}
	// 打鍵数表示
	this->_tft->viewBMP(5, 215, 57, 25, (uint8_t *)dakagi_img, 10);
	this->view_int(65, 217, common_cls.key_count_total);
	this->dakagi_last_view = common_cls.key_count_total;
	this->_last_view_info = 1;
}
// 打鍵サーモグラフを表示
void Display::view_dakagi_thermo() {
}
// 打鍵QRコードを表示
void Display::view_dakagi_qr() {
}

// 待ち受け画像表示
void Display::view_standby_image() {
	if (this->_last_view_type == DISP_TYPE_STANDBY) return; // 最後に表示したのが待ち受けなら何もしない
	if (this->_stimg_load_flag) {
		// SPRAMにデータロード済みならSPRAMに入ってる待ち受け画像を表示
		this->_tft->viewBMPspi_head(0, 0, 135, 240);
		this->_tft->viewBMPspi_data(this->_stimg_data, 64800);
	} else if (ESP.getFreePsram() > 64800) {
		// SPRAMに空き容量があれば待ち受け画像をSPRAMにロード
		this->_stimg_data = (uint8_t *)ps_malloc(64800);
		if(SPIFFS.exists("/stimg.dat")){
			File fp = SPIFFS.open("/stimg.dat", "r");
			int s = fp.read(this->_stimg_data, 64800);
			fp.close();
		}
		this->_tft->viewBMPspi_head(0, 0, 135, 240);
		this->_tft->viewBMPspi_data(this->_stimg_data, 64800);
	} else {
		// SPRAMに空きが無ければファイルから直接表示
	    this->_tft->viewBMPFile(0,0, 135, 240, "/stimg.dat", 0);
	}
	this->_last_view_type = DISP_TYPE_STANDBY;
	this->_last_view_info = 255;
}
// LED ステータス表示
void Display::view_led_stat() {
}
// LED 明るさ設定表示
void Display::view_led_bright() {
}
// LED 色設定表示
void Display::view_led_color() {
}
// LED 光らせ方設定表示
void Display::view_led_shine() {
}
// 打鍵自動保存設定表示
void Display::view_dakey_auto_save() {
}
// Wifi接続して下さいエラー表示
void Display::view_error_wifi_conn() {
	this->_tft->fillRect(0, 0,  135, 240, WHITE);
	this->_tft->viewBMP(0, 90, 199, 26, (uint8_t *)please_wifi_txt_img, 10);
	this->_last_view_type = 255;
	delay(1500);
}
// 打鍵数を保存しましたテキスト表示
void Display::view_dakey_save_comp() {
}

#endif


// 起動ムービー(AZ-66JP用)
#ifdef KEYBOARD_AZ66JP
void Display::open_movie() {
	int i;
	int skip_flag = 0;
	int ent_flag = 0;
      // 楽しいを形に…
      this->_tft->fillScreen(WHITE);
      delay(1000);
      for (i=0; i<=10; i++) {
        this->_tft->viewBMP(40, 54, 161, 20, (uint8_t *)tanoshii, i);
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
      }
	// 1.5秒待つ
      for (i=0; i<=15; i++) {
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
      }
      for (i=10; i>=0; i--) {
        this->_tft->viewBMP(40, 54, 161, 20, (uint8_t *)tanoshii, i);
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
      }
	// 1秒待つ
      for (i=0; i<=10; i++) {
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
      }
      // ロゴ表示
	skip_flag = 0;
    for (i=0; i<=10; i++) {
        this->_tft->viewBMP(0, 0, 240, 135, (uint8_t *)gimp_image, i);
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
    }
	// 3秒待つ
      for (i=0; i<=30; i++) {
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
      }
    for (i=10; i>=0; i--) {
        this->_tft->viewBMP(0, 0, 240, 135, (uint8_t *)gimp_image, i);
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
    }
      for (i=0; i<=10; i++) {
        common_cls.key_read(); // キーの状態を取得
      	if (ent_flag == 0 && common_cls.input_key[67]) { skip_flag = 1; ent_flag = 1; } else if (!common_cls.input_key[67]) { ent_flag = 0; }
        if (skip_flag) break;
        delay(100);
      }
}
// 設定モード画面表示
void Display::view_setting_mode() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(20, 24, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(124, 55, 98, 25, (uint8_t *)setting_title_img, 10);
	this->_last_view_type = DISP_TYPE_SETTING;
}
// 保存中画面表示
void Display::view_save() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(20, 24, 84, 88, (uint8_t *)setting_icon_img, 10);
    this->_tft->viewBMP(124, 55, 76, 25, (uint8_t *)save_img, 10);
	this->_last_view_type = DISP_TYPE_SAVENOW;
}
// wifi 接続中
void Display::view_wifi_conn() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(10, 27, 97, 82, (uint8_t *)wifi_icon_img, 10);
    this->_tft->viewBMP(120, 55, 109, 25, (uint8_t *)wifi_conn_img, 10);
	this->_last_view_type = DISP_TYPE_WIFICNN;
}
// Webhook中
void Display::view_webhook() {
    this->_tft->fillScreen(WHITE);
    this->_tft->viewBMP(10, 27, 97, 82, (uint8_t *)wifi_icon_img, 10);
    this->_tft->viewBMP(116, 55, 116, 25, (uint8_t *)webhook_img, 10);
	this->_last_view_type = DISP_TYPE_WEBFOOK;
}
// 暗記中
void Display::view_ankey_now() {
    this->_tft->fillRect(0, 0,  240, 135, WHITE);
    this->_tft->viewBMP(20, 25, 95, 86, (uint8_t *)ankey_icon_img, 10);
    this->_tft->viewBMP(135, 55, 75, 25, (uint8_t *)ankinow_img, 10);
	this->_last_view_type = 5;
}

// 打鍵数を表示
void Display::view_dakagi() {
	// 最後に表示したInfoが打鍵数で最後に表示した打鍵数が今の打鍵数と一緒なら何もしない
	if (this->_last_view_info == 1 && this->dakagi_last_view == common_cls.key_count_total) return;
	// 最後に表示したInfoが空か、打鍵でなければInfoを空にする
	if (this->_last_view_info != 0 && this->_last_view_info != 1) {
	    this->_tft->fillRect(0, 105,  240, 30, WHITE);
	}
	// 打鍵数表示
	this->_tft->viewBMP(5, 109, 57, 25, (uint8_t *)dakagi_img, 10);
	this->view_int(70, 111, common_cls.key_count_total);
	this->dakagi_last_view = common_cls.key_count_total;
	this->_last_view_info = 1;
}


// 打鍵サーモグラフを表示
void Display::view_dakagi_thermo() {
	int c, i, k, t;
	uint16_t set_color;
	// 最後に表示したのが打鍵サーモじゃなければ一回全て表示
	if (this->_last_view_type != DISP_TYPE_DKTHERM) {
		this->_tft->fillRect(0, 0,  240, 10, WHITE);
		this->_tft->fillRect(0, 92,  240, 43, WHITE);
		this->_tft->viewBMP(0, 10, 240, 82, (uint8_t *)az_66jp_plate_img, 10);
		for (i=0; i<KEY_INPUT_MAX; i++) {
			if (common_cls.key_count[i] < 0 || az66jp_key_position[i][0] == 0 || az66jp_key_position[i][1] == 0) continue;
			if (common_cls.key_count[i] < 508) {
				c = common_cls.key_count[i] >> 2;
			} else {
				c = 127;
			}
			this->_tft->fillRect(az66jp_key_position[i][0] - 2, az66jp_key_position[i][1] + 8,  15, 15, 0x9492);
			this->_tft->fillRect(az66jp_key_position[i][0] - 1, az66jp_key_position[i][1] + 9,  12, 12, thermo_color[c]);
		}
		this->_last_view_info = 0;
	}
	// 今押されているキーの色のみ更新
	for (i=0; i<PRESS_KEY_MAX; i++) {
		if (press_key_list[i].key_num < 0) continue;
		k = press_key_list[i].key_num;
		if (common_cls.key_count[k] < 0) continue;
		if (press_key_list[i].unpress_time <= 0) {
			set_color = GREEN;
		} else if (common_cls.key_count[k] < 508) {
			c = common_cls.key_count[k] >> 2;
			set_color = thermo_color[c];
		} else {
			set_color = thermo_color[127];
		}
		this->_tft->fillRect(az66jp_key_position[k][0] - 1, az66jp_key_position[k][1] + 9,  12, 12, set_color);
	}
	this->_last_view_type = DISP_TYPE_DKTHERM;
}

// Wifi接続して下さいエラー表示
void Display::view_error_wifi_conn() {
	this->_tft->fillRect(0, 0,  240, 135, WHITE);
	this->_tft->viewBMP(20, 55, 199, 26, (uint8_t *)please_wifi_txt_img, 10);
	this->_last_view_type = 255;
	delay(1500);
}


// 打鍵QRコードを表示
void Display::view_dakagi_qr() {
	int i, j, x, y;
	// 既にQRコードを表示済みであれば何もしない
	if (this->_last_view_type == DISP_TYPE_DKQRCOD) {
		// 何かキーが押されたらQR表示終了
		if (this->dakagi_last_view != common_cls.key_count_total) {
			this->view_dakagi_qr_on();
			this->_last_view_type = 255;
		}
		return;
	}
	// WIFIにつながっていなければエラー表示
	if (!wifi_conn_flag) {
		this->view_dakagi_qr_on();
		this->view_error_wifi_conn();
		return;
	}
	char qrurl[256];
	char file_path[32];
	// URL生成
	sprintf(qrurl, "http://azkey.jp/az66jp/?t=%s%08x", eep_data.uid, boot_count);
	i = 0;
	sprintf(file_path, "/D_%06D", boot_count);
	String res = common_cls.send_webhook_post_file(qrurl, file_path);
	res.toCharArray(qrurl, 256);
	QRCode qrcode;
	uint8_t qrcodeData[qrcode_getBufferSize(6)];
	qrcode_initText(&qrcode, qrcodeData, 6, ECC_LOW, qrurl);
    this->_tft->fillRect(0, 0,  240, 135, WHITE);
	for (uint8_t y = 0; y < qrcode.size; y++) {
		for (uint8_t x = 0; x < qrcode.size; x++) {
			if (qrcode_getModule(&qrcode, x, y)) {
				this->_tft->fillRect((x * 3) + 58, (y * 3) + 6,  3, 3, BLACK);
			}
		}
	}
	this->_last_view_type = DISP_TYPE_DKQRCOD;
	this->dakagi_last_view = common_cls.key_count_total;
}

// 待ち受け画像表示
void Display::view_standby_image() {
	if (this->_last_view_type == DISP_TYPE_STANDBY) return; // 最後に表示したのが待ち受けなら何もしない
	if (this->_stimg_load_flag == 1) {
		// SPRAMにデータロード済みならSPRAMに入ってる待ち受け画像を表示
		if (this->_info_spot) {
			// info部分だけ表示
			this->_tft->viewBMPspi_head(0, 105, 240, 30);
			this->_tft->viewBMPspi_data((uint8_t *)&this->_stimg_data[50400], 14400);
			this->_info_spot = 0;
		} else {
			// 全体を表示
			this->_tft->viewBMPspi_head(0, 0, 240, 135);
			this->_tft->viewBMPspi_data(this->_stimg_data, 64800);
		}
	} else if (this->_stimg_load_flag == 2) {
		// ファイルが無ければデフォルトの待ち受け
		if (this->_info_spot) {
			// info部分だけ表示
			this->_tft->viewBMP(0, 105, 240, 30, (uint8_t *)&stimg_default_img[50400], 10);
			this->_info_spot = 0;
		} else {
			// 全体を表示
			this->_tft->viewBMP(0, 0, 240, 135, (uint8_t *)stimg_default_img, 10);
		}
	} else if (ESP.getFreePsram() > 64800) {
		// SPRAMに空き容量があれば待ち受け画像をSPRAMにロード
		if(SPIFFS.exists("/stimg.dat")){
			this->_stimg_data = (uint8_t *)ps_malloc(64800);
			File fp = SPIFFS.open("/stimg.dat", "r");
			int s = fp.read(this->_stimg_data, 64800);
			fp.close();
			this->_tft->viewBMPspi_head(0, 0, 240, 135);
			this->_tft->viewBMPspi_data(this->_stimg_data, 64800);
			this->_stimg_load_flag = 1;
		} else {
		    this->_tft->viewBMP(0, 0, 240, 135, (uint8_t *)stimg_default_img, 10);
			this->_stimg_load_flag = 2;
		}
	} else {
		// SPRAMに空きが無ければファイルから直接表示
		if(SPIFFS.exists("/stimg.dat")){
			if (this->_info_spot) {
				// info枠の部分だけ表示
				this->_tft->viewBMPFile(0,105, 240, 30, "/stimg.dat", 50400);
				this->_info_spot = 0;
			} else {
				// 全体を表示
				this->_tft->viewBMPFile(0,0, 240, 135, "/stimg.dat", 0);
			}
		} else {
			this->_tft->fillRect(0, 0,  240, 135, BLACK);
			this->_stimg_load_flag = 2;
		}
	}
	this->_last_view_type = DISP_TYPE_STANDBY;
	this->_last_view_info = 255;
}
// LED ステータス表示
void Display::view_led_stat() {
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
    this->_tft->viewBMP(5, 109, 56, 22, (uint8_t *)led_txt_img, 10);
	if (rgb_led_cls._setting.status) {
	    this->_tft->viewBMP(70, 109, 35, 22, (uint8_t *)on_txt_img, 10);
	} else {
	    this->_tft->viewBMP(70, 109, 43, 22, (uint8_t *)off_txt_img, 10);
	}
	this->_last_view_info = 2;
	this->_wait_index = 150;
    rgb_led_cls.setting_change = 0;
}
// LED 明るさ設定表示
void Display::view_led_bright() {
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
    this->_tft->viewBMP(5, 109, 119, 26, (uint8_t *)led_bright_txt_img, 10);
	this->view_int(135, 111, rgb_led_cls._setting.bright);
	this->_last_view_info = 3;
	this->_wait_index = 150;
    rgb_led_cls.setting_change = 0;
}
// LED 色設定表示
void Display::view_led_color() {
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
    this->_tft->viewBMP(5, 109, 82, 25, (uint8_t *)led_color_txt_img, 10);
	this->view_int(98, 111, rgb_led_cls._setting.color_type);
	this->_last_view_info = 4;
	this->_wait_index = 150;
    rgb_led_cls.setting_change = 0;
}
// LED 光らせ方設定表示
void Display::view_led_shine() {
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
    this->_tft->viewBMP(5, 109, 119, 24, (uint8_t *)led_type_txt_img, 10);
	this->view_int(135, 111, rgb_led_cls._setting.shine_type);
	this->_last_view_info = 5;
	this->_wait_index = 150;
    rgb_led_cls.setting_change = 0;
}
// 打鍵自動保存設定表示
void Display::view_dakey_auto_save() {
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
    this->_tft->viewBMP(5, 109, 139, 26, (uint8_t *)dakey_auto_save_txt_img, 10);
	if (key_count_auto_save) {
	    this->_tft->viewBMP(155, 109, 35, 22, (uint8_t *)on_txt_img, 10);
	} else {
	    this->_tft->viewBMP(155, 109, 43, 22, (uint8_t *)off_txt_img, 10);
	}
	this->_last_view_info = 6;
	this->_wait_index = 150;
    rgb_led_cls.setting_change = 0;
}
// 打鍵数を保存しましたテキスト表示
void Display::view_dakey_save_comp() {
	this->_tft->fillRect(0, 105,  240, 30, WHITE);
	this->_tft->viewBMP(5, 109, 194, 26, (uint8_t *)dakey_save_comp_txt_img, 10);
	this->_last_view_info = 7;
	this->_wait_index = 190;
	this->_info_index = 200;
	rgb_led_cls.setting_change = 0;
}

#endif


// 定期処理
void Display::loop_exec() {
    unsigned long n;
    n = millis();
    // this->_tft->fillRect(0, 0,  240, 50, BLACK);
    // this->_tft->setCursor(4, 4);
    // this->_tft->setTextSize(2);
    // this->_tft->printf("%D / %D\n", ESP.getHeapSize(), ESP.getFreeHeap());
    // this->_tft->printf("%D / %D\n", ESP.getPsramSize(), ESP.getFreePsram());
    // this->_tft->printf("%D / %D\n", ESP.getFlashChipSize(), ESP.getFlashChipSpeed());
	// 待ちIndexがあれば待ち時間終わるまで画面の変更なし
	// if (this->_wait_index && rgb_led_cls.setting_change == 0) {
	// 	this->_wait_index--;
	// 	return;
	// }
	if (this->_wait_index) this->_wait_index--;
	if (this->_info_index) this->_info_index--;
	// 最後に表示したタイプとこれから表示しようとしている物が変わったら、最後に表示したタイプをbackに保持しておく
	if (this->view_type != this->_last_view_type) {
		this->_back_view_type = this->_last_view_type;
	}
	// 各表示処理
	if (rgb_led_cls.setting_change == 1) {
		this->view_led_stat();  // LEDステータス設定変更があった

	} else if (rgb_led_cls.setting_change == 2) {
		this->view_led_bright();  // LED明るさ設定変更があった
	
	} else if (rgb_led_cls.setting_change == 3) {
		this->view_led_color();  // LED色設定変更があった
	
	} else if (rgb_led_cls.setting_change == 4) {
		this->view_led_shine();  // LED光らせ方設定変更があった

	} else if (this->view_type == DISP_TYPE_DKQRCOD) {
		// 打鍵QRコード
		this->view_dakagi_qr();
		// info表示を終わる時にQRコードを表示しなおしたいので表示している内容を何もなしにする
		if (this->_wait_index == 1) this->_last_view_type = 255;

	} else if (this->view_type == DISP_TYPE_DKTHERM) {
		// 打鍵サーモ(最終表示がサーモでもまた実行する)
		this->view_dakagi_thermo();
		// 打鍵表示
		if (this->_wait_index == 0) this->view_dakagi();

	} else if (this->view_type == DISP_TYPE_STANDBY) {
		// 打鍵表示があるから最終表示が待ち受けでもまた実行する
		// 待ち受け画像
		this->view_standby_image();
		// 打鍵表示
		if (this->_wait_index == 0) {
			if (this->dakagi_last_view != common_cls.key_count_total && common_cls.key_count_total != 0) {
				// 打鍵数が増えたら打鍵数表示
				this->view_dakagi();
				this->_info_index = 150;
			} else if (this->_info_index == 1) {
				// info表示を終わる時に待ち受け画像を表示しなおしたいので表示してる内容を何もなしにする
				this->_info_spot = 1;
				this->_last_view_type = 255;
			}
		}

	} else if (this->view_type == this->_last_view_type) {
		// 最後に表示した内容と一緒であれば何もしない

	} else if (this->view_type == DISP_TYPE_SETTING) {
		// 設定画面
		this->view_setting_mode();

	} else if (this->view_type == DISP_TYPE_SAVENOW) {
		// 保存中画面
		this->view_save();

	} else if (this->view_type == DISP_TYPE_WIFICNN) {
		// Wifi接続中
		this->view_wifi_conn();

	} else if (this->view_type == DISP_TYPE_WEBFOOK) {
		// WEBフック中
		this->view_webhook();

	} else if (this->view_type == DISP_TYPE_ANKYNOW) {
		// 暗記中画面
		this->view_ankey_now();


	}
	
}

