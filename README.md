# X68K

## [エミュレータ](http://retropc.net/pi/xm6/index.html)
### 準備
- [シャープのソフトウエア](http://www.retropc.net/x68000/software/sharp/)
    - X68BIOSE.LZH, HUMN302I.LZH を展開する
        - IPLROM.DAT, HUMAN302.XD ができる
- ユーティリティー (xm6_util_20220608.zip) を展開する
    - HUMAN302.XDF をここへコピーする
    - XM6Util.exe を実行し、3 つの「～を合成する」ボタンから、CGROM.TMP, SCSIINROMDAT, SCSEXROM.DAT の 3 ファイルを作成する
- エミュレータ (xm6_typeg_334_20220823.zip) を展開する
    - xm6_typeg_334_20220823\x64 以下に IPLROM.DAT, CGROM.TMP, SCSIINROMDAT, SCSEXROM.DAT の 4 ファイルをコピーする
- HDD
    - イメージ作成
        - ツール - イメージ作成 - SCSI ハードディスクイメージの作成 (ここではデフォルト値 100 M にした)
        - ツール - オプション - SCSI 
		    - 内蔵タイプ
		    - ドライブ数を 3 に増やす - 0 無効 をクリックして上記で作成したイメージを選択する
            - ファイル - リセットで再起動
    - フォーマット、インストール
        - メディア - フロッピーディスク0 - 開く -  HUMAN302.XDF
        - $format とするとメニューが開く
            - SCSI 装置 - ハードディスク(上記で作成したイメージ) - 装置初期化 - 領域確保 で以下のような設定にする
			    - 容量 : (ここでは) 99
			    - ボリューム名 : 適当につける
			    - システム転送 : する
            -  実行 - 終了
        - $install とするとメニューが開く
            - 辞書ディスクが無いと怒られるが、中止\<A\> - バッチ処理を中止しますか \<Y/N\> で N として中止せずに進める
            - メディア - フロッピーディスク0 - イジェクト
			- ファイル - リセットで再起動
        - $switch とするとメニューが開く
            - BOOT を SCSI から STD へ変更しておく (フロッピーが入ってなければ自動的に HDD から起動するみたい)
- [Windows とのファイルやり取り](http://coexe.web.fc2.com/xm6.html)
    - WindrvXM.XDF をダウンロード
    - メディア - フロッピーディスク0 - 開く -  WindrvXM.XDF
    - 以下のようにして、フロッピー(b:) から HDD(a:) へ WindrvXM.XDF をコピー
        ~~~
	    $copy b:¥WindrvXM.SYS a:
        ~~~
    - 起動時に有効にする
        - $ed CONFIG.SYS とするとエディタが開くので、以下のように追記
            ~~~
            DEVICE = ¥WindrvXM.SYS
            ~~~
        - ESC + X で保存して終了 (ESC + Q だと破棄)
        - ファイル - リセットで再起動
        - 一旦エミュレータを終了し、XM6.ini を開き、以下のようにする
            ~~~
            [Windrv]
			Enable=1
            ~~~
    - 設定
        - ツール - オプション - Windrv
            - ドライブ数が 0 だと Windows の全フォルダがアクセス対象となる
            - 制限したい場合は、ドライブ数を増やした上でパスを指定する

    - 例えば Windows C: <-> X69 d: に割りあてられた場合なら、以下のようにして Windows C: の内容が見れる
        ~~~
        $dir d:
        ~~~
- コマンドラインから起動
    - 予め switch コマンドで BOOT を STD へしておく
    - 以下のようにすれば指定のフロッピーで起動できるみたい
        ~~~
        $xm6g.exe XXX.2HD
        ~~~
## [ソフトウエアライブラリ](http://retropc.net/x68000/software/)
- [GCC](http://retropc.net/x68000/software/develop/c/gcc_mariko/)
- [HAS](http://retropc.net/x68000/software/develop/as/has060/)
- [HLK](http://retropc.net/x68000/software/develop/lk/hlkev/)
- [XC](http://retropc.net/x68000/software/sharp/xc21/)

## [クロス開発](https://github.com/yosshin4004/xdev68k)
- XM6 で実行
    - (XM6 上から) Msys のディレクトリへ移動しておく
        ~~~
        $d:
        $cd XXX\xdev68k\example\hello
        ~~~
    - (クロスコンパイルしてできた) .X ファイルがあると思うので実行する
        ~~~
        $MAIN.X
        ~~~