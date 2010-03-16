<?
require_once("includes/ob_translate.inc");
require_once('includes/ob_cats.inc');
header('Content-Type: text/xml; charset=iso-8859-1', true);
# variables
define(TITLE, "Jessamyn.info: What I've Been Reading");
define(ENTRIES, "15");
define(DESCR, "The ongoing book list of Jessamyn West, Librarian");

# DB information
define(DBHOST, "database");
define(DBUSER, "user");
define(DBPASS, "pwd");
define(DBNAME, "database_name");

# Some URL stuff
define(BASEURL, "Hostaddress/booklist/book/");

function rssheader() {
	echo "<?xml  version=\"1.0\"?>\n". 
	"<rss version=\"0.92\">\n".
	"<channel><title>". TITLE ."</title>\n".
	"<description>". DESCR ."</description>\n".
	"<link>http://jessamyn.info/booklist</link>\n\n";
}

function rssfooter() {
	echo "</channel>\n</rss>\n";
}

function rss() {
	rssheader();
	mysql_connect(DBHOST, DBUSER, DBPASS);
	mysql_select_db(DBNAME);

	$res = mysql_query("select review.review_id as review_id,review.book_id 
	       as book,review.author_id as auth,review.review_text as text,
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
           order by review.review_date desc limit ".ENTRIES.";");

	$fp = fopen("includes/templates/rssreview.tmpl",r);
	while($row = mysql_fetch_assoc($res)) {
        // Grab book categories
        $cats = dn_select_cat_by_book( $row['review_id'], false );
        if ( count($cats) == 0 ) {
            $cat_value = '';
        } else {
            $cat_value = '<category>'.implode( '</category> <category>', $cats ).'</category>';
        }
        //
		echo "<item><title>" . translate($row['sw'] . " " . $row['title'] . " by ". $row['auth_f'] ." " . $row['auth_l'])  . 
		"</title><description><![CDATA[";
		array_push($row,$fp);
		render_review($row, false);
		echo "]]></description><link>". BASEURL . $row['review_id'] ."</link>$cat_value</item>";
		
	}
	fclose($fp);
	
	rssfooter();

}

?>
<?
rss();
?>
