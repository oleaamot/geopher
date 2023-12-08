#!/usr/bin/perl

# Copyright (C) 2015-2022  Aamot Software
#
# Author: ole@aamot.software
#
# Date: 2022-11-10T10:15:00+02
#
# Field: Incremental, movement, sql, perl
#
# URL: http://www.geopher.com/index.cgi

use strict;
use warnings;
use DBI;
use CGI qw/:standard/;
use CGI::Cookie;
use lib '../../../';
use Geopher;

my $c = CGI->new;
print "Content-Type: text/html\n\n";
print <<EOF;
<!DOCTYPE html>
<html lang="en">
    <head>
    <link rel="dns-prefetch" href="//maps.googleapis.com">
    <link rel="dns-prefetch" href="//maps.gstatic.com">
    <link rel="dns-prefetch" href="//mts0.googleapis.com">
    <link rel="dns-prefetch" href="//fonts.googleapis.com">
    <link rel="dns-prefetch" href="//yay.oka.no">
    
    <title>geopher.com - Movement-based Search Engine - Movement JavaScript API</title>
    <link href="https://www.geopher.com/my_style_form.css" type="text/css" rel="stylesheet" />
    <link href='http://fonts.googleapis.com/css?family=Titillium+Web:700' rel='stylesheet' type='text/css'>
    <link href='http://fonts.googleapis.com/css?family=Titillium+Web' rel='stylesheet' type='text/css'>
    <meta charset="utf-8" />
    </head>
    <body>
    <img src="https://www.geopher.com/geopher.png" width="600" alt="Logo" />
    <h2>Documentation</h2>
    <h3>Movement JavaScript API</h3>
    <h4>Query</h4>
    <pre>
  <span style="color: #ff0000">Example</span>

  &lt;script type="text/javascript" src="https://www.geopher.com/api/location/json.php?service=<span style="color: #ff0000">Search</span>&glat=<span style="color: #ff0000">37.4375596</span>&glon=<span style="color: #ff0000">-122.11922789999998</span>"&gt;&lt;/script&gt;
  &lt;script language="JavaScript"&gt;
    var obj = JSON.parse(movements);
    for (i=0; i &lt; obj.movements.length; i++) {
	document.write("&lt;h4&gt;" + obj.movements[i].name + "&lt;/h4&gt;&lt;h6&gt;&lt;a href='" + obj.movements[i].movement + "'&gt;" + obj.movements[i].movement + "&lt;/a&gt; (" + obj.movements[i].distance + ")&lt;/h6&gt;&lt;p&gt;" + " " + obj.movements[i].service + " " + "&lt;/p&gt;");
	document.write("&lt;p&gt;" + obj.movements[i].distance + "&lt;/p&gt;&lt;form method='GET' action='/'&gt;&lt;input type='text' name='query' placeholder='' value='" + obj.movements[i].name + "'/&gt;&lt;input type='hidden' name='glat' value='" + obj.movements[i].glat + "' /&gt;&lt;input type='hidden' name='glon' value='" + obj.movements[i].glon + "'/&gt;&lt;span id='geopher'&gt;&lt;/span&gt;&lt;select name='service'&gt;&lt;option selected value='" + obj.movements[i].service + "'&gt;" + obj.movements[i].service + "&lt;/option&gt;&lt;/select&gt;&lt;input type='submit' value='Search' /&gt;&lt;/p&gt;");
    }
  &lt;/script&gt;
</pre>
    <h4>Write</h4>
    <pre>
  <span style="color: #ff0000">Example</span>

  &lt;script type="text/javascript" src="https://api.piperpal.com/location/push.php?name=<span style="color: #ff0000">Google</span>&location=<span style="color: #ff0000">http://www.google.com/</span>&service=<span style="color: #ff0000">Books</span>&glat=<span style="color: #ff0000">37.4375596</span>&glon=<span style="color: #ff0000">-122.11922789999998</span>&paid=<span style="color: #ff0000">50</span>"&gt;&lt;/script&gt;
    </pre>
    <h4>Pull/API Read EndPoint https://www.geopher.com/api/movement/json.php</h4>
    <pre>
  <span style="color: #ff0000">Example</span>

  &lt;script type="text/javascript" src="https://www.geopher.com/api/movement/json.php?service=<span style="color: #ff0000">Books</span>&glat=<span style="color: #ff0000">37.4375596</span>&glon=<span style="color: #ff0000">-122.11922789999998</span>&paid=<span style="color: #ff0000">50</span>"&gt;&lt;/script&gt;
    </pre>
    <h4>Push/API Write EndPoint https://www.geopher.com/api/movement/push.php</h4>
    <pre>
  <span style="color: #ff0000">Example</span>
    
  https://www.geopher.com/api/movement/push.php?name=<span style="color: #ff0000">Google</span>&movement=<span style="color: #ff0000">http://www.google.com/</span>&service=<span style="color: #ff0000">Books</span>&glat=<span style="color: #ff0000">37.4375596</span>&glon=<span style="color: #ff0000">-122.11922789999998</span>&paid=<span style="color: #ff0000">50</span>
    </pre>
    <p>&copy; 2023 Aamot Engineering</p>
    </center>
    </body>
    </html>
EOF
