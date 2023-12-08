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
use CGI qw/:standard/;                                                          
use CGI::Cookie;                                                                
use lib '..';

# use Geomail;

my $c = CGI->new;

print "Content-Type: text/html\n\n";
print <<EOD;
<html>
  <head>
    <title>Geopher - Who, What, Where, When?</title>
    <meta charset="utf-8">
    <meta name="viewport" content="user-scalable=no, initial-scale=1.0, maximum-scale=1.0, width=device-width">
    <!--[if IE 8]>
    <link href="https://www.piperpal.com/css/common_o2.1_ie8-91981ea8f3932c01fab677a25d869e49.css" media="all" rel="stylesheet" type="text/css" />
    <![endif]-->
    <!--[if !(IE 8)]><!-->
    <link href="https://www.piperpal.com/css/common_o2.1-858f47868a8d0e12dfa7eb60fa84fb17.css" media="all" rel="stylesheet" type="text/css" />
    <!--<![endif]-->

    <!--[if lt IE 9]>
    <link href="https://www.piperpal.com/css/airglyphs-ie8-9f053f042e0a4f621cbc0cd75a0a520c.css" media="all" rel="stylesheet" type="text/css" />
    <![endif]-->

    <link href="https://www.piperpal.com/css/main-f3fcc4027aaa2c83f08a1d51ae189e3b.css" media="screen" rel="stylesheet" type="text/css" />
    <!--[if IE 7]>
    <link href="https://www.piperpal.com/css/p1_ie_7-0ab7be89d3999d751ac0e89c44a0ab50.css" media="screen" rel="stylesheet" type="text/css" />
    <![endif]-->
    <!--[if IE 6]>
    <link href="https://www.piperpal.com/css/p1_ie_6-7d6a1fd8fe9fdf1ce357f6b864c83979.css" media="screen" rel="stylesheet" type="text/css" />
    <![endif]-->
    <link rel="stylesheet" href="//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css">
    <link rel="dns-prefetch" href="//maps.googleapis.com">
    <link rel="dns-prefetch" href="//maps.gstatic.com">
    <link rel="dns-prefetch" href="//mts0.googleapis.com">
    <link rel="dns-prefetch" href="//fonts.googleapis.com">
    <link rel="dns-prefetch" href="//www.piperpal.com">
    <title>piperpal.com - Location-based Search Engine</title>
    <link href="my_style_form.css" type="text/css" rel="stylesheet" />
    <link href='http://fonts.googleapis.com/css?family=Titillium+Web:700' rel='stylesheet' type='text/css'>
    <link href='http://fonts.googleapis.com/css?family=Titillium+Web' rel='stylesheet' type='text/css'>
    <script type='text/javascript' src='https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script>
  </head>
  <body>
    <h1>Geopher</h1>
    <h2>Who, What, Where, When?</h2>
    <script type="text/javascript" src="https://api.piperpal.com/location/json.php?service=Restaurant&glat=60&glon=10"></script>
    <script language="JavaScript">
    var obj = JSON.parse(locations);
    document.write(obj);
    for (i=0; i < obj.locations.length; i++) {
	document.write("<p>Between " + obj.locations[i].modified + "\"><b>" + obj.locations[i].created + "</b> (<u>" + obj.locations[i].distance + "</u>)" + " <i>" + obj.locations[i].service + "</i></option>\n");
    }
    </script>
    <p>On July 4th we ate at <a href="https://www.piperpal.com/cft/s/?name=TheBestLunchPlace&service=Restaurant">\&TheBestLunchPlace</a> which we keep secret for now.</p>
    <!--
    <script type="text/javascript" src="https://api.piperpal.com/location/json.php?service=Books&glat=60&glon=10"></script> 
    -->   
    <script type="text/javascript" src="https://api.piperpal.com/location/json.php?service=Restaurant&glat=60&glon=10"></script>
    <table>
    <tr>
    <td width="300">
    <form method="POST" action="/s">
    <input size="8" name="pronome" value="Who?" />
    <input size="8" name="proverb" value="What?" />
    <select name="proverb">
    <script language="JavaScript">
    var obj = JSON.parse(locations);
    for (i=0; i < obj.locations.length; i++) {
	document.write("<option value=\"" + obj.locations[i].name + "\"><b>" + obj.locations[i].name + "</b> (<u>" + obj.locations[i].distance + "</u>)" + " <i>" + obj.locations[i].service + "</i></option>");
	<!--document.write("<p>" + obj.locations[i].distance + "</p><form method='GET' action='/search.php'><input type='text' name='name' placeholder='' value='" + obj.locations[i].name + "'/><input type='hidden' name='glat' value='" + obj.locations[i].glat + "' /><input type='hidden' name='glon' value='" + obj.locations[i].glon + "'/><span id='geopher'></span><select name='service'><option value='Food'>Food</option><option selected value='Search'>Search</option></select><input type='submit' value='Search' /><br />"); -->
    }
    </script>    
    <script language="JavaScript">
    var obj = JSON.parse(locations);
    for (i=0; i < obj.locations.length; i++) {
	document.write("<option value=\"" + obj.locations[i].name + "\"><b>" + obj.locations[i].name + "</b> (" + obj.locations[i].distance + ")" + "<i>" + obj.locations[i].service + "</i></option><br />");
    }
    </script>
    </select>
    <select name="location">
      <option value="Oslo, Norway">Oslo, Norway</option>
      <option value="Bergen, Norway">Bergen, Norway</option>
      <option value="Paris, France">Paris, France</option>
      <option value="London, England">London, England</option>
      <option value="Stockholm, Sweden">Stockholm, Sweden</option>
      <option value="New York, U.S.A.">New York, U.S.A.</option>
      <option value="San Francisco, California, U.S.A.">San Francisco, California, U.S.A.</option>	
    </select>
    <input size="8" name="location" value="Where?" />
    <input size="8" name="timeverb" value="When?" />
    <input size="8" value="Post" type="submit" />
    </form>
    </td>
    </tr>
    </table>
    <p><a href="http://www.opentable.com/">Open Table</a></p>    
  </body>
</html>
EOD
