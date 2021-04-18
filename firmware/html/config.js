

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
if (!mst.key_pattern_list) mst.key_pattern_list = {};

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



// オプションのリスト
mst.option_list = {};


// 踏みキー
mst.option_list["foot_m"] = {
    "keyboard_type": ["az_macro"], // 対応しているキーボードタイプ
    "name": "踏みキー",
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


// トラックボール
mst.option_list["trackball_m"] = {
    "keyboard_type": ["az_macro"], // 対応しているキーボードタイプ
    "name": "トラックボール",
    "pin": {
        "row": [],
        "col": [],
        "direct": [23, 22, 21, 19, 16, 17, 5, 18, 25, 26],
        "touch": []
    },
    "size": {"width": 600, "height": 520},
    "keys": [
        {"id": 0, "x": 11, "y": 35, "width": 115, "height": 115 },
        {"id": 1, "x": 163, "y": 35, "width": 115, "height": 115 },
        {"id": 2, "x": 317, "y": 35, "width": 115, "height": 115 },
        {"id": 3, "x": 471, "y": 35, "width": 115, "height": 115 },
        {"id": 4, "x": 11, "y": 188, "width": 115, "height": 115 },
        {"id": 5, "x": 163, "y": 188, "width": 115, "height": 115 },
        {"id": 6, "x": 317, "y": 188, "width": 115, "height": 115 },
        {"id": 7, "x": 471, "y": 188, "width": 115, "height": 115 },
        {"id": 8, "x": 140, "y": 380, "width": 110, "height": 110 },
        {"id": 9, "x": 340, "y": 380, "width": 110, "height": 110 }
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
            "path": [[120,360], [480,360], [480,510], [120,510]]
        },
        {
            "type": "polygon",
            "line_width": 4,
            "line_color": "black",
            "path": [[120,360], [480,360], [480,510], [120,510]]
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

