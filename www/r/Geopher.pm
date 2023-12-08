package Geopher;
                                                                                
# Copyright (C) 2020 Ole Aamot
#                                                                               
# Author: ole@geopher.com
#                                                                               
# Date: 2020-06-08T17:39:00+01
#                                                                               
# Field: Incremental, prime number, sql, perl
#                                                                               
# URL: https://www.geopher.com/Geopher.pm
                                                                                
#######################                                                         
# LOAD MODULES
#######################                                                         
use strict;                                                    
use lib '/home/5/g/geopher/share/perl/5.10.1/';
use warnings FATAL => 'all';                                                                
use 5.008001;
use Encode qw();                                                             
use HTTP::Request::Common;
use DBI;
use CGI;
use LWP;
use WWW::Mechanize;
use JSON -support_by_pp;                                                   
use Math::Round;

my @Geopher;

BEGIN {
   @Geopher = qw{get_locations}
}

sub get_locations {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=piperpal;host=piperpal.mysql.domeneshop.no", "piperpal", "FiFLHHPxyR7PXUg", {'RaiseError' => 1});
    $dbh->do ("SELECT DISTINCT name FROM piperpal WHERE paid > '0' ORDER by name;");
    my $sth = $dbh->prepare ("SELECT DISTINCT name FROM piperpal WHERE paid > '0' ORDER by name;");
    $sth->execute();
    while (my $ref = $sth->fetchrow_hashref()) {
	  #    if ('GET' eq $c->request_method && $c->param('location')) {
	  # print "<option selected value=" . $ref->('glat') . "," . $ref->{'glon'} . ">" . $ref->{'name'} . "</option>";
	  #} else {
          print "<option value='" . $ref->{'name'} . "'>" . $ref->{'name'} . "</option>";
 #}
    }
    $sth->finish();
    $dbh->disconnect();
    return;
}

