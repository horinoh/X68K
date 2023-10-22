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

- [キーボード設定](http://retropc.net/x68000/software/system/key/keywitch/)
    - KEYWB213.LZH を展開する - KeyWEnv.Lzh を展開する
    - KeyWitch.x, ascii.env(英語キーボードの場合) を適当な場所へコピー
        ~~~
        $copy d:KeyWitch.x a:
        $copy d:KeyWEnv\ascii.env a:
        ~~~
    - CONFIG.SYS に以下のように記述
        ~~~
        DEVICE=KeyWitch.x -e ascii.env
        ~~~
    - ファイル - リセットで再起動
    - 一部のキーがおかしいのを修正
        - ツール - オプション - キーボード - 編集

### 使用
- コマンドラインから起動
    - 予め switch コマンドで BOOT を STD へしておく
    - 以下のようにすれば指定のフロッピーで起動できるみたい
        ~~~
        $xm6g.exe XXX.2HD
        ~~~
- ソフトウエアキーボード
    - ツール - ソフトウエアキーボード
- ジョイスティック
    - コントローラを刺す
    - ツール - オプション - ジョイスティック - タイプ - (例えば)ポート1、デバイスA のプルダウンから選択する

### C
- アセンブラ、リンカ
    - [HAS](http://retropc.net/x68000/software/develop/as/has/)
    - [HLK](http://retropc.net/x68000/software/develop/lk/hlkev/)
        - HAS, HLK はパスの通っている A:\BIN に配置することにした
- コンパイラ
    - A:\CC を作り、ここに配置することにした
        - A:\CC は path に通しておく
    - [GCC](http://retropc.net/x68000/software/develop/c/gcc_mariko/)
        - GCC142 の中身を A:\CC へコピー
    - [XC](http://retropc.net/x68000/software/sharp/xc21/)
        - システムディスク 1 の BIN\AR.X, LIB.X を A:\BIN へコピー
        - システムディスク 2 の INCLUDE, LIB を A:\CC\INCLUDE, A:\CC\LIB へコピー
            - INCLUDE
                - DOSCALL.MAC をコピーして DOSCALL.EQU を作っておく
    - [gnulib](https://www.vector.co.jp/soft/dl/x68/prog/se023312.html)
        - libgnu.a を取得
            - オブジェクトファイルリストを得る
                ~~~
                $ar /l libgnu.a
                ~~~
            - オブジェクトファイルを抽出
                ~~~
                $ar /x libgnu.a XXX.o
                ~~~
            - libgnu.l への追加
                ~~~
                $lib /u gnulib.l XXX.o
                ~~~
        - gnulib.l を A:\CC\LIB へコピー
    
- 共通
    ~~~
    rem インクルード、ライブラリパス、拡張子
    set include=A:\CC\INCLUDE
    set lib=A:\CC\LIB
    set GCC_LIB=.l

    rem アセンブラ、オプション
    set GCC_AS=has.x
    set HAS=-u -z

    rem リンカ、オプション
    set GCC_LINK=hlk.r
    set SILK=-l

    rem GCC オプション
    set GCC_OPTION=AEFGILMTW+
    
    rem x68000 版 GCC の拡張
    set MARIKO=ABD

    rem テキストエディタ
    rem set MARINA=SUPERED
    ~~~
- LIBC
    ~~~
    set GCC_NO_XCLIB=yes
    ~~~
- XC
    ~~~
    rem set SILK=-l floatfnc.l
    set GCC_NO_XCLIB=
    ~~~
- コンパイル
    ~~~
    $gcc -O main.c FLOATEML.L
    ~~~
    - SRAND, ECVT, FCVT が無いと怒られたので FLOATEML.L を追加したら通った
    
<!--
## BASIC
- 起動
    ~~~
    $basic
    ~~~
- 終了
    ~~~
    $system
    ~~~
- 行番号付けなおし
    ~~~
    $renum
    ~~~
- コンフィグファイル
    - BASIC2\BASIC.CONF
- スプライトツール起動するには、BASIC内で以下のようにする
    ~~~
    $load "a:\etc\defsptool"
    $run
    ~~~
!-->

## [クロス開発](https://github.com/yosshin4004/xdev68k)
- [スプライト](https://github.com/yosshin4004/x68k_xsp)
<!--
    - iocscall.inc が無いと怒られる場合、コピーして iocsall.mac から iocscall.inc を作る
        - iocsall.mac は xdev68k\include\xc\ 以下にある
-->
- makefile
  - xdev68k からコピーした makefile を以下のように改変し include して使用している
    ~~~
    #EXECUTABLE = 

    #INCLUDE_FLAGS = ...
    INCLUDE_FLAGS += ...
    
    #C_SRCS = ...
    
    #ASM_SRCS = ...
    
    #LIBS = ...
    LIBS += ...
    ~~~
- XM6 で実行
    - (XM6 上から) Msys のディレクトリへ移動しておく 
    - 自分の環境では「:」は 「+」の所 (覚書)
        ~~~
        $d:
        $cd XXX\xdev68k\example\hello
        ~~~
    - Msys 上でコンパイル
    - (クロスコンパイルしてできた) .X ファイルがあると思うので実行する
        ~~~
        $MAIN.X
        ~~~
- This software includes the work that is distributed in the Apache License 2.0.

## サウンド
- [ツール]((http://retropc.net/x68000/software/sound/zmusic/zmusic3/))
    - 展開して A: に配置した
        - 再生
            ~~~
            //!< 予めやっておく必要がある
            $ZMSC3
            $ZMC -L

            //!< 再生
            $ZP3 XXX.[ZMS, ZMD]
            //!< 停止
            $ZP3 -s
            //!< トラック情報表示
            $ZP3 -q
            //!< ステータス表示 (ESCで終了)
            $ZSV
            ~~~
- [ライブラリ](http://www.z-z-z.jp/zmusic/library/Zm302_l.lzh)
    - 展開
        - エミュレータ上でコンパイル (無反応に見えるが中断せずに完了を待つ)
            ~~~
            $cd Zm302_l
            $MAKE
            ~~~
        - (ここでは) Zm302_l フォルダとして配置した
            - ZMSC3LIB.H はコンパイルでコケるので、ファイル末尾の文字を削除した
            ~~~
            Zm302_l/ZMSC3LIB.H
            Zm302_l/ZMSC3LIB.L
            ~~~

## Windows ツール

- [DiskExplorer](https://hp.vector.co.jp/authors/VA013937/editdisk/index.html)
    - このツールで .HDS (x68000のHDDイメージファイル)を Human68k HDD SCSI 形式で開くと、ファイルエクスプローラーのように操作が可能

## [X68KZ](https://github.com/horinoh/X68K/tree/master/X68KZ)

## 他
- サブモジュール更新に失敗する場合
    - サブモジュールの更新が origin/master 前提になっているのが原因、origin/main 等になっているサブモジュールだと更新に失敗してしまう
    - .gitmodules を開き、対象のサブモジュールの所に以下のように追記
        ~~~
        branch = main 
        ~~~

## リンク
- [X68000ライブラリ](http://retropc.net/x68000/)
- [GCC](http://retropc.net/x68000/software/develop/c/gcc_mariko/)
- [HAS](http://retropc.net/x68000/software/develop/as/has060/)
- [HLK](http://retropc.net/x68000/software/develop/lk/hlkev/)
- [XC](http://retropc.net/x68000/software/sharp/xc21/)
- [IOCS](https://datacrystal.romhacking.net/wiki/X68k:IOCS)
- [ZMUSIC](http://www.z-z-z.jp/zmusic/library/ZM3DLPG.htm)
