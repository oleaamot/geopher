<?php
// Check if the request ID is present in the URL
if (isset($_GET['id'])) {
    $requestId = $_GET['id'];

    // Perform actions to handle mutual location sharing
    // For demonstration purposes, echo a success message
    echo "Mutual location sharing initiated for request with ID $requestId.";
} else {
    // Handle the case where the request ID is not provided
    echo "Invalid request. Please provide a valid request ID.";
}
?>

