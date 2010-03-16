<?php

function delete_review($which) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;
	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("unable to connect to the database");
	mysql_select_db($dbname);

	$rev_sql = "delete from review where review_id = ".$which['id'].";";
	$book_sql = "delete from book where book_id =  ".$which['book'].";";

	$rev_ok = mysql_query($rev_sql);
	$book_ok = mysql_query($book_sql);
	include("./tmpl/ob_header.inc");
	if ($rev_ok == 0 || $book_ok == 0) {
		echo "<p><strong>At least one or more things went wrong with your entry. Are you messing with something?</strong></p>";
	} else {
		echo "<p><strong>Your entry has been deleted. You can quit now, or do something else here.</strong></p>";
	}
	mysql_close();

	include("./tmpl/ob_nav.inc");
}

function delete_author($which) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;
	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("unable to connect to the database");
	mysql_select_db($dbname);

	$sql = "delete from author where author_id = $which;";

	$delok = mysql_query($sql);
	include("./tmpl/ob_header.inc");
	if ($delok) {
		echo "<p><strong>That author has now been deleted.  You can quit now, or do something else here.</strong></p>";
	} else {
		echo "<p><strong>At least one or more things went wrong with your entry. Are you messing with something?</strong></p>";
	}
	mysql_close();

	include("./tmpl/ob_nav.inc");
}

function update_author($new_auth) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;

	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	$sql = "update author 
			set lastname='".addslashes($new_auth['lname'])."',
			firstname='".addslashes($new_auth['fname'])."'
			where author_id = ".$new_auth['id'].";";
	#echo $sql;

	$updok = mysql_query($sql);
	include("./tmpl/ob_header.inc");
	if($updok) {
		echo "<p>The author <strong>".$new_auth['fname']." ".$new_auth['lname']."</strong> has been updated.</p>";
	} else {
		echo "<p><strong>At least one or more things went wrong with your entry. Are you messing with something?</strong></p>";
	}
	mysql_close();
	include("./tmpl/ob_nav.inc");
}

function update_review($new_rev) {

	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;

	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	$title = sw_fix($new_rev['title'],'upd');

	$rev_sql =  "update review
				set review_text='".addslashes($new_rev['review_text'])."',
				author_id='".$new_rev['authID']."',
				rating='".$new_rev['rating']."',
				review_date = '".$new_rev['read_year']."-".$new_rev['read_month']."-".$new_rev['read_day']."'
				where review_id = ".$new_rev['id'].";";

	$book_sql = "update book
				set $title,
				author_id='".$new_rev['authID']."', 
				pubyear = '".$new_rev['year']."',
				ISBN = '".$new_rev['ISBN']."'
				where book_id = ".$new_rev['book'].";";

	$revok = mysql_query($rev_sql);
	$bookok = mysql_query($book_sql);

	# deal with the categories
	clear_cat_link($new_rev['book']);
	insert_category(array($new_rev['cid-1'],$new_rev['cid-2']), $new_rev['book']);

	include("./tmpl/ob_header.inc");
	if($revok && $bookok) {
		echo "<p>Your review for <strong>".$new_rev['title']."</strong> has been updated.</p>";
	} else {
		echo "<p><strong>At least one or more things went wrong with your entry. Are you messing with something?</strong></p>";
	}
	mysql_close();

	include("./tmpl/ob_nav.inc");
}

function clear_cat_link($bookid) {

	global $dbhost,$dbuser,$dbpass,$dbname;
	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	// Make sure the book actually exists before we start making a mess with deletes.
	$result = mysql_query("select count(*) from book where book_id = $bookid");
	echo mysql_error();
	$book_count = mysql_result($result, 0);

	if ($book_count != 1){
		echo "<b>clear_cat_link: expected to find book 1 times in book table, found: $book_count.  Failed clearing categories";
		return;
	}
  
	// For sanity sake.. lets limit this to a maximum of 2 deletes.
	$select_sql = "select count(*) from cat_book_link where book_id = " . $bookid . "";
	$result = mysql_query($select_sql);
	echo mysql_error();
	$book_count = mysql_result($result, 0);

	if (($book_count < 0) || ($book_count > 2)){
		echo "<b>clear_cat_link: expected to find 0-2 entries in cat_book_link, found: $book_count.  Failed clearing categories";
		return;
	}

	$delete_sql = "delete from cat_book_link where book_id = " . $bookid . "";
	$result = mysql_query($delete_sql);
	echo mysql_error();

	return;  
}

function update_cat_link($catid, $bookid) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	#does the category already exist for the book?
	#if yes, then update the category
	#if not, then insert a new category.

	#$checksql = "select cat_id, book_id from cat_book_link where book_id = $bookid and cat_id = $catid";
	#echo $checksql;
	#$result = mysql_query("select count(*) from cat_book_link;");
	#echo mysql_result($result, 0);
	#$catnums = mysql_num_rows($result);

	#  if($catnums == 0) {
	#     mysql_query("insert into cat_book_link(book_id, cat_id) values ($bookid, $catid);");
	#  } elseif ($catnums == 1) {
	#     $upd = "update cat_book_link set cat_id = $catid where book_id = $bookid";
	#     echo $upd;
	#     mysql_query($upd);
	#  }
	$result = mysql_query("select count(*) from book where book_id = $bookid");
	echo mysql_error();
	$book_count = mysql_result($result, 0);
   
	if ($book_count != 1){
		echo "<b>update_cat_link: expected to find book 1 times in book table, found: $book_count.  Failed adding categories";
		return;
	}
	mysql_query("insert into cat_book_link(book_id, cat_id) values ($bookid, $catid)");

}

function insert_review($review) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;

	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	# send off the title for stopword parsing.
	$title = sw_fix($review['title'],'ins');

	# this part of the function deals with accurate ISBNs.
	if (strlen($review['ISBN']) == 10 || strlen($review['ISBN']) == 13) {
		$ISBN = "'". $review['ISBN'] ."'";
	} else {
		$ISBN = "''";
	}

	$book_sql = "insert into book(title_sw,title,author_id,pubyear,ISBN)
			   values($title,'".$review['authID']."','".$review['year']."',
			   $ISBN);";

	#echo $book_sql;

	$bookok = mysql_query($book_sql);
	echo mysql_error();
	$book_id = mysql_insert_id();

	# deal with categories
	$cats = array($review['cid-1'],$review['cid-2']);
	insert_category($cats, $book_id); 

	$rev_sql = "insert into review(book_id,author_id,review_text,rating,review_date)
				values ('".$book_id."','".$review['authID']."','".addslashes($review['review_text'])."',
				'".$review['rating']."',
				'".$review['read_year']."-".$review['read_month']."-".$review['read_day']."');";
	$revok = mysql_query($rev_sql);
	include("./tmpl/ob_header.inc");
	if($revok && $bookok) {
		echo "<p>Your review for <strong>".$review['title']."</strong> has been added.</p>";
	} else {
		echo "<p><strong>At least one or more things went wrong with your entry. Are you messing with something?</strong></p>";
	}
	mysql_close();

	include("./tmpl/ob_nav.inc");
}

function insert_category($cats,$bookid) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;

	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	foreach ($cats as $cat) {
		if ($cat != 0) {
			$sql = "insert into cat_book_link(book_id, cat_id)
					values($bookid, $cat)";
			mysql_query($sql);
		}
	}
}

/*
 *  functions for inserting information into the database.
 */

function insert_author($author) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;

	mysql_connect($dbhost,$dbuser,$dbpass)
		or die("could not connect to server");
	mysql_select_db($dbname);

	$sql = "insert into author(lastname,firstname)
			values('".addslashes($author['lname'])."','".addslashes($author['fname'])."');";

	$authok = mysql_query($sql);
	include("./tmpl/ob_header.inc");
	if($authok) {
		echo "<script language=\"JavaScript\">\n\n";
		echo "closeDown();\n\n";
		echo "</script>\n";
	} else {
		echo "<p><strong>At least one or more things went wrong with your entry. Are you messing with something?</strong></p>";
	}
	mysql_close();
	echo "<p style=\"text-align:center;\"><a href=\"javascript:closeDown();\">close window</a></p>\n"; 
	include("./tmpl/ob_nav.inc");
}

function login($loginform) {
	global $dbhost, $dbuser, $dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;
	$authenticonn = mysql_connect($dbhost, $dbuser,$dbpass)
		or die("unable to connect to server");
	mysql_select_db($dbname);
	$sql = "SELECT username, password FROM users 
			WHERE username = '". $loginform['username'] ."' 
			and password = password('". $loginform['password'] ."');";
	$output = mysql_query($sql);
	$checkit = mysql_num_rows($output);
	mysql_free_result($output);
	mysql_close($authenticonn);
	if ($checkit == 1) {
		setcookie('reviewer',$loginform['username']);
		include("./tmpl/ob_header.inc");
		include("./tmpl/ob_nav.inc");
	} else {
		include("./tmpl/ob_header.inc");
		include("./forms/ob_login.inc");
	}
}


/*
 * This function analyzes the title for stopwords. If they exist, then a tokenized version of
 * the sting is returned.
 *
 */

function sw_fix($title,$action) {
	trim($title);
	if($action == 'ins') {
		if(ereg('^(The|An|A) .*$',$title)) {
			ereg('^(The|An|A) (.*$)',$title,$newtitle);
			$frag = "'".addslashes($newtitle[1])."','".addslashes($newtitle[2])."'";
		} else {
			$frag = "'','". addslashes($title) ."'";
		}
	} elseif($action == 'upd') {
		if(ereg('^(The|An|A) .*$',$title)) {
			ereg('^(The|An|A) (.*$)',$title,$newtitle);
			$frag = "title_sw='".addslashes($newtitle[1])."',title='".addslashes($newtitle[2])."'";
		} else {
			$frag = "title_sw='',title='".addslashes($title)."'";
		}
	}
	return $frag;
}

/*
 *
 * They should only have to run this function once, to update their
 * databases. But whatever.
 *
 */

function update_db() {
	global $dbhost, $dbuser, $dbpass,$dbname;
	global $index, $actfile, $editfile, $addfile;
	$authenticonn = mysql_connect($dbhost, $dbuser,$dbpass)
		or die("unable to connect to server");
	mysql_select_db($dbname);

	$check = mysql_query("select * from book");
	if(mysql_field_name($check,1) != "title_sw") {
		mysql_query("alter table book add column title_sw varachar(5) after book_id;");
	}
	mysql_free_result($check);

	$result = mysql_query("select book_id,title from book");
	while($row = mysql_fetch_array($result)) {
		if(eregi('^(The|An|A) .*$',$row[1])) {
			ereg('^(The|An|A) (.*$)',$row[1],$title);
			mysql_query("update book set title_sw = '$title[1]', title = '$title[2]' where book_id = $row[0];");
		}
	}
	mysql_free_result($result);
	include('./tmpl/ob_header.inc');
	echo "<p>The database has been updated.</p>";
}

?>
