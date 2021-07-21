# 組み立て手順

<br><br>


## 使う道具
<table>
  <tr>
    <td><img src="/images/az66jp/dougu.jpg" width="400"></td>
    <td>
      プラスドライバー（小）<br>
      プラスドライバー（中）<br>
      ピンセット<br>
      はんだ<br>
      はんだごて<br>
      瞬間接着剤(バッテリー内蔵プレートで使用)
    </td>
  </tr>
</table>

<br><br>


## ダイオードのはんだ付け
<table>
  <tr>
    <td><img src="/images/az66jp/diode_1.jpg" width="400"></td>
    <td valign="top">
      <b>向き合わせ</b><br>
      ダイオードの横線が入っている方の向きを合わせてはんだ付けして下さい。<br>
      向きを間違えるとスイッチが動作しないので注意して下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/diode_2.jpg" width="400"></td>
    <td valign="top">
      １．　まずPCB上の片側にはんだを乗せます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/diode_3.jpg" width="400"></td>
    <td valign="top">
      ２．　ピンセットでダイオードをつかみながら①で付けたはんだ部分にくっつけます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/diode_4.jpg" width="400"></td>
    <td valign="top">
      ３．　反対側もはんだ付けして完了です。<br>
      １．～３．を66個分繰り返します。
    </td>
  </tr>
</table>

<br><br>

## カラーLEDのはんだ付け
<table>
  <tr>
    <td><img src="/images/az66jp/rgbled_1.jpg" width="400"></td>
    <td valign="top">
      <b>向き合わせ</b><br>
      PCBについている三角マークと、LEDの足の角が欠けている方向を一緒にして下さい。<br>
      向きを間違えると他のLEDも含め動作しなくなるので注意して下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/rgbled_2.jpg" width="400"></td>
    <td valign="top">
      １．　位置合わせ用にピンセット等で押さえながら１か所だけはんだ付けします。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/rgbled_3.jpg" width="400"></td>
    <td valign="top">
      ２．　残り３ヶ所もはんだ付けします。<br>
      １．～２．を66個分繰り返します。
    </td>
  </tr>
</table>

<br><br>

## スイッチ用PCBソケットのはんだ付け
<table>
  <tr>
    <td><img src="/images/az66jp/switch_socket_1.jpg" width="400"><br>
    <img src="/images/az66jp/switch_socket_2.jpg" width="400"></td>
    <td valign="top">
      ソケット用の穴にソケットを差し込み、矢印部分をはんだ付けします。<br>
      66個分繰り返します。
    </td>
  </tr>
</table>

<br><br>

## USBコネクタのはんだ付け
<table>
  <tr>
    <td><img src="/images/az66jp/usb_b_1.jpg" width="400"><br><img src="/images/az66jp/usb_b_2.jpg" width="400"></td>
    <td valign="top">
      PCBの裏側からUSBコネクタを差し込み矢印部分をはんだ付けします。<br>
      足が長くて他の場所と接触してしまいそうな場合は足を少し切って短くしてからはんだ付けして下さい。<br>
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/usb_b_3.jpg" width="400"></td>
    <td valign="top">
      PCBの表側の穴の部分もはんだ付けして下さい。<br>
      表側はトッププレートと接触する部分なのではんだは少な目が良いです。<br>
      <br>
      ※ ここではMicroBコネクタをはんだ付けしましたが、電源コネクタは選べるので好きなコネクタを付けて下さい。<br>
      　　参考 → <a href="/docs/az66jp/power_line/">リンク</a>
    </td>
  </tr>
</table>

<br><br>

## スイッチ接続の動作チェック
<table>
  <tr>
    <td><img src="/images/az66jp/test_1.jpg" width="400"><br><img src="/images/az66jp/jumper.jpg" width="400"></td>
    <td valign="top">
      66スイッチ全てはんだ付けが終わらない途中の状態でもスイッチの接触確認ができます。<br>
      まずPCB裏面の矢印部分にジャンパーを挿しこんで下さい。<br><br>
      ※ ここで「VUSB」と「VIN」の間に差し込んだジャンパーは完成後も抜かずに挿したままにして下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/test_2.jpg" width="400"></td>
    <td valign="top">
      PCBの表側のESP32の隣の穴にコンスル―を差し込んで、その上に液晶プレートを差し込んで下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/test_3.jpg" width="400"></td>
    <td valign="top">
      USBコネクタに電源を繋げるとチェックプログラムが起動します。<br>
      この状態ではんだ付けしたソケットにCherryMXスイッチを差し込んで押すと該当箇所が青くなります。
    </td>
  </tr>
</table>

<br><br>

## 電源スイッチのはんだ付け
<table>
  <tr>
    <td><img src="/images/az66jp/switch_1.jpg" width="400"></td>
    <td valign="top">
      スイッチをそのままはんだ付けすると高さが足りないので、スイッチの足の下にスペーサーを挟みます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/switch_2.jpg" width="400"></td>
    <td valign="top">
      PCBの表側からスイッチを差し込んで下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/switch_3.jpg" width="400"></td>
    <td valign="top">
      PCBの裏側からスイッチの足をはんだ付けします。<br>
      この時スイッチが斜めになったりしないよう気を付けて下さい。
    </td>
  </tr>
</table>

<br><br>


## 液晶プレートの固定
<table>
  <tr>
    <td><img src="/images/az66jp/spacer_1.jpg" width="400"><br><img src="/images/az66jp/spacer_2.jpg" width="400"></td>
    <td valign="top">
      PCBの裏側から6mmスペーサーと3mmネジを矢印の部分へ止めて下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/spacer_3.jpg" width="400"></td>
    <td valign="top">
      PCBを表向きにして矢印部分にコンスル―を差し込んで下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/spacer_4.jpg" width="400"></td>
    <td valign="top">
      その上に液晶プレートを乗せて、矢印部分を3mmネジで止めて下さい。
    </td>
  </tr>
</table>

<br><br>


## スタビライザーの取り付け
<table>
  <tr>
    <td><img src="/images/az66jp/plate_6.jpg" width="400"></td>
    <td valign="top">
      まずは赤色部分のPCBの表側左下のShiftキー用のスタビライザーを取り付けます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_7.jpg" width="400"></td>
    <td valign="top">
      スタビライザーの繋がっている金具部分を上にして、穴に差し込み引っ掛けます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_8.jpg" width="400"></td>
    <td valign="top">
      浮いたもう一個の穴の部分へ押し込むとスタビライザーが取り付けられます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_9.jpg" width="400"></td>
    <td valign="top">
      同じ要領で右側のエンター部分にもスタビライザーを取り付けて下さい。
    </td>
  </tr>
</table>

<br><br>


## ボトムプレートの組み立て
<table>
  <tr>
    <td><img src="/images/az66jp/plate_1.jpg" width="400"></td>
    <td valign="top">
      まずプレートに貼ってある保護シートをピンセットなどを利用してはがして下さい。<br><br>
      　※ バッテリー内蔵プレートを組み立てる場合はこの後の「バッテリー内蔵プレートへのバッテリー貼り付け」を行ってからスポンジの貼り付けをして下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_2.jpg" width="400"></td>
    <td valign="top">
      プレートの表用のスポンジAのテープシートもはがします。<br><br>
      　※ スポンジは1枚のシートになっていますが、切れ目が入っていて簡単に切り離せるので切り離して下さい。<br>
      　※ 見た目を重視するのであればボトムプレートにスポンジを付けずに組み立てると裏面も見れてカッコよくなります。<br>
      　※ スポンジの位置合わせが難しいため心配な方はスポンジを1/2、1/3にカットしてから少しずつ張り付けて下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_3.jpg" width="400"><br><img src="/images/az66jp/plate_4.jpg" width="400"></td>
    <td valign="top">
      ネジ穴の位置にスポンジの穴が重なるようにスポンジAをボトムプレートの表側に張り付けて下さい。<br><br>
      　※ USBコネクタ用の凹みがある方が表です。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_5.jpg" width="400"></td>
    <td valign="top">
      同じ要領でボトムプレートの裏側にスポンジBを張り付けて下さい。
    </td>
  </tr>
</table>

<br><br>


## バッテリー内蔵プレートへのバッテリー取り付け
<table>
  <tr>
    <td><img src="/images/az66jp/plate_bat_1.jpg" width="400"></td>
    <td valign="top">
      ボトムプレートの保護シートをはがしたら、写真の方向でモバイルバッテリーを接着します。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_bat_2.jpg" width="400"></td>
    <td valign="top">
      モバイルバッテリーの側面に瞬間接着剤をぬります。<br><br>
      ※ 他にボンドやテープ類などくっつけば何でも良いです。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_bat_3.jpg" width="400"></td>
    <td valign="top">
      この時裏側が平らになるように平らな場所に置いて乾かして下さい。<br>乾いたら接着完了です。<br><br>
      ※ 机とのくっつき防止のために画用紙などを敷くと良いです。
    </td>
  </tr>
</table>


<br><br>


## プレートの固定
<table>
  <tr>
    <td><img src="/images/az66jp/az66jp_pw_jump.jpg" width="400"></td>
    <td valign="top">
      PCBプレートの裏側の電源ラインを付属しているジャンパーで「VUSB」と「VIN」ショートして繋げて下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_10.jpg" width="400"></td>
    <td valign="top">
      ボトムプレートの上にPCBプレートを乗せます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_11.jpg" width="400"></td>
    <td valign="top">
      その上にトッププレートを乗せます。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/plate_12.jpg" width="400"><br><img src="/images/az66jp/plate_13.jpg" width="400"></td>
    <td valign="top">
      矢印の部分を14mmネジでとめて下さい。<br>
      この時のネジの締め具合で打鍵音が変わります。ゆるい方が静かで、固く締めるほどボトムプレートに振動が伝わりカチャカチャ音がします。<br>
      オススメはトッププレートを押すとトッププレートが沈むくらいゆるく止めた方が打鍵音が良いです。
    </td>
  </tr>
</table>

<br><br>




プレートの固定まで終われば組み立て完了です。<br>
後はキースイッチを差し込んで、キーキャップを取り付けて下さい。<br>
スイッチを差し込んでいる時も電源を入れるとスイッチの接触確認ができて便利です。<br>

<br>

<img src="/images/az66jp/switch_check.jpg" width="400">

