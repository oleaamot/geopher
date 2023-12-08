<?php
require_once('/home/4/p/piperpal/stripe-php/init.php');
require_once('/home/4/p/piperpal/YayLocation.php');
$html = "";
$db_hostname = "piperpal.mysql.domeneshop.no";
$db_database = "piperpal";
$db_password = "FiFLHHPxyR7PXUg";
$notBefore = "2015-09-04";
$notAfter = "2038-09-17";
$db = mysqli_connect($db_hostname, $db_database, $db_password, $db_database);
$query = "SELECT AvailableName, AvailableService, AvailableEmail, AvailStartTime, AvailEndTime FROM (SELECT @lastEndTime as AvailStartTime, created as AvailEndTime, name as AvailableName, service as AvailableService, email as AvailableEmail, @lastEndTime := modified FROM (SELECT name,email,service,created, modified FROM piperpal WHERE service = 'Tour with Greg Thomas' AND modified >= '" . $notBefore . "' AND created < '" . $notAfter . "' ORDER BY created) e JOIN (SELECT @lastEndTime := NULL) init) x WHERE AvailEndTime > DATE_ADD(AvailStartTime, INTERVAL 180 MINUTE);";
$result = $db->query($query);
print "<table>";
while($data_object = mysqli_fetch_object($result)) {
  $html .= "<tr><td>" . $data_object->AvailableName . "</td><td>" . $data_object->AvailableService . "</td><td><a href='mailto:" . $data_object->AvailableEmail . "'>" . $data_object->AvailableEmail . "</a></td><td>" . $data_object->AvailStartTime . "</td><td>" . $data_object->AvailEndTime . "</td></tr>";
}
print $html;
print "</table>";
?>
