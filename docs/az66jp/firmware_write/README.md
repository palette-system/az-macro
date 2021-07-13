# ファームウェアの初期セットアップ
AZ-66JPのファームウェアの初期セットアップ手順の説明をします。  
  <br><br>
  
## 対象のbinファイルのダウンロード
まずは書込みするbinファイルをgithubからダウンロードします。  
下記リンクを開き最新のbinファイルをダウンロードして下さい。  
  <br><br>

[こちらからファームウェアをダウンロード](/firmware/bin/az66jp/)  
  <br><br><br>
  


最新のファイルを選びます。  
![ファイルの選択](/images/az66jp/firmware_select.jpg)  
  
  
「Download」を押します。  
![ファイルの選択](/images/az66jp/firmware_download.jpg)  
  
  <br><br>
  
## AZ-66JPの電源をONにする
USBコネクタにモバイルバッテリーなどの電源を接続し、スイッチをONにします。

![電源スイッチ](/images/az66jp/power_switch.jpg)  
<br><br>


  
## 設定画面からファームウェア書込み

- AZ-66JPの電源を入れるとスイッチチェックのプログラムが動きますが、この状態でPCからAZ-66JPのWiFiへ接続できるようになっています。<br><br>
![ファイルの選択](/images/az66jp/switch_check.jpg)<br>
![ファイルの選択](/images/az66jp/wifi_ap.jpg)
  
  <br><br>
  
- Wifiに接続できるとファームウェア書込み画面が表示されます。  
![ファイルの選択](/images/firm_setup.jpg)  
　※ 自動的に設定ページが開かれない場合はWifi接続後ブラウザから http://192.168.4.1/ を開いて下さい。  
  
  <br><br>
  
- ダウンロードしたbinファイルを選択して「書込み」を押すと、AZ-66JPにファイルが送られます。
![ファイル送信中](/images/firm_setup_upload.jpg)  
  
  <br><br>
  
- 完了すると画面が切り替わりますのでページを閉じて下さい。  
![完了](/images/firm_setup_comp.jpg)  
  
  <br><br>
  
- 以上でファームウェアの初期セットアップ完了です。

