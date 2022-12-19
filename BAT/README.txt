libgnu.a から libgnu.l を作成

オブジェクトファイルのリストは以下のように得る
$ar /l libgnu.a

各々のオブジェクトファイルを抽出
$ar /x libgnu.a XXX.o

各々のオブジェクトファイルを libgnu.l へ追加
$lib /u gnulib.l XXX.o


