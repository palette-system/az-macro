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
#include "src/lib/HTTPClient_my.h"


// キーボード
#include "src/keyboard/az_macro.h"
// #include "src/keyboard/az_66jp.h"
// #include "src/keyboard/az_68us.h"
// #include "src/keyboard/az_4key.h"


#if defined(CONFIG_ARDUHAL_ESP_LOG)
  #include "esp32-hal-log.h"
  #define LOG_TAG ""
#else
  #include "esp_log.h"
  static const char* LOG_TAG = "AZM";
#endif


// ファームウェアのバージョン文字
#define FIRMWARE_VERSION   "000103"

// EEPROMに保存しているデータのバージョン文字列
#define EEP_DATA_VERSION    "AZM006"

// JSON のファイルパス
#define SETTING_JSON_PATH "/setting.json"

// 起動回数を保存するファイルのパス
#define  BOOT_COUNT_PATH  "/boot_count"

// 打鍵数を自動保存するかどうかの設定を保存するファイルパス
#define  KEY_COUNT_AUTO_SAVE_PATH  "/key_count_auto_save"

#define  AZ_DEBUG_MODE 1

// 今押されているボタンの情報
struct press_key_data {
    short action_type; // キーの動作タイプ 0=設定なし / 1=通常入力 / 2=テキスト入力 / 3=レイヤー変更 / 4=WEBフック
    short layer_id; // キーを押した時のレイヤーID
    short key_num; // キー番号
    short key_id; // 送信した文字
    short press_time; // キーを押してからどれくらい経ったか
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

// 通常キー入力
struct setting_normal_input {
    uint8_t key_length;
    uint16_t *key;
    uint16_t hold;
    short repeat_interval;
};

// マウス移動
struct setting_mouse_move {
    int16_t x;
    int16_t y;
    int16_t speed;
};

// レイヤー切り替え
struct setting_layer_move {
    int8_t layer_id;
    int8_t layer_type;
};

// キーを押した時の設定
struct setting_key_press {
    short layer; // どのレイヤーか
    short key_num; // どのキーか
    short action_type; // 入力するタイプ
    short data_size; // データのサイズ
    char *data; // 入力データ
};

// WIFI設定
struct setting_wifi {
    char *ssid;
    char *pass;
};


// ArduinoJSON SPRAM用の定義
struct SpiRamAllocator {
    void* allocate(size_t size) {
        if (SETTING_JSON_BUF_PSRAM) {
            return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
        } else {
            return malloc(size);
        }
    }
    void deallocate(void* pointer) {
        if (SETTING_JSON_BUF_PSRAM) {
            heap_caps_free(pointer);
        } else {
            free(pointer);
        }
    }
    void* reallocate(void* ptr, size_t new_size) {
        if (SETTING_JSON_BUF_PSRAM) {
            return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);
        } else {
            return realloc(ptr, new_size);
        }
    }
};
using SpiRamJsonDocument = BasicJsonDocument<SpiRamAllocator>;

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
        String send_webhook_simple(char *url); // 単純なGETリクエストのWEBフック
        String send_webhook_post_file(char *url, char *file_path); // POSTでファイルの内容を送信する
        String send_webhook(char *setting_data); // httpかhttpsか判断してリクエストを送信する
        String http_request(char *url, const JsonObject &prm); // httpリクエスト送信
        bool create_setting_json(); // デフォルトの設定json作成
        void load_setting_json(); // jsonデータロード
        void clear_keymap(); // キーマップ用に確保しているメモリを解放
        void get_keymap(JsonObject setting_obj); // JSONデータからキーマップの情報を読み込む
        void remap_save_setting_json(); // REMAPで受け取ったデータをJSONデータに書き込む
        void set_default_layer_no(); // デフォルトレイヤー設定
        void get_keyboard_type_int(String t); // キーボードのタイプ番号を取得
        void get_option_type_int(JsonObject setting_obj); // オプションタイプの番号を取得
        int read_file(char *file_path, String &read_data); // ファイルからデータを読み出す
        int write_file(char *file_path, String &write_data); // ファイルにデータを保存する
        int remove_file(char *file_path); // ファイルを削除する
        void pin_setup(); // キーの入力ピンの初期化
        void pin_setup_sub_process(); // 入力ピン初期化のキーボード別の処理
        bool layers_exists(int layer_no); // レイヤーが存在するか確認
        setting_key_press get_key_setting(int layer_id, int key_num); // 指定したキーの入力設定を取得する
        void load_data(); // EEPROMからデータをロードする
        void save_data(); // EEPROMに保存する
        void load_boot_count(); // 起動回数を取得してカウントアップする
        void load_file_data(char *file_path, uint8_t *load_point, uint16_t load_size); // ファイルから設定値を読み込み
        void save_file_data(char *file_path, uint8_t *save_point, uint16_t save_size); // ファイルに設定値を書込み
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
        void delete_all(void); // 全てのファイルを削除
        void delete_indexof_all(String check_str); // 指定した文字から始まるファイルすべて削除
        int spiffs_total(void); // ファイル領域合計サイズを取得
        int spiffs_used(void); // 使用しているファイル領域サイズを取得
    
    private:

};

// hid
extern uint16_t hid_vid;
extern uint16_t hid_pid;

// ステータスピン番号
extern int status_pin;

// ステータスLED今0-9
extern int status_led_bit;

// ステータスLED表示モード
extern int status_led_mode;

// 入力用ピン情報
extern short col_len;
extern short row_len;
extern short direct_len;
extern short touch_len;
extern short *col_list;
extern short *row_list;
extern short *direct_list;
extern short *touch_list;

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

// キーボードの言語(日本語=0/ US=1 / 日本語(US記号) = 2)
extern uint8_t keyboard_language;

// オプションタイプの番号
extern int option_type_int;

// トラックボールの方向
extern uint8_t trackball_direction;

// トラックボールのカーソル移動速度
extern uint8_t trackball_speed;

// 踏みキーの反転フラグ
extern bool foot_inversion;

// オープニングムービー再生フラグ
extern bool op_movie_flag;

// デフォルトのレイヤー番号と、今選択しているレイヤー番号
extern int default_layer_no;
extern int select_layer_no;
extern int last_select_layer_key; // レイヤーボタン最後に押されたボタン(これが離されたらレイヤーリセット)


// 押している最中のキーデータ
extern press_key_data press_key_list[PRESS_KEY_MAX];

// 押している最中のマウス移動
extern press_mouse_data press_mouse_list[PRESS_MOUSE_MAX];

// マウスのスクロールボタンが押されているか
extern bool mouse_scroll_flag;

// オールクリア送信フラグ
extern int press_key_all_clear;


// EEPROMデータリンク
extern mrom_data_set eep_data;

// 起動回数
extern uint32_t boot_count;

// 打鍵数を自動保存するかどうか
extern uint8_t key_count_auto_save;

// 共通クラスリンク
extern AzCommon common_cls;

// 設定JSONオブジェクト
extern JsonObject setting_obj;

// remapに送る用のデータ
extern uint8_t  *setting_remap;
extern uint16_t  layer_max;
extern uint16_t  key_max;

// remap用 キー入力テスト中フラグ
extern uint16_t  remap_input_test;

// キーが押された時の設定
extern uint16_t setting_length;
extern setting_key_press *setting_press;
// wifi設定
extern uint8_t wifi_data_length;
extern setting_wifi *wifi_data;
// アクセスポイントパスワード
extern char *ap_pass_char;
// RGBLED
extern int8_t rgb_pin;
extern int8_t matrix_row;
extern int8_t matrix_col;
extern int8_t *led_num;
extern int8_t *key_matrix;
extern uint8_t led_num_length;
extern uint8_t key_matrix_length;

#endif
