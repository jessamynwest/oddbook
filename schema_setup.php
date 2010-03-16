<?php

/*

	Oddbook Database Schema setup script

	Created: 2/13/2010 by Jeff Hearn (cowbellemoo@gmail.com)

*/

include('includes/ob_vars.inc');
include('includes/ob_sidebar.inc');
include('includes/ob_translate.inc');
include('includes/ob_select.inc');
include('includes/ob_search.inc');
include('includes/ob_cats.inc');

global $dbhost,$dbuser,$dbpass,$dbname;
global $thisfile;

mysql_connect($dbhost,$dbuser,$dbpass)
	or die('Could not connect: ' . mysql_error()); 

mysql_select_db($dbname); 


echo "<pre>\nOddbook Database Schema Setup Script\n\n";


/* Schema

review
	review_id
	book_id
	author_id
	review_text
	review_date
	rating

author
	lastname
	firstname
	author_id

book
	title_sw
	title
	pubyear
	ISBN
	book_id

category
	cat_name
	cat_id

cat_book_link
	book_id
	cat_id

users
	username
	password

*/


echo "Creating review...\n";

mysql_query("CREATE TABLE IF NOT EXISTS review ( 
		review_id int(10) NOT NULL AUTO_INCREMENT, 
		PRIMARY KEY (review_id),
		book_id int(10),	
		author_id int(10), 
		review_text longtext, 
		review_date varchar(10), 
		rating varchar(1),
		FULLTEXT (review_text)
		)");

echo mysql_error() . "\n";


echo "Creating author...\n";

mysql_query("CREATE TABLE IF NOT EXISTS author (
		author_id int(10) NOT NULL AUTO_INCREMENT,
		PRIMARY KEY (author_id),
		lastname varchar(35),
		firstname varchar(35),
		FULLTEXT (lastname,firstname)
		)");

echo mysql_error() . "\n";


echo "Creating book...\n";

mysql_query("CREATE TABLE IF NOT EXISTS book (
		book_id int(10) NOT NULL AUTO_INCREMENT,
		PRIMARY KEY (book_id),
		author_id int(10),
		title_sw varchar(100),
		title varchar(100),
		pubyear varchar(35),
		ISBN varchar(35),
		FULLTEXT (title)
		)");

echo mysql_error() . "\n";


echo "Creating category...\n";

mysql_query("CREATE TABLE IF NOT EXISTS category (
		cat_id int(10) NOT NULL AUTO_INCREMENT,
		PRIMARY KEY (cat_id),
		cat_name varchar(35) UNIQUE
		)");

echo mysql_error() . "\n";


echo "Populating categories...\n";

mysql_query("INSERT INTO category SET cat_name = 'fiction'");
mysql_query("INSERT INTO category SET cat_name = 'science fiction'");
mysql_query("INSERT INTO category SET cat_name = 'undersea adventure'");
mysql_query("INSERT INTO category SET cat_name = 'ephemera'");
mysql_query("INSERT INTO category SET cat_name = 'stuff with words'");

echo mysql_error() . "\n";


echo "Creating cat_book_link...\n";

mysql_query("CREATE TABLE IF NOT EXISTS cat_book_link (
		book_id int(10),
		cat_id int(10)
		)");

echo mysql_error() . "\n";


echo "Creating users...\n";

mysql_query("CREATE TABLE IF NOT EXISTS users (
		username varchar(35) UNIQUE,
		password longtext
		)");

echo mysql_error() . "\n";


echo "Setting up admin user...\n";

mysql_query("INSERT INTO users VALUES (
		'cowbellemoo', 
		PASSWORD('password')
		)");

echo mysql_error() . "\n";


echo "Done.\n";

?>
