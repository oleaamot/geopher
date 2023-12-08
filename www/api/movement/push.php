<?php

// require_once('/home/5/g/geopher/stripe-php/init.php');
// require_once('/home/5/g/geopher/YayMovement.php');

// $yay = new YayMovement($_POST);

// $token = $_GET['stripeToken'];

//	print "INSERT IGNORE INTO geopher (name, movement, service, glat, glon, modified, created, paid, token, type, email) VALUES ('" . $_GET['name'] . "','" . $_GET['movement'] . "','" . $_GET['service'] . "','" . $_GET['glat'] . "','" . $_GET['glon'] . "','" . date("Y-m-d h:i:s",strtotime($_GET['notBefore'])) . "','" . date("Y-m-d h:i:s",strtotime($_GET['notAfter'])) . "', '" . $_GET['paid'] . "','" . $_GET['stripeToken'] . "', '" . $_GET['stripeTokenType'] . "','" . $_GET['stripeEmail'] . "') ON DUPLICATE KEY UPDATE modified = NOW();";

// try {
    
//     if ($yay->get_freedate($_GET['notBefore'], $_GET['notAfter']) == TRUE) {
        
//         $yay->get_checkout("INSERT IGNORE INTO geopher (name, movement, service, glat, glon, modified, created, paid, token, type, email) VALUES ('" . $_GET['name'] . "','" . $_GET['movement'] . "','" . $_GET['service'] . "','" . $_GET['glat'] . "','" . $_GET['glon'] . "', '" . date("Y-m-d h:i:s",strtotime($_GET['notBefore'])) . "','" . date("Y-m-d h:i:s",strtotime($_GET['notAfter'])) . "','" . $_GET['paid'] . "','" . $_GET['stripeToken'] . "', '" . $_GET['stripeTokenType'] . "','" . $_GET['stripeEmail'] . "') ON DUPLICATE KEY UPDATE modified = NOW();");
//         print_r($yay->result);
        
//         $stripe = array(
//             "secret_key"      => "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",
//             "publishable_key" => "pk_live_51MsrtFAgJ7jHvJPRzksQbNY4573e98c9MPwsnOXymtKYWFUVgh6BbmZV9tPhhTwppFLDabbfm7Lkj9dEYaJBD9em00xNBVHJzf"
//         );
        
//         \Stripe\Stripe::setApiKey($stripe['secret_key']);
        
//         if ($_GET['paid'] > 0) {
            
//             $charge = \Stripe\Charge::create(array("amount" => $_GET['paid'],
//                                                    "currency" => "usd",
//                                                    "source" => $token,
//                                                    /					 "description" => $_GET['name']));
//         }
//     }
// }
// catch(\Stripe\Error\Card $e) {
//   print "The card has been declined.  Please try another card.";
// }
$fp = fopen("/home/5/g/geopher/data.csv", "a+");
fwrite($fp, "push;" . time() . ";" . $_SERVER['REMOTE_ADDR'] . ";" . $_GET['name'] . ";" . $_GET['stripeToken'] . "\n");
fclose($fp);
$db = mysqli_connect("geophercom01.mysql.domeneshop.no", "geophercom01", "xxxxxxxx", "geophercom01");
$query = "INSERT INTO Positron (glat, glon, alt, w, h, l, re) VALUES ('" . $_GET['glat'] . "','" . $_GET['glon'] . "','" . $_GET['galt'] . "','" . $_GET['w'] . "','" . $_GET['h'] . "','" . $_GET['l'] . "','" . $_GET['re'] . "');";
print $query;
$result = $db->query($query);
$geoqi = "INSERT INTO Geopher (glat, glon, galt) VALUES ('" . $_GET['glat'] . "','" . $_GET['glon'] . "','" . $_GET['galt'] . "');";
print $geoqi;
$result = $db->query($geoqi);
header("Movement: https://www.geopher.com/?query=" . $_GET['name'] . "&glat=" . $_GET['glat'] . "&galt=" . $_GET['galt'] . "&movement=" . $_GET['movement'] . "&glon=" . $_GET['glon'] . "&service=" . $_GET['service'] . "&paid=" . $_GET['paid']);
print "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8' />";
print "<meta http-equiv='refresh' content='120; url=https://www.geopher.com/?query=" . $_GET['name'] . "&radius=10000&search=Go&glat=" . $_GET['glat'] . "&glon=" . $_GET['glon'] . "&galt=" . $_GET['galt'] . "&movement=" . $_GET['movement'] . "'>";
print "</head>\n";
print "<body>\n";
print "<h1>geopher.com</h1>\n";
print "&lt;movement name=\"" . $_GET['name'] . "\" movement=\"" . $_GET['movement'] . "\" service=\"" . $_GET['service'] . "\" glat=\"" . $_GET['glat'] . "\" glon=\"" . $_GET['glon'] . "\" alt=\"" . $_GET['galt'] . "\" notbefore=\"" . date("Y-m-d h:i:s",strtotime($_GET['notBefore'])) . "\" notafter=\"" . date("Y-m-d h:i:s",strtotime($_GET['notAfter'])) . "\" paid=\"" . $_GET['paid'] . "\" /&gt;";        
//    print "<p>We will process the payment...</p>\n";
print "<p>Redirecting to the Geopher Movement-based Search engine.</p>\n";
exit(0);
?>
