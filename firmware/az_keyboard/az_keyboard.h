#ifndef AzKeyboard_h
#define AzKeyboard_h

#include "az_common.h"


// クラスの定義
class AzKeyboard
{
    public:
        AzKeyboard();   // コンストラクタ
        void start_keyboard(); // キーボードとして処理開始
        void loop_exec();         // キーボード定期処理
        void key_action_exec(); // ステータスが変更されたキーのアクションを実行する
        void send_webhook(const JsonObject &key_set); // WEBフックを送信する
        void send_string(char *send_char); // テキストを送信する
        void key_down_action(int key_num); // キーが押された時のアクション
        void key_up_action(int key_num); // キーが離された時のアクション
        void press_key_list_push(int action_type, int key_num, int key_id, int layer_id); // キーを押しましたリストに追加
        void press_data_clear(); // キーを押したままリストをクリア
    
    private:
};

#endif
