<?php
// Check if the request ID is present in the URL
if (isset($_GET['id'])) {
    $requestId = $_GET['id'];

    // Perform actions to retrieve and display the finalized location information
    // For demonstration purposes, echo a sample result
    $locationInfo = "pnorvig@google.com is at Mountain View, California, 5223.7 km away from oka@oka.no, available for 15 minutes";

    echo "<html>
            <head>
                <title>Movement Result</title>
            </head>
            <body>
                <h1>Movement Result</h1>
                <p>$locationInfo</p>
            </body>
          </html>";
} else {
    // Handle the case where the request ID is not provided
    echo "Invalid request. Please provide a valid request ID.";
}
?>
