package Geomail;                                                                              
# Copyright (C) 2022 Ole Aamot
#                                                                               
# Author: ole@geopher.com
#                                                                               
# Date: 2022-06-07T09:01:00+01
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
#use DBI;
use CGI;
use LWP;
use Log::Log4perl;
use WWW::Mechanize;
use JSON -support_by_pp;                                                   
use Math::Round;
# use MIME::Lite::TT::HTML;
use Net::SMTP;
use Data::UUID;
use MIME::Lite;
use String::MkPasswd qw(mkpasswd);
use POSIX;

my @Geomail;

BEGIN {
   @Geomail = qw{send_respond_mail}
}

sub send_respond_mail {

    my $subject = 'Geopher Location Request from John Doe';
    my $from = 'John Doe <noreply@geopher.com>';
    my $to = 'Ole Aamot <ole@aamotsoftware.no>';
    my $messageid = POSIX::strftime('%Y%m%d.', localtime).mkpasswd(
	-length => 15,
	-minnum => 5,
	-minlower => 5,
	-minupper => 5,
	-minspecial => 0,
	);

    my $c = CGI->new;

    my $htmlbody = '<html><body><h1>Geopher Location Request from John Doe</h1><p><a href="https://www.geopher.com/r/?id=' . $messageid . '">Accept Location Request at https://www.geopher.com/r/?id=' . $messageid . '</a></body></html>';
    my $date = POSIX::strftime('%Y-%m-%dT%H:%M:%S.%f%Z.', localtime);
    
    my $textbody = 'Geopher Location Request from John Doe\n\nAccept Location Request at https://www.geopher.com/r/?id=' . $messageid;
    
    my $msg = MIME::Lite->new(        From        => $from,
				      To          => $to,
				      Subject     => $subject,
				      Date        => $date,
				      Type        => 'multipart/alternative',
				      'Message-ID'=> '<'.$messageid.'@geopher.com>',
	);
    $msg->add("Bcc" => 'noreply@geopher.com');
    $msg->attach(
	Type        => 'text/plain; charset="iso-8859-1"',
	Data        => $textbody,
	Encoding    => 'quoted-printable',
	);
    $msg->attach(
	Type        => 'text/html; charset="iso-8859-1"',
	Data        => $htmlbody,
	Encoding    => 'quoted-printable'
	);
    MIME::Lite->send('sendmail', '/usr/sbin/sendmail -f noreply@geopher.com -t -oi -oem');
    if ($msg->send()) {
	#log_result('Message sent OK');
	return 1;
    }
    #log_result('Message failed');
}
&send_respond_mail;
