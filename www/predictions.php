<?php
require("../YayLocation.php");
$YayLoc = new YayLocation($_GET);
$YayLoc->get_predictions($_GET['query']);
?>
