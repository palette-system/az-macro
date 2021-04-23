#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include "az_common.h"
#include "az_setting.h"

#include "src/html/index_bin.h"
#include "src/html/config_js_bin.h"
#include "src/html/index_js_bin.h"



//無線LANのサーバー設定
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

// キーが押されたか
int last_key_down = -1;

// IP アドレスデータを表示用の文字列にする
String toStringIp(IPAddress ip) {
    String res = "";
    for (int i = 0; i < 3; i++) {
        res += String((ip >> (8 * i)) & 0xFF) + ".";
    }
    res += String(((ip >> 8 * 3)) & 0xFF);
    return res;
}

// wifiアクセスポイントのリストをJSONで取得
String get_wifi_ap_list_json(){
    ESP_LOGD(LOG_TAG, "get_wifi_ap_list: start");
    String res = "{\"list\": [";
    int ssid_num;
    String auth_open;
    ssid_num = WiFi.scanNetworks();
    if (ssid_num == 0) {
        ESP_LOGD(LOG_TAG, "get_wifi_ap_list: no networks");
    } else {
        ESP_LOGD(LOG_TAG, "get_wifi_ap_list: %d\r\n", ssid_num);
        for (int i = 0; i < ssid_num; ++i) {
            auth_open = ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)? "true": "false");
            if (i > 0) res += ",";
            res += "{\"ssid\": \"" + WiFi.SSID(i) + "\", \"rssi\": \"" + WiFi.RSSI(i) + "\", \"auth_open\": " + auth_open + "}";
            delay(10);
        }
    }
    res += "]}";
    ESP_LOGD(LOG_TAG, "%S", res);
    return res;
}


void captivePortal() {
    //無効リクエストはすべてESP32に向ける
    server.sendHeader("Location", "http://"+toStringIp(WiFi.softAPIP())+"/", true);
    server.send(302, "text/plain", "");
    server.client().stop();
}

bool handleUrl(String path) {
    char scmd[64];
    int i, n, r;
    path.toCharArray(scmd, 64);
    ESP_LOGD(LOG_TAG, "url path: %S", scmd);
    if (path.equals("/")){
        // メインページ
        server.send(200,"text/html", index_html_bin);
        return true;

    } else if (path.indexOf("/index.js") == 0) {
        // メインjs
        server.send(200,"text/js", index_min_js_bin);
        return true;

    } else if (path.indexOf("/config.js") == 0) {
        // メインjs
        server.send(200,"text/js", config_js_bin);
        return true;

    } else if (path.indexOf("/firmware_version") == 0) {
        // ファームウェアのバージョン教えて
        server.send(200,"text/html", FIRMWARE_VERSION);
        return true;

    } else if (path.indexOf("/last_key_down") == 0) {
        // 最後に押されたキー教えて(キーの現在の設定も返す)
        sprintf(scmd, "%D", last_key_down);
        server.send(200,"text/plan", scmd);
        last_key_down = -1;
        return true;

    } else if (path.indexOf("/get_key_status") == 0) {
        // 現在のキーの入力状態を教えて
        for (i=0; i<key_input_length; i++) {
            if (common_cls.input_key[i]) {
                scmd[i] = '1';
            } else {
                scmd[i] = '0';
            }
        }
        scmd[i] = '\0';
        server.send(200,"text/plan", scmd);
        return true;

    } else if (path.indexOf("/key_length") == 0) {
        // キーの数教えて
        sprintf(scmd, "%D", key_input_length);
        server.send(200,"text/plan", scmd);
        return true;

    } else if (path.indexOf("/get_setting_json") == 0) {
        // 設定JSON教えて
        File json_file = SPIFFS.open(SETTING_JSON_PATH);
        server.streamFile(json_file, "text/json");
        json_file.close();
        return true;

    } else if (path.indexOf("/file_list") == 0) {
        // ファイルリストの取得
        File dirp = SPIFFS.open("/");
        File filep = dirp.openNextFile();
        String res = "{\"data\": [";
        while(filep){
            res += "\"" + String(filep.name()) + "\",";
            filep = dirp.openNextFile();
        }
        res += "\".\"]}";
        server.send(200,"text/plan", res.c_str());

    } else if (path.indexOf("/read_file_") == 0) {
        // 指定したファイルを読み込み ( /read_file_{ファイル名} でアクセス)
        // パスの後ろがファイル名
        String file_path = "/" + path.substring(11);
        file_path.toCharArray(scmd, 64);
        ESP_LOGD(LOG_TAG, "file path: %S", scmd);
        // 読み込んで返す
        if(SPIFFS.exists(scmd)){
            File fp = SPIFFS.open(scmd, "r");
            server.streamFile(fp, "text/plan");
            fp.close();
        } else {
            server.send(500,"text/plan", "file none");
        }
        return true;
        
    } else if (path.indexOf("/upload_file_") == 0) {
        // 受け取ったファイルを保存 ( /upload_file_{ファイル名} でアクセス)
        // POST じゃ無ければNG
        if (server.method() != HTTP_POST) {
            server.send(500,"text/plan", "not post request");
            return true;
        }
        // パスの後ろがファイル名
        String file_path = "/" + path.substring(13);
        file_path.toCharArray(scmd, 64);
        // テキストを受け取ってファイルに保存
        String post_data = server.arg("plain");
        r = common_cls.write_file(scmd, post_data);
        if (r == 0) {
            server.send(500,"text/plan", "file write error");
            return true;
        }
        server.send(200,"text/plan", "OK");
        return true;

    } else if (path.indexOf("/delete_file_") == 0) {
        // 指定されたファイルを削除( /delete_file?{ファイル名} でアクセス)
        // パスの後ろがファイル名
        String file_path = path.substring(13);
        file_path.toCharArray(scmd, 64);
        // 削除処理
        if (!common_cls.remove_file(scmd)) {
            server.send(500,"text/plan", "file delete error");
            return true;
        }
        server.send(200,"text/plan", "OK");
        return true;

    } else if (path.indexOf("/upload_setting_json_reload") == 0) {
        // 受け取った設定を保存して設定終了
        // POST じゃ無ければNG
        if (server.method() != HTTP_POST) {
            server.send(500,"text/plan", "not post request");
            return true;
        }
        // テキストを受け取ってファイルに保存
        String post_data = server.arg("plain");
        r = common_cls.write_file(SETTING_JSON_PATH, post_data);
        if (r == 0) {
            server.send(500,"text/plan", "file write error");
            return true;
        }
        common_cls.change_mode(1); // 設定モードで再起動

    } else if (path.indexOf("/upload_setting_json") == 0) {
        // 受け取った設定を保存して設定終了
        // POST じゃ無ければNG
        if (server.method() != HTTP_POST) {
            server.send(500,"text/plan", "not post request");
            return true;
        }
        // テキストを受け取ってファイルに保存
        String post_data = server.arg("plain");
        r = common_cls.write_file(SETTING_JSON_PATH, post_data);
        if (r == 0) {
            server.send(500,"text/plan", "file write error");
            return true;
        }
        common_cls.change_mode(0); // キーボードモードに切り替え

    } else if (path.indexOf("/init_setting_json") == 0) {
        // 設定の初期化
        if (common_cls.create_setting_json()) {
            // 成功
            server.send(200,"text/plan", "OK");
        } else {
            // 失敗
            server.send(500,"text/plan", "NG");
        }

    } else if (path.indexOf("/get_ap_list") == 0) {
        // WIFIのアクセスポイントのリスト教えて
        server.send(200,"text/json", get_wifi_ap_list_json());
        return true;
        
    } else if (path.indexOf("/wifi_conn_check") == 0) {
        // wifiに接続できるか確認
        // POST じゃ無ければNG
        if (server.method() != HTTP_POST) {
            server.send(500,"text/plan", "not post request");
            return true;
        }
        // パラメーターのWIFI設定を受け取る
        String post_data = server.arg("plain");
        String wifi_setting[3] = {"\0"};
        char wifi_ssid[64];
        char wifi_pass[64];
        n = common_cls.split(post_data, '\n', wifi_setting);
        if (n < 2) {
            server.send(500,"text/plan", "param error");
            return true;
        }
        wifi_setting[0].toCharArray(wifi_ssid, 64);
        wifi_setting[1].toCharArray(wifi_pass, 64);
        ESP_LOGD(LOG_TAG, "wifi connect : %S %S\r\n", wifi_ssid, wifi_pass);
        // wifi 接続
        WiFi.disconnect(false, true);
        WiFi.begin(wifi_ssid, wifi_pass);
        n = 0;
        r = 0;
        while (true) {
            if (WiFi.status() != WL_CONNECTED) {
                ESP_LOGD(LOG_TAG, ".");
                delay(500);
                n++;
                if (n >= 30) break;
            } else {
                ESP_LOGD(LOG_TAG, "\r\nconnect complate!\r\n");
                r = 1;
                break;
            }
        }
        ESP_LOGD(LOG_TAG, "\r\nconnect status: %D\r\n", r);
        // 接続終了
        // WiFi.disconnect(false, false); // wifi事態をOFFにするか / 今回設定したwifi設定を削除するか
        if (r > 0) {
            server.send(200,"text/plan", "OK");
        } else {
            server.send(200,"text/plan", "NG");
        }
        return true;


    } else if (path.indexOf("/end_setting") == 0) {
        // キーボードモードに切り替えて
        common_cls.change_mode(0); // キーボードモードに切り替え

    }
    return false;
}


// コンストラクタ
AzSetting::AzSetting() {
}

// wifi 初期処理
void start_wifi() {
    int i, j;
    
    //無線LAN接続AP(アクセスポイント)モード
    WiFi.mode(WIFI_AP_STA);
    String ap_pass = setting_obj["ap"]["pass"].as<String>();
    char ap_pass_char[32];
    ap_pass.toCharArray(ap_pass_char, 32);
    WiFi.softAP(eep_data.ap_ssid, ap_pass_char);

    // DNSサーバー起動
    IPAddress myIP = WiFi.softAPIP();
    dnsServer.start(DNS_PORT, "*", myIP); // 全ドメインを自分に向ける
    ESP_LOGD(LOG_TAG, "server ip : %S", toStringIp(myIP));

    // OTA 用updater
    server.on("/firmware_update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        delay(2000);
        ESP.restart();
    }, []() {
        // ステータスLEDをファームウェア更新中にする
        status_led_mode = 3;
        // ファイルを受け取ってファームウェアを更新
        HTTPUpload& upload = server.upload();
        if (upload.status == UPLOAD_FILE_START) {
            ESP_LOGD(LOG_TAG, "Update: file start %s\n", upload.filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            /* flashing firmware to ESP*/
            ESP_LOGD(LOG_TAG, "Update: write %D\n", upload.currentSize);
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            ESP_LOGD(LOG_TAG, "Update: end\n");
            if (Update.end(true)) { //true to set the size to the current progress
                ESP_LOGD(LOG_TAG, "Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
                Update.printError(Serial);
            }
            // ステータスLED消灯
            status_led_mode = 0;
        }
    });
    // httpサーバーそれ以外のページ
    server.onNotFound([]() {
        if (!handleUrl(server.uri())) {
            captivePortal(); //ESP32のページにリダイレクトする capative portalの仕組み
        }
    });
    // httpサーバー起動
    server.begin();

}


// 初期処理
void AzSetting::start_setting() {
    // ステータスLED wifi接続中
    status_led_mode = 4;

    // wifi 初期化
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    start_wifi();
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );

    // ステータスLED設定
    status_led_mode = 2;
}

// キーが押された時の処理
void AzSetting::key_down_action(int key_num) {
    // 最後に押されたキーを格納しておく
    last_key_down = key_num;
}

// 前回のキーのステータスと比較して変更があった物だけ処理を実行する
void AzSetting::key_action_exec() {
    int i;
    for (i=0; i<key_input_length; i++) {
        if (common_cls.input_key_last[i] != common_cls.input_key[i]) {
            if (common_cls.input_key[i]) {
                // キーは押された
                key_down_action(i);
            }
        }
    }
}

// 設定モード中のループ処理
void AzSetting::loop_exec() {
    // dnsサーバー定期処理
    dnsServer.processNextRequest();
    // httpサーバー定期処理
    server.handleClient();

    // 現在のキーの状態を取得
    common_cls.key_read();
    // キー入力のアクション実行
    key_action_exec();
    // 現在のキーの状態を前回部分にコピー
    common_cls.key_old_copy();
    delay(10);
}
