<?php

/*

	This is the master User/Site Settings File

*/

$dbhost = "";
$dbuser = "";
$dbpass = "";
$dbname = "";

$adminUsername = "";
$adminPassword = "";

$initialCategories = array("fiction", "non-fiction", "science fiction", "graphic novels", "biography", "poetry", "ya");

$siteTitle = "oddbook";
$siteDescription = "A book list.";

$startyear = 2010;
$rssMaxEntries = "15";

$oddbookInstallDir = "/oddbook";
$indexFilename = "booklist";
$baseURLforOddbook = "http://" . $_SERVER['SERVER_NAME'] . $oddbookInstallDir;
$fullURLToOddbook = $baseURLforOddbook . "/" . $indexFilename;

?>
