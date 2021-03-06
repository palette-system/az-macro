#include "Arduino.h"
#include "az_keyboard.h"
#include "az_common.h"
#include "src/lib/ble_keyboard_jis.h"
#include "src/lib/custom_func.h"
#include "src/lib/ankey.h"
#include "src/lib/dakey.h"
#include "src/lib/paw3204.h"

// BLEキーボードクラス
BleKeyboardJIS bleKeyboard(BLUETOOTH_SEARCH_NAME);

// 拡張関数クラス
CustomFunc my_function = CustomFunc();

// トラックボールクラス
Paw3204 pawTrackball = Paw3204();

// 暗記ボタンクラス
Ankey ankeycls = Ankey();

// 打鍵カウントクラス
Dakey dakeycls = Dakey();


// コンストラクタ
AzKeyboard::AzKeyboard() {
}

// キーボードとして処理開始
void AzKeyboard::start_keyboard() {
    // ステータスLED wifi接続中
    status_led_mode = 4;

    // メモリ空けるためファイルシステム終了
    // SPIFFS.end();

    // EEPROMも終了
    EEPROM.end();

    // Wifi 接続
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    common_cls.wifi_connect();
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    
    // bluetoothキーボード開始
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    bleKeyboard.begin();
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    
    // キーボードの言語を指定(日本語=0/ US=1)
    bleKeyboard.set_keyboard_language(setting_obj["keyboard_language"].as<signed int>());

    // ステータスLED点灯
    status_led_mode = 1;

    // キーの入力状態初期化
    common_cls.key_read();
    common_cls.key_old_copy();

    // マウス移動リスト初期化
    press_mouse_list_clean();

    // バッテリーレベル
    // bleKeyboard.setBatteryLevel(100);

    // 暗記ボタン初期化
    ankeycls.begin(this);

    // 打鍵クラス初期化
    dakeycls.begin();

    // 各ユニット初期化
    start_unit();

    press_key_all_clear = -1;

    // 拡張関数 開始処理
    my_function.begin();

    // 液晶は待ち受け画像
    if (common_cls.on_tft_unit()) disp->view_type = DISP_TYPE_STANDBY;
  
}

// 各ユニットの初期化
void AzKeyboard::start_unit() {
    if (option_type_int == 2) {
        // トラックボール
        pawTrackball.begin(27, 12);
    }
}

// 前回のキーのステータスと比較して変更があった物だけ処理を実行する
void AzKeyboard::key_action_exec() {
    // 暗記データのキー入力中は何もしない
    if (ankeycls.ankey_flag == 2) return;
    // キー入力チェック
    int i;
    for (i=0; i<key_input_length; i++) {
        if (common_cls.input_key_last[i] != common_cls.input_key[i]) {
            if (common_cls.input_key[i]) {
                // キーが押された
                key_down_action(i); // 押された時の動作
                rgb_led_cls.set_led_buf(i, 1); // LED に押したよを送る
                ankeycls.key_down(i); // 暗記クラスに押したよを送る(暗記用)
                // 打鍵数カウントアップ
                common_cls.key_count[i]++;
                common_cls.key_count_total++;
            } else {
                // キーは離された
                key_up_action(i); // 離された時の動作
                rgb_led_cls.set_led_buf(i, 0); // LED に離したよを送る
                ankeycls.key_up(i); // 暗記クラスに離したよを送る(暗記用)
            }
        }
    }
}

// キー連打処理
void AzKeyboard::key_repeat_exec() {
    int i, k;
    for (i=0; i<PRESS_KEY_MAX; i++) {
        if (press_key_list[i].key_num < 0) continue;
        if (press_key_list[i].action_type == 1 && 
            press_key_list[i].repeat_interval >= 0 &&
            press_key_list[i].repeat_interval <= 50) { // 通常キー入力で連打設定がある
            if (press_key_list[i].repeat_index >= press_key_list[i].repeat_interval) {
                k = press_key_list[i].key_id;
                if (k & MOUSE_CODE) {
                    // マウスボタンだった場合
                    bleKeyboard.mouse_press(k - MOUSE_CODE); // マウスボタンを押す
                    delay(10);
                } else {
                    // キーコードだった場合
                    bleKeyboard.press_raw(k); // キーを押す
                    delay(10);
                }
                press_key_list[i].repeat_index = 0;
            }
            if (press_key_list[i].repeat_index == 0) {
                // 押してスグキーを離す
                if (k & MOUSE_CODE) {
                    // マウスボタンだった場合
                    bleKeyboard.mouse_release(k - MOUSE_CODE); // マウスボタンを離す
                } else {
                    // キーコードだった場合
                    bleKeyboard.release_raw(k); // キーを離す
                }
            }
            press_key_list[i].repeat_index++;
        }
    }
}

// キーを押しましたリストに追加
// 
void AzKeyboard::press_key_list_push(int action_type, int key_num, int key_id, int layer_id, int repeat_interval) {
    int i, k = -1;
    // 既にリストに自分がいないかチェック(離してスグ押した時とかに自分がいる可能性がある)
    for (i=0; i<PRESS_KEY_MAX; i++) {
        if (press_key_list[i].key_num == key_num && press_key_list[i].key_id == key_id) {
            k = i;
            break;
        }
    }
    // 空いている所を探す
    if (k < 0) {
        for (i=0; i<PRESS_KEY_MAX; i++) {
            if (press_key_list[i].key_num < 0) {
                k = i;
                break;
            }
        }
    }
    // キーデータを入れる(入れる場所が無ければ何もしない)
    if (k >= 0) {
        press_key_list[k].action_type = action_type;
        press_key_list[k].key_num = key_num;
        press_key_list[k].key_id = key_id;
        press_key_list[k].layer_id = layer_id;
        press_key_list[k].unpress_time = 0;
        press_key_list[k].repeat_interval = repeat_interval;
        press_key_list[k].repeat_index = 0;
    }
}


// マウス移動リストを空にする
void AzKeyboard::press_mouse_list_clean() {
    int i;
    for (i=0; i<PRESS_MOUSE_MAX; i++) {
        press_mouse_list[i].key_num = -1;
        press_mouse_list[i].move_x = 0;
        press_mouse_list[i].move_y = 0;
        press_mouse_list[i].move_speed = 0;
        press_mouse_list[i].move_index = 0;
    }
}


// マウス移動リストに追加
void AzKeyboard::press_mouse_list_push(int key_num, short move_x, short move_y, short move_speed) {
    int i;
    for (i=0; i<PRESS_MOUSE_MAX; i++) {
        // データが入っていれば次
        if (press_mouse_list[i].key_num >= 0) continue;
        // 空いていればデータを入れる
        press_mouse_list[i].key_num = key_num;
        press_mouse_list[i].move_x = move_x;
        press_mouse_list[i].move_y = move_y;
        press_mouse_list[i].move_speed = move_speed;
        press_mouse_list[i].move_index = 0;
        break;
    }
}


// マウス移動リストから削除
void AzKeyboard::press_mouse_list_remove(int key_num) {
    int i;
    for (i=0; i<PRESS_MOUSE_MAX; i++) {
        // 該当のキーで無ければ何もしない
        if (press_mouse_list[i].key_num != key_num) continue;
        // 該当のキーのデータ削除
        press_mouse_list[i].key_num = -1;
        press_mouse_list[i].move_x = 0;
        press_mouse_list[i].move_y = 0;
        press_mouse_list[i].move_speed = 0;
        press_mouse_list[i].move_index = 0;
    }
}


// マウス移動処理
void AzKeyboard::move_mouse_loop() {
    int i;
    int mx, my;
    for (i=0; i<PRESS_MOUSE_MAX; i++) {
        // 入力無しならば何もしない
        if (press_mouse_list[i].key_num < 0) continue;
        if (press_mouse_list[i].move_speed == 0 && press_mouse_list[i].move_index == 0) {
            // スピード0なら最初の1回だけ移動
            bleKeyboard.mouse_move(press_mouse_list[i].move_x, press_mouse_list[i].move_y, 0, 0);
        } else {
            // スピードで割った分だけ移動
            mx = ((press_mouse_list[i].move_x * press_mouse_list[i].move_speed) / 100);
            my = ((press_mouse_list[i].move_y * press_mouse_list[i].move_speed) / 100);
            bleKeyboard.mouse_move(mx, my, 0, 0);
            delay(5);
        }
        // index をカウント
        if (press_mouse_list[i].move_index < 1000) press_mouse_list[i].move_index++;
    }
}


// WEBフックを送信する
void AzKeyboard::send_webhook(const JsonObject &key_set) {
    if (!wifi_conn_flag) {
        send_string("wifi not connected.");
        return;
    }
    // 液晶にwebhook中を表示する
    if (common_cls.on_tft_unit()) disp->view_webhook();
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    char res_char[1024];
    // httpリクエスト送信
    String r = common_cls.send_webhook(key_set);
    r.toCharArray(res_char, 1024);
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    ESP_LOGD(LOG_TAG, "http res: %S\n", res_char);
    // 液晶に待ち受け画像を表示する
    if (common_cls.on_tft_unit()) disp->view_standby_image();
    send_string(res_char);
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
}

// テキスト入力
void AzKeyboard::send_string(char *send_char) {
    // Bluetooth接続してなければ何もしない
    if (!bleKeyboard.isConnected()) return;
    int i = 0;
    // 全て離す
    bleKeyboard.releaseAll();
    while (send_char[i] > 0) {
        // 連続して同じ文字の入力だったら一回離す
        if (i > 0 && send_char[i] == send_char[i - 1]) {
            bleKeyboard.releaseAll();
            delay(70);
        }
        // 指定したキーだけ押す
        bleKeyboard.press_set(send_char[i]);
        delay(70);
        i++;
    }
    // 全て離す
    bleKeyboard.releaseAll();
}

// キーが押された時の処理
void AzKeyboard::key_down_action(int key_num) {
    int i, m, k, r, lid;
    // キーの設定取得
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    JsonObject key_set = common_cls.get_key_setting(select_layer_no, key_num);
    ESP_LOGD(LOG_TAG, "mmm: %D %D\n", heap_caps_get_free_size(MALLOC_CAP_32BIT), heap_caps_get_free_size(MALLOC_CAP_8BIT) );
    // キーの押された時の設定があるか確認
    if (key_set.isNull() || !key_set.containsKey("press") || !key_set["press"].containsKey("action_type")) {
        // 設定が無ければ何もしない
        return;
    }
    // キーが押された時の動作タイプ取得
    int action_type = key_set["press"]["action_type"].as<signed int>();
    // キーボードの接続が無ければ何もしない(レイヤー切り替え、WEBフック以外)
    if (action_type != 3 && action_type != 4 && action_type != 6 && action_type != 7 && action_type != 8 && !bleKeyboard.isConnected()) {
        // 押したよリストに追加だけする
        press_key_list_push(-1, key_num, -1, select_layer_no, -1);
        // 拡張メソッド実行
        my_function.key_press(key_num, key_set);
        return;
    }
    // 打鍵QRコード表示中は何もしない
    if (common_cls.on_tft_unit() && disp->_qr_flag) return;
    // 動作タイプ別の動作
    if (action_type == 1) {
        // 通常キー入力
        m = key_set["press"]["key"].size();
        r = -1;
    	if (key_set["press"].containsKey("repeat_interval")) r = key_set["press"]["repeat_interval"];
        for (i=0; i<m; i++) {
            k = key_set["press"]["key"][i].as<signed int>();
            if (r < 0 || r > 50) {
                if (k & MOUSE_CODE) {
                    // マウスボタンだった場合
                    bleKeyboard.mouse_press(k - MOUSE_CODE); // マウスボタンを押す
                } else {
                    // キーコードだった場合
                    bleKeyboard.press_raw(k); // キーを押す
                }
            }
            // キー押したよリストに追加
            press_key_list_push(action_type, key_num, k, select_layer_no, r);
            ESP_LOGD(LOG_TAG, "key press : %D %D\r\n", key_num, k);
        }

    } else if (action_type == 2) {
        // 固定テキストの入力
        String text_str = key_set["press"]["text"].as<String>();
        char text_char[512];
        text_str += "\0";
        text_str.toCharArray(text_char, 512);
        send_string(text_char); // 特定の文章を送る
        // キー押したよリストに追加
        press_key_list_push(action_type, key_num, -1, select_layer_no, -1);

    } else if (action_type == 3) {
        // マウス移動リストクリア
        press_mouse_list_clean();
        // レイヤーの切り替え
        lid = key_set["press"]["layer"].as<signed int>();
        m = select_layer_no;
        select_layer_no = lid;
        // 最後に押されたレイヤーボタン設定
        last_select_layer_key = key_num;
        // キー押したよリストに追加
        press_key_list_push(action_type, key_num, -1, m, -1);
        ESP_LOGD(LOG_TAG, "key press layer : %D %D\r\n", key_num, lid);

    } else if (action_type == 4) {
        // webフック
        send_webhook(key_set["press"]["webhook"]);
        
    } else if (action_type == 5) {
        // マウス移動
        press_mouse_list_push(key_num,
            key_set["press"]["move"]["x"].as<signed int>(),
            key_set["press"]["move"]["y"].as<signed int>(),
            key_set["press"]["move"]["speed"].as<signed int>());
        // キー押したよリストに追加
        press_key_list_push(action_type, key_num, -1, select_layer_no, -1);

    } else if (action_type == 6) {
        // 暗記ボタン
        ankeycls.ankey_down(select_layer_no, key_num);
        // キー押したよリストに追加
        press_key_list_push(action_type, key_num, -1, select_layer_no, -1);

    } else if (action_type == 7 && ankeycls.ankey_flag == 0) {
        // LED設定ボタン(暗記処理中は動作無視)
        m = key_set["press"]["led_setting_type"].as<signed int>();
        if (m == 0) {
            // ON / OFF
            rgb_led_cls.setting_status();
        } else if (m == 1) {
            // 明るさアップ
            rgb_led_cls.setting_bright_up();
        } else if (m == 2) {
            // 明るさダウン
            rgb_led_cls.setting_bright_down();
        } else if (m == 3) {
            // 色変更
            rgb_led_cls.setting_color_type();
        } else if (m == 4) {
            // 光らせ方変更
            rgb_led_cls.setting_shine_type();
        }

    } else if (action_type == 8 && ankeycls.ankey_flag == 0) {
        // 打鍵設定ボタン(暗記処理中は動作無視)
        m = key_set["press"]["dakagi_settype"].as<signed int>();
        if (m == 0) {
            // サーモグラフ表示
            disp->view_dakagi_thermo_on();
        } else if (m == 1) {
            // 打鍵数をファイルに保存
            dakeycls.save_dakey(0);
            // QRコード表示
            disp->view_dakagi_qr_on();
        } else if (m == 2) {
            // 自動保存設定を変更
            dakeycls.set_auto_save_change();
        } else if (m == 3) {
            // 打鍵数をファイルに保存
            dakeycls.save_dakey(1);
        }
    }

    // 拡張メソッド実行
    my_function.key_press(key_num, key_set);
    
}

// キーが離された時の処理
void AzKeyboard::key_up_action(int key_num) {
    int i, action_type;
    for (i=0; i<PRESS_KEY_MAX; i++) {
        if (press_key_list[i].key_num != key_num) continue;
        ESP_LOGD(LOG_TAG, "key release action_type: %D - %D - %D\r\n", key_num, i, press_key_list[i].action_type);
        action_type = press_key_list[i].action_type;
        // キーボードの接続が無ければ何もしない(レイヤー切り替え、WEBフック以外)
        if (action_type != 3 && action_type != 4 && action_type != 6 && action_type != 7 && action_type != 8 && !bleKeyboard.isConnected()) {
            // 離したよだけやる、離したよカウンターカウント開始
            press_key_list[i].unpress_time = 1;
            // 拡張メソッド実行
            my_function.key_release(press_key_list[i].key_num, press_key_list[i]);
            continue;
        }
        if (action_type == 1) {
            // 通常入力
            if (press_key_list[i].key_id & MOUSE_CODE) {
                // マウスボタンだった場合
                bleKeyboard.mouse_release(press_key_list[i].key_id - MOUSE_CODE); // マウスボタンを離す
            } else {
                // キーコードだった場合
                bleKeyboard.release_raw(press_key_list[i].key_id); // キーを離す
            }
            ESP_LOGD(LOG_TAG, "key release : %D\r\n", press_key_list[i].key_id);
        } else if (action_type == 3) {
            // レイヤー選択
            // 最後に押されたレイヤーボタンならばレイヤーを解除
            ESP_LOGD(LOG_TAG, "key release : last_select_layer_key : %D\r\n", last_select_layer_key);
            if (last_select_layer_key == key_num) {
                select_layer_no = default_layer_no;
                last_select_layer_key = -1;
            }
        } else if (action_type == 5) {
            // マウス移動ボタン
            press_mouse_list_remove(key_num); // 移動中リストから削除
        } else if (action_type == 6) {
            // 暗記ボタン
            ankeycls.ankey_up(press_key_list[i].layer_id, key_num);
        }
        // スグクリアしない。離したよカウンターカウント開始
        press_key_list[i].unpress_time = 1;
        // 拡張メソッド実行
        my_function.key_release(press_key_list[i].key_num, press_key_list[i]);
        
    }
}

// 押されているキーの情報を全てリセットする
void AzKeyboard::press_data_reset() {
    int i;
    select_layer_no = default_layer_no;
    last_select_layer_key = -1;
    for (i=0; i<PRESS_KEY_MAX; i++) {
        press_key_list[i].action_type = -1;
        press_key_list[i].key_num = -1;
        press_key_list[i].key_id = -1;
        press_key_list[i].layer_id = -1;
        press_key_list[i].unpress_time = -1;
        press_key_list[i].repeat_interval = -1;
        press_key_list[i].repeat_index = -1;
    }
    for (i=0; i<key_input_length; i++) {
        common_cls.input_key_last[i] = 0;
        common_cls.input_key[i] = 0;
    }
    bleKeyboard.releaseAll();
    press_key_all_clear = -1;
    this->press_mouse_list_clean();
}

// 押されたキーの情報クリア
void AzKeyboard::press_data_clear() {
    int i;
    int press_count_start = 0, press_count_end = 0;
    // 処理前の押されたままキー数取得
    for (i=0; i<PRESS_KEY_MAX; i++) {
        if (press_key_list[i].action_type == 1 && !(press_key_list[i].key_id & MOUSE_CODE) &&  press_key_list[i].key_num >= 0) {
            press_count_start++;
        }
    }
    // 離したよカウントを加算していき閾値を超えたらクリア
    for (i=0; i<PRESS_KEY_MAX; i++) {
        if (press_key_list[i].key_num < 0 || press_key_list[i].unpress_time < 1) continue;
        press_key_list[i].unpress_time++;
        if (press_key_list[i].unpress_time > 10) {
            if (press_key_list[i].action_type == 1) {
                // 通常入力(キー離したよをもう一回送る)
                bleKeyboard.release_raw(press_key_list[i].key_id); // キーを離す
                ESP_LOGD(LOG_TAG, "key release : %D\r\n", press_key_list[i].key_id);
            }
            // 押したよデータクリア
            press_key_list[i].action_type = -1;
            press_key_list[i].key_num = -1;
            press_key_list[i].key_id = -1;
            press_key_list[i].layer_id = -1;
            press_key_list[i].unpress_time = -1;
            press_key_list[i].repeat_interval = -1;
            press_key_list[i].repeat_index = -1;
        }
    }
    // 処理後の押されたままキー数取得
    for (i=0; i<PRESS_KEY_MAX; i++) {
        if (press_key_list[i].key_num >= 0) {
            press_count_end++;
        }
    }
    // キーの入力があったならオールクリアカウントリセット
    if (press_count_start > 0) {
        press_key_all_clear = -1;
    }
    // 押してるキー数が0になったらオールクリアカウント開始
    if (press_count_start > 0 && press_count_end == 0) {
        press_key_all_clear = 1;
    }
    // オールクリアカウントが閾値を超えたらオールクリア送信
    if (press_key_all_clear > 0) {
        press_key_all_clear++;
        if (press_key_all_clear > 10) {
            bleKeyboard.releaseAll();
            press_key_all_clear = -1;
        }
    }
    
}

// ユニットごとの定期処理
void AzKeyboard::unit_loop_exec(void) {
    int x, y;
    if (option_type_int == 2) {
        // トラックボール
        paw3204_xy p = pawTrackball.getxy();
        if (p.x > 2 || p.x < -2 || p.y > 2 || p.y < -2) {
            if (trackball_direction == 0) {
                // 向き 上
                x = p.y * trackball_speed * -1;
                y = p.x * trackball_speed;
            } else if (trackball_direction == 1) {
                // 向き 右
                x = p.x * trackball_speed;
                y = p.y * trackball_speed;
            } else if (trackball_direction == 2) {
                // 向き 下
                x = p.y * trackball_speed;
                y = p.x * trackball_speed * -1;
            } else if (trackball_direction == 3) {
                // 向き 左
                x = p.x * trackball_speed * -1;
                y = p.y * trackball_speed * -1;
            }
            bleKeyboard.mouse_move(x / 40, y / 40, 0, 0);
        }
    }
}

// 押された所を1にする

// 定期実行の処理
void AzKeyboard::loop_exec(void) {
  unsigned long n;
  n = millis();
  while (true) {

    // 現在のキーの状態を取得
    common_cls.key_read();

    // キー入力のアクション実行
    key_action_exec();

    // 暗記ボタン定期処理
    ankeycls.loop_exec();

    // キー連打処理
    key_repeat_exec();

    // マウス移動処理
    move_mouse_loop();

    // キー入力クリア処理
    press_data_clear();

    // 打鍵数定期処理(自動保存など)
    dakeycls.loop_exec();

    // 各ユニットの定期処理
    unit_loop_exec();

    // RGB_LEDを制御する定期処理
    rgb_led_cls.rgb_led_loop_exec();

    // ディスプレイ表示処理
    if (common_cls.on_tft_unit()) {
        disp->loop_exec();
    }

    // 拡張関数 ループ処理
    my_function.loop();

    // 現在のキーの状態を前回部分にコピー
    common_cls.key_old_copy();

    delay(5);
  }
}
