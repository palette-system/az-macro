#ifndef AzCommon_h
#define AzCommon_h

#if defined(CONFIG_ARDUHAL_ESP_LOG)
  #include "esp32-hal-log.h"
  #define LOG_TAG ""
#else
  #include "esp_log.h"
  static const char* LOG_TAG = "AZM";
#endif

#include "FS.h"
#include "SPIFFS.h"

#include <EEPROM.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>


// キーボードの商品コード
#define KEYBOARD_CODE    "AZ-Macro-001"

// メモリに保持するキーの数(メモリを確保するサイズ)
#define KEY_INPUT_MAX  16

// レイヤー切り替え同時押し許容数
#define PRESS_KEY_MAX 16

// マウス移動ボタン同時押し許容数
#define PRESS_MOUSE_MAX 4

// WIFIアクセスポイントの名前
#define WIFI_AP_SSI_NAME    "AZ-Macro"

// ファームウェアのバージョン文字
#define FIRMWARE_VERSION   "000013"

// EEPROMに保存しているデータのバージョン文字列
#define EEP_DATA_VERSION    "AZM001"

// JSON のファイルパス
#define SETTING_JSON_PATH "/setting.json"

// EEPROM 読み込み時のサイズ
#define EEPROM_BUF_SIZE   256

// WEBフック用のバッファサイズ
// #define WEBFOOK_BUF_SIZE 5120
#define WEBFOOK_BUF_SIZE 512

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
        void debug_cpu_info(); // cpuの動作情報をシリアル通信に流す
        void key_read(); // 現在のキーの状態を取得
        void key_read_sub_process(void); // キー状態取得後のキーボード別の処理
        void key_old_copy(); // 現在のキーの状態を過去用配列にコピー
        char input_key[KEY_INPUT_MAX]; // 今入力中のキー
        char input_key_last[KEY_INPUT_MAX]; // 最後にチェックした入力中のキー
    
    private:

};

// ステータスピン番号
extern int status_pin;

// ステータスLED今0-9
extern int status_led_bit;

// ステータスLED表示モード
extern int status_led_mode;

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


#endif
