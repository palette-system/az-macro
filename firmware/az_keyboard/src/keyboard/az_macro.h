// AZ-Macro 用設定

// 初期起動時のデフォルト設定
#include "setting_azmacro_default.h"

// メモリに保持するキーの数(メモリを確保するサイズ)
#define KEY_INPUT_MAX  16

// レイヤー切り替え同時押し許容数
#define PRESS_KEY_MAX 16

// マウス移動ボタン同時押し許容数
#define PRESS_MOUSE_MAX 4

// WIFIアクセスポイントの名前
#define WIFI_AP_SSI_NAME    "AZ-Macro"

// Bluetooth で検索した時表示される名前
#define BLUETOOTH_SEARCH_NAME    "az-macro"

// EEPROM 読み込み時のサイズ
#define EEPROM_BUF_SIZE   256

// WEBフック用のバッファサイズ
#define WEBFOOK_BUF_SIZE 512

// 設定JSONのバッファサイズ
#define SETTING_JSON_BUF_SIZE 10240

// 設定モードに入るためのキー番号
#define SETTING_MODE_KEY 0

// ディスプレイ用
#define TFT_FLG   0 // ディスプレイが接続されているか(0=ディスプレイ表示無し / 1=ディスプレイ表示あり)
#define TFT_DC   26 // DC
#define TFT_RST  25 // TFTのリセット
#define TFT_CS   -1 // 1つなので使わない
#define TFT_MOSI 21 // SDA
#define TFT_SCLK 22 // SCL

