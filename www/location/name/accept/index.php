<?php
// Check if the request ID is present in the URL
if (isset($_GET['id'])) {
    $requestId = $_GET['id'];

    // Perform actions to handle the acceptance
    // For demonstration purposes, echo a success message
    echo "Movement request with ID $requestId accepted successfully.";
} else {
    // Handle the case where the request ID is not provided
    echo "Invalid request. Please provide a valid request ID.";
}
?>
