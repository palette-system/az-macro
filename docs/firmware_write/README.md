# ファームウェアの初期セットアップ
AZ-Macroのファームウェアの初期セットアップ手順の説明をします。  
  
  
## 対象のbinファイルのダウンロード
まずはアップデートするbinファイルをgithubからダウンロードします。  
下記リンクを開き対象のbinファイルをダウンロードして下さい。  

[ファームウェア リスト リンク](/firmware/bin/)  
  


対象のファイルを選びます。  
![ファイルの選択](/images/github_bin.png)  
  
  
「Download」を押します。  
![ファイルの選択](/images/github_bin_download.png)  
  
  
「ファイルを保存する」を選択して「OK」を押します。  
![ファイルの選択](/images/github_bin_download_ok.png)  
  
  
## AZ-Macroにバッテリーを繋ぎ電源をONにする
まずバッテリーのPHプラグを出っ張りがある方を上にしてPCBボードへ接続して下さい。<br><br>
プラグは硬めなので強く差し込んで下さい。写真の所まで差し込めたらOKです。<br><br>

![ファイルの選択](/images/batset.jpg)  
<br><br>

バッテリーが接続できると表面にあるスイッチを下に下げれば電源が入ります。<br><br>
電源が入ると緑色の電源LEDが点滅します。<br><br>

![ファイルの選択](/images/green_led.jpg)  
<br><br>

  
## 設定画面からファームウェア書込み

- AZ-Macroの緑色のLEDが点滅してWiFiのアクセスポイントとなっているので、PCからAZ-MacroのWiFiへ接続します。
  
  
- 接続できるとファームウェア書込み画面が表示されます。  
![ファイルの選択](/images/firm_setup.jpg)  
  
  
- ダウンロードしたbinファイルを選択します  
![ファイルの選択](/images/firm_setup_file.jpg)  
  
  
- 「書込み」を押します  
  
  
- binファイルがAZ-Macroに送られます  
![ファイル送信中](/images/firm_setup_upload.jpg)  
  
  
- 送信が完了するとAZ-Macroがファームウェア書込み作業が始まります。(1分ほどかかりますのでそのままお待ち下さい)  
![ファームウェア更新中](/images/firm_setup_write.jpg)  
  
  
- 完了すると画面が切り替わりますのでページを閉じて下さい。  
![完了](/images/firm_setup_comp.jpg)  
  
  
- 以上でファームウェアの初期セットアップ完了です。

