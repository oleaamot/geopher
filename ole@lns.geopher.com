package Geomail;                                                                              
# Copyright (C) 2020 Ole Aamot
#                                                                               
# Author: ole@geopher.com
#                                                                               
# Date: 2020-08-06T11:25:00+01
#                                                                               
# Field: Mail, Transfer, Agent, MTA, SMTP
#                                                                               
# URL: https://www.geopher.com/Geomail.pm
                                                                                
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
# use MIME::Lite::TT::HTML;
use Net::SMTP;
use Data::UUID;

my @Geomail;

BEGIN {
   @Geomail = qw{send_respond_mail}
}

sub send_respond_mail {
    my %params;
    $params{first_name} = 'Ole';
    $params{last_name}  = 'Aamot';
    $params{geopher_p}  = '0.50';
    my $ug    = Data::UUID->new;
    my $uuid1 = $ug->create();
    my $str   = $ug->to_string( $uuid1 );
    my $uuid  = $ug->from_string( $str );
    $params{geopher_id} = $uuid;
    $params{geopher_e}  = 'ole@aamot.software';
    my $smtp = Net::SMTP->new('smtp.domeneshop.no');
#    $smtp->auth('CRAM-MD5', 'geopher2', 'xxxxxxxx');
    $smtp->mail($ENV{USER});
    $smtp->to($params{geopher_e});
    $smtp->data();
    $smtp->datasend("From: noreply\@geopher.com\n");
    $smtp->datasend("To: ole\@aamot.software\n");
    $smtp->datasend("\n");
    $smtp->datasend("Hi,\n");
    $smtp->datasend("Please visit\n\n");
    $smtp->datasend("https://www.geopher.com/respond/?id=" . $params{geopher_id} . "\n\n");
    $smtp->datasend("to accept, reject or ignore the location request.\n\n");
    $smtp->datasend("Cheers,\n");
    $smtp->datasend("The Geopher Team\n");
    $smtp->datasend("https://www.geopher.com/\n");
    $smtp->dataend();
    $smtp->quit;
#    my %options;
#    $options{INCLUDE_PATH} = '/home/5/g/geopher/templates';
    
#    my $msg = MIME::Lite::TT::HTML->new(
#	From        =>  'noreply@geopher.com',
#	To          =>  'ole@aamot.software',
#	Subject     =>  'Geopher Location Request from John Doe',
#	Template    =>  {
#	    text    =>  'geopher.txt.tt',
#	    html    =>  'geopher.html.tt',
#	},
#	TmplOptions =>  \%options,
#	TmplParams  =>  \%params,
#	);
 #   $msg->send;
}
&send_respond_mail;
