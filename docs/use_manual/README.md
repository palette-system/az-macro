# 基本操作マニュアル
AZ-Macroの基本操作説明をします。
<br><br>

## 本体説明
![本体説明](/images/btn_detail.jpg)  


### 緑LED
|  状態  |  ステータス  |
|  --  |  --  |
|  消灯  |  電源OFF  |
|  点滅（ゆっくり）  |  設定モード、WIFIアクセスポイント  |
|  点滅（早い）  |  WEBフック中、ファームウェア書込み中  |
|  点滅（２回点灯）  |  WIFI接続中  |
|  点灯  |  電源ON  |


### 赤LED
|  状態  |  ステータス  |
|  --  |  --  |
|  消灯  |  充電無し、充電完了  |
|  点灯  |  充電中  |

※ 充電しながら電源ONにした場合、充電が完了しても赤LEDが点灯したままになります。

### 電源SW
|  状態  |  ステータス  |
|  --  |  --  |
|  上  |  電源OFF  |
|  下  |  電源ON  |


### USB入力
※ USBは充電用の電源入力のみです。接続している間リチウムバッテリーの充電が行われます。

### キースイッチ
各キーを押したまま電源をONにするとそれぞれ起動モードが変わります。
|  スイッチ  |  起動モード  |
|  --  |  --  |
|  ０キー  |  設定モードで起動  |
|  １キー  |  -  |
|  ２キー  |  -  |
|  ３キー  |  -  |
|  ４キー  |  レイヤー２をデフォルトにして起動  |
|  ５キー  |  レイヤー３をデフォルトにして起動  |
|  ６キー  |  レイヤー４をデフォルトにして起動  |
|  ７キー  |  レイヤー５をデフォルトにして起動  |

<br><br>

## 通常起動
通常起動中は緑LEDが点灯した状態で、PC、スマートフォンからBluetoothでキーボードとして認識できます。<br>
※ WIFI設定をしていると電源ONにした時に設定したWIFIに接続し、接続完了後Bluetoothキーボードとして認識するようになります。

<br><br>

## 設定モード起動
０キーを押したまま電源をONにすると設定モードとして起動し、緑LEDがゆっくり点滅した状態になります。<br>
設定モード中はWIFIのアクセスポイントとして動作していて、PC、スマートフォンからWIFI接続できます。<br>
設定モードの詳しい説明は設定マニュアルをご覧下さい。<br>
[設定マニュアル](/docs/az-macro-setting-manual.pdf)

<br><br>

## 拡張ポート
外部接続用の拡張ポートが付いています。<br>
![拡張ポート](/images/connecter.jpg)  

### CONN１
ESP32-WROOM-32 へ書き込みを行うポートです。<br>
スイッチサイエンスで購入できる「FLINT ESP Programmer」とピン配置が互換していてそのまま接続できます。<br>
またコンスル―対応のビアサイズになっているので、コンスル―を使用すれば本体へのはんだ付け無しに接続できます。<br>
[FLINT ESP Programmer](https://www.switch-science.com/catalog/5241/)


|  ピン  |  内容  |
|  --  |  --  |
|  １  |  EN  |
|  ２  |  TX  |
|  ３  |  RX  |
|  ４  |  VIN  |
|  ５  |  IO0  |
|  ６  |  GND  |

<br><br>


### CONN２
いろいろなセンサーやスピーカーなどの外部拡張ができるポートです。

|  ピン  |  内容  |
|  --  |  --  |
|  １  |  GND  |
|  ２  |  IO２５  |
|  ３  |  IO２６  |
|  ４  |  IO１２  |
|  ５  |  IO２７  |
|  ６  |  ３．３V OUT  |

<br><br>