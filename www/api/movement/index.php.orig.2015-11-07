<?php
$db = mysqli_connect("piperpal.mysql.domeneshop.no","piperpal","FiFLHHPxyR7PXUg","piperpal");
$query = "SELECT DISTINCT id,name,service,location,modified,created,glat,glon,paid,token,type,email,111.045*DEGREES(ACOS(COS(RADIANS(latpoint))*COS(RADIANS(glat))*COS(RADIANS(longpoint)-RADIANS(glon))+SIN(RADIANS(latpoint))*SIN(RADIANS(glat)))) AS distance_in_km FROM piperpal JOIN (SELECT  " . $_GET['glat'] . "  AS latpoint, " . $_GET['glon'] . " AS longpoint) AS p ON 1=1 WHERE service = '" . $_GET['service'] . "' ORDER BY distance_in_km";
$result = $db->query($query);
$num_coords = mysqli_num_rows($result);
if ($num_coords == 0) {
  header("Location: http://piperpal.com/");
} else {
  // print "$(function(){\n  var locations = [\n";
  print "var locations = '{ \"locations\" : [' + '";
  $count = 0;
  while($object = mysqli_fetch_object($result)) {
    $count++;
    if ($count == $num_coords) {
      print '{"id": "' . $object->id . '", "name": "' . $object->name . '", "service": "' . $object->service . '", "location": "' . $object->location . '", "modified": "' . $object->modified . '", "created": "' . $object->created . '", "glat": "' . $object->glat . '", "glon": "' . $object->glon . '", "paid": "' . $object->paid . '", "token": "' . $object->token . '", "type": "' . $object->type . '", "distance": "' . $object->distance_in_km . '", "email": "' . $object->email . '"}';
    } else {
      print '{"id": "' . $object->id . '", "name": "' . $object->name . '", "service": "' . $object->service . '", "location": "' . $object->location . '", "modified": "' . $object->modified . '", "created": "' . $object->created . '", "glat": "' . $object->glat . '", "glon": "' . $object->glon . '", "paid": "' . $object->paid . '", "token": "' . $object->token . '", "type": "' . $object->type . '", "distance": "' . $object->distance_in_km . '", "email": "' . $object->email . '"},';
    }
  }
  print "]}';\n";
}
?>