<?php
  $kouginum = '';
  if(!empty($_POST['kouginum'])){
    $kouginum = $_POST['kouginum'];
  }
  $gakusekinum = '';
  if(!empty($_POST['gakusekinum'])){
    $gakusekinum = $_POST['gakusekinum'];
  }
  $name = '';
  if(!empty($_POST['name'])){
    $name = $_POST['name'];
  }
  $classname = '';
  if(!empty($_POST['classname'])){
    $classname = $_POST['classname'];
  }
  $day = '';
  if(!empty($_POST['day'])){
    $day = $_POST['day'];
  }
  $anketo1 = '';
  if(!empty($_POST['anketo1'])){
    $anketo1 = $_POST['anketo1'];
  }
  $anketo2 = '';
  if(!empty($_POST['anketo2'])){
    $anketo2 = $_POST['anketo2'];
  }
  $anketo3 = '';
  if(!empty($_POST['anketo3'])){
    $anketo3 = $_POST['anketo3'];
  }
  $anketo4 = '';
  if(!empty($_POST['anketo4'])){
    $anketo4 = $_POST['anketo4'];
  }
  $kansou = '';
  if(!empty($_POST['kansou'])){
    $kansou = $_POST['kansou'];
  }
  
  $db = new mysqli('','','','');//host name,user name, password,databases name
  if(!$db){
    print("データベースの接続に失敗しました。");
  }
  print '接続に成功しました。<br>';
  
  $cmd = 'INSERT INTO data(
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
  "'.$kouginum.'",
  "'.$gakusekinum.'",
  "'.$name.'",
  "'.$classname.'",
  "'.$day.'",
  "'.$anketo1.'",
  "'.$anketo2.'",
  "'.$anketo3.'",
  "'.$anketo4.'",
  "'.$kansou.'"'.');';
  $result = mysqli_query($db,$cmd);
  if(!$result){
    print("データ追加に失敗しました。<br>");
  }
  print '情報をデータベースに追加しました。<br>';

?>
