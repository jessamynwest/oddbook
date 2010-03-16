<?php

function search($text) {
	global $dbhost,$dbuser,$dbpass,$dbname;
	global $thisfile;
	$searchconn = mysql_connect($dbhost,$dbuser,$dbpass)
		or die("unable to connect to server");
	mysql_select_db($dbname);

   # the sql in this search is getting quite funky. Keep an eye out
   # for a better way of dealing with searches.

   $sql = "select review.review_id as review_id,
			review.book_id as book,
			review.author_id as auth,
			review.review_text as text,
			(match(review.review_text) against ('$text') +
			match(author.lastname,author.firstname) against ('$text') +
			match(book.title) against('$text')) as score,
			DAYOFMONTH(review.review_date) as review_day,
			MONTHNAME(review.review_date) review_month,
			YEAR(review.review_date) as review_year,
			review.rating as rating,
			author.lastname as auth_l, author.firstname as auth_f,
			book.title_sw as sw, book.title as title, book.pubyear as pubyear, book.ISBN as isbn
			from review
			inner join author on author.author_id = review.author_id
			inner join book on book.book_id = review.book_id
			where match(book.title) against('$text') or
			match(review.review_text) against ('$text') or
			match(author.lastname,author.firstname) against ('$text')
			order by score desc;";
	// Note: There must be at least 3 records for FULLTEXT matching
	$result = mysql_query($sql);

	if(mysql_numrows($result) > 0) {
		$fp = fopen("includes/templates/review.tmpl",r);
		while($row = mysql_fetch_assoc($result)) {
			array_push($row,$fp);
			render_review($row);
		}  
		fclose($fp);
	} else {
		print "<h1>Nothing</h1>\n";
		print "<p>Your search for <strong>$text</strong> yielded nothing. Please try something else.</p>\n";
	}
	mysql_free_result($result);
	mysql_close($searchconn);
}

function checktext($haystack,$needle) {
    $werds = split(" ",$needle);
    foreach($werds as $werd) {
		trim($werd);
		$haystack = preg_replace("'($werd)'i", " <span class=\"ul\">$1</span>$2",$haystack);
    }
    print translate($haystack);
}
?>
