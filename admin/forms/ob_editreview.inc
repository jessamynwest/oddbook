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

function get_review($id) {
	global $dbhost, $dbuser, $dbpass,$dbname;
	global $editfile, $actfile;
	$connect = mysql_connect($dbhost, $dbuser,$dbpass)
		or die("unable to connect to server");
	mysql_select_db($dbname);
	$sql = "select review.review_id,
			review.book_id,
			review.author_id,
			review.review_text,
			review.rating,
			MONTH(review.review_date),
			DAYOFMONTH(review.review_date),
			YEAR(review.review_date),
			book.book_id,
			book.title_sw,
			book.title,
			book.pubyear,
			book.ISBN,
			author.*
			from review
			inner join book on book.book_id = review.book_id
			inner join author on author.author_id = review.author_id
			where review.review_id = $id;";
	$result = mysql_query($sql);
	$elements = mysql_fetch_array($result);
	return $elements;
	mysql_free_result($result);
	mysql_close($connect);
}

function date_read($datepart,$type) {
	$months = array (
			'January',
			'February',
			'March',
			'April',
			'May',
			'June',
			'July',
			'August',
			'September',
			'October',
			'November',
			'December'
			);
	switch($type) {
		case 'month':
			for($count = 0;$count <= 11;$count++) {
				if($datepart == ($count + 1)) {
					print "<option selected value=\"".($count+1)."\">".$months[$count]."</option>\n";
				} else {
					print "<option value=\"".($count+1)."\">".$months[$count]."</option>\n";
				}
			}
			break;
		case 'day':
			for($count = 1;$count <= 31;$count++) {
				if($datepart == $count) {
					print "<option selected value=\"".$count."\">".$count."</option>\n";
				} else {
					print "<option value=\"".$count."\">".$count."</option>\n";
				}
			}
			break;
	}
}

$thisreview = get_review($_GET['id']);

?>

<form method="post" action="<?= $actfile ?>">

	<input type="hidden" name="action" value="update">
	<input type="hidden" name="what" value="review">
	<input type="hidden" name="id" value="<?= $thisreview[0] ?>">
	<input type="hidden" name="book" value="<?= $thisreview[1] ?>">

	<h2>Edit a Review</h2>

	<p><span class="formtext">Author Name (<a href="<?= $addfile ?>?action=author">add an author</a>)</span>
	<br>
	<select class="forminput" name="authID">
		<? get_authors($thisreview[2]); ?>
	</select>

	<br><br>
	<span class="formtext">Title</span><br>

	<input name="title" type="text" size="100" value="<?= $thisreview[9] . "" . stripslashes($thisreview[10]) ?>" class="forminput">

	<br><br>
	<span class="formtext">ISBN</span><br>

	<input name="ISBN" type="text" size="35" value="<?= $thisreview[12] ?>" class="forminput">

	<br><br>

	<span class="formtext">Publication Year</span><br>

	<input name="year" size="35" value="<?= $thisreview[11] ?>" class="forminput">

	<br><br>

	<?php
	$cat_array = get_linked_cats($thisreview[1]);
	#echo $cat_array[1];
	?>

	<span class="formtext">Category:</span>
	<select class="forminput" name="cid-1">
	<option value="0">-</option>
	<? get_cats($thisreview[1], $cat_array[0]); ?>
	</select>
	<select class="forminput" name="cid-2">
	<option value="0">-</option>
	<? get_cats($thisreview[1], $cat_array[1]); ?>
	</select> <span class="formtext">Rating</span>
	<select name="rating" class="forminput">

	<?php
	$ratings = array('+','0','-');
	foreach($ratings as $rating){
	  if ($rating == $thisreview[4]) {
		echo "<option value=\"$rating\" selected>$rating</option>\n";
	  } else {
		echo "<option value=\"$rating\">$rating</option>\n";
	  }
	}
	?>

	</select>
	<br><br>

	<span class="formtext">Review</span><br>

	<textarea name="review_text" rows="12" cols="50" class="forminput"><?= 
	stripslashes($thisreview[3]) ?></textarea>

	<br><br>

	<span class="formtext">Date Read</span><br>
	<select name="read_month" class="forminput">
	<?php
	date_read($thisreview[5],'month');
	?>
	</select>&nbsp;&nbsp;
	<select name="read_day" class="forminput">
	<?php
	date_read($thisreview[6],'day');
	?>
	</select>&nbsp;&nbsp;
	<input name="read_year" size="4" type="text" class="forminput" value="<?= $thisreview[7] ?>"><br>

	<br>
	<input type="submit" value="do it." class="button">
	
</form>
