<?php

/*

	This is the master User/Site Settings File
	
	Fill out the variables below before running the Oddbook setup script.

*/

/*
	Database Configuration:
	
	Oddbook uses MySQL to store all its data.  Without a database server (host), 
	username, password, and (preferably) empty database, Oddbook won't be usable.
*/
$dbhost = "";
$dbuser = "";
$dbpass = "";
$dbname = "";

/*
	Username & Password:
	
	These are used to log into the Oddbook Administrative interface, located by
	default at /oddbook/admin.  Make sure you fill these in before running the
	setup script, otherwise you won't be able to add anything to Oddbook!
*/
$adminUsername = "";
$adminPassword = "";

/*
	Categories:
	
	Oddbook does not provide facilities for changing the book categories listed
	on the left-hand menu, so choose well if you don't feel up to adding them
	through MySQL.
*/
$initialCategories = array("fiction", "non-fiction", "science fiction", "graphic novels", "biography", "poetry", "drama", "ya");

/*
	Site Title:
	
	This is displayed at the top of each Oddbook page as well as in the RSS feed.
*/
$siteTitle = "oddbook";

/*
	Site Description:
	
	This is the description listed in the site's RSS feed.  It is not currently
	used on the homepage.
*/
$siteDescription = "A book list.";

/*
	Start Year:
	
	The calendar on the left-hand menu shows years and months from the present
	back through time until the year defined by this variable.  The calendar 
	will display these years and month links regardless if there are entries
	dated between the start year and present or not.
*/
$startyear = 2010;

/*
	RSS Entries:
	
	This variable determines how many entries are included in the RSS feed.
*/
$rssMaxEntries = "15";

/*
	Oddbook Install Directory:
	
	The subfolder(s) on your server where oddbook is installed. For example,
	placing oddbook in the root server directory (http://www.example.com/oddbook)
	should list "/oddbook" in the install directory variable.
*/
$oddbookInstallDir = "/oddbook";

/*
	Oddbook Index Filename:
	
	To make user-friendly URLs, oddbook is served from a file which does not 
	have an extension.  The default is "booklist" but you may change this in 
	the variable below but also in the actual filename as well as the .htaccess
	file which reforms the URLs.
*/
$indexFilename = "booklist";


/*	These are for internal use and should not be altered		*/
$baseURLforOddbook = "http://" . $_SERVER['SERVER_NAME'] . $oddbookInstallDir;
$fullURLToOddbook = $baseURLforOddbook . "/" . $indexFilename;

?>
