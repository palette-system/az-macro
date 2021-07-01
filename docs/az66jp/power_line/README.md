# 電源について
AZ-66JPは無線接続なのでモバイルバッテリー等から給電すれば使用できます。<br>
給電用コネクタについては状況に応じて選べるようになっているのでこちらを参考にはんだ付けして下さい。<br>
<br>


## コネクタ接続
<table>
  <tr>
    <th>接続箇所</th>
    <th>形状</th>
    <th>備考</th>
  </tr>
  <tr>
    <td><img src="/images/az66jp/az66jp_pw_typec.jpg"></td>
    <td>USB Type－C</td>
    <td valign="top">・モバイルバッテリー、USBアダプタ、PCなどから5V給電<br><br>※ 接続部分に絶縁テープが貼ってあるのではがしてからはんだ付けして下さい。</td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/az66jp_pw_typeb.jpg"></td>
    <td>USB MicroB</td>
    <td valign="top">・モバイルバッテリー、USBアダプタ、PCなどから5V給電<br><br>
      ※ 専用の「バッテリー内蔵プレートセット」を使用する場合はこちらのMicroBコネクタを使用して下さい。
    </td>
  </tr>
  <tr>
    <td><img src="/images/az66jp/az66jp_pw_bat.jpg"></td>
    <td>その他電源</td>
    <td valign="top">
    ■ 主な対応電池<br>
    　・単三電池 3～4本<br>
    　・18650（PSEマーク付きの物）<br>
    <br>
    電圧は 3.5～8V で、電流は 500mA 必要です。<br><br>
    ※ 8V 以上の電圧を流すと壊れます。<br>
    ※ CR2021などのボタン電池では電流が足りません。<br>
    ※ 電池を接続した状態でUSBコネクタから給電すると液漏れ発火等の原因となりますのでご遠慮ください。<br>
    </td>
  </tr>
</table>

<br><br>

## 電源部分までの経路
<table>
  <tr>
    <td valign="top"><img src="/images/az66jp/az66jp_pw.jpg"></td>
    <td valign="top">
      上部のコネクタ部分から電源が入り、真ん中あたりの「VUSB、VIN、GND」のコネクタを経由して下部の電源スイッチに繋がっています。<br>
    </td>
  </tr>
  <tr>
    <td valign="top"><img src="/images/az66jp/az66jp_pw_jump.jpg"></td>
    <td valign="top">
      真ん中のコネクタ部分にリチウムバッテリーの充電モジュールなどを後から追加できるようにしていますが、通常は付属しているジャンパーで「VUSB」と「VIN」ショートして繋げて下さい。
    </td>
  </tr>
</table>


