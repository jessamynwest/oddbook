# Introduction #

Oddbook-0.1 is experimental. Do not use this software unless you know enough PHP and MySQL to get out of any trouble you may encounter.


# Installation #

<ol>
<li>Extract the contents of the zip file onto your server.</li>
<li>Prepare an empty database in MySQL.</li>
<li>In the oddbook files, locate <b>/includes/ob_vars.inc</b> and <b>/admin/includes/ob_vars.inc</b>.</li>
<li>In these files, locate the text block below and insert your database information:<br>
<pre><code><br>
# Fill in the variables with the values specific to<br>
# your system below.<br>
<br>
$dbhost = "www.example.com";<br>
$dbuser = "tinkerbell";<br>
$dbpass = "clapclapclap";<br>
$dbname = "myoddbookdb";<br>
</code></pre>
<li>In the file <b>/schema_setup.php</b>, input each category you would like the booklist to keep track of.  This list can be added to through MySQL, but Oddbook's admin interface does not provide a way to change these later.<br>
<pre><code><br>
echo "Populating categories...\n";<br>
<br>
# Change these to fit your own tastes<br>
<br>
mysql_query("INSERT INTO category SET cat_name = 'fiction'");<br>
mysql_query("INSERT INTO category SET cat_name = 'science fiction'");<br>
mysql_query("INSERT INTO category SET cat_name = 'undersea adventure'");<br>
mysql_query("INSERT INTO category SET cat_name = 'ephemera'");<br>
mysql_query("INSERT INTO category SET cat_name = 'stuff with words'");<br>
</code></pre></li>
<li>Also in the <b>/schema_setup.php</b> file, input the username and password you want to use with the Oddbook admin interface:<br>
<pre><code><br>
echo "Setting up admin user...\n";<br>
<br>
mysql_query("INSERT INTO users VALUES (<br>
'tinkerbell',<br>
PASSWORD('clapclapclap')<br>
)");<br>
</code></pre></li>
<li>Run the install script by visiting your website wherever Oddbook is installed, (ex. <a href='http://www.example.com/oddbook/schema_setup.php'>http://www.example.com/oddbook/schema_setup.php</a>).  Running this script multiple times will have no effect once the tables are initially created.</li>
<li>Oddbook is now ready to use!  Visit your administration page (ex. <a href='http://www.example.com/oddbook/admin/index.php'>http://www.example.com/oddbook/admin/index.php</a>) and log in to start populating your book list.