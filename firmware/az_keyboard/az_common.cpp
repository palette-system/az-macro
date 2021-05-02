#include "az_common.h"

// セッティングJSONを保持する領域
DynamicJsonDocument setting_doc(SETTING_JSON_BUF_SIZE);
JsonObject setting_obj;

// ステータス表示用ピン番号
int status_pin = -1;

// ステータスLED今0-9
int status_led_bit = 0;

// ステータスLED表示モード
int status_led_mode;

// 液晶オブジェクト
Arduino_ST7789 *tft;

// 液晶表示用オブジェクト
Display *disp;

// rgb_led制御用クラス
Neopixel rgb_led_cls = Neopixel();

//timer オブジェクト
hw_timer_t *timer = NULL;

// WIFI接続オブジェクト
WiFiMulti wifiMulti;

// WIFI接続フラグ
int wifi_conn_flag;

// http用のバッファ
char webhook_buf[WEBFOOK_BUF_SIZE];

// 入力キーの数
int key_input_length;

// キーボードタイプの番号
int keyboard_type_int;

// オプションタイプの番号
int option_type_int;

// デフォルトのレイヤー番号と、今選択しているレイヤー番号と、最後に押されたレイヤーボタン
int default_layer_no;
int select_layer_no;
int last_select_layer_key;


// 押している最中のキーデータ
press_key_data press_key_list[PRESS_KEY_MAX];

// 押している最中のマウス移動
press_mouse_data press_mouse_list[PRESS_MOUSE_MAX];

// オールクリア送信フラグ
int press_key_all_clear;



// ステータス用LED点滅
void IRAM_ATTR status_led_write() {
    int set_bit;
    status_led_bit++;
    if (status_led_bit >= 20) status_led_bit = 0;
    if (status_led_mode == 0) {
        set_bit = 0; // 消灯

    } else if (status_led_mode == 1) {
        set_bit = 1; // 点灯
      
    } else if (status_led_mode == 2) {
        // 設定モード
        if (status_led_bit < 5 || (status_led_bit >= 10 && status_led_bit < 15)) {
            set_bit = 1;
        } else {
            set_bit = 0;
        }
      
    } else if (status_led_mode == 3) {
        // ファームウェア更新中
        if (status_led_bit % 2) {
            set_bit = 1;
        } else {
            set_bit = 0;
        }

    } else if (status_led_mode == 4) {
        // wifi接続中
        if (status_led_bit == 0 || status_led_bit == 2 || status_led_bit == 10 || status_led_bit == 12) {
            set_bit = 1;
        } else {
            set_bit = 0;
        }
    }
    if (status_pin >= 0) digitalWrite(status_pin, set_bit);
}

// ランダムな文字生成(1文字)
char getRandomCharLower(void) {
    const char CHARS[] = "abcdefghijklmnopqrstuvwxyz";
    int index = random(0, (strlen(CHARS) - 1));
    char c = CHARS[index];
    return c;
}

// ランダムな文字生成(1文字)
char getRandomNumber(void) {
    const char CHARS[] = "0123456789";
    int index = random(0, (strlen(CHARS) - 1));
    char c = CHARS[index];
    return c;
}

// ランダムな文字列生成(文字数指定)
void getRandomCharsLower(int le, char *cbuf) {
    int i;
    for(i=0; i<le; i++){
        cbuf[i]  = getRandomCharLower();
    }
    cbuf[i] = '\0';
}

// ランダムな文字列生成(数字)
void getRandomNumbers(int le, char *cbuf) {
    int i;
    for(i=0; i<le; i++){
        cbuf[i]  = getRandomNumber();
    }
    cbuf[i] = '\0';
}

// コンストラクタ
AzCommon::AzCommon() {
}

// 共通処理の初期化
void AzCommon::common_start() {
    // 乱数初期化
    randomSeed(millis());
    // ファイルシステム初期化
    if(!SPIFFS.begin(true)){
        ESP_LOGD(LOG_TAG, "SPIFFS begin error\n");
        return;
    }
    // WIFI 接続フラグ
    wifi_conn_flag = 0;
    // 押している最中のキーデータ初期化
    int i;
    for (i=0; i<PRESS_KEY_MAX; i++) {
        press_key_list[i].action_type = -1;
        press_key_list[i].key_num = -1;
        press_key_list[i].key_id = -1;
        press_key_list[i].layer_id = -1;
        press_key_list[i].unpress_time = -1;
    }
}


// ステータスLEDチカ用タイマー登録
void AzCommon::set_status_led_timer() {
    timer = timerBegin(0, 80, true); //timer=1us
    timerAttachInterrupt(timer, &status_led_write, true);
    timerAlarmWrite(timer, 100000, true); // 100ms
    timerAlarmEnable(timer);
}

// WIFI 接続
void AzCommon::wifi_connect() {
    // WIFI 接続
    int i;
    int wifi_len = setting_obj["wifi"].size();
    String ssid, pass;
    char ssid_char[64], pass_char[64];
    if (wifi_len <= 0) {
        ESP_LOGD(LOG_TAG, "wifi : not setting\r\n");
        wifi_conn_flag = 0;
        return;
    }
    // WiFi.mode(WIFI_STA);
    for (i=0; i<wifi_len; i++) {
        ssid = setting_obj["wifi"][i]["ssid"].as<String>();
        pass = setting_obj["wifi"][i]["pass"].as<String>();
        ssid.toCharArray(ssid_char, 64);
        pass.toCharArray(pass_char, 64);
        wifiMulti.addAP(ssid_char, pass_char);
        // WiFi.begin(ssid_char, pass_char);
        ESP_LOGD(LOG_TAG, "wifi : [%S] [%S]\r\n", ssid_char, pass_char);
        // break;
    }
    ESP_LOGD(LOG_TAG, "wifi : connect start\r\n");
    i = 0;
    wifi_conn_flag = 1;
    // while (WiFi.status() != WL_CONNECTED) {
    while (wifiMulti.run() != WL_CONNECTED) {
        ESP_LOGD(LOG_TAG, "wifi : try %D\r\n", i);
        delay(1000);
        i++;
        if (i > 20) {
            ESP_LOGD(LOG_TAG, "wifi : connect error\r\n");
            wifi_conn_flag = 0;
            break;
        }
    }
    if (wifi_conn_flag) {
        ESP_LOGD(LOG_TAG, "wifi : connect OK!\r\n");
    }
}

// URLからドメイン名だけ抜き出す
void AzCommon::get_domain(char *url, char *domain_name) {
    int i = 0, j = 0, s = 0;
    while (url[i] > 0) {
        if (s == 0 && url[i] == '/') {
            s = 1;
        } else if (s == 1 && url[i] == '/') {
            s = 2;
        } else if (s == 2) {
            if (url[i] == '/' || url[i] == ':') {
                s = 3;
                domain_name[j] = 0x00;
                break;
            } else if (url[i] == '@') {
                j = 0;
                domain_name[j] = 0x00;
            } else {
                domain_name[j] = url[i];
                j++;
            }
        } else {
            s = 0;
        }
        i++;
    }
    domain_name[j] = 0x00;
}

// webリクエストを送信する
String AzCommon::send_webhook(const JsonObject &prm) {
    String url = prm["url"].as<String>();
    char url_char[1024];
    url += "\0";
    url.toCharArray(url_char, 1024);
    if (url.startsWith("http://") || url.startsWith("https://")) {
        return http_request(url_char, prm);        
    } else {
        return String("url error");
    }
}

// HTTPリクエストを送信する
String AzCommon::http_request(char *url, const JsonObject &prm) {
    if (!wifi_conn_flag) return "";
    status_led_mode = 3;
    ESP_LOGD(LOG_TAG, "http : %S\r\n", url);
    char hkey[64];
    int i;
    int header_len = prm["header"].size();
    // httpリクエスト用オブジェクト
    HTTPClient http;
    http.begin(url);
    // ヘッダー送信
    for (i=0; i<header_len; i++) {
        String hk = prm["header"][i]["key"].as<String>();
        String hv = prm["header"][i]["value"].as<String>();
        hk.toCharArray(hkey, 64);
        hv.toCharArray(webhook_buf, WEBFOOK_BUF_SIZE);
        http.addHeader(hkey, webhook_buf);
    }
    // POSTデータがあればPOST
    String pd = prm["post"].as<String>();
    int status_code;
    if (pd.length() > 0) {
        // POST
        pd.toCharArray(webhook_buf, WEBFOOK_BUF_SIZE);
        status_code = http.POST(webhook_buf);
    } else {
        // GET
        status_code = http.GET();
    }
    ESP_LOGD(LOG_TAG, "http status: %D\r\n", status_code);
    int ot = prm["keyoutput"].as<signed int>();
    if (status_code == HTTP_CODE_OK) {
        String res_body = http.getString();
        http.end();
        status_led_mode = 1;
        if (ot == 0) {
            return "";
        } else if (ot == 1) {
            return String(status_code);
        } else if (ot == 2) {
            return res_body;
        }
        return "";
    } else {
        http.end();
        status_led_mode = 1;
        if (ot == 1) {
            return String(status_code);
        }
        String res_buf = "status code:" + String(status_code);
        return res_buf;
    }
}



// 区切り文字で分割する
int AzCommon::split(String data, char delimiter, String *dst){
    int index = 0;
    int arraySize = (sizeof(data)/sizeof((data)[0]));  
    int datalength = data.length();
    for (int i = 0; i < datalength; i++) {
        char tmp = data.charAt(i);
        if ( tmp == delimiter ) {
            index++;
            if ( index > (arraySize - 1)) return -1;
        }
        else dst[index] += tmp;
    }
    return (index + 1);
}

// JSONデータを読み込む
void AzCommon::load_setting_json() {
    // ファイルが無い場合はデフォルトファイル作成
    if (!SPIFFS.exists(SETTING_JSON_PATH)) {
        if (!create_setting_json()) return;
    }
    // ファイルオープン
    File json_file = SPIFFS.open(SETTING_JSON_PATH);
    if(!json_file){
        ESP_LOGD(LOG_TAG, "load_setting_json open error\n");
        return;
    }
    // 読み込み＆パース
    DeserializationError err = deserializeJson(setting_doc, json_file);
    if (err) {
        ESP_LOGD(LOG_TAG, "load_setting_json deserializeJson error\n");
        return;
    }
    json_file.close();
    // オブジェクトを保持
    setting_obj = setting_doc.as<JsonObject>();
    ESP_LOGD(LOG_TAG, "status_pin: %D\r\n", setting_obj["status_pin"].as<signed int>());
    // ステータス表示用ピン番号取得
    if (setting_obj.containsKey("status_pin")) {
        status_pin = setting_obj["status_pin"].as<signed int>();
    }
    // デフォルトのレイヤー番号設定
    default_layer_no = setting_obj["default_layer"].as<signed int>();
    // 今選択してるレイヤーをデフォルトに
    select_layer_no = default_layer_no;
    // キーボードのタイプ番号を取得
    get_keyboard_type_int();
    // オプションタイプの番号を取得
    get_option_type_int();
}

// デフォルトレイヤー番号設定
void AzCommon::set_default_layer_no() {
    // 設定されているデフォルトレイヤー取得
    default_layer_no = setting_obj["default_layer"].as<signed int>();
    // キー4が押されていた時 デフォルトを1へ
    if (common_cls.input_key[4] && layers_exists(1)) default_layer_no = 1;
    // キー5が押されていた時 デフォルトを2へ
    if (common_cls.input_key[5] && layers_exists(2)) default_layer_no = 2;
    // キー6が押されていた時 デフォルトを3へ
    if (common_cls.input_key[6] && layers_exists(3)) default_layer_no = 3;
    // キー7が押されていた時 デフォルトを4へ
    if (common_cls.input_key[7] && layers_exists(4)) default_layer_no = 4;
    // 今選択してるレイヤーをデフォルトに
    select_layer_no = default_layer_no;
}

// キーボードタイプの番号を取得する
void AzCommon::get_keyboard_type_int() {
    String t = setting_obj["keyboard_type"].as<String>();
    keyboard_type_int = 0;
    if (t.equals("az_macro")) {
        keyboard_type_int = 1;
    }
}

// ユニットのタイプ番号を取得する
void AzCommon::get_option_type_int() {
    option_type_int = 0;
    if (!setting_obj.containsKey("option_set")) return;
    if (!setting_obj["option_set"].containsKey("type")) return;
    String t = setting_obj["option_set"]["type"].as<String>();
    if (t.equals("foot_m")) {
        // 踏みキー
        option_type_int = 1;
    } else if (t.equals("trackball_m")) {
        // トラックボール
        option_type_int = 2;
    } else if (t.equals("display_m")) {
        // AZ-Macro用 液晶モジュール
        option_type_int = 3;
    } else if (t.equals("display_66jp")) {
        // AZ-66JP用 液晶モジュール
        option_type_int = 4;
    }
}


// ファイルを開いてテキストをロードする
int AzCommon::read_file(char *file_path, String &read_data) {
    ESP_LOGD(LOG_TAG, "read file: %S\n", file_path);
    // ファイルが無ければエラー
    if (!SPIFFS.exists(file_path)) {
        ESP_LOGD(LOG_TAG, "read_file not file: %S\n", file_path);
        return 0;
    }
    // ファイルオープン
    File fp = SPIFFS.open(file_path, "r");
    if(!fp){
        ESP_LOGD(LOG_TAG, "read_file open error: %S\n", file_path);
        return 0;
    }
    // 読み込み
    read_data = fp.readString();
    fp.close();
    return 1;
}

// テキストをファイルに書き込む
int AzCommon::write_file(char *file_path, String &write_data) {
    // 書込みモードでファイルオープン
      ESP_LOGD(LOG_TAG, "write_file open path: %S\n", file_path);
    File fp = SPIFFS.open(file_path, FILE_WRITE);
    if(!fp){
        ESP_LOGD(LOG_TAG, "write_file open error: %S\n", file_path);
        return 0;
    }
    // 書込み
    ESP_LOGD(LOG_TAG, "save");
    if(!fp.print(write_data)){
        ESP_LOGD(LOG_TAG, "write_file print error");
        fp.close();
        return 0;
    }
    fp.close();
    ESP_LOGD(LOG_TAG, "write_file print ok");
    return 1;
}

// ファイルを削除
int AzCommon::remove_file(char *file_path) {
    if (SPIFFS.remove(file_path)) {
        return 1;
    } else {
        return 0;
    }
}


// デフォルトのsetting.jsonを生成する
bool AzCommon::create_setting_json() {
    // 書込みモードでファイルオープン
    File json_file = SPIFFS.open(SETTING_JSON_PATH, FILE_WRITE);
    if(!json_file){
        ESP_LOGD(LOG_TAG, "create_setting_json open error");
        return false;
    }
    // 書込み
    if(!json_file.print(setting_default_json_bin)){
        ESP_LOGD(LOG_TAG, "create_setting_json print error");
        json_file.close();
        return false;
    }
    json_file.close();
    ESP_LOGD(LOG_TAG, "create_setting_json print ok");
    return true;
}

// キーの入力ピンの初期化
void AzCommon::pin_setup() {
    // output ピン設定 (colで定義されているピンを全てoutputにする)
    int i;
    int col_len = setting_obj["keyboard_pin"]["col"].size();
    ESP_LOGD(LOG_TAG, "col len : %D\r\n", col_len);
    for (i=0; i<col_len; i++) {
        pinMode(setting_obj["keyboard_pin"]["col"][i].as<signed int>(), OUTPUT_OPEN_DRAIN);
        ESP_LOGD(LOG_TAG, "output : %D\r\n", setting_obj["keyboard_pin"]["col"][i].as<signed int>());
    }
    // row で定義されているピンを全てinputにする
    int row_len = setting_obj["keyboard_pin"]["row"].size();
    ESP_LOGD(LOG_TAG, "row len : %D\r\n", row_len);
    for (i=0; i<row_len; i++) {
        pinMode(setting_obj["keyboard_pin"]["row"][i].as<signed int>(), INPUT_PULLUP);
        ESP_LOGD(LOG_TAG, "input : %D\r\n", setting_obj["keyboard_pin"]["row"][i].as<signed int>());
    }
    // direct(スイッチ直接続)で定義されているピンを全てinputにする
    int direct_len = setting_obj["keyboard_pin"]["direct"].size();
    ESP_LOGD(LOG_TAG, "direct len : %D\r\n", direct_len);
    for (i=0; i<direct_len; i++) {
        pinMode(setting_obj["keyboard_pin"]["direct"][i].as<signed int>(), INPUT_PULLUP);
        ESP_LOGD(LOG_TAG, "input : %D\r\n", setting_obj["keyboard_pin"]["direct"][i].as<signed int>());
    }
    // タッチピンの数を取得
    int touch_len = setting_obj["keyboard_pin"]["touch"].size();
    // キー数の計算
    key_input_length = (col_len * row_len) + direct_len + touch_len;
    if (key_input_length > KEY_INPUT_MAX) key_input_length = KEY_INPUT_MAX;
    ESP_LOGD(LOG_TAG, "key length : %D\r\n", key_input_length);
    // キー入力ピン初期化のキーボード別の処理
    pin_setup_sub_process();
}


// キー入力ピン初期化のキーボード別の処理
void AzCommon::pin_setup_sub_process() {
    if (option_type_int == 1) {
        // 踏みキー
        pinMode(27, INPUT_PULLUP);
    }
}

// レイヤーが存在するか確認
bool AzCommon::layers_exists(int layer_no) {
    char lkey[16];
    // レイヤーのキー名取得
    sprintf(lkey, "layer_%D", layer_no);
    // キーの設定があるか確認
    if (!setting_obj["layers"].containsKey(lkey)) {
      return false;
    }
    return true;
}

// 指定したキーの入力設定オブジェクトを取得する
JsonObject AzCommon::get_key_setting(int key_num) {
    char lkey[16];
    char kkey[16];
    // 今選択中のレイヤーのキー名取得
    sprintf(lkey, "layer_%D", select_layer_no);
    // キーのキー名取得
    sprintf(kkey, "key_%D", key_num);
    // キーの設定があるか確認
    if (!setting_obj["layers"].containsKey(lkey) ||
        !setting_obj["layers"][lkey]["keys"].containsKey(kkey)) {
        // 設定が無ければ何もしない
        JsonObject r;
        return r;
    }
    return setting_obj["layers"][lkey]["keys"][kkey];
}


//データをEEPROMから読み込む。保存データが無い場合デフォルトにする。
void AzCommon::load_data() {
    // EEPROM初期化
    EEPROM.begin(EEPROM_BUF_SIZE);
    ESP_LOGD(LOG_TAG, "eeprom size: %D", EEPROM.length());
    ESP_LOGD(LOG_TAG, "eeprom load\r\n");
    EEPROM.get<mrom_data_set>(0, eep_data);
    ESP_LOGD(LOG_TAG, "eeprom check: %S", eep_data.check);
    if (strcmp(eep_data.check, EEP_DATA_VERSION)) { //バージョンをチェック
        ESP_LOGD(LOG_TAG, "eeprom set default\r\n");
        //保存データが無い場合デフォルトを設定
        // 起動モード
        eep_data.boot_mode = 0;
        // データチェック文字列
        strcpy(eep_data.check, EEP_DATA_VERSION);
        // WIFIアクセスポイントの名前
        char b[16];
        getRandomNumbers(4, b);
        sprintf(eep_data.ap_ssid, "%S-%S", WIFI_AP_SSI_NAME, b);
        // ユニークID
        getRandomNumbers(10, eep_data.uid);
        // 受け渡し用テキスト
        strcpy(eep_data.text, "");
        // 設定JSONも作り直す
        create_setting_json();
        // キーボードモードで再起動(ここでeep_dataも保存される)
        change_mode(0);
    }
}

// データをEEPROMに書き込む
void AzCommon::save_data() {
    //EEPROMに設定を保存する。
    strcpy(eep_data.check, EEP_DATA_VERSION);
    ESP_LOGD(LOG_TAG, "save eeprom boot mode: %D", eep_data.boot_mode);
    ESP_LOGD(LOG_TAG, "save eeprom check sum: %S", eep_data.check);
    ESP_LOGD(LOG_TAG, "text: %S", eep_data.text);
    ESP_LOGD(LOG_TAG, "data sizeof: %D", sizeof(mrom_data_set));
    EEPROM.put<mrom_data_set>(0, eep_data);
    delay(200);
    EEPROM.commit(); //大事
    delay(200);
    ESP_LOGD(LOG_TAG, "save complete\r\n");
}

// 起動モードを変更してEEPROMに保存
void AzCommon::set_boot_mode(int set_mode) {
    eep_data.boot_mode = set_mode;
    save_data();
}

// モードを切り替えて再起動
void AzCommon::change_mode(int set_mode) {
    set_boot_mode(set_mode);
    ESP.restart(); // ESP32再起動
}

// 現在のキーの入力状態を取得
void AzCommon::key_read(void) {
    int i, j, n, s;
    int col_len = setting_obj["keyboard_pin"]["col"].size();
    int row_len = setting_obj["keyboard_pin"]["row"].size();
    int direct_len = setting_obj["keyboard_pin"]["direct"].size();
    int touch_len = setting_obj["keyboard_pin"]["touch"].size();
    n = 0;
    // ダイレクト入力の取得
    for (i=0; i<direct_len; i++) {
        input_key[n] = !digitalRead(setting_obj["keyboard_pin"]["direct"][i].as<signed int>());
        n++;
    }
    // タッチ入力の取得
    for (i=0; i<touch_len; i++) {
        // ESP_LOGD(LOG_TAG, "[%D][%D] %D = %D\r\n", n, i, setting_obj["keyboard_pin"]["touch"][i].as<signed int>(), touchRead(setting_obj["keyboard_pin"]["touch"][i].as<signed int>()));
        if (touchRead(setting_obj["keyboard_pin"]["touch"][i].as<signed int>()) < 25) {
            input_key[n] = 1;
        } else {
            input_key[n] = 0;
        }
        n++;
    }
    // マトリックス入力の取得
    for (i=0; i<col_len; i++) {
        // 対象のcolピンのみ lowにする
        for (j=0; j<col_len; j++) {
            if (i == j) { s = 0; } else { s = 1; }
            digitalWrite(setting_obj["keyboard_pin"]["col"][j].as<signed int>(), s);
        }
        delayMicroseconds(50);
        // row の分キー入力チェック
        for (j=0; j<row_len; j++) {
            input_key[n] = !digitalRead(setting_obj["keyboard_pin"]["row"][j].as<signed int>());
            n++;
        }
    }
    // キーボード別の後処理
    key_read_sub_process();
}

// キーボード別の後処理
void AzCommon::key_read_sub_process(void) {
    if (option_type_int == 1) {
        // 踏みキー
        if (setting_obj["option_set"]["inversion"].as<signed int>() && digitalRead(27) == 0) {
            // ジャックが刺されている間はON/OFF を反転
            input_key[8] = ! input_key[8];
            input_key[9] = ! input_key[9];
        }
    }
}

// 今回の入力状態を保持
void AzCommon::key_old_copy(void) {
    int i;
    for (i=0; i<key_input_length; i++) {
        input_key_last[i] = input_key[i];
    }
}

// 液晶ユニットが付いているか
bool AzCommon::on_tft_unit(void) {
    if (option_type_int == 3 || option_type_int == 4) {
        return true;
    }
    return false;
}
