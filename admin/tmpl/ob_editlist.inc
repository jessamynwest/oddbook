<?php
if ($action == "review") {
	$title1 = "Edit a Review";
	$title2 = "Book Title";
} elseif ($action == "author") {
	$title1 = "Edit an Author";
	$title2 = "Author Name";
}
?>

<h2><?= $title1; ?></h2>
<table align="center" width="400" border="0" cellspacing="0"  cellpadding="0">
	<tr>
		<td width="250">
			<p style=\"text-align:center;font-weight:bold;\"><?= $title2 ?></p>
		</td>
		<td colspan="2">
			<p style=\"text-align:center;font-weight:bold;\">Action</p>
		</td>
	</tr>
	
<?php
if($action == "author") {
	list_authors();
} elseif($action == "review") {
	if(isset($_GET['all'])) {
		list_reviews();
	} else {
		list_latest();
	}
}
?>

</table>

<?
if(!isset($_GET['all'])) {
    echo "<p style=\"text-align:center\"><a href=\"$thisfile?action=review&amp;all=y\">all reviews</a></p>";
}
?>

