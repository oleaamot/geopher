<?php
require("../YayLocation.php");
$YayLoc = new YayLocation($_GET);
$db = mysqli_connect("piperpal.mysql.domeneshop.no","piperpal","FiFLHHPxyR7PXUg","piperpal");
$query = "SELECT DISTINCT name,glat,glon FROM piperpal WHERE service LIKE '%Tour with Greg Thomas%' AND paid = '1' ORDER by name;";
$result = $db->query($query);
$num_coords = mysqli_num_rows($result);
print "$(function(){\n  var tours = [\n";
while($object = mysqli_fetch_object($result)) {
	print "    { value: '" . $object->name . "', data: '" . $object->glat . "," . $object->glon . "' },\n";
}
print "];\n";
print "\n";
print "// setup autocomplete function pulling from tours[] array\n";
print "  $('#simple-search-location').autocomplete({\n";
print "    lookup: tours,\n";
print "    onSelect: function (suggestion) {\n";
print "      var thehtml = '<form method=GET action=><strong>Location Tour:</strong> ' + suggestion.value + ' <br> <strong>Location Data:</strong> ' + suggestion.data + '<input type=hidden name=glat size=16 value=' + position.coords.latitude + ' /><input type=hidden name=glon size=16 value=' + position.coords.longitude + ' /><select name=center onchange=this.form.submit() >" . $YayLoc->get_names() . "</select></form>';";
print "$('#outputcontent').html(thehtml);\n";
print "    }\n";
print "  });\n";
print "\n";
print "});";
?>