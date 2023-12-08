#!/usr/bin/perl
# Copyright (C) 2020  Aamot Software                                      
#                                                                               
# Author: ole@aamotsoftware.com                                                 
#                                                                               
# Date: 2022-06-06T23:47:00+0200                                                
#                                                                               
# Field: Incremental, location, sql, perl                                       
#                                                                               
# URL: https://www.geopher.com/index.cgi                                       
                                                                                
use strict;                                                                     
use warnings;                                                                   
#use DBI;
#use DBI::mysql;
use CGI qw/:cgi-lib/;                                                          
use CGI::Cookie;                                                                
use lib '.';
use Net::SMTP;
use Data::UUID;
use MIME::Lite;
use String::MkPasswd qw(mkpasswd);
use POSIX;

use Geomail;
#use Geopher;

my $messageid = POSIX::strftime('%Y%m%d.', localtime).mkpasswd(
   	-length => 15,
	-minnum => 5,
	-minlower => 5,
	-minupper => 5,
	-minspecial => 0,
	);
my $c = CGI->new;
if (!$c->{id} eq "") {    
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
<form method="POST" action="/p">
<input size="8" name="pronome" value="Who?" />
<input size="8" name="proverb" value="What?" />
EOD
    print <<EOE;
<select name="location">
EOE
    my $loc = &Geopher::get_locations();
    print <<EOF;
</select>
EOF
    print '<input size="8" name="identify" value="Who?" value="' . $c->{id} . '" />';
    print '<input size="8" name="location" value="Where?" value="' . $messageid . '" />';
    print <<EOG;    
    <input size="8" name="timeverb" value="When?" />
    <input size="8" value="Post" type="submit" />
    </form>
    </body>
    </html>
EOG
} else {
    print 'Invalid id!';
}
