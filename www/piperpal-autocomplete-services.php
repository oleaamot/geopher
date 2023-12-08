<?php
require("../YayLocation.php");
$YayLoc = new YayLocation($_GET);
$db = mysqli_connect("piperpal.mysql.domeneshop.no","piperpal","FiFLHHPxyR7PXUg","piperpal");
$query = "SELECT DISTINCT service,glat,glon FROM piperpal WHERE paid = '1' ORDER by service;";
$result = $db->query($query);
$num_coords = mysqli_num_rows($result);
print "$(function(){\n  var services = [\n";
while($object = mysqli_fetch_object($result)) {
	print "    { value: '" . $object->service . "', data: '" . $object->glat . "," . $object->glon . "' },\n";
}
print "];\n";
print "\n";
print "// setup autocomplete function pulling from services[] array\n";
print "  $('#service').autocomplete({\n";
print "    lookup: services,\n";
print "    onSelect: function (suggestion) {\n";
print "      var thehtml = '<form method=GET action=><strong>Location Name:</strong> ' + suggestion.value + ' <br> <strong>Location Data:</strong> ' + suggestion.data + '<input type=hidden name=glat size=16 value=' + position.coords.latitude + ' /><input type=hidden name=glon size=16 value=' + position.coords.longitude + ' /><select name=center onchange=this.form.submit() >" . $YayLoc->get_services() . "</select></form>';";
print "$('#outputcontent').html(thehtml);\n";
print "    }\n";
print "  });\n";
print "\n";
print "});";
?>