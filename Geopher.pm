package Geopher;

# Copyright (C) 2015 Ole Aamot
#
# Author: oka@oka.no
#
# Date: 2015-08-22T16:45:00+01
#
# Field: Incremental, prime number, sql, perl
#
# URL: https://www.geopher.com/Geopher.pm

#######################
# LOAD MODULES
#######################
use strict;

use lib '/home/4/p/piperpal/share/perl/5.10.1/';
use warnings FATAL => 'all';

use 5.008001;
use Encode qw();

use HTTP::Request::Common;
use DBI;
use CGI;
# use LWP;
use WWW::Mechanize;
use JSON -support_by_pp;
use HTML::Entities;
use Math::Round;
use DateTime;

my @Geopher;

BEGIN {
    @Geopher = qw{get_movement input_movement input_publisher mns_item mns_market_item is_valid is_paid initialize update_movement select_movement} 
}

sub get_movement {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
    $dbh->do ("SELECT DISTINCT * FROM Geopher WHERE fix = '1' ORDER by movement;");
    my $sth = $dbh->prepare ("SELECT DISTINCT * FROM Geopher WHERE fix = '1' ORDER by movement;");
    $sth->execute();
    while (my $ref = $sth->fetchrow_hashref()) {
	if ('GET' eq $c->request_method && $c->param('movement')) {
	    print "<option selected value=" . $ref->('glat') . "," . $ref->{'glon'} . "," . $ref->{'galt'} . ":" . $ref->{'movement'} . ">" . $ref->{'movement'} . "</option>";
	} else {
	    print "<option value='" . $ref->('glat') . "," . $ref->{'glon'} . "," . $ref->{'galt'} . ":" . $ref->{'movement'} . ">" . $ref->{'movement'} . "</option>";
	}
    }
    $sth->finish();
    $dbh->disconnect();
    return;
}

sub get_services {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
    $dbh->do ("SELECT DISTINCT service,name,glat,glon,galt FROM piperpal ORDER by service;");
    my $sth = $dbh->prepare ("SELECT DISTINCT service,name,glat,glon FROM piperpal WHERE ORDER by service;");
    $sth->execute();
    if ('GET' eq $c->request_method && $c->param('service')) {
	while (my $ref = $sth->fetchrow_hashref()) {
	    if ($ref->{'service'} == $c->param('service')) {
		print "<option selected value=" . $ref->('glat') . "," . $ref->{'glon'} . "," . $ref->{'galt'} . ">" . $ref->{'service'} . "</option>";
	    } else {
		print "<option value=" . $ref->('glat') . "," . $ref->{'glon'} . "," . $ref->{'galt'} . ">" . $ref->{'service'} . "</option>";
		
	    } 
	}
    }
    $sth->finish();
    $dbh->disconnect();    
    return;
}
sub input_searchers {
    my @radiuses = (1,2,5,10,25,50,100,250,500,750,1000,1250,1500,2000,2500,3000,4000,5000,6000,7000,8000,9000,10000,20000,40075);
    my $r;
    my $sth;
    my $dbh;
    my $c = CGI->new;
    my $service;
    print "<form onsubmit='updateGeo()' method='GET' action='https://www.piperpal.com/#results' id='formID'>";
    print '<table>';
    if ('GET' eq $c->request_method && $c->param('query')) {
	print '<tr><td><center><input size="30" type="text" autofocus class="input_form_custom" id="query" name="query" placeholder="Geopher-search" value="' . HTML::Entities::encode($c->param('query')) . '" autocomplete="query webauthn" /></center></td></tr>';
	#	$dbh = DBI->connect("DBI:mysql:database=piperpalcom02;host=piperpalcom02.mysql.domeneshop.no", "piperpalcom02", "Cup-tales-rafta-1920-vispe", {'RaiseError' => 1});                
	#	$dbh->{'mysql_enable_utf8'} = 1;                                           
	#	if ($c->param('query')) {                                                   
	#	    $sth = $dbh->prepare ("SELECT name,movement,service FROM piperpal WHERE (name LIKE '%" . $c->param('query') . "%' OR service LIKE '%" . $c->param('query') . "%') ORDER by modified DESC;");                                  $sth->execute();                                                        
	#	    while (my $ref = $sth->fetchrow_hashref()) {
	#	       print '<tr><td></td><td>';
	#	       mns_item($ref->{'name'}, $ref->{'movement'}, $ref->{'service'}, $ref->{'glat'}, $ref->{'glon'}, $ref->{'modified'}, $ref->{'created'}, $ref->{'distance_in_km'});
	#              print '</td></tr>';
#	#   }
	#       }
	#:        $sth->finish();
	# $ref->{'name'}, $ref->{'movement'}, $ref->{'service'}, $ref->{'glat'}, $ref->{'glon'}, $ref->{'modified'}, $ref->{'created'}, $ref->{'distance_in_km'}
    } else {
	print '<tr><td><center><input size="30" type="text" class="input_form_custom" id="query" name="query" placeholder="Where to remember&quest;" /></center></td>';
	print '<td><select size="8" type=hidden name="radius" id="radius" value="1000" class="input_form_custom">';
	foreach $r (@radiuses) {
	    if ($c->param('radius')) {
		if ($c->param('radius')==$r) {
		print "<option value='" . $r . "' selected>In " . $r . " m<sup>3</sup></option>";
	    } else {
		print "<option value='" . $r . "'>In " . $r . " m<sup>3</sup></option>";
	    }
	    } else {
	    if ($r == 5) {
		print "<option value='" . $r . "' selected>In " . $r . " m<sup>3</sup></optio>";	    
	    } else {
		print "<option value='" . $r . "'>In " . $r . " m<sup>3</sup></option>";
	    }
	    }
	    
	}
	print '</select></td>';
    }
    print '<td><input type="submit" id="search" name="search" value="Go" /></td></tr></table>';
    print "<span id='status'><input type='hidden' name='glat' value='" . $c->param('glat') . "'/><input type='hidden' name='glon' value='" . $c->param('glon') . "'/><input type='hidden' name='galt' value='" . $c->param('galt') . "'/></span>\n";
    print "</form>";
    print "<h3>Remember in the world around you</h3>";
    print "<p><a href='https://www.geopher.com/apple.html'>Submit entries in Geopher\'s Movement-aware Search Engine</a></p>";
    #&Geopher::input_publisher();
    #&Geopher::insert_publisher();
    print '<p>Movement JavaScript API: <a href="http://www.geopher.com/api/movement/">Geopher</a></p>';;
    print '<p>Mobile Browsers: <a href="http://www.chromium.org/">Chromium</a>, <a href="http://www.mozilla.org/firefox">Firefox</a>, <a href="http://www.vivaldi.com/">Vivaldi</a></p>';;
    print '<p><a href="https://www.geopher.com/?query=&radius=5&search=Go&service=Books&glat=55.6828273&glon=12.6082921&galt=0#results">Copenhagen</a>, <a href="https://www.geopher.com/?query=Apple&radius=40075&search=Go&service=Books&glat=37.3316756&glon=-122.0327639#results">Apple Infinite Loop</a>, <a href="https://www.geopher.com/?query=&radius=5&search=Go&service=Books&glat=51.5073219&glon=-0.1276474&galt=0#results">London</a>, <a href="https://www.geopher.com/?query=&radius=5&search=Go&service=Books&glat=40.6399278&glon=-73.7786925&galt=0#results">New York</a>, <a href="https://www.geopher.com/?query=&radius=5&search=Go&service=Books&glat=48.8566969&glon=2.3514616&galt=0#results">Paris</a></p>';
    print '<p>LLM: <a href="http://chat.openai.com/">ChatGPT</a>, <a href="https://ai.meta.com/llama/">Llama 2</a>, <a href="https://bard.google.com/">Bard</a>, <a href="http://ai.bing.com/">Bing</a></p>';    
    print '<p>Maps: <a href="http://maps.google.com/">Google Maps</a>, <a href="http://www.openstreetmap.org/">Open Street Map</a>, <a href="http://www.bing.com/maps/">Bing Maps</a>, <a href="http://maps.apple.com/">Apple Maps</a></p>';
    print '<p>Search: <a href="http://www.google.com/">Google</a>, <a href="http://www.duckduckgo.com/">DuckDuckGo</a>, <a href="http://www.piperpal.com/">Piperpal</a>, <a href="http://www.bing.com/">Bing</a>, <a href="http://www.yahoo.com/">Yahoo!</a></p>';
    print "<p>Copyright &copy; 2023 <a href=\"https://www.aamot.engineering/\">Aamot Engineering</a></p>";
}

sub input_publisher {

    my $c = CGI->new;
    print "<tr><td width='60'>&nbsp;</td><td><form onsubmit='updateGeo()' id='welcomeForm' name='welcomeForm' action='https://www.geopher.com/api/movement/push.php' method='GET'>";
    print '<span class="input_form">';
    print '<img src="img/Name_Icon.png" title="Name of Movement-aware Content Tag" class="icon_form" height="70" width="70">';
    if ($c->param('query')) {
	print '<input type="text" id="name" class="input_form_custom" name="name" placeholder="Name" value=' . HTML::Entities::encode($c->param('query')) . ' />';
    } else {
	print '<input type="text" id="name" class="input_form_custom" name="name" placeholder="Name" />';
    }
    print '</span>';
    print '</td></tr><tr><td width=60>&nbsp;</td><td>';
    print '<span class="input_form">';
    print '<img src="img/Movement_Icon.png" title="URL of Movement-aware Content Tag" class="icon_form" height="70" width="70">';
    print '<input type="text" id="movement" class="input_form_custom" name="movement" placeholder="http://">';
    print '</span>';
    print '</td></tr><tr><td width=60>&nbsp;</td><td>';
   print '<span class="input_form">';
    print '<img src="img/Service_Icon.png" title="Service type of Movement-aware Content Tag" class="icon_form" height="70" width="70">';
    print '</td></tr><tr><td width=60>';
    print '<select id="simple-search-movement" class="input-large js-search-movement" id="service" name="service" class=biginput><option value="Restaurant">Restaurant</option><option value="Bar">Bar</option><option value="Concert">Concert</option><option value="Film">Film</option><option value="Books">Books</option><option value="Health">Health</option><option value="Clothes">Clothes</option><option value="Food">Food</option><option value="Music">Music</option><option value="Electronics">Electronics</option><option value="Transport">Transport</option><option value="Rental">Rental</option><option value="Search">Search</option></select></td></tr>';
    print '<input type="text" id="service" name="service" placeholder="Service">';
    # print '<h3>News</h3>';
    #print '<p><b>2021</b></p>';    
    #print '<p><i><a href="http://www.aamotsoftware.com/">Aamot Software</a>\'s second functional example of HTML with movement tagging and fetching was stored on <a href="http://geopher.com/cft/s/">http://geopher.com/cft/s/</a></i></p>';
    #print '<p><b>2020</b></p>';
    #print '<p><i><a href="http://www.aamotsoftware.com/">Aamot Software</a>\'s Indexer for Geopher written in the programming language Python can now recursively index movement tags as specified on <a href="http://www.aamotsoftware.com/movement.html">http://www.aamotsoftware.com/movement.html</a> from web pages that are listed for such indexing on <a href="http://www.aamotsoftware.com/movement-source.html">http://www.aamotsoftware.com/movement-source.html</a></i></p>';
    #print '<p><b>2015</b></p>';    
    #print '<p><i><a href="http://www.aamotsoftware.com/">Aamot Software</a>\'s first practical example of movement tagging with Geopher was stored on <a href="http://geopher.com/Google">http://geopher.com/Google</a> at a lunch table with <a href="http://www.norvig.com/">Peter Norvig</a> in the Google Visitor Center in Mountain View, California in 2015 where he mentioned crowd sourcing of movement tags with a neural network filter as future work.</i></p>';
    #print '<p><i><a href="http://www.aamotsoftware.com/">Aamot Software</a>\'s presentation for <a href="http://research.google.com/">Google Research</a>: <a href="http://www.geopher.com/doc/3.0/Geopher-Movement-aware-ContentTag.pdf">Movement-aware Content Tag: &lt;movement&gt;,&movement markup</a></p>';

    print '<span class="row row-condensed space-top-2 space-2">
	<span class="col-sm-6">
        <label for="simple-search-tourin" class="screen-reader-only">
	Tour in
        </label>
        <input
	id="simple-search-tourin"
          type="text"
          name="notBefore"
          class="input-large tourin js-search-tourin"
          placeholder="Not Before">
      </span>
      <span class="col-sm-6">
        <label for="simple-search-tourout" class="screen-reader-only">
          Tour out
          </label>
        <input
          id="simple-search-tourout"
          type="text"
          name="notAfter"
          class="input-large tourout js-search-tourout"
          placeholder="Not After">
      </span>
    </span>';
  #  print '</span>';
    print "<span id='status_publisher'>\n";
#    print "<span class='input_form_custom'>";
    print "<input id='glat' class='input_form_custom' type='text' name='glat' placeholder='Latitude' size=35 />\n";
#    print "<span class='input_form_custom'>
    print "<input id='glon' class='input_form_custom' type='text' name='glon' placeholder='Longitude' size=35 />\n";
    print "<input id='galt' class='input_form_custom' type='text' name='galt' placeholder='Altitude' size=35 />\n";    
    print "</span>\n";
    print "<input type='hidden' name='c' value='INSERT' />\n";
    print '<span class="send_form">';
    print "<script src='http://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_dg4Qj9EUNdnBicNW40nNoEJh' data-amount='0' data-name='Aamot Software' data-description='Geopher Entry ($0.01 USD)' data-image='/img/Movement_Icon.png'></script>";
    # print '<input class="custom_send_button" type="submit" value="PAY WITH CARD">';
    print '</span>';
    print '</form>';
    print '</td></tr>';
    
#    print "<input type='hidden' name='c' value='INSERT' />\n";
#    print "<table cellpadding=5><tr>";
    #   print "<td><a href='http://www.geopher.com/Geopher'><img border=0 width=16 height=16 src='js-icon.png' /></td>";
  #  print "<td><input size=16 type=text name=name class=biginput id=name placeholder='Name' /></td>\n";
    # print "<td><input size=20 type=text name=movement class=biginput id=movement placeholder='http://' /></td>\n";
    #print "<td><input size=16 type=text name=service class=biginput id=service placeholder='Service' /></td>\n";
    #print "<span id='status'><input type='hidden' name='glat' placeholder='Latitude' size=16 /><input type='hidden' name='glon' placeholder='Longitude' size=16 /></span>\n";
    # print "<td><form action='http://www.geopher.com/checkout.php' method='GET'><script src='https://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_odDlc1NMTUJdPN4WC2VTLvvu' data-amount='0' data-name='Aamot Software' data-description='1 Hour Programming/Support (10 cent)' data-image='/128x128.png'></script></td>";
  #  print "</tr>\n";
   # print "</form>\n";


}

sub input_advertiser {

    my $c = CGI->new;
    print "<input type='hidden' name='c' value='INSERT' />\n";
    print "<table cellpadding=5><tr>";
    print "<td>Word</td><td><input type=text name=name class=biginput id=name placeholder='Name'></textarea></td>\n";
    print "<td><input size=20 type=text name=movement class=biginput id=movement placeholder='http://' /></td>\n";
    print "<td><input size=16 type=text name=service class=biginput id=service placeholder='Service' /></td>\n";
#    print '<td><span class="row row-condensed space-top-2 space-2">
#      <span class="col-sm-6">
#        <label for="simple-search-tourin" class="screen-reader-only">
#          Tour in
#        </label>
#        <input
#          id="simple-search-tourin"
#          type="text"
#          name="notBefore"
#          class="input-large tourin js-search-tourin"
#          placeholder="Not Before">
#      </span>
#      <span class="col-sm-6">
#        <label for="simple-search-tourout" class="screen-reader-only">
#          Tour out
#          </label>
#       <input
#          id="simple-search-tourout"
#          type="text"
#          name="notAfter"
#          class="input-large tourout js-search-tourout"
#          placeholder="Not After">
#      </span>
#    </span>';
    print "<span id='status'><input type='hidden' name='glat' placeholder='Latitude' size=16 value='" . $c->param('glat') . "'/><input type='hidden' name='glon' placeholder='Longitude' size=16 value='" . $c->param('glon') . "' /><inpyt type='hidden' name='galt' placeholder='Altitude' size=16 value='" . $c->param('galt') . "' /></span>\n";
    print "<td><form action='https://www.geopher.com/api/movement/push.php' method='GET'><script src='http://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_dg4Qj9EUNdnBicNW40nNoEJh' data-amount='4500' data-name='Aamot Engineering' data-description='1 Hour Programming/Support (45 USD)' data-image='/img/Movement_Icon.png'></script></td>";
    print "</tr>\n";
    print "</form>\n";

}

sub mns_item {
    my $c = CGI->new;
    # my $dbh = DBI->connect("DBI:mysql:database=geophercom02;host=geophercom02.mysql.domeneshop.no", "geophercom02", "Cup-tales-rafta-1920-vispe", {'RaiseError' => 1});

    my $name = shift(@_);
    my $movement = shift(@_);
    my $glat = shift(@_);
    my $glon = shift(@_);
    my $galt = shift(@_);
    my $modified = shift(@_);
    my $created = shift(@_);
    my $distance = shift(@_);
    my $service = shift(@_);
    
    print "<tr><td width=60>&nbsp;</td><td>";
    print "<form onsubmit='updateGeo()' id='mnsForm' name='mnsForm' action='https://www.piperpal.com/' method='GET'>";
    # print '<span class="name_form input_form">';
    print "<movement href='" . $movement . "' lat='" . $glat . "' lon='" . $glon . "' alt='" . $galt . "'><a href='" . $movement . "'><h2>" . $name . "</h2></a></movement>";    
#    print "<h3>" . nearest(0.1, $distance) . " km away</h3>";
#    print "<script type='text/javascript' lang='JavaScript'>";
#    print "var latpoint = document.getElementById('glat');";
#    print "var longpoint = document.getElementById('glon');";  
#    print "latpoint.value = position.coords.latitude;";
#    print "longpoint.value = position.coords.longitude;";
#    print "print latpoint.value;";
#    print "print longpoint.value;";
#    print "</script>";
#    print "111.045*DEGREES(ACOS(COS(RADIANS(latpoint))*COS(RADIANS(glat))*COS(RADIANS(longpoint)-RADIANS(glon))+SIN(RADIANS(latpoint))*SIN(RADIANS(glat))))";
    print "<table valign='left'>";
    print "<tr><td width='60'>";
    print '<a href="/' . $name . '"><img src="/img/Name_Icon.png" title="Name of Movement-aware Content Tag" height="70" width="70"></a>';
    print '</td><td><input type="text" id="' . $name .'" name="name" placeholder="Name" value="' . $name . '"></td></tr>';
  #  print '</span>';
#    print '<br>';
    #    print '<span class="website_form input_form">';
    print "<tr><td width='60'>";    
    print '<a href="' . $movement . '"><img src="/img/Movement_Icon.png" title="URL of Movement-aware Content Tag" height="70" width="70"></a>';
    print '</td><td><input type="text" id="' . $name . '_movement' . '" name="movement" placeholder="http://" value="' . $movement . '">';
 #   print '</span>';
 #    print '<br>';
    #    print '<span class="service_form input_form">';
    print "</td></tr><tr><td width='60'>";        
    print '<a href="/service/' . $service . '"><img src="/img/Service_Icon.png" title="Service type of Movement-aware Content Tag" height="70" width="70"></a></td><td>';
    print '<input type="text" id="' . $name . '_service' . '" name="service" placeholder="Service" value="' . $service . '">';
    print "</td></tr><tr><td width='60'>";            
#    print '<span class="row row-condensed space-top-2 space-2">
#      <span class="col-sm-6">
#        <label for="simple-search-tourin" class="screen-reader-only">
#          Tour in
#        </label>
#        <input
#          id="datepicker"
#          type="text"
#          name="notBefore"
#          class="input-large tourin js-search-tourin"
#          placeholder="Not Before" value="' . $created . '">
#      </span>
#      <span class="col-sm-6">
#        <label for="simple-search-tourout" class="screen-reader-only">
#          Tour out
#          </label>
#        <input
#          id="datepicker"
#          type="text"
#          name="notAfter"
#          class="input-large tourout js-search-tourout"
#          placeholder="Not After" value="' . $modified . '">
#      </span>
#    </span>';
#    print '</span>';
    print "</td></tr><tr><td width='60'>";            
    print "<span id='status_mns'>\n";
#    print "<span class='service_form input_form'>";
    print "<img src='/img/Latitude_Icon.png' alt='Icon2' height='70' width='70'></td><td><input id='" . $name . "_glat' type='text' name='glat' placeholder='Latitude' size=35 value='" . $glat . "' />\n";
    print "</td></tr><tr><td width='60'>";

#</span>\n";

#    print "<span class='input_form_custom'><img src='img/Latitude_Icon.png' alt='Icon2' class='icon_form' height='70' width='70'><input id='" . $name . "_glat' class='input_form_custom' type='text' name='glat' placeholder='Latitude' size=32 value='" . $glat . "' /></span>\n";

    #   print "<span class='service_form input_form'>
    print "</td></tr><tr><td width='60'>";    
    print "<img src='/img/Longitude_Icon.png' alt='Icon2' height='70' width='70'></td><td><input id='" . $name . "_glon' type='text' name='glon' placeholder='Longitude' size=35 value='" . $glon . "' />\n";
#</span>\n";

 #   print "<span class='input_form_custom'><img src='img/Longitude_Icon.png' alt='Icon2' class='icon_form' height='70' width='70'><input id='" . $name . "_glon' class='input_form_custom' type='text' name='glon' placeholder='Longitude' size=32 value='" . $glon . "' /></span>\n";

    print "</td></tr><tr><td width='60'>";                
    print "<input type='hidden' name='c' value='INSERT' />\n";
#    print '<span class="send_form">';
#    print "<script src='http://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_dg4Qj9EUNdnBicNW40nNoEJh' data-amount='0' data-name='Aamot Software' data-description='Geopher Entry (1 dollar)' data-image='/img/Movement_Icon.png'></script>";
    # print '<input class="custom_send_button" type="submit" value="PAY WITH CARD">';
#    print '</span>';
    print "</td></tr>";
    print "</table>";
    # print "<form action='http://www.geopher.com/checkout.php?name=" . $name . "&service=" . $service . "' method='GET'>";
    # print '<span class="name_form input_form">';
    # print '<img src="img/icon1.png" alt="Icon1" style="margin-right:27px" class="icon_form" height="70" width="70">';
    # print '<input type="text" value="' . $name . '" id="' . $name . '" class="input_form_custom" name="name" placeholder="' . $name . '">';
    # print '</span>';
    # print '<br>';
    # print '<span class="website_form input_form">';
    # print '<img src="img/icon2.png" alt="Icon2" class="icon_form" height="70" width="70">';
    # print '<input type="text" value="' . $movement . '" id="movement" class="input_form_custom" name="movement" placeholder="' . $movement . '">';
    # print '</span>';
    # print '<br>';
    # print '<span class="service_form input_form">';
    # print '<img src="img/icon3.png" alt="Icon3" class="icon_form" height="70" width="70">';
    # print '<input type="text" value="' . $service . '" id="service" class="input_form_custom" name="service" placeholder="' . $service . '">';
    # print '</span>';
    # print "<span id='status_mns'>\n";
    # print "<span class='service_form input_form'>";
    # print '<img src="img/icon2.png" alt="Icon2" class="icon_form" height="70" width="70">';
    # print "<input id='glat' value='" . $glat . "' class='input_form_custom' type='text' name='glat' placeholder='" . $glat . "' size=16 /></span>\n";
    # print "<span class='service_form input_form'>";
    # print '<img src="img/icon2.png" alt="Icon2" class="icon_form" height="70" width="70">';
    # print "<input id='glon' value='" . $glon . "' class='input_form_custom' type='text' name='glon' placeholder='" . $glon . "' size=16 /></span>\n";
    # print "</span>\n";
    # print "<input type='hidden' name='c' value='INSERT' />\n";
    # print '<span class="send_form_item">';
    # print "<script src='http://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_odDlc1NMTUJdPN4WC2VTLvvu' data-amount='500' data-name='Aamot Software' data-description='" . $service . " (5 USD)' data-image='/img/icon2.png'></script>";
    # print '</span>';
    # print '</form>';

}

sub mns_market_item {
    my $c = CGI->new;
    # my $dbh = DBI->connect("DBI:mysql:database=geophercom02;host=geophercom02.mysql.domeneshop.no", "geophercom02", "Cup-tales-rafta-1920-vispe", {'RaiseError' => 1});

    my $name = shift(@_);
    my $movement = shift(@_);
    my $service = shift(@_);
    my $glat = shift(@_);
    my $glon = shift(@_);
    my $modified = shift(@_);
    my $created = shift(@_);
    my $distance = shift(@_);
    print "<tr><td width=60>&nbsp;</td><td>";
    print "<form onsubmit='updateGeo()' id='mnsForm' name='mnsForm' action='https://www.geopher.com/api/movement/push.php' method='GET'>";
    # print '<span class="name_form input_form">';
    print "<movement name='" . $name . "' href='" . $movement . "' lat='" . $glat . "' lon='" . $glon . "'><a href='" . $movement . "'>";
    print "<h4><a href='" . $movement . "'>" . $name . "</a></h4></movement>";
    print "<h5 style='color: #aaaadd'>" . $service . "</h5>";
    print "<h5>" . nearest(0.1, $distance) . " km away</h5>";
    print "<h6><a href='" . $movement . "'>" . $movement . "</a></h6>";
#    my $date = $created;
#    my $long = $modified;
#    my $dt = DateTime->now( time_zone => 'local' )->set_time_zone('floating');
#    print "<p><b>Created: " . $dt->subtract_datetime($date) . " days ago<br />";
#    print "Modified: "; print $dt->subtract_datetime($long) . " days ago</p>";
#    print "<p><b>";
    print "<table>";
    print "<tr><td width='60'>";
    print '<a href="/' . $name . '"><img src="/img/Name_Icon.png" title="Name of Movement-aware Content Tag" height="70" width="70"></a>';
    print '</td><td><input type="text" id="' . $name .'" name="name" placeholder="Name" value="' . $name . '"></td></tr>';
  #  print '</span>';
#    print '<br>';
    #    print '<span class="website_form input_form">';
    print "<tr><td width='60'>";    
    print '<a href="' . $movement . '"><img src="/img/Movement_Icon.png" title="URL of Movement-aware Content Tag" height="70" width="70"></a>';
    print '</td><td><input type="text" id="' . $name . '_movement' . '" name="movement" placeholder="http://" value="' . $movement . '">';
 #   print '</span>';
 #    print '<br>';
    #    print '<span class="service_form input_form">';
    print "</td></tr><tr><td width='60'>";        
    print '<a href="/service/' . $service . '"><img src="/img/Service_Icon.png" title="Service type of Movement-aware Content Tag" height="70" width="70"></a></td><td>';
    print '<select id="simple-search-movement" class="input-large js-search-movement" id="service" name="service" class=biginput><option selected value="' . $name . '.' . $service . '">' . $service . '</option><option value="Restaurant">Restaurant</option><option value="Bar">Bar</option><option value="Concert">Concert</option><option value="Film">Film</option><option value="Books">Books</option><option value="Health">Health</option><option value="Clothes">Clothes</option><option value="Food">Food</option><option value="Music">Music</option><option value="Electronics">Electronics</option><option value="Transport">Transport</option><option value="Rental">Rental</option></select>';
    print '<input type="hidden" id="paid_' . $name . '_service' . '" name="paid" placeholder="paid" value="0">';
    print "</td></tr><tr><td width='60'></td><td>";            
#    print '<span class="row row-condensed space-top-2 space-2">
#      <span class="col-sm-6">
#        <label for="simple-search-tourin" class="screen-reader-only">
#          Tour in
#        </label>
#        <input
#          id="datepicker"
#          type="text"
#          name="notBefore"
#          class="input-large tourin js-search-tourin"
#          placeholder="Not Before" value="' . $created . '">
#      </span>
#      <span class="col-sm-6">
#        <label for="simple-search-tourout" class="screen-reader-only">
#          Tour out
#          </label>
#        <input
#          id="datepicker"
#          type="text"
#          name="notAfter"
#          class="input-large tourout js-search-tourout"
#          placeholder="Not After" value="' . $modified . '">
#      </span>
#    </span>';
#    print '</span>';
    print "</td></tr><tr><td width='60'>";            
    print "<span id='status_mns'>\n";
#    print "<span class='service_form input_form'>";
    print "<img src='/img/Latitude_Icon.png' alt='Icon2' height='70' width='70'></td><td><input id='" . $name . "_glat' type='text' name='glat' placeholder='Latitude' size=35 value='" . $glat . "' />\n";
#</span>\n";

#    print "<span class='input_form_custom'><img src='img/Latitude_Icon.png' alt='Icon2' class='icon_form' height='70' width='70'><input id='" . $name . "_glat' class='input_form_custom' type='text' name='glat' placeholder='Latitude' size=32 value='" . $glat . "' /></span>\n";

    #   print "<span class='service_form input_form'>
    print "</td></tr><tr><td width='60'>";    
    print "<img src='/img/Longitude_Icon.png' alt='Icon2' height='70' width='70'></td><td><input id='" . $name . "_glon' type='text' name='glon' placeholder='Longitude' size=35 value='" . $glon . "' />\n";
#</span>\n";

 #   print "<span class='input_form_custom'><img src='img/Longitude_Icon.png' alt='Icon2' class='icon_form' height='70' width='70'><input id='" . $name . "_glon' class='input_form_custom' type='text' name='glon' placeholder='Longitude' size=32 value='" . $glon . "' /></span>\n";                             
    print "</td></tr><tr><td width='60'>";
    print "<img src='/img/Email_Icon.png' alt='Icon2' height='70' width='70'></td><td>";
    print "<input id='" . $name . "_expire' type='text' name='expire' placeholder='' size=35 value='" . $modified . "' />\n";
    print "</td></tr><tr><td width='60'>";                
    print "<img src='/img/Phone_Icon.png' alt='Icon2' height='70' width='70'></td><td>";       
    print "<input id='" . $name . "_expire' type='text' name='expire' placeholder='' size=35 value='" . $created . "' />\n";                                                                     print "</td></tr><tr><td width='60'>";
    print "<input type='hidden' name='c' value='INSERT' />\n";
#    print '<span class="send_form">';
#    print "<script src='http://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_dg4Qj9EUNdnBicNW40nNoEJh' data-amount='0' data-name='Aamot Software' data-description='Geopher Entry (1 dollar)' data-image='/img/Movement_Icon.png'></script>";
    # print '<input class="custom_send_button" type="submit" value="PAY WITH CARD">';
#    print '</span>';
    print "</td></tr>";
    print "</table>";
    # print "<form action='http://www.geopher.com/checkout.php?name=" . $name . "&service=" . $service . "' method='GET'>";
    # print '<span class="name_form input_form">';
    # print '<img src="img/icon1.png" alt="Icon1" style="margin-right:27px" class="icon_form" height="70" width="70">';
    # print '<input type="text" value="' . $name . '" id="' . $name . '" class="input_form_custom" name="name" placeholder="' . $name . '">';
    # print '</span>';
    # print '<br>';
    # print '<span class="website_form input_form">';
    # print '<img src="img/icon2.png" alt="Icon2" class="icon_form" height="70" width="70">';
    # print '<input type="text" value="' . $movement . '" id="movement" class="input_form_custom" name="movement" placeholder="' . $movement . '">';
    # print '</span>';
    # print '<br>';
    # print '<span class="service_form input_form">';
    # print '<img src="img/icon3.png" alt="Icon3" class="icon_form" height="70" width="70">';
    # print '<input type="text" value="' . $service . '" id="service" class="input_form_custom" name="service" placeholder="' . $service . '">';
    # print '</span>';
    # print "<span id='status_mns'>\n";
    # print "<span class='service_form input_form'>";
    # print '<img src="img/icon2.png" alt="Icon2" class="icon_form" height="70" width="70">';
    # print "<input id='glat' value='" . $glat . "' class='input_form_custom' type='text' name='glat' placeholder='" . $glat . "' size=16 /></span>\n";
    # print "<span class='service_form input_form'>";
    # print '<img src="img/icon2.png" alt="Icon2" class="icon_form" height="70" width="70">';
    # print "<input id='glon' value='" . $glon . "' class='input_form_custom' type='text' name='glon' placeholder='" . $glon . "' size=16 /></span>\n";
    # print "</span>\n";
    # print "<input type='hidden' name='c' value='INSERT' />\n";
    # print '<span class="send_form_item">';
    # print "<script src='http://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_odDlc1NMTUJdPN4WC2VTLvvu' data-amount='500' data-name='Aamot Software' data-description='" . $service . " (5 USD)' data-image='/img/icon2.png'></script>";
    # print '</span>';
    # print '</form>';

}

sub is_valid {
    my $movement = shift;
    my $ua = LWP::UserAgent->new;
    my $result = $ua->request(GET $movement);
    print "is_valid.\n";
    print_r($result);
    return 0 if ($result==0);
    return 1 if (($result==1)||($result==2));
}

sub is_paid {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
    if ('GET' eq $c->request_method && $c->param('paid') eq "1" && $c->param('query') && $c->param('movement')) {
	$dbh->do ("UPDATE geopher SET paid = paid + 1, modified = NOW() WHERE name = '" . HTML::Entities::encode($c->param('query')) . "' and movement = '" . $c->param('movement') . "';");
    }
    return;
}

sub delete_movement {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
    if ('GET' eq $c->request_method && $c->param('c') eq "DELETE" && $c->param('query') && $c->param('movement') && $c->param('service')) {
	$dbh->do ("DELETE FROM geopher WHERE name = '" . $c->param('query') . "' AND movement = '" . $c->param('movement') . "' AND service = '" . $c->param('service') . "';");
    }
    return;
}

sub insert_movement {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
    if ('GET' eq $c->request_method && $c->param('c') eq "INSERT" && $c->param('query') && $c->param('movement') && $c->param('service')) {
	# $dbh->do ("INSERT IGNORE INTO geopher (name, movement, service, glat, glon, modified, created, paid, token, type, email) VALUES ('" . $c->param('query') . "','" . $c->param('movement') . "','" . $c->param('service') . "','" . $c->param('glat') . "','" . $c->param('glon') . "', NOW(), NOW(), 1, '" . $c->param('stripeToken') . "', '" . $c->param('stripeTokenType') . "','" . $c->param('stripeEmail') . "') ON DUPLICATE KEY UPDATE modified = NOW();");
    }
    return;
}

sub insert_publisher {
    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
    my $q;
    if ($c->request_method && $c->param('c') && $c->param('query') && $c->param('movement') && $c->param('service')) {
	my @tags = ($c->param('query') =~ m/&(\w+)/g);
	my $name = $c->param('query');

	foreach my $tag (@tags)
	{
	    next unless $tag =~ m/[a-zA-záäåāąæćčéēėęģíīįķļłńņðóöøōőŗśšúüūűųýźżžþ]/i;  
	    $name =~ s{&$tag}{<a href="https://www.geopher.com/register.cgi?name=$tag">&$tag</a>}g;
	}
	$q = "INSERT INTO geopher (name, movement, service, glat, glon, galt, modified, created, paid, token, type, email) VALUES ('" . $name . "','" . $c->param('movement') . "','" . $c->param('service') . "','" . $c->param('glat') . "','" . $c->param('glon') . "','" . $c->param('galt') . "', NOW(), NOW(), 1, '" . $c->param('stripeToken') . "', '" . $c->param('stripeTokenType') . "','" . $c->param('stripeEmail') . "') ON DUPLICATE KEY UPDATE modified = NOW();";
	print $q;
	$dbh->do ($q);
    } else {
	# print "Error in inserting data.";
    }
    return;
}

sub update_movement {
    my $c = CGI->new();
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
#    $dbh->{'mysql_enable_utf8'} = 1;
    if ($c->param('query')) {
	my $sth = $dbh->prepare ("SELECT name,movement,service FROM geopher WHERE (name LIKE '%" . HTML::Entities::encode($c->param('query')) . "%' OR service LIKE '%" . HTML::Entities::encode($c->param('query')) . "%') ORDER by modified DESC;");
	$sth->execute();
	while (my $ref = $sth->fetchrow_hashref()) {
	    my @tags = ($ref->{'name'} =~ m/&(\w+)/g);
		foreach my $tag (@tags) {
		    next unless $tag =~ m/[a-zA-záäåāąæćčéēėęģíīįķļłńņðóöøōőŗśšúüūűųýźżžþ]/i;  
		    print "<form method='GET' action='adverts.cgi'>";
		    print "<td>Word:</td><td><input type='name' name='" . $tag . "' value='" . $tag . "' /></td>";
		    print "</form>\n";
		}
	}
	$sth->finish();
    }
    $dbh->disconnect();    
    return;
}

sub insert_advertiser {

    my $c = CGI->new;
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
#    $dbh->{'mysql_enable_utf8'} = 1;
    if ('GET' eq $c->request_method && $c->param('c') eq "INSERT" && $c->param('query') && $c->param('movement') && $c->param('service')) {
	
	my $sth = $dbh->prepare ("UPDATE Geopher SET movement = '" . $c->param('movement') . "', name = '" . HTML::Entities::encode($c->param('query')) . "', service = '" . $c->param('service') . "' = '" . $c->param('movement') . "', service = '" . $c->param('service') . " WHERE name = '" . HTML::Entities::encode($c->param('query')) . "';");
	$sth->execute();
	while (my $ref = $sth->fetchrow_hashref()) {
	    if (is_paid($ref->{'movement'})) {
		print "<pre>UPDATE:The movement of " . $ref->{'name'} . " " . $ref->{'movement'} . " is a paid geopher movement.</pre>\n";
		$dbh->do ("UPDATE Geopher SET movement = 'https://www.geopher.com/index.cgi?name=" . $ref->{'name'} . "&service" . $ref->{'service'} . "&movement=" . ($ref->{'movement'}) . "&paid=0', paid = paid + 1, modified = NOW() WHERE name = '" . $ref->{'name'} . "';");
		print "<pre>Paid +1</pre>\n";
	    } else {
		print "<pre>UPDATE:The movement of " . $ref->{'name'} . " " . $ref->{'movement'} . " is not a paid geopher movement.</pre>\n";
		$dbh->do ("UPDATE Geopher SET movement = 'https://www.geopher.com/index.cgi?name=" . $ref->{'name'} . "&service" . $ref->{'service'} . "&movement=" . ($ref->{'movement'}) . "&paid=-1', paid = paid - 1, modified = NOW() WHERE name = '" . $ref->{'name'} . "';");
		print "<pre>Paid -1</pre>\n";
	    }
	$sth->finish();
	}
    }
    $dbh->disconnect();    
    return;
}

sub select_publisher {
    my $c = CGI->new;
    my $q;
    my $r;
    my $s;
    my $latitude;
    my $longitude;
    my $fp;
#    my $fn = "/home/4/p/geopher/pull.csv";
#    my $string = "pull:" . $ENV{'REMOTE_ADDR'} . ":" . $q . "\n";    
    if ($c->param('query')) {
	$q = HTML::Entities::encode($c->param('query'));
#	open(FH, '>', $fn) or die $!;
#	print FH $string;
#	print $fp;
#	close($fp);
    } else {
	$q = "GoogleVisitorCenter";
    }
    if ($c->param('service')) {
	$s = $c->param('service');
    } else {
	$s = 'Search';
    }
    if ($c->param('radius')) {
	$r = $c->param('radius');
    } else {
	$r = 10;
    }
    if ($c->param('glat')) {
	$latitude = $c->param('glat');
    } else {
	# FIXME: READ LATITUDE FROM JAVASCRIPT
	$latitude = $ENV{'position.coords.latitude'};
# 37.8790153;
    }
    if ($c->param('glon')) {
	$longitude = $c->param('glon');
    } else {
	# FIXME: READ LONGITUDE FROM JAVASCRIPT
	$longitude = $ENV{'position.coords.longitude'};
#-122.26242529999999;
    }
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
#    $dbh->{'mysql_enable_utf8'} = 1;
    my $query = "SELECT name,movement,glat,glon,modified,created,paid,token,type,email FROM geopher WHERE (name LIKE '%" . HTML::Entities::encode($c->param('query')) . "%') ORDER by modified DESC;";
    $query = "SELECT DISTINCT id,name,movement,service,modified,created,glat,glon,paid,token,type,email,3979*(ACOS(COS(RADIANS(latpoint))*COS(RADIANS(glat))*COS(RADIANS(longpoint)-RADIANS(glon))+SIN(RADIANS(latpoint))*SIN(RADIANS(glat)))) AS distance_in_km FROM Geopher JOIN (SELECT  " . $latitude . "  AS latpoint, " . $longitude . " AS longpoint) AS p ON 1=1 WHERE (name LIKE '%" . HTML::Entities::encode($c->param('query')) . "%') HAVING distance_in_km < " . $r . " ORDER BY distance_in_km ASC, modified DESC";
    my $sth = $dbh->prepare ($query);
    $sth->execute();
    print "<a name='results'><a href=\"https://www.geopher.com/\"><img src='/geopher.png' alt='geopher.com Logo' width=\"320\" align=center/></a><br /><h3><a href=\"https://www.geopher.com/\">Movement Search Results</a></h3></a>";
    print "<ol>";
    print "<table>";
    while (my $ref = $sth->fetchrow_hashref()) {
	print "<tr><td width='60'>&nbsp;</td><td>";
	print "<form onsubmit='updateGeo()' method='GET' action='https://www.geopher.com/cft/s/' id='formID'>";
	mns_market_item($ref->{'movement'}, $ref->{'glat'}, $ref->{'glon'}, $ref->{'galt'});
	print "<input type='submit' value='Submit Movement for " . $ref->{'name'} . "'/>";	
	print "</form>";
	print "</td></tr>";
    }
    print "</table>";
    print "</ol>";
    $sth->finish();
    $dbh->disconnect();
    return;
}

sub select_movement {
    my $c = CGI->new;
    my $q;
    my $r;
    my $latitude;
    my $longitude;
    my $fp;
    my $fn = "/home/5/g/geopher/move.csv";
    my $string = "pull:" . $ENV{'REMOTE_ADDR'} . ":" . $q . "\n";    
    if ($c->param('query')) {
	$q = HTML::Entities::encode($c->param('query'));
	open(FH, '>', $fn) or die $!;
	print FH $string;
	print $fp;
	close($fp);
    } else {
	$q = "GoogleVisitorCenter";
    }
    if ($c->param('radius')) {
	$r = $c->param('radius');
    } else {
	$r = 1;
    }
    if ($c->param('glat')) {
	$latitude = $c->param('glat');
    } else {
	$latitude = 37.8790153;
    }
    if ($c->param('glon')) {
	$longitude = $c->param('glon');
    } else {
	$longitude = -122.26242529999999;
    }
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
#    $dbh->{'mysql_enable_utf8'} = 1;

#    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
#    $dbh->{'mysql_enable_utf8'} = 1;
    #my $sth = $dbh->prepare ("SELECT DISTINCT id,name,service,movement,modified,created,glat,glon,paid,token,type,email,111.045*DEGREES(ACOS(COS(RADIANS(latpoint))*COS(RADIANS(glat))*COS(RADIANS(longpoint)-RADIANS(glon))+SIN(RADIANS(latpoint))*SIN(RADIANS(glat)))) AS distance_in_km FROM geopher JOIN (SELECT  " . $latitude . "  AS latpoint, " . $longitude . " AS longpoint) AS p ON 1=1 WHERE paid > '0' AND name LIKE '%" . $q . "%' HAVING distance_in_km < " . $r . " ORDER BY distance_in_km");
    my $sth = $dbh->prepare ("SELECT DISTINCT name,movement,service,glat,glon,modified,created,paid,token,type,email FROM Geopher WHERE modified < NOW() and created > NOW() ORDER by modified DESC, name ASC;");
    $sth->execute();
    while (my $ref = $sth->fetchrow_hashref()) {
	#print "<h3><a href='https://www.geopher.com/" . $ref->{'name'}  . "'>" . $ref->{'name'} . "</a></h3>";
	print "<form onsubmit='updateGeo()' method='GET' action='https://www.geopher.com/cft/s/' id='formID'>";	
	mns_market_item($ref->{'name'}, $ref->{'movement'}, $ref->{'service'}, $ref->{'glat'}, $ref->{'glon'}, $ref->{'modified'}, $ref->{'created'});
	print "<input type='submit' value='Submit Movement for " . $ref->{'name'} . "'/>";
	print "</form>\n";
    }
    $sth->finish();    
    $dbh->disconnect();
    return;
}

sub select_market {
    my $c = CGI->new;
    my $q;
    my $r;
    my $latitude;
    my $longitude;
    if ($c->param('query')) {
	$q = HTML::Entities::encode($c->param('query'));
    } else {
	$q = "GoogleVisitorCenter";
    }
    if ($c->param('radius')) {
	$r = $c->param('radius');
    } else {
	$r = 25;
    }
    if ($c->param('glat')) {
	$latitude = $c->param('glat');
    } else {
	$latitude = 37.8790153;
    }
    if ($c->param('glon')) {
	$longitude = $c->param('glon');
    } else {
	$longitude = -122.26242529999999;
    }
    my $dbh = DBI->connect("DBI:mysql:database=geophercom01;host=geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", {'RaiseError' => 1});
#    $dbh->{'mysql_enable_utf8'} = 1;
    my $query = "SELECT name,movement,service,glat,glon,modified,created,paid,token,type,email FROM Geopher WHERE (name LIKE '%" . $q . "%' OR service LIKE '%" . $q . "%') AND paid > '0' ORDER by modified;";
    $query = "SELECT DISTINCT id,name,movement,modified,created,glat,glon,paid,token,type,email,3979*(ACOS(COS(RADIANS(latpoint))*COS(RADIANS(glat))*COS(RADIANS(longpoint)-RADIANS(glon))+SIN(RADIANS(latpoint))*SIN(RADIANS(glat)))) AS distance_in_km FROM Geopher JOIN (SELECT  " . $latitude . "  AS latpoint, " . $longitude . " AS longpoint) AS p ON 1=1 WHERE (name LIKE '%" . $q . "%') HAVING distance_in_km < " . $r . " ORDER BY distance_in_km,modified";
    my $sth = $dbh->prepare ($query);
    $sth->execute();
#    print "</td></tr></table><table><tr><td>";
    while (my $ref = $sth->fetchrow_hashref()) {
	print "<form onsubmit='updateGeo()' id='mnsForm' name='mnsForm' action='https://www.geopher.com/api/movement/push.php' method='GET'>";
#	print "<table><tr><td width='60'>&nbsp;</td><td>";
	mns_market_item($ref->{'movement'}, $ref->{'glat'}, $ref->{'glon'}, $ref->{'galt'});
	print "<input type='submit' value='Submit Movement for " . $ref->{'name'} . "'/>";
#	print "</td></tr></table>";
	print "</form>";
    }
    print "</td></tr></table>";
    $sth->finish();    
    $dbh->disconnect();
    return;
}
