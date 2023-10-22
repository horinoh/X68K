# X68KZ

## UART 接続
### 接続
- X68000Z の UART ケーブル と シリアル USB 変換アダプタ を以下のように接続する
    |UART ケーブル|シリアル USB アダプタ|
    |----|----|
    |RX (赤)|TX|
    |TX (青)|RX|
    |GND (緑)|GND|
- UART ケーブルを X68000Z へ、シリアル USB 変換アダプタを PC へ接続する

### PC側 ([TeraTerm](https://ttssh2.osdn.jp/))
- シリアル接続
- 設定 - 端末 - コーディング受信、送信の文字コードを SJIS に
- 通信が安定しないときは低いボーレートにする

### 使い方
- X68000Z 側で以下のように入力すると、制御が PC 側(TeraTerm) へ
    ~~~
    $CTTY AUX
    ~~~
- PC 側(TeraTerm) で以下のように入力すると、制御が X68000Z 側に戻る
    ~~~
    $CTTY CON
    ~~~

<!--
## [リモートドライブ](https://github.com/yunkya2/x68kzremotedrv/tree/main)
- ユーザ名の確認
    ~~~
    $echo %username%
    ~~~
- パスワードの確認
    - a
- ワークグループの確認
    - 特に何もしていなければ "WORKGROUP" になっているはず
    - スタートメニュー右クリック - システム - ドメインまたはワークグループ
- サーバー名の確認
    - スタートメニュー右クリック - システム - デバイス名

## [DiskExplorer](https://hp.vector.co.jp/authors/VA013937/editdisk/index.html)
- Windows ツール
- 起動しUSBメモリ上の .HDS (x68000のHDDイメージファイル) を Human68k HDD SCSI 形式で開くと、ファイルエクスプローラーのようにファイル操作が可能
-->