<?php

require_once('/home/4/p/piperpal/stripe-php/init.php');
require_once('/home/4/p/piperpal/YayLocation.php');

//print $_POST['stripeToken'] . "<br>\n";
//print $_POST['stripeTokenType'] . "<br>\n";
//print $_POST['stripeEmail'] . "<br>\n";
//print $_POST['paid'] . "<br>\n"; /* Update paid statement in SQL */

$yay = new YayLocation($_GET);

$token = $_POST['stripeToken'];

print "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8' />";
print "<meta http-equiv='refresh' content='120; url=https://www.piperpal.com/?query=" . $_POST['name'] . "&radius=10000&search=Go&glat=" . $_POST['glat'] . "&glon=" . $_POST['glon'] . "'>";
try {
    print "</head>\n";
    print "<body>\n";
    print "<h1>piperpal.com</h1>\n";
    print "&lt;location name=\"" . $_POST['name'] . "\" location=\"" . $_POST['location'] . "\" service=\"" . $_POST['service'] . "\" glat=\"" . $_POST['glat'] . "\" glon=\"" . $_POST['glon'] . "\" notbefore=\"" . date("Y-m-d h:i:s",strtotime($_POST['notBefore'])) . "\" notafter=\"" . date("Y-m-d h:i:s",strtotime($_POST['notAfter'])) . "\" paid=\"" . $_POST['paid'] . "\" /&gt;";
    
    print "<p>We have processed the payment...</p>\n";
    print "<p>Redirecting to the administration panel.</p>\n";

    //      print "INSERT IGNORE INTO piperpal (name, location, service, glat, glon, modified, created, paid, token, type, email) VALUES ('" . $_POST['name'] . "','" . $_POST['location'] . "','" . $_POST['service'] . "','" . $_POST['glat'] . "','" . $_POST['glon'] . "','" . date("Y-m-d h:i:s",strtotime($_POST['notBefore'])) . "','" . date("Y-m-d h:i:s",strtotime($_POST['notAfter'])) . "', '" . $_POST['paid'] . "','" . $_POST['stripeToken'] . "', '" . $_POST['stripeTokenType'] . "','" . $_POST['stripeEmail'] . "') ON DUPLICATE KEY UPDATE modified = NOW();";
    
    // if ($yay->get_freedate($_POST['notBefore'], $_POST['notAfter']) == TRUE) {
    
    $yay->get_checkout("INSERT IGNORE INTO piperpal (name, location, service, glat, glon, modified, created, paid, token, type, email) VALUES ('" . $_POST['name'] . "','" . $_POST['location'] . "','" . $_POST['service'] . "','" . $_POST['glat'] . "','" . $_POST['glon'] . "', '" . date("Y-m-d h:i:s",strtotime($_POST['notBefore'])) . "','" . date("Y-m-d h:i:s",strtotime($_POST['notAfter'])) . "','" . $_POST['paid'] . "','" . $_POST['stripeToken'] . "', '" . $_POST['stripeTokenType'] . "','" . $_POST['stripeEmail'] . "') ON DUPLICATE KEY UPDATE modified = NOW();");
// print_r($yay->result);
    
    $stripe = array(
        "secret_key" => "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",
        "publishable_key" => "pk_live_51GPZU7DObaLe8ONvW0jGKfT4xjCbVO0YBpL35ZZSpmq1Scf9rBqpRtL3oPlYIdAbvj9VKh3ZbuYI6ZP15D4lSubh00S9Nx9t3X"
    );

    $stripe_client = new \Stripe\StripeClient($stripe['secret_key']);

    $customer = $stripe->customers->create([
            'description' => _POST['name'],
            'email' => _POST['stripeEmail'],
            'payment_method' => 'pm_card_visa',
    ]);
    
    \Stripe\Stripe::setApiKey($stripe['secret_key']);
    
    $charge = \Stripe\Charge::create(array("amount" => 1,
                                           "currency" => "usd",
                                           "source" => $token,
                                           "description" => $_POST['name']));
    $fp = fopen("/home/4/p/piperpal/push.csv", "a+");
    fwrite($fp, "push;" . time() . ";" . $_POST['name'] . ";" . $_POST['stripeToken'] . ";" . $_POST['stripeEmail'] . ";" . $_SERVER['REMOTE_ADDR'] . ";" . $_POST['name'] . ";" . $token . "\n");
    fclose($fp);
} catch(\Stripe\Error\Card $e) {
    print "The card has been declined.  Please try another card.";
}
?>
