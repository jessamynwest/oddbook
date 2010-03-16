<?php

/*
 * This file is part of Oddbook.
 *
 * Oddbook is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * Oddbook is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Oddbook; if not, write to the Free Software Foundation, Inc.,  59
 * Temple Place, Suite 330, Boston, MA  02111-1307  USA
**/


/* =======================================================================
 * review select functions
 *
 * These functions select the review functions, then pass off the book and
 * author id's to be matched up in a different function.
 *
 * See section 3 for these additional functions
 *========================================================================
**/

function select_by_title() {
   global $dbhost,$dbuser,$dbpass,$dbname;
   global $thisfile;
   $titleconn = mysql_connect($dbhost,$dbuser,$dbpass);
   mysql_select_db($dbname);
   $sql = "select book.book_id, book.title_sw, book.title, 
           review.review_id, YEAR(review.review_date), 
           MONTHNAME(review.review_date) 
           from book 
           inner join review on review.book_id = book.book_id 
           order by book.title";
   $result = mysql_query($sql);
   while ($row = mysql_fetch_array($result)) {
      echo "<p><a href=\"$thisfile/book/$row[3]\">$row[1] ";
      echo translate($row[2]) . "</a></p>\n";
   }
   mysql_free_result($result);
   mysql_close($titleconn);
}

function select_by_author() {
   global $dbhost,$dbuser,$dbpass,$dbname;
   $authorconn = mysql_connect($dbhost,$dbuser,$dbpass)
     or die("unable to connect to database");
   mysql_select_db($dbname);
   $sql = "select * from author order by lastname;";
   $result = mysql_query($sql);
   while ($row = mysql_fetch_array($result)) {
     echo "<h1>" . $row[2] . " " . $row[1] . "</h1>\n\n";
     print_books_by_author($authorconn,$row[0]);
   }
   mysql_free_result($result);
   mysql_close($authorconn);
}

//select by date
function select_by_date() {
   $year = func_get_arg(0);
   $month = func_get_arg(1);
   global $months,$thisfile;

   //first, determine whether the month is for real.
   $realmonth = false;
   foreach ($months as $str){
      if($str == $month) {
         $realmonth = true;
	 $month = ucfirst($month);
      }
   }
   if ($realmonth == true) {
      echo "<h1 style=\"text-align:center;padding-bottom:25px;\">&laquo; $month &raquo;</h1>\n\n";
   }

   global $dbhost,$dbuser,$dbpass,$dbname;
   $dateconn = mysql_connect($dbhost,$dbuser,$dbpass)
     or die("unable to connect to database");
   mysql_select_db($dbname);
   $sql = "select review.review_id as review_id,review.book_id,review.author_id,review.review_text as text,
           DAYOFMONTH(review.review_date) review_day,
           MONTHNAME(review.review_date) review_month,
           YEAR(review.review_date) review_year,
           review.rating as rating,
           author.lastname as auth_l, author.firstname as auth_f,
           book.title_sw as sw, book.title as title, book.pubyear as pubyear, book.ISBN as isbn
           from review
           inner join author on author.author_id = review.author_id
           inner join book on book.book_id = review.book_id
           where YEAR(review_date)='$year'
           and MONTHNAME(review_date)='$month' 
           order by review.review_date desc;";
   $result = mysql_query($sql);

   if (mysql_num_rows($result) == 0) {
      echo "<h1>Nothing</h1>\n\n";
      if ($year >= datepart('year') && $realmonth == true) {
         echo "<p>Well, it doesn't seem that I've read anything for this month,
               or else I have not written a review. Sigh.</p>\n\n";
      } else {
         echo "<p>How did you get here? OK, to be honest, I really don't care.
               But just so you know, I started this thing in $startdate, so
               the reviews start there.</a>.</p>\n\n";
      }
   } else {
       $fp = fopen("includes/templates/review.tmpl",r);
       while($row = mysql_fetch_array($result)) {
           array_push($row,$fp);
	   render_review($row);
       }
       fclose($fp);
   }
   mysql_free_result($result);
   mysql_close($dateconn);
}

function select_rating($rating) {
  global $dbhost,$dbuser,$dbpass,$dbname;
  global $thisfile;

  switch($rating) {
  case '+':
    echo "<h1 style=\"text-align:center;padding-bottom:25px;\">";
    echo "&laquo; Positive Ratings (+) &raquo;</h1>";
    $rating = '+';
    break;
  case '-':
    echo "<h1 style=\"text-align:center;padding-bottom:25px;\">";
    echo "&laquo; Negative Ratings (-) &raquo;</h1>";
    $rating = '-';
    break;
  default:
    echo "<h1 style=\"text-align:center;padding-bottom:25px;\">";
    echo "&laquo; Average Ratings (0) &raquo;</h1>";
    $rating = '0';
    break;
  }

  $sql = "select review.review_id,review.book_id,review.author_id,
          MONTHNAME(review.review_date) as review_month,
          YEAR(review.review_date) as review_year,
          DAYOFMONTH(review.review_date) as review_day,
          author.lastname as auth_l, author.firstname as auth_f,
          book.title_sw as sw, book.title,book.pubyear
          from review
          inner join author on author.author_id = review.author_id
          inner join book on book.book_id = review.book_id
          where review.rating = '$rating'
	  order by book.title";
  $ratingconn = mysql_connect($dbhost,$dbuser,$dbpass)
     or die("unable to connect to the database");
  mysql_select_db($dbname);
  $result = mysql_query($sql,$ratingconn);
  $fp = fopen("includes/templates/rating.tmpl",r);
  while($row = mysql_fetch_array($result)) {
      array_push($row,$fp);
      render_review($row);
  }
  fclose($fp);
  mysql_free_result($result);
  mysql_close($ratingconn);
}

function select_book($which) {
   global $dbhost,$dbuser,$dbpass,$dbname;
   global $thisfile;
   $bookconn = mysql_connect($dbhost,$dbuser,$dbpass)
     or die("unable to connect to server");
   mysql_select_db($dbname);
   $sql = "select review.review_id as review_id,review.book_id,review.author_id,review.review_text as text,
           DAYOFMONTH(review.review_date) as review_day,
           MONTHNAME(review.review_date) as review_month,
           YEAR(review.review_date) as review_year,
           review.rating,
           author.lastname as auth_l, author.firstname as auth_f,
           book.title_sw as sw, book.title, book.pubyear
           from review
           inner join author on author.author_id = review.author_id
           inner join book on book.book_id = review.book_id
           where review_id = $which;";
   $result = mysql_query($sql);
   $fp = fopen("includes/templates/review.tmpl",r);
   while($row = mysql_fetch_assoc($result)) {
       array_push($row,$fp);
       render_review($row);
   }
   mysql_free_result($result);
   mysql_close($bookconn);
}


//this is the default function.
function select_last_five() {
   global $dbhost,$dbuser,$dbpass,$dbname;
   global $thisfile;
   $glfconn = mysql_connect($dbhost,$dbuser,$dbpass)
     or die("unable to connect to server");
   mysql_select_db($dbname);
   $sql = "select review.review_id as review_id,review.book_id as book,review.author_id as auth,review.review_text as text,
           DAYOFMONTH(review.review_date) as review_day,
           MONTHNAME(review.review_date) review_month,
           YEAR(review.review_date) as review_year,
           review.rating as rating,
           author.lastname as auth_l, author.firstname as auth_f,
           book.title_sw as sw, book.title as title, book.pubyear as pubyear,
             book.ISBN as isbn
           from review
           inner join author on author.author_id = review.author_id
           inner join book on book.book_id = review.book_id
	   order by review.review_date desc limit 5;";
   $result = mysql_query($sql);
   $fp = fopen("includes/templates/review.tmpl",r);
   while($row = mysql_fetch_assoc($result)) {
       array_push($row,$fp);
       render_review($row);
   }
   fclose($fp);
   mysql_free_result($result);
   mysql_close($glfconn);
}

/*
 * book information functions
 *
 * These functions get the author and book information that correspond
 * to a given review and put them to an array. It is the job of the 
 * functions in ob_translate.inc to actually display the information.
 *
**/

function print_books_by_author($authorconn,$whichauthor) {
   $sql = "select review.review_id,
           YEAR(review.review_date), MONTHNAME(review.review_date),
           book.title_sw, book.title, book.pubyear 
           from review 
           inner join book on book.book_id = review.book_id 
           where review.author_id = $whichauthor;";
   $result = mysql_query($sql,$authorconn);
   $numrows = mysql_num_rows($result);
   $thiscount = 1;

   global $thisfile;
    echo "<p>";
   while($thebooks = mysql_fetch_array($result)) {
      echo "<a href=\"$thisfile/book/$thebooks[0]\">$thebooks[3] ";
      echo translate($thebooks[4]) ."</a>";
      if ($thiscount < $numrows) {
         $thiscount++;
         echo "<br />\n";
      }
   }
   echo "</p>\n\n";
   mysql_free_result($result);
}
?>
