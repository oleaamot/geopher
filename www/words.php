<?php
require("../YayLocation.php");
$YayLoc = new YayLocation($_GET);
$YayLoc->get_word_predictions(37.437559,-122.1192152);
$YayLoc->get_word_predictions(37.42281050,-122.08737760);
?>

