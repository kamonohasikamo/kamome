<?php
  $classname = '';
  if(!empty($_POST['classname'])){
    $classname = $_POST['classname'];
  }else if(!empty($_GET['classname'])){
    $classname = $_GET['classname'];
  }
  $kouginum = "";
  if(!empty($_POST['kouginum'])){
    $kouginum = $_POST['kouginum'];
  }else if(!empty($_GET['kouginum'])){
    $kouginum = $_GET['kouginum'];
  }
  try{
  $sql = new PDO('mysql:host=;dbname=;charset=utf8','',''); //host name, database name,user name, password
  print '接続に成功しました。<br>';
  print 'アンケートは５段階評価を行っています。<br>';
  print '1.とても当てはまる、2.少し当てはまる、3.どちらでもない、4.あまり当てはまらない、5.当てはまらない<br>';
  echo '<table border="1">';
  echo '<tr>';
  echo '<th>講義番号</th>';
  echo '<th>学籍番号</th>';
  echo '<th>氏名</th>';
  echo '<th>クラス名（科目名）</th>';
  echo '<th>日付情報</th>';
  echo '<th>[1]講義内容を理解できたか</th>';
  echo '<th>[2]講義内容に興味が湧いた</th>';
  echo '<th>[3]講義内容へ満足できた</th>';
  echo '<th>[4]授業スタイルを継続していい</th>';
  echo '<th>感想</th>';
  echo '</tr>';
  if(!empty($kouginum) && !empty($classname)){
  foreach ($sql->query("SELECT * FROM data WHERE kouginum=".'"'.$kouginum.'"'." AND classname=".'"'."$classname".'"') as $row) {
    echo '<tr align="center">';
    echo "<td>$row[kouginum]";
    echo "<td>$row[gakusekinum]";
    echo "<td>$row[name]";
    echo "<td>$row[classname]";
    echo "<td>$row[day]";
    echo "<td>$row[anketo1]";
    echo "<td>$row[anketo2]";
    echo "<td>$row[anketo3]";
    echo "<td>$row[anketo4]";
    echo "<td>$row[kansou]";
    echo '</tr>';
  }
  }else if(!empty($kouginum) || !empty($classname)){
    foreach ($sql->query("SELECT * FROM data WHERE kouginum=".'"'.$kouginum.'"'." OR classname=".'"'."$classname".'"') as $row) {
    echo '<tr align="center">';
    echo "<td>$row[kouginum]";
    echo "<td>$row[gakusekinum]";
    echo "<td>$row[name]";
    echo "<td>$row[classname]";
    echo "<td>$row[day]";
    echo "<td>$row[anketo1]";
    echo "<td>$row[anketo2]";
    echo "<td>$row[anketo3]";
    echo "<td>$row[anketo4]";
    echo "<td>$row[kansou]";
    echo '</tr>';
  }
  }else{
    echo "<h1>エラー！文字を入れてください。</h1>";
  }
  echo "<br><p>検索文字列↓</p><p>講義番号:$kouginum</p>";
  echo "<p>クラス名:$classname</p>"; 
  } catch( PDOException $e){
    print "接続エラー：{$e->getMessage()}";
  }
  $sql=null;
?>
