<?php
require("com/yayimages/YayLocation.php");
$YayLoc = new YayLocation($_GET);
$db = mysqli_connect("aamot.mysql.domeneshop.no","aamot","V9!7$5z9","aamot");
$query = "SELECT DISTINCT name,glat,glon FROM yaylocation modified < NOW() and created > NOW() ORDER by name LIMIT 50;";
$result = $db->query($query);
$num_coords = mysqli_num_rows($result);
print "$(function(){\n  var currencies = [\n";
while($object = mysqli_fetch_object($result)) {
	print "    { value: '" . $object->name . "', data: '" . $object->glat . "," . $object->glon . "' },\n";
}
print "];\n";
print "\n";
print "// setup autocomplete function pulling from currencies[] array\n";
print "  $('#autocomplete').autocomplete({\n";
print "    lookup: currencies,\n";
print "    onSelect: function (suggestion) {\n";
print "      var thehtml = '<form method=GET action=><strong>Location Name:</strong> ' + suggestion.value + ' <br> <strong>Location Data:</strong> ' + suggestion.data + '<input type=hidden name=glat size=16 value=' + position.coords.latitude + ' /><input type=hidden name=glon size=16 value=' + position.coords.longitude + ' /><select name=center onchange=this.form.submit() >" . $YayLoc->get_locations() . "</select></form>';";
print "$('#outputcontent').html(thehtml);\n";
print "    }\n";
print "  });\n";
print "\n";
/* print "$.ajax({"; */
/* print "   type: 'GET',"; */
/* print "   url: http://yay.oka.no/,"; */
/* print "   data: suggestion.value,"; */
/* print "   success: success,"; */
/* print "   dataType: dataType"; */
/* print "});"; */
print "});";
?>
