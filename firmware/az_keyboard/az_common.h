#ifndef AzCommon_h
#define AzCommon_h

#include "Arduino.h"
#include "FS.h"
#include "SPIFFS.h"

#include <EEPROM.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>

#include "src/lib/neopixel.h"
#include "src/lib/Arduino_ST7789_my.h"
#include "src/lib/display.h"


// キーボード
#include "src/keyboard/az_macro.h"
// #include "src/keyboard/az_66jp.h"


#if defined(CONFIG_ARDUHAL_ESP_LOG)
  #include "esp32-hal-log.h"
  #define LOG_TAG ""
#else
  #include "esp_log.h"
  static const char* LOG_TAG = "AZM";
#endif

// ファームウェアのバージョン文字
#define FIRMWARE_VERSION   "000015"

// EEPROMに保存しているデータのバージョン文字列
#define EEP_DATA_VERSION    "AZM003"

// JSON のファイルパス
#define SETTING_JSON_PATH "/setting.json"


// 今押されているボタンの情報
struct press_key_data {
    short action_type; // キーの動作タイプ 0=設定なし / 1=通常入力 / 2=テキスト入力 / 3=レイヤー変更 / 4=WEBフック
    short key_num; // キー番号
    short key_id; // 送信した文字
    short layer_id; // レイヤー切り替えボタンだった場合レイヤーIDが入る(デフォルト：-1)
    short unpress_time; // キーを離してからどれくらい経ったか
    short repeat_interval; // 連打の間隔
    short repeat_index; // 現在の連打カウント
};


// 今押されているマウスボタン情報
struct press_mouse_data {
    short key_num; // キー番号
    short move_x; // X座標
    short move_y; // Y座標
    short move_speed; // 移動速度
    short move_index; // 移動index
};

// EEPROMに保存するデータ
struct mrom_data_set {
    char check[10];
    char text[128];
    char ap_ssid[32];
    int boot_mode; // 起動モード 0=キーボード / 1=設定モード
    char uid[12];
};

// クラスの定義
class AzCommon
{
    public:
        AzCommon();   // コンストラクタ
        void common_start(); // 共通処理の初期処理(setup時に呼ばれる)
        int split(String data, char delimiter, String *dst); // 区切り文字で分割する
        void set_status_led_timer(); // ステータスLED点滅タイマー登録
        void wifi_connect(); // WIFI接続
        void get_domain(char *url, char *domain_name); // URLからドメイン名だけ取得
        String send_webhook(const JsonObject &prm); // httpかhttpsか判断してリクエストを送信する
        String http_request(char *url, const JsonObject &prm); // httpリクエスト送信
        bool create_setting_json(); // デフォルトの設定json作成
        void load_setting_json(); // jsonデータロード
        void set_default_layer_no(); // デフォルトレイヤー設定
        void get_keyboard_type_int(); // キーボードのタイプ番号を取得
        void get_option_type_int(); // オプションタイプの番号を取得
        int read_file(char *file_path, String &read_data); // ファイルからデータを読み出す
        int write_file(char *file_path, String &write_data); // ファイルにデータを保存する
        int remove_file(char *file_path); // ファイルを削除する
        void pin_setup(); // キーの入力ピンの初期化
        void pin_setup_sub_process(); // 入力ピン初期化のキーボード別の処理
        bool layers_exists(int layer_no); // レイヤーが存在するか確認
        JsonObject get_key_setting(int key_num); // 指定したキーの入力設定を取得する
        void load_data(); // EEPROMからデータをロードする
        void save_data(); // EEPROMに保存する
        void set_boot_mode(int set_mode); // 起動モードを切り替えてEEPROMに保存
        void change_mode(int set_mode); // モードを切り替えて再起動
        void key_read(); // 現在のキーの状態を取得
        void key_read_sub_process(void); // キー状態取得後のキーボード別の処理
        void key_old_copy(); // 現在のキーの状態を過去用配列にコピー
        char input_key[KEY_INPUT_MAX]; // 今入力中のキー
        char input_key_last[KEY_INPUT_MAX]; // 最後にチェックした入力中のキー
        uint16_t key_count[KEY_INPUT_MAX]; // キー別の打鍵した数
        uint16_t key_count_total;
        bool on_tft_unit(void); // 液晶ディスプレイが付いているか
    
    private:

};

// ステータスピン番号
extern int status_pin;

// ステータスLED今0-9
extern int status_led_bit;

// ステータスLED表示モード
extern int status_led_mode;

// 液晶オブジェクト
extern Arduino_ST7789 *tft;

// 液晶表示用オブジェクト
extern Display *disp;

// rgb_led制御用クラス
extern Neopixel rgb_led_cls;

//timer オブジェクト
extern hw_timer_t *timer;

// WIFI接続オブジェクト
extern WiFiMulti wifiMulti;

// WIFI接続フラグ
extern int wifi_conn_flag;

// http用のバッファ
extern char webhook_buf[WEBFOOK_BUF_SIZE];

// 入力キーの数
extern int key_input_length;

// キーボードタイプの番号
extern int keyboard_type_int;

// オプションタイプの番号
extern int option_type_int;

// デフォルトのレイヤー番号と、今選択しているレイヤー番号
extern int default_layer_no;
extern int select_layer_no;
extern int last_select_layer_key; // レイヤーボタン最後に押されたボタン(これが離されたらレイヤーリセット)


// 押している最中のキーデータ
extern press_key_data press_key_list[PRESS_KEY_MAX];

// 押している最中のマウス移動
extern press_mouse_data press_mouse_list[PRESS_MOUSE_MAX];

// オールクリア送信フラグ
extern int press_key_all_clear;


// EEPROMデータリンク
extern mrom_data_set eep_data;

// 共通クラスリンク
extern AzCommon common_cls;

// 設定JSONオブジェクト
extern JsonObject setting_obj;

// 暗記ボタン作動中かどうか
extern int ankey_flag;

// どのキーの暗記ボタンか
extern int ankey_id;

// 暗記保存するファイルパス
extern String ankey_file_path;




#endif
