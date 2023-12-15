<?php
// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    // Retrieve the action and request ID from the form
    $action = $_POST["action"] ?? '';
    $requestId = $_POST["request_id"] ?? '';

    // Perform actions based on the user's response
    switch ($action) {
        case 'accept':
            handleAcceptance($requestId);
            break;
        case 'ignore':
            handleIgnore($requestId);
            break;
        case 'negotiate':
            handleNegotiation($requestId);
            break;
        case 'cancel':
            handleCancellation($requestId);
            break;
        default:
            // Handle unknown actions or errors
            echo "Invalid action";
            break;
    }
}

// Function to handle the "Accept" action
function handleAcceptance($requestId) {
    // Perform actions to retrieve and share location
    // For demonstration purposes, echo a success message
    echo "Movement accepted successfully.";
    echo "<a href='https://geopher.com/location/name/submit?inititorEmail=" . $_OST['initiatorEmail'] . "&targetEmail=" . $_POST['targetEmail'] . "&price=" . $_POST['price'] . "&timePeriod=" . $_POST['timePeriod'] . "'>Submit Movement Request to " . $_POST['initatorEmail'] . "</a>";
}

// Function to handle the "Ignore" action
function handleIgnore($requestId) {
    // Perform actions to ignore the location request
    // For demonstration purposes, echo a success message
    echo "Movement request ignored.";
}

// Function to handle the "Negotiate" action
function handleNegotiation($requestId) {
    // Perform actions for negotiation (if needed)
    // For demonstration purposes, echo a success message
    echo "Negotiation initiated.";
}

// Function to handle the "Cancel" action
function handleCancellation($requestId) {
    // Perform actions to cancel the location request
    // For demonstration purposes, echo a success message
    echo "Movement request canceled.";
}
?>
