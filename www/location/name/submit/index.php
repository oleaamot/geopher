<?php
// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    // Retrieve form data
    $initiatorEmail = $_POST["initiatorEmail"] ?? '';
    $targetEmail = $_POST["targetEmail"] ?? '';
    $price = $_POST["price"] ?? '';
    $timePeriod = $_POST["timePeriod"] ?? '';

    // TODO: Implement validation and error handling

     // Log the form data
    $logMessage = "Movement Search Request - Initiator Email: $initiatorEmail, Target Email: $targetEmail, Price: $price, Time Period: $timePeriod";
    error_log($logMessage, 3, '/home/5/g/geopher/log/logfile.log');

    // Prepare the email subject and message
    $subject = "Movement Search Request";
    $message = "Initiator Email: $initiatorEmail\n";
    $message .= "Target Email: $targetEmail\n";
    $message .= "Price: $price\n";
    $message .= "Time Period: $timePeriod\n";
    $message .= "<a href='https://geopher.com/location/name/locate/?id=abcdefghijklmnopqrs'>https://geopher.com/location/name/locate/?id=abcdefghijklmnopqrs</a>";
    $message .= "<a href='https://geopher.com/?query=&radius=50&search=Go&glat=$glat&glon=$glon&glat=null#results'>https://geopher.com/?query=&radius=50&search=Go&glat=$glat&glon=$glon&glat=null#results</a>";
    // Send the email
    $recipient = $targetEmail; // Replace with the actual recipient email address
    $headers = "From: Geopher Movement Search <noreply@geopher.com>";

    $success = mail($recipient, $subject, $message, $headers);

    if ($success) {
        echo "<html>
                <head>
                    <title>Movement Search Form Result</title>
                </head>
                <body>
                    <h1>Movement Search Form Result</h1>
                    <p>Email sent successfully!</p>
                </body>
              </html>";
    } else {
        echo "Failed to send the email.";
    }
} else {
    // Handle the case where the form is not submitted
    echo "Invalid request. Please submit the form.";
}
?>
