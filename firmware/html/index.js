// JavaScript 圧縮ツール
//   https://tm-webtools.com/Tools/jsMinify

// jquery もどき
function $(id) {
    return document.getElementById(id);
}
// 要素表示
function show(id) {
    if (!$(id)) return;
    $(id).style.display = "block";
}
// 要素非表示
function hide(id) {
    if (!$(id)) return;
    $(id).style.display = "none";
}
// HTML表示
function set_html(id, html) {
    $(id).innerHTML = html;
}
// オブジェクトのクローン作製
function obj_clone(obj) {
    return JSON.parse(JSON.stringify(obj));
}
// GETメソッド送信
function ajax(path, cb_func) {
    var req = new XMLHttpRequest();
    req.open("GET", path, true); // 第3パラメータ true で非同期
    req.setRequestHeader('Pragma', 'no-cache');
    req.setRequestHeader('Cache-Control', 'no-cache');
    req.setRequestHeader('If-Modified-Since', 'Thu, 01 Jun 1970 00:00:00 GMT');
    req.onreadystatechange = function() {
        if (req.readyState < 4) return;
        if(req.status == 200 ) {
            cb_func(true, req.responseText, req);
        } else {
            cb_func(false, req);
        }
    }
    req.send();
}

// POSTメソッド送信
function ajax_post(path, send_data, cb_func) {
    var req = new XMLHttpRequest();
    req.open("POST", path, true); // 第3パラメータ true で非同期
    req.setRequestHeader("Content-Type", "text/plain");
    req.setRequestHeader('Pragma', 'no-cache');
    req.setRequestHeader('Cache-Control', 'no-cache');
    req.setRequestHeader('If-Modified-Since', 'Thu, 01 Jun 1970 00:00:00 GMT');
    req.onreadystatechange = function() {
        if (req.readyState < 4) return;
        if(req.status == 200 ) {
            cb_func(true, req.responseText, req);
        } else {
            cb_func(false, req);
        }
    }
    req.send(send_data);
}


if (!window.mst) window.mst = {};


// キーボード画像上のキーの位置
mst.key_pattern = {};

// キーボードの言語リスト
mst.key_language_list = [
    "日本語 キーボード",
    "US キーボード"
];

// キーボードのタイプデフォルト
mst.key_pattern_default = "az_macro";

// 各キーボード別の設定
mst.key_pattern_list = {};

// AZ macro 標準
mst.key_pattern_list["az_macro"] = {
    "name": "AZ Macro",
    "pin": {
        "row": [],
        "col": [],
        "direct": [23, 22, 21, 19, 16, 17, 5, 18],
        "touch": []
    },
    "size": {"width": 600, "height": 340},
    "keys": [
        {"id": 0, "x": 11, "y": 35, "width": 115, "height": 115 },
        {"id": 1, "x": 163, "y": 35, "width": 115, "height": 115 },
        {"id": 2, "x": 317, "y": 35, "width": 115, "height": 115 },
        {"id": 3, "x": 471, "y": 35, "width": 115, "height": 115 },
        {"id": 4, "x": 11, "y": 188, "width": 115, "height": 115 },
        {"id": 5, "x": 163, "y": 188, "width": 115, "height": 115 },
        {"id": 6, "x": 317, "y": 188, "width": 115, "height": 115 },
        {"id": 7, "x": 471, "y": 188, "width": 115, "height": 115 }
    ],
    "parts": [
        {
            "type": "polygon",
            "fill_color": "#666",
            "fill": true, // 塗りつぶし
            "path": [[2,2], [598,2], [598,338], [2,338]]
        },
        {
            "type": "polygon",
            "line_width": 4,
            "line_color": "black",
            "path": [[2,2], [598,2], [598,338], [2,338]]
        },
    ]
};

// AZ macro 踏みボタン
mst.key_pattern_list["az_macro_foot"] = {
    "name": "AZ Macro 踏みキー",
    "pin": {
        "row": [],
        "col": [],
        "direct": [23, 22, 21, 19, 16, 17, 5, 18, 25, 26],
        "touch": []
    },
    "size": {"width": 600, "height": 560},
    "keys": [
        {"id": 0, "x": 11, "y": 35, "width": 115, "height": 115 },
        {"id": 1, "x": 163, "y": 35, "width": 115, "height": 115 },
        {"id": 2, "x": 317, "y": 35, "width": 115, "height": 115 },
        {"id": 3, "x": 471, "y": 35, "width": 115, "height": 115 },
        {"id": 4, "x": 11, "y": 188, "width": 115, "height": 115 },
        {"id": 5, "x": 163, "y": 188, "width": 115, "height": 115 },
        {"id": 6, "x": 317, "y": 188, "width": 115, "height": 115 },
        {"id": 7, "x": 471, "y": 188, "width": 115, "height": 115 },
        {"id": 8, "x": 140, "y": 380, "width": 110, "height": 150 },
        {"id": 9, "x": 340, "y": 380, "width": 110, "height": 150 }
    ],
    "parts": [
        {
            "type": "polygon",
            "fill_color": "#666",
            "fill": true, // 塗りつぶし
            "path": [[2,2], [598,2], [598,338], [2,338]]
        },
        {
            "type": "polygon",
            "line_width": 4,
            "line_color": "black",
            "path": [[2,2], [598,2], [598,338], [2,338]]
        },
        {
            "type": "polygon",
            "fill_color": "#666",
            "fill": true, // 塗りつぶし
            "path": [[120,360], [480,360], [480,550], [120,550]]
        },
        {
            "type": "polygon",
            "line_width": 4,
            "line_color": "black",
            "path": [[120,360], [480,360], [480,550], [120,550]]
        },
    ]
};

// AZ macro 踏みボタン(反転)
mst.key_pattern_list["az_macro_foot_r"] = {
    "name": "AZ Macro 踏みキー(反転)",
    "pin": {
        "row": [],
        "col": [],
        "direct": [23, 22, 21, 19, 16, 17, 5, 18, 25, 26],
        "touch": []
    },
    "size": {"width": 600, "height": 560},
    "keys": [
        {"id": 0, "x": 11, "y": 35, "width": 115, "height": 115 },
        {"id": 1, "x": 163, "y": 35, "width": 115, "height": 115 },
        {"id": 2, "x": 317, "y": 35, "width": 115, "height": 115 },
        {"id": 3, "x": 471, "y": 35, "width": 115, "height": 115 },
        {"id": 4, "x": 11, "y": 188, "width": 115, "height": 115 },
        {"id": 5, "x": 163, "y": 188, "width": 115, "height": 115 },
        {"id": 6, "x": 317, "y": 188, "width": 115, "height": 115 },
        {"id": 7, "x": 471, "y": 188, "width": 115, "height": 115 },
        {"id": 8, "x": 140, "y": 380, "width": 110, "height": 150 },
        {"id": 9, "x": 340, "y": 380, "width": 110, "height": 150 }
    ],
    "parts": [
        {
            "type": "polygon",
            "fill_color": "#666",
            "fill": true, // 塗りつぶし
            "path": [[2,2], [598,2], [598,338], [2,338]]
        },
        {
            "type": "polygon",
            "line_width": 4,
            "line_color": "black",
            "path": [[2,2], [598,2], [598,338], [2,338]]
        },
        {
            "type": "polygon",
            "fill_color": "#666",
            "fill": true, // 塗りつぶし
            "path": [[120,360], [480,360], [480,550], [120,550]]
        },
        {
            "type": "polygon",
            "line_width": 4,
            "line_color": "black",
            "path": [[120,360], [480,360], [480,550], [120,550]]
        },
    ]
};


// キーのボタンリスト
mst.key_list = [
    {"key": "16385", "char": "LCk", "value": "Left Click"},
    {"key": "16386", "char": "RCk", "value": "Right Click"},
    {"key": "16388", "char": "MCk", "value": "Middle Click"},

    {"key": "224", "char": "LCtrl", "value": "Left Ctrl"},
    {"key": "225", "char": "LShift", "value": "Left Shift"},
    {"key": "226", "char": "LAlt", "value": "Left Alt"},
    {"key": "227", "char": "LGUI", "value": "Left GUI"},
    {"key": "228", "char": "RCtrl", "value": "Right Ctrl"},
    {"key": "229", "char": "RShift", "value": "Right Shift"},
    {"key": "230", "char": "RAlt", "value": "Right Alt"},
    {"key": "231", "char": "RGUI", "value": "Right GUI"},
    {"key": "82", "char": "↑", "value": "↑"},
    {"key": "81", "char": "↓", "value": "↓"},
    {"key": "80", "char": "←", "value": "←"},
    {"key": "79", "char": "→", "value": "→"},

    {"key": "42", "char": "BS", "value": "BackSpace"},
    {"key": "43", "char": "TAB", "value": "Tab"},
    {"key": "40", "char": "ENT", "value": "Enter"},
    {"key": "41", "char": "ESC", "value": "Esc"},
    {"key": "73", "char": "INS", "value": "Insert"},
    {"key": "74", "char": "HOME", "value": "Home"},
    {"key": "76", "char": "DEL", "value": "Delete"},
    {"key": "77", "char": "END", "value": "End"},
    {"key": "57", "char": "CPL", "value": "CaplLock"},
    {"key": "70", "char": "PrtSc", "value": "PrtSc"},
    {"key": "71", "char": "SL", "value": "ScrollLock"},
    {"key": "72", "char": "Pause", "value": "Pause"},
    {"key": "75", "char": "PgUp", "value": "PageUp"},
    {"key": "78", "char": "PgDw", "value": "PageDown"},
    {"key": "136", "char": "H/K", "value": "Hira / Kana"},

    {"key": "8193", "char": "EJC", "value": "Eject"},
    {"key": "8194", "char": "MNX", "value": "Media Next"},
    {"key": "8195", "char": "MPT", "value": "Media Previous"},
    {"key": "8196", "char": "MST", "value": "Media Stop"},
    {"key": "8197", "char": "MPL", "value": "Media Play / Pause"},
    {"key": "8198", "char": "MMT", "value": "Media Mute"},
    {"key": "8199", "char": "MVI", "value": "Media Volume +"},
    {"key": "8200", "char": "MVD", "value": "Media Volume -"},

    {"key": "138", "char": "変換", "value": "変換"},
    {"key": "139", "char": "無変換", "value": "無変換"},
    {"key": "144", "char": "Kana", "value": "Kana(mac)"},
    {"key": "145", "char": "Eisu", "value": "Eisu(mac)"},
    {"key": "101", "char": "App", "value": "App"},
    {"key": "102", "char": "Power", "value": "Power"},
    {"key": "58", "char": "F1", "value": "F1"},
    {"key": "59", "char": "F2", "value": "F2"},
    {"key": "60", "char": "F3", "value": "F3"},
    {"key": "61", "char": "F4", "value": "F4"},
    {"key": "62", "char": "F5", "value": "F5"},
    {"key": "63", "char": "F6", "value": "F6"},
    {"key": "64", "char": "F7", "value": "F7"},
    {"key": "65", "char": "F8", "value": "F8"},
    {"key": "66", "char": "F9", "value": "F9"},
    {"key": "67", "char": "F10", "value": "F10"},
    {"key": "68", "char": "F11", "value": "F11"},
    {"key": "69", "char": "F12", "value": "F12"},

    {"key": "44", "char": "SP", "value": "Space"},
    {"key": "4126", "char": "!", "value": "!"}, // 30 + shift
    {"key": "4148", "char": "*", "value": "*"}, // 52 + shift
    {"key": "4128", "char": "#", "value": "#"}, // 32 + shift
    {"key": "4129", "char": "$", "value": "$"}, // 33 + shift
    {"key": "4130", "char": "%", "value": "%"}, // 34 + shift
    {"key": "4132", "char": "'", "value": "'"}, // 36 + shift
    {"key": "52", "char": ":", "value": ":"},
    {"key": "4134", "char": ")", "value": ")"}, // 38 + shift
    {"key": "4133", "char": "(", "value": "("}, // 37 + shift
    {"key": "4142", "char": "~", "value": "~"}, // 46 + shift
    {"key": "4143", "char": "`", "value": "`"}, // 47 + shift
    {"key": "54", "char": ",", "value": ","},
    {"key": "45", "char": "-", "value": "-"},
    {"key": "4231", "char": "_", "value": "_"}, // 135 + shift
    {"key": "55", "char": ".", "value": "."},
    {"key": "56", "char": "/", "value": "/"},
    {"key": "4147", "char": "+", "value": "+"}, // 51 + shift
    {"key": "51", "char": ";", "value": ";"},
    {"key": "4150", "char": "<", "value": "<"}, // 54 + shift
    {"key": "46", "char": "^", "value": "^"},
    {"key": "4151", "char": ">", "value": ">"}, // 55 + shift
    {"key": "4152", "char": "?", "value": "?"}, // 56 + shift
    {"key": "4127", "char": "\"", "value": "\""}, // 31 + shift
    {"key": "47", "char": "@", "value": "@"},
    {"key": "50", "char": "]", "value": "]"},
    {"key": "4233", "char": "|", "value": "|"}, // 137 + shift
    {"key": "48", "char": "[", "value": "["},
    {"key": "4144", "char": "{", "value": "{"}, // 48 + shift
    {"key": "4146", "char": "}", "value": "}"}, // 50 + shift
    {"key": "4131", "char": "&", "value": "&"}, // 35 + shift
    {"key": "4141", "char": "=", "value": "="}, // 45 + shift
    {"key": "135", "char": "<span style='font-family: Arial;'>\\</span>", "value": "<span style='font-family: Arial;'>\\</span>"},
    {"key": "137", "char": "&yen;", "value": "&yen;"},
    {"key": "53", "char": "h/w", "value": "半角/全角"},

    {"key": "39", "char": "0", "value": "0"},
    {"key": "30", "char": "1", "value": "1"},
    {"key": "31", "char": "2", "value": "2"},
    {"key": "32", "char": "3", "value": "3"},
    {"key": "33", "char": "4", "value": "4"},
    {"key": "34", "char": "5", "value": "5"},
    {"key": "35", "char": "6", "value": "6"},
    {"key": "36", "char": "7", "value": "7"},
    {"key": "37", "char": "8", "value": "8"},
    {"key": "38", "char": "9", "value": "9"},

    {"key": "4",  "char": "a", "value": "a"},
    {"key": "5",  "char": "b", "value": "b"},
    {"key": "6",  "char": "c", "value": "c"},
    {"key": "7", "char": "d", "value": "d"},
    {"key": "8", "char": "e", "value": "e"},
    {"key": "9", "char": "f", "value": "f"},
    {"key": "10", "char": "g", "value": "g"},
    {"key": "11", "char": "h", "value": "h"},
    {"key": "12", "char": "i", "value": "i"},
    {"key": "13", "char": "j", "value": "j"},
    {"key": "14", "char": "k", "value": "k"},
    {"key": "15", "char": "l", "value": "l"},
    {"key": "16", "char": "m", "value": "m"},
    {"key": "17", "char": "n", "value": "n"},
    {"key": "18", "char": "o", "value": "o"},
    {"key": "19", "char": "p", "value": "p"},
    {"key": "20", "char": "q", "value": "q"},
    {"key": "21", "char": "r", "value": "r"},
    {"key": "22", "char": "s", "value": "s"},
    {"key": "23", "char": "t", "value": "t"},
    {"key": "24", "char": "u", "value": "u"},
    {"key": "25", "char": "v", "value": "v"},
    {"key": "26", "char": "w", "value": "w"},
    {"key": "27", "char": "x", "value": "x"},
    {"key": "28", "char": "y", "value": "y"},
    {"key": "29", "char": "z", "value": "z"}
];

// 入力タイプのリスト
mst.input_type_list = {
    "0": "動作無し",
    "1": "通常キー入力",
    "2": "テキスト入力",
    "3": "レイヤー切り替え",
    "4": "WEBフック",
    "5": "マウス移動"
};


// 設定JSONデータ
mst.setting_data = {
    "ap": {"pass": ""},
    "wifi": [{"ssid": "", "pass": ""}],
    "status_pin": 13,
    "keyboard_language": 0,
    "keyboard_type": mst.key_pattern_default,
    "keyboard_pin": {
        "row": [],
        "col": [],
        "direct": [15]
    },
    "default_layer": 0,
    "layers": {
        "layer_0": {
            "name": "レイヤー0",
            "keys": {
                "key_0": {
                    "press": {
                        "action_type": 1,
                        "key": [4]
                    },
                    "long_press": {},
                    "long_press_time": 0
                }
            }
        }
    }
};

// ファームウェアのバージョン
mst.firmware_version = "none";

// 今編集中のレイヤー
mst.edit_layer = 0;

// セレクト実行時のコールバック関数保持する変数
mst.select_exec_cbfunc = null;

// 編集中のwifiデータ
mst.wifi_edit_kid = -1;
mst.wifi_edit_data = null;

// キー設定編集中のデータ
mst.key_edit_kid = -1;
mst.key_edit_data = null;

// ファームウェア選択されたファイルの情報
mst.firmware_file_data = null;

// ボタン接触確認中かどうか
mst.switch_check_mode = 0;

// 設定終了かどうか
mst.end_flag = false;

// 終了タイプ
mst.end_type = 0;

// 初期処理
mst.init = function() {
    // スマホなら画面を90度回転
    if (mst.is_mobile()) mst.body_rotate();
    // ブラウザのボタン設定
    mst.browser_btn_control();
    // 読み込みメッセージ表示
    set_html("info_box", "読み込み中..");
    mst.view_box(["info_box"]);
    // ファームウェアのバージョン取得
    ajax("/firmware_version", function(stat, res) {
        if (stat && res) {
            mst.firmware_version = res;
        }
        // 設定JSON取得
        mst.get_setting_json();
    });
};

// ブラウザのボタン設定
mst.browser_btn_control = function() {
    // 戻るボタン無効化
    history.pushState(null, null,  location.href);
    window.addEventListener('popstate', function(e) {
        history.pushState(null, null,  location.href);
    });
    window.onpopstate = function(e) {
        if (mst.end_flag) return;
        updateBreadCrumbObservable();
    };
    window.onbeforeunload = function(e) {
        if (mst.end_flag) return false;
        return "別のページへ移動しますか？";
    };
};

// 設定JSON取得
mst.get_setting_json = function() {
    // 設定JSON取得
    ajax("/get_setting_json", function(stat, res) {
        if (!stat) {
            set_html("info_box", "キー設定 読み込み 失敗: /get_setting_json");
            mst.key_pattern = mst.key_pattern_list[ mst.key_pattern_default ];
            set_html("top_title", mst.key_pattern.name);
            mst.view_layer();
            return;
        }
        mst.setting_data = JSON.parse(res);
        set_html("info_box", "キー設定 読み込み 完了 ");
        // キーボードの設定を選ぶ
        if (mst.key_pattern_list[mst.setting_data.keyboard_type]) {
            mst.key_pattern = mst.key_pattern_list[mst.setting_data.keyboard_type];
        } else {
            mst.key_pattern = mst.key_pattern_list[ mst.key_pattern_default ];
        }
        // ページタイトルをキータイプにする
        set_html("top_title", mst.key_pattern.name);
        // デフォルトレイヤーを編集中にする
        mst.edit_layer = mst.setting_data.default_layer;
        // レイヤー表示
        mst.view_layer();
    });
};

// スマホ判定
mst.is_mobile = function() {
    return false;
    var ut = navigator.userAgent;
    if (ut.indexOf('iPhone') > 0 || ut.indexOf('iPod') > 0 || ut.indexOf('Android') > 0 && ut.indexOf('Mobile') > 0) {
        return true;
    } else if(ut.indexOf('iPad') > 0 || ut.indexOf('Android') > 0) {
        return true;
    }
    return false;
};

// 画面を90度回転
mst.body_rotate = function() {
    var bobj = $("body_box");
    var sh = bobj.offsetHeight;
    var sw = bobj.offsetWidth;
    var st = "rotate(90deg)";
    bobj.style.transformOrigin = "0 0 0";
    bobj.style.transform = st;
    bobj.style.MozTransform = st;
    bobj.style.msTransform = st;
    bobj.style.OTransform = st;
    bobj.style.top = 0;
    bobj.style.left = window.innerWidth + "px";
    bobj.style.width = (window.innerHeight - 50) + "px";
};

// 指定した枠を表示
mst.view_box = function(view_list) {
    var box_list = ["info_box", "select_box", "setting_box", "layer_box", "layer_menu", "key_img_box", "top_menu_box", "menu_box"];
    var i;
    for (i in box_list) {
        if (view_list.indexOf(box_list[i]) >= 0) {
            show(box_list[i]);
        } else {
            hide(box_list[i]);
        }
    }
    window.scrollTo(0, 0);
};

// キーコードから表示用の文字列を取得
mst.get_key_char = function(key_code, key_name) {
    var i;
    if (!key_name) key_name = "char";
    for (i in mst.key_list) {
        if (parseInt(mst.key_list[i].key) == key_code) {
            return mst.key_list[i][key_name];
        }
    }
    return "";
};

// レイヤー枠表示
mst.view_layer = function() {
    var s = "";
    s += "" +  mst.get_layer_name(mst.edit_layer) + "　";
    s += "<div style='display: inline-block;'>";
    s += "<div id='layer_menu'>";
    s += "<a href='#' class='update_button' onClick='javascript:mst.select_layer(); return false;'>▼</a>　";
    if (mst.edit_layer > 0) {
        s += "<a href='#' class='update_button' onClick='javascript:mst.delete_layer(); return false;'>×</a>　";
    }
    s += "<a href='#' class='update_button' onClick='javascript:mst.add_layer(); return false;'>＋</a>　";
    s += "</div>";
    s += "</div>";
    set_html("layer_box", s);
    mst.create_key_image(); // キーボード図形作成
    mst.create_key_btn(); // ボタン作成
    mst.view_box(["layer_box", "layer_menu", "key_img_box", "menu_box", "top_menu_box", "info_box"]);
};

// 編集中レイヤー選択
mst.select_layer = function() {
    var l = mst.get_layer_list();
    // 選択画面表示
    mst.select_exec(l, mst.edit_layer+"", function(select_key) {
        mst.edit_layer = parseInt(select_key);
        mst.view_layer();
    });
};

// レイヤー追加
mst.add_layer = function() {
    var k, n, m = 0;
    for (k in mst.setting_data.layers) {
        n = parseInt(k.substring(6));
        if (n > m) m = n;
    }
    m++;
    mst.setting_data.layers["layer_" + m] = {
        "name": "レイヤー" + m,
        "keys": {}
    };
    mst.edit_layer = m;
    mst.view_layer();
};

// レイヤー削除(選択中のレイヤーを削除)
mst.delete_layer = function() {
    if (mst.edit_layer > 0) {
        delete mst.setting_data.layers["layer_" + mst.edit_layer];
        mst.edit_layer = 0;
    }
    mst.view_layer();
};


// キータッチ用のオブジェクト作成
mst.create_key_btn = function() {
    var c, f, i, j, k, h, l, p, m, s;
    // 画像の位置取得
    h = "";
    for (i in mst.key_pattern["keys"]) {
        k = mst.key_pattern.keys[i];
        p = mst.get_key_setting_num(k.id); // キーの設定
        s = "position: absolute;";
        s += "margin: -2px; border: 3px solid black; border-radius: 12px;";
        if (mst.switch_check_mode) {
            // キー動作確認中はグレー
            s += "background-color: rgba(80,80, 80, 0.8);";
        } else if (p.press.action_type == 0) {
            // 処理なし
            s += "background-color: rgb(255, 73, 73);";
        } else {
            // 処理あり
            s += "background-color: rgb(129, 255, 129);";
        }
        s += "top: " + k["y"] + "px; left: " + k["x"] + "px;";
        s += "width: " + k["width"] + "px; height: " + k["height"] + "px;";
        h += "<div id='key_" + i + "' style='" + s + "' onClick='javascript: mst.key_click("+i+");'>";
        h += "<table style='width: " + k["width"] + "px; height: " + k["height"] + "px;'><tr><td align='center'>";
        if (mst.switch_check_mode) {
            // キー動作確認中は番号を表示
            h += "<div id='key_top_"+i+"' style='color: white; font-size: 50px;'>"+i+"</div>";
        } else if (p.press.action_type == 0) {
            // 処理なし
            h += "<div id='key_top_"+i+"' style='color: black; font-size: 27px;'>None</div>";
        } else if (p.press.action_type == 1) {
            // 通常入力
            if (p.press.key.length <= 1) {
                c = mst.get_key_char(p.press.key[0]);
                f = (c.length > 3)? "30px": "43px";
                h += "<div id='key_top_"+i+"' style='color: black; font-size: "+f+";'>" + c + "</div>";
            } else {
                h += "<div id='key_top_"+i+"' style='color: black; font-size: 27px;'>";
                l = [];
                for (j in p.press.key) {
                    l.push(mst.get_key_char(p.press.key[j]));
                    console.log(j + " : " +p.press.key[j] + " : " + mst.get_key_char(p.press.key[j]));
                }
                console.log(l);
                h += l.join(" + ");
                h += "</div>";
            }
        } else if (p.press.action_type == 2) {
            // テキスト入力
            h += "<div id='key_top_"+i+"' style='color: black; font-size: 27px;'>text</div>";
        } else if (p.press.action_type == 3) {
            // レイヤー変更
            h += "<div id='key_top_"+i+"' style='color: black; font-size: 27px;'>" + mst.get_layer_name(p.press.layer) + "</div>";
        } else if (p.press.action_type == 4) {
            // WEBフック
            h += "<div id='key_top_"+i+"' style='color: black; font-size: 27px;'>WEB</div>";
        } else if (p.press.action_type == 5) {
            // マウス移動
            h += "<div id='key_top_"+i+"' style='color: black; font-size: 27px;'>MUS</div>";
        }
        h += "</td></tr></table>";
        h += "</div>";
    }
    
    set_html("key_objs_box", h);
    
};

// キーボードの図形作成
mst.create_key_image = function() {
    var i, j, p;
    $("key_box").style.width = mst.key_pattern.size.width + "px";
    $("key_box").style.height = mst.key_pattern.size.height + "px";
    $("key_img_box").style.width = mst.key_pattern.size.width + "px";
    $("key_img_box").style.height = mst.key_pattern.size.height + "px";
    $("key_img").width = mst.key_pattern.size.width;
    $("key_img").height = mst.key_pattern.size.height;
    var cv = $("key_img").getContext("2d");
    // 描画するパーツ分ループ
    for (i in mst.key_pattern.parts) {
        p = mst.key_pattern.parts[i];
        if (p.type == "polygon") {
            // 表示タイプポリゴン
            if (p.line_width) cv.lineWidth = p.line_width; // 線の太さ
            if (p.line_color) cv.strokeStyle  = p.line_color; // 線の色
            if (p.fill_color) cv.fillStyle = p.fill_color; // 塗りつぶしの色
            cv.beginPath();
            for (j in p.path) {
                console.log(p.path[j]);
                if (j == 0) {
                    cv.moveTo(p.path[j][0], p.path[j][1]);
                } else {
                    cv.lineTo(p.path[j][0], p.path[j][1]);
                }
            }
            cv.closePath();
            if (p.fill) {
                cv.fill(); // 塗りつぶし
            } else {
                cv.stroke(); // 線だけ
            }
        }
    }
};

// 画像上のキーをクリックした時のイベント
mst.key_click = function(key_num) {
    // キー動作確認中は何もしない
    if (mst.switch_check_mode) return;
    // キーの設定画面表示
    var kid = mst.key_pattern.keys[key_num].id;
    mst.view_key_setting(kid);
    set_html("info_box", "");
};

// キーの設定を取得
mst.get_key_setting_num = function(key_id) {
    // 設定データが無ければデフォルトを設定
    if (!mst.setting_data.layers["layer_" + mst.edit_layer].keys["key_" + key_id]) {
        mst.setting_data.layers["layer_" + mst.edit_layer].keys["key_" + key_id] = {
            "press": {"action_type": 0}, // 処理なし
            "long_press": {},
            "long_press_time": 0
        };
    }
    // 設定データを返す
    return mst.setting_data.layers["layer_" + mst.edit_layer].keys["key_" + key_id]
};


// セレクトを選択した時の処理
mst.select_on_click = function(select_key) {
    mst.select_exec_cbfunc(select_key);
    set_html("select_box", "");
    hide("select_box");
    mst.select_exec_cbfunc = null;
};

// 選択枠表示
mst.select_exec = function(list_data, select_key, cb_func) {
    var i, o, sl, sli = -1, t, v;
    // コールバック関数を保持
    mst.select_exec_cbfunc = cb_func;
    var s = "";
    s += "<div id='lists' class='lists' style='width: "+(window.innerWidth - 100)+"px;'>";
    for (i in list_data) {
        o = list_data[i];
        if (o.key == select_key) {
            sl = "background-color: #34F464;";
            sli = i;
        } else {
            sl = "";
        }
        
        s += "<div id='opt_"+i+"' style='border-bottom: solid 1px #888;margin: 0; padding: 17px; font-size: 50px;display: block;"+sl+"' onClick='javascript:mst.select_on_click(\""+o.key+"\")'>"+o.value+"</div>";
    }
    s += "</div>";
    set_html("select_box", s);
    /*
    if (mst.is_mobile()) {
        $("lists").style.height = (window.innerWidth - 100) + "px";
        $("lists").style.width = (window.innerHeight - 50) + "px";
    } else {
        $("lists").style.height = (window.innerHeight - 180) + "px";
        $("lists").style.width = (window.innerWidth - 50) + "px";
    }
    */
    mst.view_box(["select_box"]);
    // スクロールの位置を選択してる項目の所へ移動
    if (sli >= 0) {
        v = $("opt_" + sli).getBoundingClientRect();
        window.scrollTo(0, v.top - 100);
    }
};



// レイヤーのリストを取得
mst.get_layer_list = function() {
    var v, n;
    var l = [];
    for (v in mst.setting_data.layers) {
        n = v.substring(6);
        l.push({"key": n, "value": mst.setting_data.layers[v].name});
    }
    return l;
};

// レイヤー番号からレイヤー名を取得
mst.get_layer_name = function(layer_no) {
    if (!mst.setting_data.layers["layer_" + layer_no]) return "";
    return mst.setting_data.layers["layer_" + layer_no].name;
};

// 入力タイプ選択(データが無い場合はここでデフォルトのデータを入れる)
mst.select_input_type = function() {
    var i, l = [];
    for (i in mst.input_type_list) {
        l.push({"key": i, "value": mst.input_type_list[i]});
    }
    mst.select_exec(l, mst.key_edit_data.press.action_type+"", function(select_key) {
        mst.key_edit_data.press.action_type = parseInt(select_key);
        if (mst.key_edit_data.press.action_type == 1) {
            // 通常入力
            if (!("key" in mst.key_edit_data.press)) {
                mst.key_edit_data.press.key = [4];
                mst.key_edit_data.press.repeat_interval = 51;
            }
        } else if (mst.key_edit_data.press.action_type == 2) {
            // テキスト入力
            if (!("text" in mst.key_edit_data.press)) mst.key_edit_data.press.text = "";
        } else if (mst.key_edit_data.press.action_type == 3) {
            // レイヤー切り替え
            if (!("layer" in mst.key_edit_data.press)) mst.key_edit_data.press.layer = 0;
        } else if (mst.key_edit_data.press.action_type == 4) {
            // WEBフック
            if (!("webhook" in mst.key_edit_data.press)) mst.key_edit_data.press.webhook = {"url": "http://palette-system.com/ct/", "header": [], "post": "", "keyoutput": 0};
        } else if (mst.key_edit_data.press.action_type == 5) {
            // マウス移動
            if (!("move" in mst.key_edit_data.press)) mst.key_edit_data.press.move = {"x": 0, "y": 0, "speed": 100};
        }
        mst.view_key_setting(mst.key_edit_kid);
    });
};


// 入力文字選択
mst.select_input_key = function(num) {
    mst.select_exec(mst.key_list, mst.key_edit_data.press.key[num]+"", function(select_key) {
        mst.key_edit_data.press.key[num] = parseInt(select_key);
        mst.view_key_setting(mst.key_edit_kid);
    });
};

// 切り替えレイヤーの選択
mst.select_change_layer = function() {
    mst.select_exec(mst.get_layer_list(), mst.key_edit_data.press.layer+"", function(select_key) {
        mst.key_edit_data.press.layer = parseInt(select_key);
        mst.view_key_setting(mst.key_edit_kid);
    });
};

// テキストに全角文字が入っていないかチェック
mst.check_ascii = function(elm){
    var txt = elm.value;
    for(i=0 ; i<txt.length ; i++){
        if(escape(txt.charAt(i)).length >= 4){
            alert("半角英数字を入力してください。");
            elm.value = "";
            return false;
        }
    }
    return true;
};

// テキスト内容変更イベント
mst.text_on_change = function() {
    var obj = $("key_text");
    mst.check_ascii(obj);
    mst.key_edit_data.press.text = obj.value;
};

// webフック用URLチェック
mst.web_hook_url_check = function(url) {
    // 入力が無い場合はOK
    if (!url.length) return true;
    // 頭7文字が http:// で始まらなければNG
    if (url.slice(0, 7) != "http://" && url.slice(0, 8) != "https://") {
        alert("http:// か https:// のみ指定できます");
        return false;
    }
    // それ以外はOK
    return true;
};

// URL内容変更イベント
mst.url_on_change = function() {
    var obj = $("url_text");
    var url = obj.value;
    // 入力チェックNGなら入力を元に戻す
    if (!mst.web_hook_url_check(url)) {
        obj.value = mst.key_edit_data.press.webhook.url;
        return;
    }
    mst.key_edit_data.press.webhook.url = url;
};

// URLがhttpsかどうか
mst.is_https_url = function(url) {
    if (url.length < 8) return false;
    if (url.slice(0, 8) == "https://") return true;
    return false;
};

// キー設定画面表示
mst.view_key_setting = function(key_id) {
    if (mst.key_edit_kid < 0) {
        mst.key_edit_kid = key_id;
        mst.key_edit_data = obj_clone(mst.get_key_setting_num(mst.key_edit_kid));
    }
    var pss = mst.key_edit_data.press; // 押された時アクションの設定
    var at = pss.action_type;
    var f, i, k, s = "", st;
    var hrst = "border: 1px solid #9a9fe3;";
    s += "<table cellpadding='20' style='min-width: 520px;'>";
    s += "<tr><td colspan='2'><b>キー番号：</b> <font style='font-size: 40px;'>" + mst.key_edit_kid + "</font></td></tr>";
    s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
    s += "<tr><td><b>動作：</b><br><font style='font-size: 40px;'>" + mst.input_type_list[at] + "</font></td><td align='right'>";
    s += "<a href='#' class='update_button' onClick='javascript:mst.select_input_type(); return false;'>変更</a>";
    s += "</td></tr>";
    if (at == 1) {
        // 通常入力
        for (i in pss.key) {
            k = mst.get_key_char(pss.key[i], "value");
            if (k.length < 12) { f = 40; } else { f = 30; }
            s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
            s += "<tr><td>";
            s += "<b>キー "+(parseInt(i)+1)+"：</b> <font style='font-size: "+f+"px;'>" + k + "</font>　";
            s += "</td><td align='right'>";
            s += "<a href='#' class='update_button' onClick='javascript:mst.select_input_key("+i+"); return false;'>変更</a>";
            if (pss.key.length > 1) {
                s += " <a href='#' class='update_button' onClick='javascript:mst.delete_input_key("+i+"); return false;'>×</a>";
            }
            s += "</td></tr>";
        }
        if (pss.key.length < 5) {
            s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
            s += "<tr><td colspan='2' align='right'>";
            s += "<br><a href='#' class='update_button' onClick='javascript:mst.add_input_key(); return false;'>入力キー追加</a>";
            s += "</td></tr>";
        }
        if (pss.repeat_interval === undefined) pss.repeat_interval = 51;
        console.log(pss);
        s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
        s += "<tr><td colspan='2'>";
        s += "<b>連打間隔：</b>　<font id='move_repeat_interval_val'></font><br><br>";
        s += "<center><input type='range' id='move_repeat_interval' name='move_repeat_interval' min='0' max='51' style='width: 420px;' value='"+pss.repeat_interval+"' onChange='javascript:mst.view_move_input(\"repeat_interval\");'></center>";
        s += "</td></tr>";
        
    } else if (at == 2) {
        // テキスト入力
        s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
        st = "font-size: 30px; width: 520px; border: 3px solid black;";
        s += "<tr><td colspan='2'>";
        s += "<b>テキスト：</b><br><input type='text' id='key_text' style='"+st+"' value='' onChange='javascript:mst.text_on_change();'>";
        s += "</td></tr>";
    } else if (at == 3) {
        // レイヤー切り替え
        s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
        s += "<tr><td>";
        s += "<b>レイヤー：</b><br><font style='font-size: 40px;'>"+mst.get_layer_name(pss.layer)+"</font></td><td align='right'>";
        s += "<a href='#' class='update_button' onClick='javascript:mst.select_change_layer(); return false;'>変更</a>";
        s += "</td></tr>";
        s += "<tr><td colspan='2'>";
        s += "<br><br><font style='font-size: 30px;'>※ このキーを押している間、指定したレイヤーの動作に切り替わります。</font><br><br>";
        s += "</td></tr>";
    } else if (at == 4) {
        // WEBフック
        s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
        st = "font-size: 30px; width: 520px; border: 3px solid black;";
        s += "<tr><td colspan='2'>";
        s += "<b>URL ：</b><br><input type='text' id='url_text' style='"+st+"' value='' onChange='javascript:mst.url_on_change();'>";
        s += "<br><br>";
        s += "<b>HTTPヘッダー ：</b><br>";
        for (i in pss.webhook.header) {
            s += "<p style='font-size: 24px; margin: 0; padding: 0; overflow: hidden; width: 520px;'>　" + pss.webhook.header[i].key + " : " + pss.webhook.header[i].value + "</p><br>";
            s += "<p style='text-align: right; margin: 0; padding: 6px;'><a href='#' class='update_button' onClick='javascript:mst.view_webhook_header_edit("+i+");return false;'>編集</a>　";
            s += "<a href='#' class='update_button' onClick='javascript:mst.delete_webfook_header("+i+");return false;'>削除</a></p>";
        }
        s += "<p style='text-align: right; margin: 0; padding: 30px 6px;'><a href='#' class='update_button' onClick='javascript:mst.add_webfook_header();return false;'>HTTPヘッダー追加</a></p>";
        s += "<b>POSTデータ ：</b><br>";
        s += "<textarea id='webhook_post_text' style='font-size: 30px; width: 520px; height: 200px; border: 3px solid black;'></textarea>";
        s += "<br><br>";
        s += "<b>キー動作 ：</b><br>";
        s += "<select id='webhook_keyoutput' style='font-size: 30px; border: 3px solid black;'>";
        s += "<option value='0'>無し</option>";
        s += "<option value='1'>ステータスコードを入力</option>";
        s += "<option value='2'>HTTPレスポンスを入力</option>";
        s += "</select>";
        s += "</td></tr>";
        if (!mst.setting_data.wifi.length) {
            s += "<tr><td colspan='2'>";
            s += "<font style='font-size: 30px;'>※ 有効にするにはWIFIの設定が必要です。</font><br>";
            s += "</td></tr>";
        }
        
    } else if (at == 5) {
        // マウス移動
        s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
        s += "<tr><td colspan='2'>";
        s += "<b>Ｘ：</b><font id='move_x_val'>"+pss.move.x+"</font><br><input type='range' id='move_x' name='move_x' min='-100' max='100' style='width: 400px;' value='"+pss.move.x+"' onChange='javascript:mst.view_move_input(\"x\");'><br><br>"
        s += "<b>Ｙ：</b><font id='move_y_val'>"+pss.move.y+"</font><br><input type='range' id='move_y' name='move_y' min='-100' max='100' style='width: 400px;' value='"+pss.move.y+"' onChange='javascript:mst.view_move_input(\"y\");'><br><br>"
        s += "<b>スピード：</b><font id='move_speed_val'>"+pss.move.speed+"</font><br><input type='range' id='move_speed' name='move_speed' min='0' max='100' style='width: 400px;' value='"+pss.move.speed+"' onChange='javascript:mst.view_move_input(\"speed\");'><br><br>"
        s += "</td></tr>";
    }
    s += "</table>";
    s += "<br><br>";
    s += "<center>";
    s += "<a href='#' class='button' onClick='javascript:mst.key_setting_btn_click(1);return false;'>決定</a>　　";
    s += "<a href='#' class='button' onClick='javascript:mst.key_setting_btn_click(0);return false;'>キャンセル</a>";
    s += "</center>";
    s += "<br><br>";
    set_html("setting_box", s);
    // テキストは後からvalueに値を入れる
    if (at == 1) {
        mst.view_move_input("repeat_interval");
    } else if (at == 2) {
        $("key_text").value = pss.text;
    } else if (at == 4) {
        $("url_text").value = pss.webhook.url;
        $("webhook_post_text").value = pss.webhook.post;
        $("webhook_keyoutput").value = pss.webhook.keyoutput + "";
    }
    mst.view_box(["info_box", "setting_box", "layer_box"]);
};

// マウス移動のバー情報を画面に反映
mst.view_move_input = function(t) {
    var s = $("move_"+t).value;
    if (t == "repeat_interval") {
        if (s > 50) s = "連打無し";
    }
    set_html("move_"+t+"_val", s);
};


// WEBフックヘッダーを１つ削除
mst.delete_webfook_header = function(num) {
    var i, l = [];
    for (i in mst.key_edit_data.press.webhook.header) {
        if (i == num) continue;
        l.push(mst.key_edit_data.press.webhook.header[i]);
    }
    mst.key_edit_data.press.webhook.header = l;
    mst.view_key_setting(mst.key_edit_kid);
};


// WEBフックヘッダーを１つ追加
mst.add_webfook_header = function(num) {
    mst.key_edit_data.press.webhook.header.push({"key": "", "value": ""});
    mst.view_webhook_header_edit(mst.key_edit_data.press.webhook.header.length - 1);
};


// WEBフックヘッダーを編集するページを表示
mst.view_webhook_header_edit = function(num) {
    var s = "", st;
    var hd = mst.key_edit_data.press.webhook.header[num];
    mst.key_edit_data.press.webhook.url = $("url_text").value;
    mst.key_edit_data.press.webhook.post = $("webhook_post_text").value;
    mst.key_edit_data.press.webhook.keyoutput = parseInt($("webhook_keyoutput").value);
    st = "font-size: 30px; width: 520px; border: 3px solid black;";
    s += "<b style='font-size: 30px;'>HTTPヘッダー</b><br><br><br>";
    s += "<b>Key ：</b><br><input type='text' id='webheader_key' style='"+st+"' value=''>";
    s += "<br><br>";
    s += "<b>Value ：</b><br><input type='text' id='webheader_value' style='"+st+"' value=''>";
    s += "<br><br><br><br>";
    s += "<center>";
    s += "<a href='#' class='button' onClick='javascript:mst.webhook_header_end_btn("+num+", 1);return false;'>決定</a>　　";
    s += "<a href='#' class='button' onClick='javascript:mst.webhook_header_end_btn("+num+", 0);return false;'>キャンセル</a>";
    s += "</center>";
    s += "<br><br>";
    set_html("setting_box", s);
    mst.view_box(["info_box", "setting_box", "layer_box"]);
    $("webheader_key").value = hd.key;
    $("webheader_value").value = hd.value;
};

// WEBフックヘッダー決定ボタン
mst.webhook_header_end_btn = function(num, save_flag) {
    if (save_flag) {
        // 決定ボタンだった場合入力を反映
        mst.key_edit_data.press.webhook.header[num].key = $("webheader_key").value;
        mst.key_edit_data.press.webhook.header[num].value = $("webheader_value").value;
    }
    mst.view_key_setting(mst.key_edit_kid);
};

// 入力キーを１つ削除
mst.delete_input_key = function(num) {
    var i, l = [];
    for (i in mst.key_edit_data.press.key) {
        if (i == num) continue;
        l.push(mst.key_edit_data.press.key[i]);
    }
    mst.key_edit_data.press.key = l;
    mst.view_key_setting(mst.key_edit_kid);
};

// 入力キーを１つ追加
mst.add_input_key = function(num) {
    mst.key_edit_data.press.key.push(4);
    mst.select_input_key(mst.key_edit_data.press.key.length - 1);
};



// キー設定ボタンイベント(type_id : 0=キャンセル / 1=決定)
mst.key_setting_btn_click = function(type_id) {
    // 決定ならば設定データ更新
    var s;
    if (type_id == 1) {
        s = {"action_type": mst.key_edit_data.press.action_type};
        if (s.action_type == 1) { // 通常キー入力
            s.key =  mst.key_edit_data.press.key;
            s.repeat_interval = $("move_repeat_interval").value
        } else if (s.action_type == 2) { // テキスト入力
            s.text =  mst.key_edit_data.press.text;
        } else if (s.action_type == 3) { // レイヤー切り替え
            s.layer =  mst.key_edit_data.press.layer;
        } else if (s.action_type == 4) { // WEBフック
            mst.key_edit_data.press.webhook.url = $("url_text").value;
            mst.key_edit_data.press.webhook.post = $("webhook_post_text").value;
            mst.key_edit_data.press.webhook.keyoutput = parseInt($("webhook_keyoutput").value);
            s.webhook =  mst.key_edit_data.press.webhook;
        } else if (s.action_type == 5) { // マウス移動
            s.move = {"x": $("move_x").value, "y": $("move_y").value, "speed": $("move_speed").value};
        }
        mst.setting_data.layers["layer_" + mst.edit_layer].keys["key_" + mst.key_edit_kid].press = s;
    }
    mst.key_edit_kid = -1;
    mst.key_edit_data = null;
    mst.create_key_btn(); // キーのボタンオブジェクト作り直し
    set_html("info_box", "");
    mst.view_box(["info_box", "layer_box", "layer_menu", "key_img_box", "top_menu_box", "menu_box"]);
};



// 終了ボタン end_type : 0 = 保存せずに終了 / 1 = 保存して終了 / 2 = 保存して設定モードで再起動
mst.end_setting = function(end_type) {
    var api_path;
    // 終了フラグを立てる
    mst.end_flag = true;
    mst.end_type = end_type;
    if (mst.end_type == 1 || mst.end_type == 2) {
        // 保存して終了
        set_html("info_box", "保存中.. ");
        mst.view_box(["info_box"]);
        mst.save_setting_json();
    } else {
        // 保存せずに終了
        set_html("info_box", "終了中.. ");
        ajax("/end_setting", function(stat, res) {
            set_html("info_box", "ページを閉じて下さい");
            mst.view_box(["info_box"]);
        });
        mst.view_box(["info_box"]);
        setTimeout(function() {
            window.open('about:blank','_self').close();
        }, 1500);
    }
};


// 設定JSON保存
mst.save_setting_json = function() {
    mst.setting_data.keyboard_pin = mst.key_pattern_list[ mst.setting_data.keyboard_type ].pin;
    api_path = "/upload_setting_json";
    if (mst.end_type == 2) api_path = "/upload_setting_json_reload";
    ajax_post(api_path, JSON.stringify(mst.setting_data), function(stat, res) {
        if (!stat) {
            set_html("info_box", "ページを閉じて下さい");
            mst.view_box(["info_box"]);
            return;
        }
        set_html("info_box", "終了中..");
    });
};


// wifi 設定画面表示(リスト表示)
mst.view_wifi_setting = function() {
    var i;
    var s = "";
    var hrst = "border: 1px solid #9a9fe3; margin: 40px 0;";
    s += "<b style='font-size: 30px;'>WIFI設定</b>";
    s += "<table style='min-width: 520px;'>";
    for (i in mst.setting_data.wifi) {
        s += "<tr><td colspan='2' style='padding: 12px 0;'><hr style='"+hrst+"'></td></tr>";
        s += "<tr><td><b style='font-size: 27px;'>" + mst.setting_data.wifi[i].ssid + "</b></td><td align='right'>";
        s += "<a href='#' class='button' onClick='javascript:mst.wifi_edit_btn("+i+");return false;'>編集</a>　";
        s += "<a href='#' class='button' onClick='javascript:mst.wifi_delete_btn("+i+");return false;'>削除</a>";
        s += "</td></tr>";
    }
    s += "<tr><td colspan='2' style='padding: 20px 0;'><hr style='"+hrst+"'></td></tr>";
    s += "<tr><td colspan='2' style='padding: 20px 0;' align='right'>";
    s += "<a href='#' class='button' onClick='javascript:mst.wifi_edit_btn(-1);return false;'>WIFI追加</a>";
    s += "</td></tr></table>";
    s += "<br><br><br>";
    s += "<center>";
    s += "<a href='#' class='button' onClick='javascript:mst.view_detail_setting();return false;'>完了</a>";
    s += "</center>";
    set_html("setting_box", s);
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// wifi 編集ボタンクリック
mst.wifi_edit_btn = function(num) {
    // 追加の場合レコード追加
    if (num < 0) {
        num = mst.setting_data.wifi.length;
        mst.setting_data.wifi.push({"new_flag": true, "ssid": "", "pass": ""});
    }
    // 編集中のデータを指定されたデータにして設定画面表示
    mst.wifi_edit_kid = num;
    mst.wifi_edit_data = obj_clone(mst.setting_data.wifi[num]);
    mst.view_wifi_setting_one(mst.wifi_edit_data);
};

// wifi 削除ボタンクリック
mst.wifi_delete_btn = function(num) {
    mst.setting_data.wifi.splice(num, 1);
    mst.view_wifi_setting();
};

// wifi 設定画面表示(１つ分)
mst.view_wifi_setting_one = function(wifi_data) {
    var s = "";
    s += "<b style='font-size: 30px;'>WIFI設定</b><br><br><br>";
    s += "<b>ssid ： </b><br>";
    s += "<input type='text' id='wifi_ssid_text' style='font-size: 35px; border: 3px solid black; width: 380px;' value=''> ";
    s += "<a href='#' class='update_button' onClick='javascript:mst.wifi_search(); return false;'>▼</a>";
    s += "<br><br><br>";
    s += "<b>pass ： </b><br>";
    s += "<input type='password' id='wifi_pass_text' style='font-size: 35px; border: 3px solid black; width: 380px;' value=''>";
    // s += "<br><br><br>";
    // s += "<a href='#' class='update_button' onClick='javascript:mst.wifi_conn_check(); return false;'>接続確認</a> ";
    // s += "<font id='wifi_conn_check_info_box'></font>";
    s += "<br><br><br><br><br>";
    s += "<center><div id='wifi_setting_btn_box'>";
    s += "<a href='#' class='button' onClick='javascript:mst.wifi_setting_btn_click(1);return false;'>決定</a>　　";
    s += "<a href='#' class='button' onClick='javascript:mst.wifi_setting_btn_click(0);return false;'>キャンセル</a>";
    s += "</div></center>";
    set_html("setting_box", s);
    $("wifi_ssid_text").value = wifi_data.ssid;
    $("wifi_pass_text").value = wifi_data.pass;
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// wifi 検索
mst.wifi_search = function() {
    mst.view_box(["info_box"]);
    set_html("info_box", "アクセスポイント 検索中 ...");
    ajax("/get_ap_list", function(stat, res) {
        if (!stat) {
            mst.view_wifi_setting_one(mst.wifi_edit_data);
            set_html("info_box", "アクセスポイント検索 失敗");
            return;
        }
        var rdata = JSON.parse(res);
        if (!rdata["list"], !rdata.list.length) {
            mst.view_wifi_setting_one(mst.wifi_edit_data);
            set_html("info_box", "アクセスポイント検索 失敗");
            return;
        }
        set_html("info_box", "");
        var o, l = [];
        for (i in rdata.list) {
            o = (rdata.list[i].auth_open)? "(open)": "";
            l.push({"key": rdata.list[i].ssid, "value": rdata.list[i].ssid + " " + o});
        }
        mst.select_exec(l, mst.wifi_edit_data.ssid, function(select_key) {
            mst.wifi_edit_data.ssid = select_key;
            mst.view_wifi_setting_one(mst.wifi_edit_data);
        });
    });
};

// wifi接続確認
mst.wifi_conn_check = function() {
    var ssid = $("wifi_ssid_text").value;
    var pass = $("wifi_pass_text").value;
    if (!ssid.length) {
        set_html("wifi_conn_check_info_box", "ssidを指定してください");
        return;
    }
    set_html("wifi_conn_check_info_box", "接続中...");
    hide("wifi_setting_btn_box");
    ajax_post("/wifi_conn_check", ssid + "\n" + pass, function(stat, res) {
        if (!stat) {
            set_html("wifi_conn_check_info_box", "<font style='color: #FF9999;'><b>エラー</b></font>");
            show("wifi_setting_btn_box");
            return;
        }
        if (res == "OK") {
            set_html("wifi_conn_check_info_box", "<font style='color: #00FF99;'><b>OK</b></font>");
        } else {
            set_html("wifi_conn_check_info_box", "<font style='color: #FF9999;'><b>NG</b></font>");
        }
        show("wifi_setting_btn_box");
    });
};

// wifi設定完了
mst.wifi_setting_btn_click = function(save_flag) {
    var i;
    if (save_flag) {
        // 決定が押された時
        i = mst.wifi_edit_kid;
        mst.setting_data.wifi[i].ssid = $("wifi_ssid_text").value;
        mst.setting_data.wifi[i].pass = $("wifi_pass_text").value;
        if ("new_flag" in mst.setting_data.wifi[i]) delete mst.setting_data.wifi[i].new_flag;
    } else if (mst.wifi_edit_data.new_flag) {
        // キャンセルを押されたけど新しく追加したデータ場合追加したデータを削除
        mst.setting_data.wifi.splice(mst.wifi_edit_kid, 1);
    }
    mst.wifi_edit_kid = -1;
    mst.wifi_edit_data = null;
    mst.view_wifi_setting();
};

// キーボードの言語設定ページ表示
mst.view_language_setting = function(select_language) {
    var s = "";
    s += "<b style='font-size: 30px;'>日本語/US 切り替え</b><br><br><br><br>";
    if (!select_language) select_language = mst.setting_data.keyboard_language;
    s += "　　<b style='font-size: 32px;'>" + mst.key_language_list[select_language] + "</b>";
    s += "<div style='text-align: right;padding: 0 50px;'><a href='#' class='update_button' onClick='javascript:mst.keylanguage_select(\""+select_language+"\"); return false;'>変更</a></div>";
    s += "<br><br><br><br><br><br>";
    s += "<center><div id='wifi_setting_btn_box'>";
    s += "<a href='#' class='button' onClick='javascript:mst.keylanguage_setting_btn_click(1, \""+select_language+"\");return false;'>決定</a>　　";
    s += "<a href='#' class='button' onClick='javascript:mst.keylanguage_setting_btn_click(0, \""+select_language+"\");return false;'>キャンセル</a>";
    s += "</div></center>";
    set_html("setting_box", s);
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// キーボード言語選択
mst.keylanguage_select = function(select_language) {
    var i;
    var l = [];
    for (i in mst.key_language_list) {
        l.push({"key": i, "value": mst.key_language_list[i]});
    }
    mst.select_exec(l, select_language, function(select_key) {
        mst.view_language_setting(select_key);
    });
};

// キーボード言語決定
mst.keylanguage_setting_btn_click = function(save_flag, select_language) {
    // キャンセルなら何もしない | 元の設定から変更が無ければ何もしない
    if (!save_flag || mst.setting_data.keyboard_language == select_language) {
        mst.view_detail_setting();
        return;
    }
    // 設定が変更されていて決定が押された時
    mst.setting_data.keyboard_language = select_language; // キーボード言語変更
    mst.view_detail_setting(); // 設定メニューに戻る
};

// キーボードの種類設定ページ表示
mst.view_keytype_setting = function(select_type) {
    var s = "";
    s += "<b style='font-size: 30px;'>キーボードの種類設定</b><br><br><br><br>";
    if (!select_type) select_type = mst.setting_data.keyboard_type;
    s += "　　<b style='font-size: 32px;'>" + mst.key_pattern_list[select_type].name + "</b>";
    s += "<div style='text-align: right;padding: 10px 50px;'><a href='#' class='update_button' onClick='javascript:mst.keytype_select(\""+select_type+"\"); return false;'>変更</a></div>";
    s += "<br><br><br><br><br><br>";
    s += "<center><div id='wifi_setting_btn_box'>";
    s += "<a href='#' class='button' onClick='javascript:mst.keytype_setting_btn_click(1, \""+select_type+"\");return false;'>決定</a>　　";
    s += "<a href='#' class='button' onClick='javascript:mst.keytype_setting_btn_click(0, \""+select_type+"\");return false;'>キャンセル</a>";
    s += "</div></center>";
    set_html("setting_box", s);
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// キーボードタイプ選択
mst.keytype_select = function(select_type) {
    var i;
    var l = [];
    for (i in mst.key_pattern_list) {
        l.push({"key": i, "value": mst.key_pattern_list[i].name});
    }
    mst.select_exec(l, select_type, function(select_key) {
        mst.view_keytype_setting(select_key);
    });
};

// キーボードタイプ決定
mst.keytype_setting_btn_click = function(save_flag, select_type) {
    // キャンセルなら何もしない | 元の設定から変更が無ければ何もしない
    if (!save_flag || mst.setting_data.keyboard_type == select_type) {
        mst.view_detail_setting();
        return;
    }
    // 設定が変更されていて決定が押された時
    mst.setting_data.keyboard_type = select_type; // キーボードタイプ変更
    // 設定ファイルを保存して設定モードで再起動
    mst.end_setting(2);
};


// 詳細設定表示
mst.view_detail_setting = function() {
    var s = "";
    var bs = "style='width: 450px;height: 70px; background: #78d3df; font-size: 35px; display: inline-block;'";
    s += "<b style='font-size: 30px;'>設定メニュー</b><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.view_language_setting();return false;'>日本語/US 切り替え</a><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.view_keytype_setting();return false;'>キーボードの種類</a><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.view_switch_check();return false;'>スイッチ接触確認</a><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.view_wifi_setting();return false;'>WIFI設定</a><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.view_wifi_pass_setting();return false;'>ログイン設定</a><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.view_init_setting();return false;'>設定の初期化</a><br><br>";
    s += "<a href='#' class='update_button' "+bs+" onClick='javascript:mst.firmware_setting();return false;'>ファームウェア</a><br><br>";
    s += "<br><br><br>";
    s += "<center>";
    s += "<a href='#' class='button' onClick='javascript:mst.view_layer();return false;'>完了</a>";
    s += "</center>";
    set_html("setting_box", s);
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// ボタン接触確認表示
mst.view_switch_check = function() {
    // 接触確認中にする
    mst.switch_check_mode = 1;
    // 確認画面作成
    var s = "";
    s += "<center>";
    s += "<a href='#' class='button' onClick='javascript:mst.switch_check_mode = 0; mst.view_detail_setting();return false;'>完了</a>";
    s += "</center>";
    set_html("info_box", s);
    mst.create_key_btn();
    mst.view_box(["info_box", "key_img_box"]);
    
    // 接触状態取得のループを開始する
    mst.switch_check_loop();
};

// ボタン情報取得ループ
mst.switch_check_loop = function() {
    ajax("/get_key_status", function(stat, res) {
        var i, k, s;
        if (stat && res.length) {
            for (i in mst.key_pattern["keys"]) {
                k = mst.key_pattern.keys[i];
                s = res.slice(parseInt(k.id), parseInt(k.id)+1); // キーの状態を取得
                if (s == "0") {
                    $("key_"+i).style.backgroundColor = "rgba(80, 80, 80, 0.8)";
                } else {
                    $("key_"+i).style.backgroundColor = "rgba(100, 100, 233, 0.8)";
                }
            }
        }
        // 接触確認中であれば再度アクセス
        if (mst.switch_check_mode) {
            setTimeout(mst.switch_check_loop, 20);
        }
    });
};

// WIFIパスワード設定画面表示
mst.view_wifi_pass_setting = function() {
    var s = "";
    s += "<b style='font-size: 30px;'>ログイン設定</b><br><br>";
    s += "<font style='font-size: 32px;'>このページへアクセスするWIFIのパスワードを設定します。</font><br><br><br>";
    s += "<b>pass ： </b><br>";
    s += "<input type='password' id='ap_pass_text' style='font-size: 35px; border: 3px solid black;' value='"+mst.setting_data.ap.pass+"'>";
    s += "<br><br><br><br>";
    s += "<font style='font-size: 32px;'>※ 8文字以上で有効になります。</font><br>";
    s += "<br><br><br>";
    s += "<center>";
    s += "<div id='firmware_back_btn'>";
    s += "<a href='#' class='button' onClick='javascript:mst.wifi_pass_setting(1);return false;'>決定</a>　　　";
    s += "<a href='#' class='button' onClick='javascript:mst.wifi_pass_setting(0);return false;'>キャンセル</a>";
    s += "</div>";
    s += "</center>";
    set_html("setting_box", s);
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// パスワード設定ボタン
mst.wifi_pass_setting = function(save_flag) {
    if (save_flag) {
        mst.setting_data.ap.pass = $("ap_pass_text").value;
    }
    mst.view_detail_setting();
};

// ファームウェアのバージョンを表示用に成形
mst.firmware_view_convert = function(v) {
    if (v.length != 6) return v;
    var r = "";
    r += parseInt(v.slice(0,2));
    r += " . " + parseInt(v.slice(2,4));
    r += " . " + parseInt(v.slice(4,6));
    return r;
};

// ファームウェア設定画面表示
mst.firmware_setting = function() {
    var s = "";
    var fstyle = "font-size: 25px;border: 4px solid black;background-color: #e6f1ff;padding: 12px;width: 500px;";
    s += "<form method='POST' enctype='multipart/form-data' id='firmware_form'>";
    s += "<b style='font-size: 30px;'>ファームウェア</b><br><br>";
    s += "<b>バージョン：</b><br>　　<font style='font-size: 40px;'>" + mst.firmware_view_convert(mst.firmware_version) + "</font><br><br><br>";
    s += "<b>ファイル：</b><br>";
    s += "<input type='file' id='firmware_file' name='update' style='"+fstyle+"'><br><br>";
    s += "<div id='firmware_btn_box' style='text-align: right;'>";
    s += "<a href='#' class='update_button' onClick='javascript:mst.firmware_update();return false;'>アップデート</a><br><br>";
    s += "</div>";
    s += "<div id='firmware_info'></div>";
    s += "<br><br><br>";
    s += "<center>";
    s += "<div id='firmware_back_btn'>";
    s += "<a href='#' class='button' onClick='javascript:mst.view_detail_setting();return false;'>キャンセル</a>";
    s += "</div>";
    s += "</center>";
    s += "</form>";
    set_html("setting_box", s);
    set_html("info_box", "");
    // ファイルが選択された時のイベント
    mst.firmware_file_data = null;
    $("firmware_file").addEventListener('change', (evt) => {
        // 選択されたファイルの情報を保持
        mst.firmware_file_data = evt.target.files;
    });
    mst.view_box(["info_box", "setting_box"]);
};


// ファームウェア更新
mst.firmware_update = function() {
    if (!mst.firmware_file_data || !mst.firmware_file_data.length) {
        set_html("firmware_info", "bin ファイルを指定して下さい");
        return;
    }
    hide("firmware_back_btn");
    hide("firmware_btn_box");
    // フォームの情報を送信
    var fd = new FormData($("firmware_form"));
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/firmware_update", true);
    xhr.upload.addEventListener('progress', function(evt) {
        if (!evt.lengthComputable) return;
        var per = Math.round((evt.loaded / evt.total) * 100);
        if (per < 100) {
            set_html("firmware_info", "ファイル送信中： " + per + " %");
        } else {
            set_html("firmware_info", "ファームウェア更新中 ...");
        }
    });
    xhr.addEventListener("error", mst.firmware_update_error);
    xhr.upload.addEventListener("abort", mst.firmware_update_error);
    xhr.upload.addEventListener("error", mst.firmware_update_error);
    xhr.upload.addEventListener("timeout", mst.firmware_update_error);
    xhr.onreadystatechange = function(e) {
        if (this.readyState == 4 && this.status == 200) {
            mst.firmware_update_ok(this);
        } else {
            mst.firmware_update_error(null);
        }
    };
    xhr.send(fd);
};

// ファームウェア更新エラー時の処理
mst.firmware_update_error = function(err) {
    set_html("info_box", "<b>エラー</b><br>ページを閉じて下さい。");
    mst.view_box(["info_box"]);
};

// ファームウェア更新OK
mst.firmware_update_ok = function(xhr) {
    set_html("info_box", "<b>アップデート成功</b><br>ページを閉じて下さい。");
    mst.view_box(["info_box"]);
};

// 設定の初期化画面表示
mst.view_init_setting = function() {
    var s = "";
    s += "<b style='font-size: 30px;'>設定の初期化</b><br><br>";
    s += "<font style='font-size: 32px;'>全ての設定を出荷時の状態に戻します。<br><br><br>";
    s += "<font style='color: #ff6347;'>※ 初期化すると元に戻せません。</font></font><br>";
    s += "<br><br><br>";
    s += "<div id='init_setting_info'></div>";
    s += "<center>";
    s += "<div id='init_setting_menu'>";
    s += "<a href='#' class='button' onClick='javascript:mst.init_setting();return false;'>初期化する</a>　　　";
    s += "<a href='#' class='button' onClick='javascript:mst.view_detail_setting();return false;'>キャンセル</a>";
    s += "</div>";
    s += "</center><br>";
    set_html("setting_box", s);
    set_html("info_box", "");
    mst.view_box(["info_box", "setting_box"]);
};

// 設定の初期化実行
mst.init_setting = function() {
    hide("init_setting_menu");
    set_html("init_setting_info", "初期化中...");
    ajax("/init_setting_json", function(stat, res) {
        // 失敗したら初期化画面のまま
        if (!stat) {
            set_html("init_setting_info", "エラー 初期化できませんでした");
            show("init_setting_menu");
            return;
        }
        // 成功したらキーボードモードで再起動
        set_html("init_setting_info", "初期化完了しました");
        setTimeout(function() {
            mst.end_setting(0);
        }, 1000);
    });
};


