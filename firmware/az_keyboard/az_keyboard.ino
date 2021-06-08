#include "az_common.h"
#include "az_keyboard.h"
#include "az_setting.h"


// 起動モード
int boot_type;

// 共通クラス
AzCommon common_cls = AzCommon();

// キーボードモードクラス
AzKeyboard azkb = AzKeyboard();

// 設定モードクラス
AzSetting azstg = AzSetting();

void setup() {
    int i, j, s;
    // 共通処理の初期化
    common_cls.common_start();
    // 設定jsonの読み込み
    common_cls.load_setting_json();
    // ステータス表示用のLED初期化
    if (status_pin >= 0 && option_type_int != 3) {
        pinMode(status_pin, OUTPUT);
        digitalWrite(status_pin, 0);
        status_led_mode = 0;
        common_cls.set_status_led_timer();
    }
    // ディスプレイ初期化
    if (common_cls.on_tft_unit()) {
        disp = new Display();
        disp->begin(tft, option_type_int);
    }
    // RGB_LEDクラス初期化
    if (setting_obj.containsKey("rgb_pin") &&
            setting_obj.containsKey("matrix_row") &&
            setting_obj.containsKey("matrix_col")) {
        rgb_led_cls.begin(
            setting_obj["rgb_pin"].as<signed int>(),
            setting_obj["matrix_row"].as<signed int>(),
            setting_obj["matrix_col"].as<signed int>(),
            &select_layer_no
        );
        s = setting_obj["led_num"].size();
        for (i=0; i<s; i++) {
            rgb_led_cls.set_led_num(i, setting_obj["led_num"][i].as<signed int>());
        }
        s = setting_obj["key_matrix"].size();
        for (i=0; i<s; i++) {
            rgb_led_cls.set_key_matrix(i, setting_obj["key_matrix"][i].as<signed int>());
        }
        
    }
    // キーの入力ピンの初期化
    common_cls.pin_setup();
    // 起動回数を読み込み
    common_cls.load_boot_count();
    // 打鍵数を自動保存するかどうかの設定を読み込み
    key_count_auto_save = 0;
    common_cls.load_file_data(KEY_COUNT_AUTO_SAVE_PATH, (uint8_t *)&key_count_auto_save, 1);
    // eepromからデータ読み込み
    common_cls.load_data();
    ESP_LOGD(LOG_TAG, "boot_mode = %D\r\n", eep_data.boot_mode);
    boot_type = eep_data.boot_mode;
    // 0番目のキーが押されていたら設定モードにする
    common_cls.key_read(); // キーの状態を取得
    if (common_cls.input_key[SETTING_MODE_KEY]) boot_type = 1;
    // 4～5番目のキーが押されていたらデフォルトレイヤーを切り替える
    common_cls.set_default_layer_no();
    if (boot_type == 1) {
        ESP_LOGD(LOG_TAG, "設定モード起動\n");
        // 設定モード開始
        azstg.start_setting();
        // 次回起動時キーボード起動するようモード設定
        common_cls.set_boot_mode(0);

    } else {
        ESP_LOGD(LOG_TAG, "キーボードモード起動\n");
        if (common_cls.on_tft_unit() && setting_obj["option_set"]["op_movie"].as<signed int>()) {
            disp->open_movie();
        }
        // キーボードとして起動
        azkb.start_keyboard();
    }
}


// ループ処理本体
void loop() {
    if (boot_type == 1) {
      // 設定モード用ループ
      azstg.loop_exec();

    } else {
      // キーボードモード用ループ
      azkb.loop_exec();
    }
}
