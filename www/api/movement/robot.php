<?php

$fp = fopen("/home/4/p/piperpal/data.csv", "a+");
fwrite($fp, "push;" . $_SERVER['REMOTE_ADDR'] . ";" . $_GET['name'] . "\n");
fclose($fp);
#header("Location: https://piperpal.com/cft/s/?name=" . $_GET['name'] . "&glat=" . $_GET['glat'] . "&location=" . $_GET['location'] . "&glon=" . $_GET['glon'] . "&service=" . $_GET['service'] . "&paid=" . $_GET['paid']);

#exit(0);

# echo $_SERVER['REMOTE_ADDR'];

if ($_SERVER['REMOTE_ADDR']=="178.255.144.178" || $_SERVER['REMOTE_ADDR']=="51.175.231.6") {
    $db = mysqli_connect("piperpal.mysql.domeneshop.no","piperpal","FiFLHHPxyR7PXUg","piperpal");
    $query = "INSERT INTO piperpal (name,location,service,glat,glon,paid) VALUES ('" . $_GET['name'] . "', '" . $_GET['location'] . "', '" . $_GET['service'] . "', " . $_GET['glat'] . "," . $_GET['glon'] . "," . $_GET['paid'] . ") WHERE NOT EXISTS (SELECT name FROM piperpal WHERE name = '" . $_GET['name'] . "');";
    $result = $db->query($query);
}
?>
