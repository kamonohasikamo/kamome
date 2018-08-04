コメントペーパーの情報を入力する画面，検索する画面の実装を行った．
検索画面からは科目名と講義番号から検索することを可能にした．
追加画面として，学籍番号，氏名，クラス名(科目名)，日付，アンケート情報，感想を入力することを可能にした．


実装設計としては以下のとおりである．
final.htmlに情報を追加する画面を
final_index.htmlに情報を検索する画面を実装した．

final.htmlに入力された値をそれぞれ変数に格納し，
insert.phpで情報を追加するように指定する．
情報はデータベースで管理されており，各情報をデータベースに追加する処理を行う．
追加方法として，INSERT INTO data　VALUES(値…);というクエリを実行するように指定する．

また，final_index.htmlでは，講義番号，クラス名(講義名)を入力すると，その値をsearch.phpに送り，その値から検索するように指定する．
両方入力していないのに送信ボタンを押すとエラーが表示されるように例外処理を行い，
どちらか片方だけ入力した場合はOR検索，両方入力した場合はAND検索を行うように指定する．
具体的には
SELECT * FROM data WHERE classname="値"　ORまたはAND　classnum="値";
と指定する．

以下にデータベースのテーブル情報を記載する．
列名：概要：例

kouginum: 講義回数：第1回なら1

gakusekinum：学籍番号：99999999

name：名前：○○○○（氏名）

classname:クラス名（科目名）：○○○○○○○○（講義名）

day：日付：20180707

anketo1～4:アンケート：１～５の五段階数値
kansou：感想：文字列(２００字以内とする）


作成したテーブル情報

CREATE TABLE data(
  
kouginum int,
  
gakusekinum int,
  
name nchar(20),
  
classname nchar(100),
  
day datetime,
  
anketo1 int,
  
anketo2 int,
  
anketo3 int,
  
anketo4 int,
  
kansou nchar(200)

);


INSERT文の一例：
INSERT INTO data(
  
kouginum,
  
gakusekinum,
  
name,
  
classname,
  
day,
  
anketo1,
  
anketo2,
  
anketo3,
  
anketo4,
  
kansou

)VALUE(
  
"2",
  
"99999999",
  
"○○○○（氏名）",
  
"○○○○○○○○（講義名）",
  
"20180723",
  
"1",
  
"1",
  
"1",
  
"1",
  
"まあまあです。"
);


再現するための手順
１．データベースを作成する．
２．テーブルを作成する．(データベース名，テーブル名は任意の文字列)
テーブル情報は上記に記載した通りである．
３．今回のファイル一式をvar/www/html下に置く．
４．insert.php，search.phpのクエリの部分をデータベース名等変更しておく．
５．http://localhost/index.htmlを開く．
６．情報を入力し，送信ボタンを押すと次ページでデータベースに接続しましたと表示されれば成功である．
７．コメントペーパー参照ボタンを押すと検索画面が現れる．
８．情報を入力し，先ほど追加した情報が表示されれば成功である．
９．各ページの戻るボタンを押すともう一方のページが表示されるはずである．

以上が実行手順である．

