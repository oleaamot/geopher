<?php
// Check if the request ID is present in the URL
if (isset($_GET['id'])) {
    $requestId = $_GET['id'];

    // Check if the user is logged in or authenticated (implement your authentication logic)
    $loggedInUser = 'oka@oka.no'; // Replace with actual authenticated user

    // Check if the logged-in user is authorized to charge for the location
    if ($loggedInUser == 'oka@oka.no') {
        // Perform actions to charge for the location
        // Generate a unique payment ID or reference
        $paymentId = uniqid('payment_');

        // Redirect to PayPal for payment
        $paypalUrl = "https://www.paypal.com/cgi-bin/webscr?cmd=_xclick&business=pnorvig%40google.com&item_name=Movement%20Charge&amount=5.00&currency_code=USD&custom=$paymentId&return=https://geopher.com/location/name/result/?id=$requestId";

        header("Location: $paypalUrl");
        exit();
    } else {
        echo "Unauthorized to charge for the location.";
    }
} else {
    // Handle the case where the request ID is not provided
    echo "Invalid request. Please provide a valid request ID.";
}
?>
