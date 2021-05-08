

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

// AZ macro
mst.key_pattern_list["az_macro"] = {
	"name": "AZ Macro",
	"pin": {
		"row": [],
		"col": [],
		"direct": [23, 22, 21, 19, 16, 17, 5, 18],
		"touch": []
	},
	"status_pin": 32,
	"rgb_pin": -1,
	"rgb_len": -1,
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


// AZ 66JP
mst.key_pattern_list["az_66jp"] = {
	"name": "AZ 66JP",
	"pin": {
		"row": [35, 34, 39, 36, 23],
		"col": [1, 3, 19, 18, 5, 4, 0, 2, 15, 32, 33, 27, 12, 13],
		"direct": [],
		"touch": []
	},
	"status_pin": -1,
	"rgb_pin": 14,
	"rgb_len": 67,
	"led_num": [
		52, 51, 25, 22, 24,  53, 50, 26, 21, 23,
		54, 49, 27, 20, -1,  55, 48, 28, 19, -1,
		56, 47, 29, 18,  0,  57, 46, 30, 17,  1,
		58, 45, 31, 16,  2,  59, 44, 32, 15,  3,
		60, 43, 33, 14,  4,  61, 42, 34, 13,  5,
		62, 41, 35, 12,  6,  63, 40, 36, 11,  7,
		64, 39, 37, -1,  8,  65, 66, 38, 10,  9
	],
	"key_matrix": [
		0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 66,
		1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, -1, -1,
		2, 7, 12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, -1,
		3, 8, 13, 18, 23, 28, 33, 38, 43, 48, 53, 58, 68, -1, -1,
		4, 9, -1, -1, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69, -1
	],
	"size": {"width": 1355, "height": 445},
	"keys": [
		{"id": 0, "x": 8, "y": 6, "width": 66, "height": 66 },
		{"id": 5, "x": 98, "y": 6 , "width": 66, "height": 66 },
		{"id": 10, "x": 189, "y": 6 , "width": 66, "height": 66 },
		{"id": 15, "x": 279, "y": 6 , "width": 66, "height": 66 },
		{"id": 20, "x": 370, "y": 6 , "width": 66, "height": 66 },
		{"id": 25, "x": 460, "y": 6 , "width": 66, "height": 66 },
		{"id": 30, "x": 551, "y": 6 , "width": 66, "height": 66 },
		{"id": 35, "x": 642, "y": 6 , "width": 66, "height": 66 },
		{"id": 40, "x": 733, "y": 6 , "width": 66, "height": 66 },
		{"id": 45, "x": 824, "y": 6 , "width": 66, "height": 66 },
		{"id": 50, "x": 914, "y": 6 , "width": 66, "height": 66 },
		{"id": 55, "x": 1005, "y": 6 , "width": 66, "height": 66 },
		{"id": 60, "x": 1096, "y": 6 , "width": 66, "height": 66 },
		{"id": 65, "x": 1186, "y": 6 , "width": 66, "height": 66 },
		{"id": 66, "x": 1277, "y": 6 , "width": 66, "height": 66 },

		{"id": 1, "x": 16 , "y": 96, "width": 99, "height": 66 },
		{"id": 6, "x": 143, "y": 96, "width": 66, "height": 66 },
		{"id": 11, "x": 234, "y": 96, "width": 66, "height": 66 },
		{"id": 16, "x": 324, "y": 96, "width": 66, "height": 66 },
		{"id": 21, "x": 416, "y": 96, "width": 66, "height": 66 },
		{"id": 26, "x": 506, "y": 96, "width": 66, "height": 66 },
		{"id": 30, "x": 596, "y": 96, "width": 66, "height": 66 },
		{"id": 36, "x": 688, "y": 96, "width": 66, "height": 66 },
		{"id": 41, "x": 778, "y": 96, "width": 66, "height": 66 },
		{"id": 46, "x": 869, "y": 96, "width": 66, "height": 66 },
		{"id": 51, "x": 959, "y": 96, "width": 66, "height": 66 },
		{"id": 56, "x": 1050, "y": 96, "width": 66, "height": 66 },
		{"id": 61, "x": 1141, "y": 96, "width": 66, "height": 66 },

		{"id": 2, "x": 16, "y": 187, "width": 115, "height": 66 },
		{"id": 7, "x": 166, "y": 187, "width": 66, "height": 66 },
		{"id": 12, "x": 256, "y": 187, "width": 66, "height": 66 },
		{"id": 17, "x": 347, "y": 187, "width": 66, "height": 66 },
		{"id": 22, "x": 438, "y": 187, "width": 66, "height": 66 },
		{"id": 27, "x": 529, "y": 187, "width": 66, "height": 66 },
		{"id": 32, "x": 619, "y": 187, "width": 66, "height": 66 },
		{"id": 37, "x": 710, "y": 187, "width": 66, "height": 66 },
		{"id": 42, "x": 801, "y": 187, "width": 66, "height": 66 },
		{"id": 47, "x": 891, "y": 187, "width": 66, "height": 66 },
		{"id": 52, "x": 982, "y": 187, "width": 66, "height": 66 },
		{"id": 57, "x": 1073, "y": 187, "width": 66, "height": 66 },
		{"id": 62, "x": 1164, "y": 187, "width": 66, "height": 66 },

		{"id": 67, "x": 1262, "y": 100, "width": 66, "height": 150 },

		{"id": 3, "x": 16, "y": 278, "width": 165, "height": 66 },
		{"id": 8, "x": 212, "y": 278, "width": 66, "height": 66 },
		{"id": 13, "x": 302, "y": 278, "width": 66, "height": 66 },
		{"id": 18, "x": 393, "y": 278, "width": 66, "height": 66 },
		{"id": 23, "x": 483, "y": 278, "width": 66, "height": 66 },
		{"id": 28, "x": 575, "y": 278, "width": 66, "height": 66 },
		{"id": 33, "x": 665, "y": 278, "width": 66, "height": 66 },
		{"id": 38, "x": 756, "y": 278, "width": 66, "height": 66 },
		{"id": 43, "x": 846, "y": 278, "width": 66, "height": 66 },
		{"id": 48, "x": 937, "y": 278, "width": 66, "height": 66 },
		{"id": 53, "x": 1027, "y": 278, "width": 66, "height": 66 },
		{"id": 58, "x": 1118, "y": 278, "width": 66, "height": 66 },
		{"id": 68, "x": 1215, "y": 278, "width": 115, "height": 66 },

		{"id": 4, "x": 8, "y": 369, "width": 83, "height": 66 },
		{"id": 9, "x": 121, "y": 369, "width": 66, "height": 66 },
		{"id": 24, "x": 461, "y": 369, "width": 66, "height": 66 },
		{"id": 29, "x": 551, "y": 369, "width": 66, "height": 66 },
		{"id": 34, "x": 642, "y": 369, "width": 66, "height": 66 },
		{"id": 39, "x": 733, "y": 369, "width": 66, "height": 66 },
		{"id": 44, "x": 824, "y": 369, "width": 66, "height": 66 },
		{"id": 49, "x": 914, "y": 369, "width": 66, "height": 66 },
		{"id": 54, "x": 1005, "y": 369, "width": 66, "height": 66 },
		{"id": 59, "x": 1096, "y": 369, "width": 66, "height": 66 },
		{"id": 64, "x": 1186, "y": 369, "width": 66, "height": 66 },
		{"id": 69, "x": 1277, "y": 369, "width": 66, "height": 66 },
	],
	"parts": [
		{
			"type": "polygon",
			"fill_color": "#666",
			"fill": true, // 塗りつぶし
			"path": [[2,2], [1353,2], [1353,443], [2,443]]
		},
		{
			"type": "polygon",
			"line_width": 4,
			"line_color": "black",
			"path": [[2,2], [1353,2], [1353,443], [2,443]]
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

// AZ-Macro液晶モジュール
mst.option_list["display_m"] = {
	"keyboard_type": ["az_macro"], // 対応しているキーボードタイプ
	"name": "液晶"
};

// AZ-66JP液晶モジュール
mst.option_list["display_66jp"] = {
	"keyboard_type": ["az_66jp"], // 対応しているキーボードタイプ
	"name": "液晶"
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
	"5": "マウス移動",
	"6": "暗記ボタン"
};

