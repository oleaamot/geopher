<?php
$db = mysqli_connect("piperpal.mysql.domeneshop.no","piperpal","FiFLHHPxyR7PXUg","piperpal");
$query = "SELECT DISTINCT id,name,service,location,modified,created,glat,glon,paid,token,type,email,111.045*DEGREES(ACOS(COS(RADIANS(latpoint))*COS(RADIANS(glat))*COS(RADIANS(longpoint)-RADIANS(glon))+SIN(RADIANS(latpoint))*SIN(RADIANS(glat)))) AS distance_in_km FROM piperpal JOIN (SELECT  " . $_GET['latitude'] . "  AS latpoint, " . $_GET['longitude'] . " AS longpoint) AS p ON 1=1 WHERE name = '" . $_GET['name'] . "' ORDER BY distance_in_km";
$result = $db->query($query);
$num_coords = mysqli_num_rows($result);
if ($num_coords == 0) {
    print "<form method='GET' action='http://www.piperpal.com/'>\n";
    print "<input type='hidden' name='c' value='INSERT' />\n";
    print "<table cellpadding=5><tr>";
    print "<td><a href='http://piperpal.com/" . $_GET['name'] . "'><img border=0 width=16 height=16 src='https://piperpal.com/img/Location_Icon.png' /></td>";
    print "<td><input size=16 type=text name=name class=biginput id=name placeholder='Name' value='" . $_GET['name'] . "' /></td>\n";
    print "<td><input size=20 type=text name=location class=biginput id=location placeholder='http://' /></td>\n";
    print "<td><input size=16 type=text name=service class=biginput id=service placeholder='Service' /></td>\n";
    print "<div id='status'><input type='hidden' name='glat' placeholder='Latitude' size=16 value='" . $_GET['latitude'] . "' /><input type='hidden' name='glon' placeholder='Longitude' size=16 value='" . $_GET['longitude'] . "' /></div>\n";
    print "<td><form action='' method='POST'><script src='https://checkout.stripe.com/checkout.js' class='stripe-button' data-key='pk_live_9UbKhDJJWaAFnMjYQTBA8I9i00H8Z5eMmL' data-amount='10' data-name='Ole Aamot Software' data-description='1 Hour Programming/Support (10 cent)' data-image='/img/LocationIcon.png'></script></td>";
    print "</tr>\n";
    print "</form>\n";
} else {
  print "<p>$(function(){\n  var locations = [\n";
  while($object = mysqli_fetch_object($result)) {
    print "    { id: '" . $object->id . "', name: '" . $object->name . "', service: '" . $object->service . "', location: '" . $object->location . "', modified: '" . $object->modified . "', created: '" . $object->created . "', glat: '" . $object->glat . ", glon: '" . $object->glon . "', paid: '" . $object->paid . "', token: '" . $object->token . "', type: '" . $object->type . "', email: '" . $object->email . "' },<br>\n";
  }
  print "];</p>";
  echo '<p>Latitude: '.$_POST['latitude'].'<br>';
  echo 'Latitude: '.$_POST['longitude'] .'<br>';
  echo 'Location: '.$_POST['location'] .'</p>';
}
?>
