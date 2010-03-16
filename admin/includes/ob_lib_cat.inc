<?php
function list_authors() {
  global $dbhost, $dbuser, $dbpass,$dbname;
  global $editfile, $actfile;
  $connect = mysql_connect($dbhost, $dbuser,$dbpass)
    or die("unable to connect to server");
  mysql_select_db($dbname);
  $sql = "SELECT * FROM author ORDER BY lastname;";
  $result = mysql_query($sql);
  while($authors = mysql_fetch_array($result)) {
    echo "<tr><td><p>".$authors[1].", ".$authors[2]."</p></td>";
    echo "<td><p><a href=\"$editfile?action=author&id=".$authors[0]."\">edit</a></p></td>";
    echo "<td><p><a href=\"$actfile?action=delete&what=author&id=".$authors[0]."\">delete</a></p></td>";
  }
  mysql_free_result($result);
  mysql_close($connect);
}

function list_reviews() {
  global $dbhost, $dbuser, $dbpass,$dbname;
  global $editfile, $actfile;
  $connect = mysql_connect($dbhost, $dbuser,$dbpass)
    or die("unable to connect to server");
  mysql_select_db($dbname);
  $sql = "SELECT review.review_id,review.book_id,
          book.title_sw, book.title
          FROM review
          INNER JOIN book ON book.book_id = review.book_id
          ORDER BY book.title;";
  $result = mysql_query($sql);
  while($reviews = mysql_fetch_array($result)) {
    echo "<tr><td><p>$reviews[2] $reviews[3]</p></td>";
    echo "<td><p><a href=\"$editfile?action=review&id=".$reviews[0]."\">edit</a></p></td>";
    echo "<td><p><a href=\"$actfile?action=delete&what=review&book=".$reviews[1]."&id=".$reviews[0]."\">delete</a></p></td>";
  }
  mysql_free_result($result);
  mysql_close($connect);
}

function list_latest() {
  global $dbhost, $dbuser, $dbpass,$dbname;
  global $editfile, $actfile;
  $connect = mysql_connect($dbhost, $dbuser,$dbpass)
    or die("unable to connect to server");
  mysql_select_db($dbname);
  $sql = "SELECT review.review_id,review.book_id,
          book.title_sw, book.title
          FROM review
          INNER JOIN book ON book.book_id = review.book_id
          ORDER BY review.review_date desc limit 10;";
  $result = mysql_query($sql);
  while($reviews = mysql_fetch_array($result)) {
    echo "<tr><td><p>$reviews[2] $reviews[3]</p></td>";
    echo "<td><p><a href=\"$editfile?action=review&id=".$reviews[0]."\">edit</a></p></td>";
    echo "<td><p><a href=\"$actfile?action=delete&what=review&book=".$reviews[1]."&id=".$reviews[0]."\">delete</a></p></td>";
  }
  mysql_free_result($result);
  mysql_close($connect);
}

function get_authors() {
  global $dbhost,$dbuser,$dbpass,$dbname;
  
  if(@func_get_arg(0)) {
    $which = @func_get_arg(0);
  } else {
    $which = "noauthor";
  }

  $connect = mysql_connect($dbhost,$dbuser,$dbpass);
  mysql_select_db($dbname);

  $sql = "SELECT * FROM author ORDER BY lastname";
  $result = mysql_query($sql,$connect);
  while ($authors = mysql_fetch_array($result)) {
    if ($authors[0] == $which) {
      echo "<option selected value=\"".$authors[0]."\">".$authors[1].", ".$authors[2]."</option>\n";
    } else {
      echo "<option value=\"".$authors[0]."\">".$authors[1].", ".$authors[2]."</option>\n";
    }
  }
  mysql_free_result($result);
  mysql_close($connect);
}

function get_cats() {
  global $dbhost,$dbuser,$dbpass,$dbname;
  
  if(@func_get_arg(0)) {
    $which = @func_get_arg(0);
  } else {
    $which = "nocat";
  }

  $connect = mysql_connect($dbhost,$dbuser,$dbpass);
  mysql_select_db($dbname);

  $sql = "SELECT * FROM category ORDER BY cat_name";
  $result = mysql_query($sql,$connect);
  while ($cats = mysql_fetch_array($result)) {
      echo "<option value=\"".$cats[0]."\">".$cats[1]."</option>\n";
    }
  }
?>
