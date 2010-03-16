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

function get_author($id) {
	global $dbhost, $dbuser, $dbpass,$dbname;
	global $editfile, $actfile;
	$connect = mysql_connect($dbhost, $dbuser,$dbpass)
		or die("unable to connect to server");
	mysql_select_db($dbname);
	$sql = "select * from author where author_id = $id";
	$result = mysql_query($sql);
	$elements = mysql_fetch_array($result);
	return $elements;
	mysql_free_result($result);
	mysql_close($connect);
}

$thisauthor = get_author($_GET['id']);

function get_cat($id) {
	global $dbhost, $dbuser, $dbpass,$dbname;
	global $editfile, $actfile;
	$connect = mysql_connect($dbhost, $dbuser,$dbpass)
		or die("unable to connect to server");
	mysql_select_db($dbname);
	$sql = "select * from category where cat_id = $id";
	$result = mysql_query($sql);
	$elements = mysql_fetch_array($result);
	return $elements;
	mysql_free_result($result);
	mysql_close($connect);
}

$thiscat = get_cat($_GET['id']);
?>

<form method="post" action="<?= $actfile ?>">

	<input type="hidden" name="action" value="update">
	<input type="hidden" name="what" value="author">
	<input type="hidden" name="id" value="<?= $thisauthor[0] ?>">

	<input type="hidden" name="action" value="update">
	<input type="hidden" name="what" value="author">
	<input type="hidden" name="id" value="<?= $thisauthor[0] ?>">

	<h2><a name="a_rev"></a>Edit an Author</h2>

	<span class="formtext">Last Name</span><br>
	<input name="lname" type="text" size="35" class="forminput" value="<?= stripslashes($thisauthor[1]) ?>">
	<br><br>
	<span class="formtext">First Name</span><br>

	<input name="fname" size="35" class="forminput" value="<?= stripslashes($thisauthor[2]) ?>"><br><br>
	<input type="submit" value="do it." class="button">

</form>
