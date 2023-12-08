<?php
$db = mysqli_connect("geophercom01.mysql.domeneshop.no","geophercom01","xxxxxxxx","geophercom01");
// mysqli_set_charset($db,"utf8");
if (isset($_GET['name'])) {
    $query = "SELECT DISTINCT glat,glon,alt,w,h,l,re FROM Positron WHERE glat = '" . $_GET['glat'] . "' AND glon = '" . $_GET['glon'] . "';";
} else {
    if (isset($_GET['service'])) {
        $query = "SELECT DISTINCT glat,glon,alt,w,h,l,re FROM Positron WHERE glat = '" . $_GET['glat'] . "' AND glon = '" . $_GET['glon'] . "';";
    } else {
        $query = "SELECT DISTINCT glat,glon,alt,w,h,l,re FROM Positron WHERE glat = '" . $_GET['glat'] . "' AND glon = '" . $_GET['glon'] . "';";
    }
}
$result = $db->query($query);
// print $query;
$num_coords = mysqli_num_rows($result);
if ($num_coords == 0) {
  print '<h3>' . $_GET['service'] . '</h3><ul><li><a href="http://geopher.com/cft/?movement=' . $_GET['movement'] . '&service=' . basename($_SERVER['HTTP_REFERER']) . '">New</a></li><li>Upvote</li><li>Comment</li><li>Stamp</li></ul></ul>';
//  header("Movement: http://geopher.com/");
} else {
  // print "$(function(){\n  var movements = [\n";
  print "var movements = '{ \"movements\" : [' + '";
  $count = 0;
  //  print "<h1>" . $_GET['service'] . "</h1>";
  while($object = mysqli_fetch_object($result)) {
    $count++;
    if ($count == $num_coords) {
      print '{"id": "' . $object->id . '", "name": "' . $object->name . '", "service": "' . $object->service . '", "movement": "' . $object->movement . '", "modified": "' . $object->modified . '", "created": "' . $object->created . '", "glat": "' . $object->glat . '", "glon": "' . $object->glon . '", "alt": "' . $object->alt . '", "paid": "' . $object->paid . '", "token": "' . $object->token . '", "type": "' . $object->type . '", "distance": "' . $object->distance_in_km . '", "email": "' . $object->email . '"}';
    } else {
      print '{"id": "' . $object->id . '", "name": "' . $object->name . '", "service": "' . $object->service . '", "movement": "' . $object->movement . '", "modified": "' . $object->modified . '", "created": "' . $object->created . '", "glat": "' . $object->glat . '", "glon": "' . $object->glon . '", "alt": "' . $object->alt . '", "paid": "' . $object->paid . '", "token": "' . $object->token . '", "type": "' . $object->type . '", "distance": "' . $object->distance_in_km . '", "email": "' . $object->email . '"},';
    }
  }
  print "]}';\n";
}
?>
