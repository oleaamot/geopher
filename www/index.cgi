#!/usr/bin/perl

# Copyright (C) 2015, 2019  Aamot Software
#
# Author: ole@aamotsoftware.com
#
# Date: 2015-09-03T11:15:00+01
#
# Field: Incremental, movement, sql, perl
#
# URL: https://www.geopher.com/index.cgi

use strict;
use warnings;
use DBI;
use CGI qw/:standard/;
use CGI::Cookie;
use lib '..';
use Geopher;

my $c = CGI->new;
print "Content-Type: text/html\n\n";
print <<EOF;
<!DOCTYPE html>
<html lang="en">
    <head>
    <style>
    #name label{
    display: inline-block;
    width: 100px;
    text-align: right;
    }
    #name_submit{
    padding-left: 100px;
    }
    #name div{
    margin-top: 1em;
    }
    textarea{
    vertical-align: top;
    height: 5em;
    }

    .error{
    display: none;
    margin-left: 10px;
    }

    .error_show{
    color: red;
    margin-left: 10px;
    }

    input.invalid, textarea.invalid{
    border: 2px solid red;
    }

    input.valid, textarea.valid{
    border: 2px solid green;
    }
    </style>
    <meta property="al:android:app_name" content="Geopher" />
    <meta property="al:android:package" content="com.geopher.api.android" />
    <meta property="al:android:url" content="https://www.geopher.com/Android" />
    <!--[if IE]><![endif]-->
    <meta charset="iso-8859-1">

    <!--[if IE 8]>
      <link href="/css/common_o2.1_ie8-91981ea8f3932c01fab677a25d869e49.css" media="all" rel="stylesheet" type="text/css" />
    <![endif]-->
   <!--[if !(IE 8)]><!-->
      <link href="/css/common_o2.1-858f47868a8d0e12dfa7eb60fa84fb17.css" media="all" rel="stylesheet" type="text/css" />
    <!--<![endif]-->

    <!--[if lt IE 9]>
      <link href="/css/airglyphs-ie8-9f053f042e0a4f621cbc0cd75a0a520c.css" media="all" rel="stylesheet" type="text/css" />
    <![endif]-->

    <link href="/css/main-f3fcc4027aaa2c83f08a1d51ae189e3b.css" media="screen" rel="stylesheet" type="text/css" />
  <!--[if IE 7]>
    <link href="/css/p1_ie_7-0ab7be89d3999d751ac0e89c44a0ab50.css" media="screen" rel="stylesheet" type="text/css" />
  <![endif]-->
  <!--[if IE 6]>
    <link href="/css/p1_ie_6-7d6a1fd8fe9fdf1ce357f6b864c83979.css" media="screen" rel="stylesheet" type="text/css" />
    <![endif]-->
    <!-- FIXME-->
    <script type="text/javascript" src="https://www.geopher.com/geopher-autocomplete-tours.php"></script>
    <!--FIXME -->
  <link rel="stylesheet" href="//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css">
  <script src="//code.jquery.com/jquery-1.10.2.js"></script>
    <script src="//code.jquery.com/ui/1.11.4/jquery-ui.js"></script>
    <meta name="viewport" content="user-scalable=yes, initial-scale=1.0, maximum-scale=3, minimum-scale=0.5, width=device-width">
    <!--
    <link rel="dns-prefetch" href="//maps.googleapis.com">
    -->
    <link rel="dns-prefetch" href="//maps.gstatic.com">
    <link rel="dns-prefetch" href="//mts0.googleapis.com">
    <link rel="dns-prefetch" href="//fonts.googleapis.com">
    <link rel="dns-prefetch" href="//www.geopher.com">
    <title>geopher.com - Movement-based Search Engine</title>
    <link href="my_style_form.css" type="text/css" rel="stylesheet" />
    <link href='https://fonts.googleapis.com/css?family=Titillium+Web:700' rel='stylesheet' type='text/css'>
    <link href='https://fonts.googleapis.com/css?family=Titillium+Web' rel='stylesheet' type='text/css'>
    <meta charset="iso-8859-1" />
    <script>
    function price_changed() {
        var priceWidget = document.getElementById('price');
        var price = priceWidget.options[priceWidget.selectedIndex].value;
        var stripeSubmit = document.getElementsByClassName('stripe-button-el')[0];
        var regularSubmit = document.getElementById('regular-submit');
        if (price > 0) {
	    stripeSubmit.style.display = 'inline-block';
	    regularSubmit.style.display = 'none';
        } else {
	    stripeSubmit.style.display = 'none';
	    regularSubmit.style.display = 'inline-block';
        }
}

function updateGeo() {
    var glat = document.getElementById("glat");
    var glon = document.getElementById("glon");
    var galt = document.getElementById("galt");
    glat.value = position.coords.latitude;
    glon.value = position.coords.longitude;
    galt.value = position.coords.altitude;

    alert(glat+","+glon+","+galt);
}

function getWikipedia() {
    jQuery(function($) {
	$.getJSON('https://api.geonames.org/findNearbyWikipediaJSON?formatted=true&lat='+ position.coords.latitude +'&lng='+ position.coords.longitude +'&username=username&style=full&lang=en&wikipediaUrl&thumbnailImg', function(json){

	    for(var i = 0; i < json.geonames.length; i++)
	    {
		$("#wikipedia").prepend('<span style="font-family: geneva, arial, helvetica, sans-serif;"><br><br><img src="wikilogo.gif"><br>' + json.geonames[i].summary + '<br><a href="https://'+ json.geonames[i].wikipediaUrl +'" target="_blank">'+ json.geonames[i].wikipediaUrl +'</a><br></span>');
		  }
	    }); });
}

function submit() {
        // Strip hijacks the form submit, so we need to un-hijack it.
	    var form = document.getElementById('form');
        form.submit();
}
    </script>
    <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" >
    <meta http-equiv="X-UA-Compatible" content="IE=edge" >
    <link href='//fonts.googleapis.com/css?family=Titillium+Web:300italic,400,700,400italic,600italic' rel='stylesheet' type='text/css'>
    <link href='//fonts.googleapis.com/css?family=Titillium+Web:300italic,400,700,400italic,600italic' rel='stylesheet' type='text/css'>

    <link rel="stylesheet" href="//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css">
    <script src="//code.jquery.com/jquery-1.10.2.js"></script>
    <script src="//code.jquery.com/ui/1.11.4/jquery-ui.js"></script>

    <script type="text/javascript" src="https://www.geopher.com/jquery-1.9.1.min.js"></script>
    <script type="text/javascript" src="https://www.geopher.com/jquery.autocomplete.min.js"></script>
    <!-- FIXME -->
    <script type="text/javascript" src="https://www.geopher.com/geopher-autocomplete.php"></script>
    <script type="text/javascript" src="https://www.geopher.com/geopher-autocomplete-names.php"></script>
    <script type="text/javascript" src="https://www.geopher.com/geopher-autocomplete-services.php"></script>
    <script type="text/javascript" src="https://www.geopher.com/geopher-autocomplete-movements.php"></script>
    <script type="text/javascript" src="https://www.geopher.com/geopher-autocomplete-queries.php"></script>
    <!-- FIXME -->
    <meta name="viewport" content="user-scalable=yes, initial-scale=1.0, maximum-scale=3, minimum-scale=0.5, width=device-width">
    <script>
    \$(function() {
	\$( "#datepicker" \)\.datepicker\(\)\;
	\$( "#simple-search-tourout" \)\.datepicker\(\)\;
    \}\)\;
    </script>
    <meta name="viewport" content="user-scalable=yes, initial-scale=1.0, maximum-scale=3, minimum-scale=0.5, width=device-width">	    
    </head>
    <body style="background: #ffffff;" onload="document.getElementById('query').focus();">

    <!--
    <script type="text/javascript" src="https://maps.google.com/maps/api/js?sensor=true"></script>-->
    <!--script type="text/javascript" src="https://maps.google.com/maps/api/js?sensor=false"--><!--/script-->
    <script>
	function success(position) {
	var s = document.querySelector('#status');
	
	if (s.className == 'success') {
		// not sure why we're hitting this twice in FF, I remember it's to do with a cached result coming back    
		return;
	}
	
        s.innerHTML = '<input type=hidden class="input_form_custom" name=glat value=' + position.coords.latitude + ' /><input type=hidden class="input_form_custom" name=glon value=' + position.coords.longitude + ' /><input type=hidden class="input_form_custom" name=galt value=' + position.coords.altitude + ' />';
	s.className = 'success';

	var q = document.querySelector('#status_publisher');
	
	if (q.className == 'success') {
		// not sure why we're hitting this twice in FF, I remember it's to do with a cached result coming back    
		return;
	}
	
        q.innerHTML = '<img src="img/Latitude_Icon.png" title="Latitude of Movement-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glat size=16 value=' + position.coords.latitude + ' /><br /><img src="img/Longitude_Icon.png" title="Longitude of Movement-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glon size=16 value=' + position.coords.longitude + ' />';

        // '<input type=text name=glat size=16 value=' + position.coords.latitude + ' /><input type=text name=glon size=16 value=' + position.coords.longitude + ' />';
	q.className = 'success';

	var r = document.querySelector('#status_mns');
	
	if (r.className == 'success') {
		// not sure why we're hitting this twice in FF, I remember it's to do with a cached result coming back    
		return;
	}
        r.innerHTML =  '<img src="img/Latitude_Icon.png" title="Latitude of Movement-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glat size=16 value=' + position.coords.latitude + ' /><br /><img src="img/Longitude_Icon.png" title="Longitude of Movement-aware Content Tag" class="icon_form" height="36" width="36"><input type=text class="input_form_custom" name=glon size=16 value=' + position.coords.longitude + ' />';

//'<input type=hidden class="input_form_custom" name=glat value=' + position.coords.latitude + ' /><input type=hidden class="input_form_custom" name=glon value=' + position.coords.longitude + ' />';
	r.className = 'success';

	var mapcanvas = document.createElement('div');
	mapcanvas.id = 'mapcanvas';
	mapcanvas.style.height = '400px';
	mapcanvas.style.width = '640px';
	
	document.querySelector('article').appendChild(mapcanvas);
	
	var latlng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
	var myOptions = {
	zoom: 15,
	center: latlng,
	mapTypeControl: false,
	navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL},
	mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	var map = new google.maps.Map(document.getElementById("mapcanvas"), myOptions);
	
	var marker = new google.maps.Marker({
		position: latlng, 
				map: map, 
				title:"You are here! (at least within a "+position.coords.accuracy+" meter radius)"
				});

        var movements = [
         ['Banja Luka', 44.766666699999990000, 17.183333299999960000, 4],
    ['Tuzla', 44.532841000000000000, 18.670499999999947000, 5],
    ['Zenica', 44.203439200000000000, 17.907743200000027000, 3],
    ['Sarajevo', 43.850000000000000000, 18.250000000000000000, 2],
    ['Mostar', 43.333333300000000000, 17.799999999999954000, 1]
];

var infowindow = new google.maps.InfoWindow();

var marker, i;
for (i = 0; i < movements.length; i++) {
    marker = new google.maps.Marker({
      position: new google.maps.LatLng(movements[i][1], movements[i][2]),
      map: map
				    });

google.maps.event.addListener(marker, 'click', (function (marker, i) {
    return function () {
	infowindow.setContent(movements[i][0]);
	infowindow.open(map, marker);
    }
						})(marker, i));
}
}

function error(msg) {
	// var s = document.querySelector('#status');
	// s.innerHTML = typeof msg == 'string' ? msg : "failed";
	// s.className = 'fail';
	
	// console.log(arguments);
}

if (navigator.geolocation) {
	navigator.geolocation.getCurrentPosition(success, error);
} else {
	error('not supported');
}

</script>

    <center><table border='0'><tr><td valign='top' width='100%' align='center'><a href="https://www.geopher.com/"><h1>Geopher</h1></a></td></tr>
    
    <div class="background_form">
EOF

print "<tr><td valign='top' width='100%' align='center'>";
#print "<h3>Discover the world around you in <span id='countdowntimer'></span> seconds</h3>";
print "<script type='text/javascript'>";
print "function increase(){";
print "            var counterElement = document.getElementById(\"countdowntimer\");";
print "            var counter = counterElement.textContent;";
print "            counter++;";
print "            counterElement.innerHTML = counter;";
print "        }";
print "        window.onload = increase;";
print "</script>";
print "<h4>36 Billion Movements at Your Fingertips</h4>";
#print "<label for=\"countdowntimer\">Movement Search progress</label>";
#print "<progress id=\"countdowntimer\" max=\"50\">10%</progress>";
#print "<script type=\"text/javascript\" src=\"https://api.geopher.com/movement/json.php?service=Restaurant&glat=' + position.coords.longitude + '&glon=' + position.coords.longitude + '\"></script>\n";
#print "<script language=\"JavaScript\">\n";
#print "var obj = JSON.parse(movements);\n";
#print "for (i=0; i < obj.movements.length; i++) {\n";
#print "document.write(\"<h1>\" + obj.movements[i].name + \"</h1><h2><a href='\" + obj.movements[i].movement + \"'>\" + obj.movements[i].movement + \"</a> (\" + obj.movements[i].distance + \")</h2><h3>\" + \" \" + obj.movements[i].service + \" \" + \"</h3>\n\");\n";
#print "<!--document.write(\"<p>\" + obj.locations[i].distance + \"</p><form method='GET' action='/search.php#results'><input type='text' name='name' placeholder='' value='\" + obj.locations[i].name + \"'/><input type='hidden' name='glat' value='\" + obj.locations[i].glat + \"' /><input type='hidden' name='glon' value='\" + obj.locations[i].glon + \"'/><span id='geopher'></span><select name='service'><option value='Food'>Food</option><option selected value='Search'>Search</option></select><input type='submit' value='Search' /><br />\"); -->\n";
#print "}\"\n";
#print "</script>\n";
#print "<h3>It\'s not where you\'re from, it\'s where you\'re at</h3>";
#print "<p><a href=\"https://www.geopher.com/tutorial/\">Geopher 4.0 Tutorial</a></p>";
# print "<p>The Geopher implementation of Movement Search for World Wide Web<br />is described in <a href=\"https://www.geopher.com/thesis.pdf\">https://www.geopher.com/thesis.pdf</a> ready for 2026.</p>";
&Geopher::input_searchers($c);
# print "<a name='results'><a href=\"https://www.geopher.com/\"><img src='/geopher.png' alt='geopher.com Logo' width=\"320\" align=center/></a><br />
#<h3><a href=\"https://www.geopher.com/\">Movement Search Results</a></h3></a>";
&Geopher::select_publisher();
print "<br />";
print "<br />";
print "<br />";
print "<br />";
print "<br />";
print "<p>You could markup with &lt;location&gt; tag in <a href='https://www.w3.org/wiki/HTML/next#.3Clocation.3E_element_.28like_.29_for_expressing_geo_information.2C_eg_with_attributes_lat.2C_long.2C_altitude'>HTML</a><br />";
print "<a href=\"https://www.aamotsoftware.com/location.html\">https://www.aamotsoftware.com/location.html</a></p>";
print "<p><a href=\'https://www.stripe.com/\'><img alt=\'Powered by stripe\' src=\'/powered_by_stripe.png\'></a>&nbsp;<a href=\'https://play.google.com/store/apps/details?id=com.geopher.api.android&pcampaignid=MKT-Other-global-all-co-prtnr-py-PartBadge-Mar2515-1'><img alt='Get it on Google Play\' src=\'/google-geopher.png\'/></a></p>";
print "<p>Copyright &copy; 2023  <location name='Aamot Engineering' href='https://www.aamot.engineering/' lat='37.4219999' lon='-122.0862462' service='Electronics'>Aamot Software</location><br /><location name='Geopher' href='https://www.geopher.com/' lat='59.94215220' lon='10.71697530' service='Crawler'>Oslo, Norway</location> - <location name='Geopher' href='https://www.geopher.com/' lat='37.879015' lon='-122.262425' service='Crawler'>Berkeley, California, USA</location></p>";
#print "<h2>Wikipedia Movement-aware Content</h2>";
#&Geopher::insert_wikipedia();
#print "</td></tr><tr><td valign='top' width=512>";
#print "<h3>Be discovered by the world around you</h3>";
#print "<p>Submit entries in Geopher\'s Movement-aware Search Engine</p>";
#&Geopher::input_publisher();
#&Geopher::insert_publisher();
print '<h3>News</h3>';
print '<p><b>2023</b></p>';
print '<p><a href="https://geopher.com/">Geopher</a>\'s Where to move? feature is now active.  You need a VISA/MasterCard to add new locations at $0.01 USD at <a href="https://www.geopher.com/apple.html">https://www.geopher.com/apple.html</a></p>';
print '<a href="https://www.geopher.com/"><img src="/geopher.png" alt="geopher.com Logo" width="320" align="center/"></a><form id="form" method="GET" action="https://www.geopher.com/cft/s/"><table><tr><td>Text: <input id="name" type="text" name="name" placeholder="Example: &HappyJuly4th" size="24" /><span class="error">This field is required</span></td></tr><tr><td>Email: <input id="email" type="text" name="email" placeholder="your.name@gmail.com" /><span class="error">This field is required</span></td></tr><tr><td>Service: <select id="service" name="service"><option value="Restaurant">Restaurant</option><option value="Bar">Bar</option><option value="Concert">Concert</option><option value="Film">Film</option><option value="Books">Books</option><option value="Health">Health</option><option value="Clothes">Clothes</option><option value="Food">Food</option><option value="Music">Music</option><option value="Electronics">Electronics</option><option value="Transport">Transport</option><option value="Rental">Rental</option><option value="Search">Search</option></select></td></tr><tr><td>Movement: <input type="text" name="location" placeholder="https://yourwebsite.com/" /></td></tr><!--<tr><td>Latitude: <input type="text" name="glat" value="37.4375596"></td></tr><tr><td>Longitude: <input type="text" name="glon" value="-122.11922789999998"></td></tr><tr><td>Altitude: <input type="text" name="galt" value="0"></td></tr>--><tr><td>Payment (¢): <input type="currency" name="paid" value="1" placeholder="Type a price"></td></tr><tr><td><input type="submit" name="Submit" value="Submit" /></td></tr></table></form>';
print '<p><b>2022</b></p>';
print '<p><a href="https://www.aamotsoftware.com/">Aamot Software</a>\'s Movement Entries can be ordered for $0.01 USD per location at <a href="https://www.geopher.com/cft/s/">https://www.geopher.com/cft/s/</a>';
print '<p><b>2021</b></p>';    
print '<p><a href="https://www.aamotsoftware.com/">Aamot Software</a>\'s second functional example of HTML with location tagging and fetching was stored on <a href="https://geopher.com/apple.html">https://geopher.com/cft/s/</a></p>';
print '<p><b>2020</b></p>';
print '<p><a href="https://www.aamotsoftware.com/">Aamot Software</a>\'s Indexer for Geopher written in the programming language Python can now recursively index location tags as specified on <a href="https://www.aamotsoftware.com/location.html">https://www.aamotsoftware.com/location.html</a> from web pages that are listed for such indexing on <a href="https://www.aamotsoftware.com/location-source.html">https://www.aamotsoftware.com/location-source.html</a></p>';
print '<p><b>2015</b></p>';    
print '<p><a href="https://www.aamotsoftware.com/">Aamot Software</a>\'s first practical example of location tagging with Geopher was stored on <a href="https://geopher.com/Googleplex">https://geopher.com/Googleplex</a> at a lunch table with <a href="https://www.norvig.com/">Peter Norvig</a> in the Googleplex in Mountain View, California in 2015 where he mentioned crowd sourcing of location tags with a neural network filter as future work.</p>';
print '<p><a href="https://www.aamotsoftware.com/">Aamot Software</a>\'s presentation for <a href="https://research.google.com/">Google Research</a>: <a href="https://www.geopher.com/doc/3.0/Geopher-Movement-aware-ContentTag.pdf">Movement-aware Content Tag: &lt;location&gt;,&location markup</a></p>';
#<tr><td width=60>&nbsp;</td><td><p>Copyright &copy; 2015-2022 <a href='https://www.aamotsoftware.com/'>Ole Aamot Software</a>";
print "</td></tr></table>\n";
#print "<p>Copyright &copy; 2018 <a href=\"https://www.aamotsoftware.com/\">Ole Aamot Software</a></p>";
print "</body>\n</html>\n";
