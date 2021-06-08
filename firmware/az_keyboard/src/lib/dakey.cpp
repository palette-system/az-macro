#include "Arduino.h"
#include "dakey.h"


// コンストラクタ
Dakey::Dakey() {
}


// 打鍵数クラス初期化
void Dakey::begin() {
	this->last_save_key_count = -1;
	this->last_save_time = 0;
	// 打鍵数を保存(最初の0を保存)
	this->save_dakey();
}


// 打鍵数自動保存するかどうかの設定を変更
void Dakey::set_auto_save_change() {
	if (key_count_auto_save) {
		// OFFにする
		key_count_auto_save = 0;
	} else {
		// ONにする
		key_count_auto_save = 1;
		// 現在の打鍵数を保存
		this->save_dakey();
	}
	common_cls.save_file_data(KEY_COUNT_AUTO_SAVE_PATH, (uint8_t *)&key_count_auto_save, 1);
	disp->view_dakey_auto_save();
}


// 現在の打鍵数を保存する
void Dakey::save_dakey() {
	char save_path[32];
	String date_now;
	int i;
	// WiFiにつながって無ければ何もしない
	if (!wifi_conn_flag) {
		// WiFiに接続して下さいエラー表示
		disp->view_error_wifi_conn();
		return;
	}
	// WEBから現在日時を取得
	date_now = common_cls.send_webhook_simple("http://azkey.jp/api/date.php");
	// ファイルに書き込む
	File fp;
	sprintf(save_path, "/D_%05D", boot_count);
	if (SPIFFS.exists(save_path)){
		// ファイルがあれば追記
		fp = SPIFFS.open(save_path, "a");
	} else {
		// ファイルが無ければ新規作成
		fp = SPIFFS.open(save_path, "w");
	}
	if (!fp) {
		// ファイル書込み失敗
		return;
	}
	// 日時を書込み
	fp.print(date_now);
	if (common_cls.key_count_total == 0) {
		// 起動して最初の書込み
		fp.print(",0");
	} else if (this->last_save_key_count == common_cls.key_count_total) {
		// 最後に書き込んだ打鍵数から増えてない
		fp.print(",1");
	} else {
		// 打鍵数を書込み
		fp.print(",2,");
		// 打鍵データをURLに追加する
		for (i=0; i<KEY_INPUT_MAX; i++) {
			fp.printf("%04x", common_cls.key_count[i]);
		}
	}
	fp.print("\n");
	fp.close();
	this->last_save_key_count = common_cls.key_count_total;
	this->last_save_time = millis();
	// 打鍵数を保存しましたを表示
	disp->view_dakey_save_comp();
	
}


// 定期処理
void Dakey::loop_exec() {
	// 自動保存処理
	if (wifi_conn_flag && // Wifiに繋がっている
		key_count_auto_save && // 自動保存ON
		(this->last_save_time + AUTO_SAVE_INTERVAL) < millis() ) { // 最後に保存した時間から一定以上時間が経ったら
		this->save_dakey();
	}
}


