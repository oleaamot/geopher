<?php
require("../YayLocation.php");
$YayLoc = new YayLocation($_GET);
$YayLoc->get_word_predictions("37.437548899999996","-122.11916289999999");
?>
