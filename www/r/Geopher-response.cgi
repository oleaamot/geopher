#!/usr/bin/perl
# Copyright (C) 2020  Aamot Software                                      
#                                                                               
# Author: ole@aamotsoftware.com                                                 
#                                                                               
# Date: 2020-06-08T11:37:00+0200                                                
#                                                                               
# Field: Incremental, location, sql, perl                                       
#                                                                               
# URL: https://www.geopher.com/index.cgi                                       
                                                                                
use strict;                                                                     
use warnings;                                                                   
use DBI;                                                                        
use CGI qw/:cgi-lib/;                                                          
use CGI::Cookie;                                                                
use lib '.';

use Geopher;
use Geomail;

print "Content-Type: text/html\n\n";
print <<EOD;
<html>
<head>
<title>Geopher - Who, What, Where, When?</title>
</head>
<body>
<h1>Geopher</h1>
<h2>Who, What, Where, When?</h2>
<p>We eat at \&TheBestLunchPlace in Oslo, Norway on Saturday at 12pm</p>
<form method="POST" action="/s">
<input size="8" name="pronome" value="Who?" />
<input size="8" name="proverb" value="What?" />
EOD
print <<EOE;
<select name="location">
EOE
my $loc = &Geopher::get_locations();
print <<EOF;
</select>
<input size="8" name="location" value="Where?" />
<input size="8" name="timeverb" value="When?" />
<input size="8" value="Post" type="submit" />
</form>
</body>
</html>
EOF
