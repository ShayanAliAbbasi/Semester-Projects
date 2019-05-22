<head>
    <link rel="shortcut icon" href="../assets/logo.png">
    <title>Logging Out </title>
</head>

<?php 
    session_start();

    session_unset();

    session_destroy();

    header("Refresh: 2, url= ../login.php?logout=success");
?>