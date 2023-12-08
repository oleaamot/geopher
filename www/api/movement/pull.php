<?php

$fp = fopen("/home/5/g/geopher/move.csv", "a+");
fwrite($fp, "pull" . ";" . $_SERVER['REMOTE_ADDR'] . ";" . $_GET['name'] . "\n");
fclose($fp);

header("Location: https://geopher.com/cft/s/?glat=" . $_GET['glat'] . "&glon=" . $_GET['glon'] . "&galt=" . $_GET['galt'] . "&service=" . $_GET['service'] . "&paid=" . $_GET['paid']);

exit(0);

/* $db = mysqli_connect("piperpal.mysql.domeneshop.no","piperpal","FiFLHHPxyR7PXUg","piperpal"); */

/* $query = "INSERT INTO piperpal (name,location,service,glat,glon) VALUES ('" . $_GET['name'] . "', '" . $_GET['location'] . "', '" . $_GET['service'] . "', " . $_GET['glat'] . "," . $_GET['glon'] . ");"; */

/* $result = $db->query($query); */
?>
