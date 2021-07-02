#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include <ESPmDNS.h>
#include <DNSServer.h>

#include "index_bin.h"


// ステータス表示用ピン番号
int status_pin;
int status_led_mode;
int status_led_bit;

//timer オブジェクト
hw_timer_t *timer = NULL;


//無線LANのサーバー設定
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

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
    digitalWrite(status_pin, set_bit);
}

// IP アドレスデータを表示用の文字列にする
String toStringIp(IPAddress ip) {
    String res = "";
    for (int i = 0; i < 3; i++) {
        res += String((ip >> (8 * i)) & 0xFF) + ".";
    }
    res += String(((ip >> 8 * 3)) & 0xFF);
    return res;
}

//無効リクエストはすべてESP32に向ける
void captivePortal() {
    server.sendHeader("Location", "http://"+toStringIp(WiFi.softAPIP())+"/", true);
    server.send(302, "text/plain", "");
    server.client().stop();
}


// wifi 初期処理
void start_wifi() {
    int i, j;
    char text_buf[255];
    
    //無線LAN接続AP(アクセスポイント)モード
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("az-macro", "");

    // DNSサーバー起動
    IPAddress myIP = WiFi.softAPIP();
    dnsServer.start(DNS_PORT, "*", myIP); // 全ドメインを自分に向ける
    ESP_LOGD(LOG_TAG, "server ip : %S", toStringIp(myIP));

    // メインページ
    server.on("/", []() {
        server.send(200, "text/html", index_bin);
    });
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
        ESP_LOGD(LOG_TAG, "onNotFound: %S", server.uri().c_str());
        // メインページにリダイレクト
        server.sendHeader("Location", "http://"+toStringIp(WiFi.softAPIP())+"/", true);
        server.send(302, "text/plain", "");
        server.client().stop();
    });
    // httpサーバー起動
    server.begin();
}



void setup() {
    Serial.begin(115200);
    // ステータス表示用のLED
    status_pin = 32;
    status_led_mode = 0;
    status_led_bit = 0;
    pinMode(status_pin, OUTPUT);
    digitalWrite(status_pin, 0);
    timer = timerBegin(0, 80, true); //timer=1us
    timerAttachInterrupt(timer, &status_led_write, true);
    timerAlarmWrite(timer, 100000, true); // 100ms
    timerAlarmEnable(timer);
    // 設定モード開始
    status_led_mode = 4;
    start_wifi();
    status_led_mode = 2;
}


// ループ処理本体
void loop() {
    // dnsサーバー定期処理
    dnsServer.processNextRequest();
    // httpサーバー定期処理
    server.handleClient();
}
