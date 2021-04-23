// AZ-60JIS 用設定


// 初期起動時のデフォルト設定
#include "setting_az60jis_default.h"

// メモリに保持するキーの数(メモリを確保するサイズ)
#define KEY_INPUT_MAX  80

// レイヤー切り替え同時押し許容数
#define PRESS_KEY_MAX 16

// マウス移動ボタン同時押し許容数
#define PRESS_MOUSE_MAX 4

// WIFIアクセスポイントの名前
#define WIFI_AP_SSI_NAME    "AZ-60JIS"

// Bluetooth で検索した時表示される名前
#define BLUETOOTH_SEARCH_NAME    "az-60jis"

// EEPROM 読み込み時のサイズ
#define EEPROM_BUF_SIZE   256

// WEBフック用のバッファサイズ
#define WEBFOOK_BUF_SIZE 512

// 設定JSONのバッファサイズ
#define SETTING_JSON_BUF_SIZE 20480

// 設定モードに入るためのキー番号
#define SETTING_MODE_KEY 0


