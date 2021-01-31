#include "az_common.h"
#include "az_keyboard.h"
#include "az_setting.h"


// 起動モード
int boot_type;

// eepromのデータ
mrom_data_set eep_data;

// 共通クラス
AzCommon common_cls = AzCommon();

// キーボードモードクラス
AzKeyboard azkb = AzKeyboard();

// 設定モードクラス
AzSetting azstg = AzSetting();

void setup() {
    // 共通処理の初期化
    common_cls.common_start();
    // CPU情報の表示
    common_cls.debug_cpu_info();
    // 設定jsonの読み込み
    common_cls.load_setting_json();
    // ステータス表示用のLED
    pinMode(status_pin, OUTPUT);
    digitalWrite(status_pin, 0);
    // キーの入力ピンの初期化
    common_cls.pin_setup();
    // eepromからデータ読み込み
    common_cls.load_data();
    ESP_LOGD(LOG_TAG, "boot_mode = %D\r\n", eep_data.boot_mode);
    boot_type = eep_data.boot_mode;
    // 0番目のキーが押されていたら設定モードにする
    common_cls.key_read(); // キーの状態を取得
    if (common_cls.input_key[0]) boot_type = 1;
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
