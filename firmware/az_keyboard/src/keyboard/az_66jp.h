// AZ-60JIS 用設定


// 初期起動時のデフォルト設定
#include "setting_az66jp_default.h"
#include "../image/common.h"
#include "../image/led_setting.h"
#include "../image/az_66jp_img.h"



// キーボードの定義
#define  KEYBOARD_AZ66JP

// ESP32の種類 (0 = ESP32 / 1 = ESP32-WROVER)
#define  AZESP32_TYPE  1

// メモリに保持するキーの数(メモリを確保するサイズ)
#define KEY_INPUT_MAX  70

// レイヤー切り替え同時押し許容数
#define PRESS_KEY_MAX 16

// マウス移動ボタン同時押し許容数
#define PRESS_MOUSE_MAX 4

// WIFIアクセスポイントの名前
#define WIFI_AP_SSI_NAME    "AZ-66JP"

// Bluetooth で検索した時表示される名前
#define BLUETOOTH_SEARCH_NAME    "az-66jp"

// EEPROM 読み込み時のサイズ
#define EEPROM_BUF_SIZE   256

// WEBフック用のバッファサイズ
#define WEBFOOK_BUF_SIZE 512

// JSONバッファにPSRAMを使うかのフラグ
#define SETTING_JSON_BUF_PSRAM 1

// 設定JSONのバッファサイズ
#define SETTING_JSON_BUF_SIZE 262144

// 設定モードに入るためのキー番号
#define SETTING_MODE_KEY 0

// 暗記ボタンで暗記できる数
#define ANKEY_DATA_MAX_LENGTH  512

// Neopixデータ送信周波数(400 or 800)
#define AZ_NEO_KHZ 400

// ディスプレイモジュールの有無
#define AZ_DISPLAY_ENABLE true

// remap用 デフォルトの vid  pid
#define BLE_HID_VID  0xE502
#define BLE_HID_PID  0x0300

// remap用 データ送信時のキー数
#define REMAP_KEY_MAX  70

// remap用col,row (remap用JSON内で定義したROWとCOL)
#define REMAP_ROW  1
#define REMAP_COL  70

