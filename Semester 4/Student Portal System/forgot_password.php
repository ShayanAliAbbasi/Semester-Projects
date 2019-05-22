<?php session_start(); ?>
<?php require_once "scripts/connection.php" ?>

<!DOCTYPE html>

<html lang="en">

<head>

    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">

    <title>Forgot Password | Student Portal</title>

    <link href="assets/logo.png" rel="shortcut icon">
    <link href="styles/login.css" rel="stylesheet">

</head>

<body>

    <?php

    if (isset($_SESSION['id'])) { sleep(2); header("Location: home.php"); }

    $email = "";
    $out_col = "";
    $err_dis = "none";
    $tool_col = "";
    $succ_dis = "none";
    $sub_success = false;

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $email = test_input($_POST["em"]);

        $quer = "SELECT roll_no, email_address FROM Student_Contact_Details WHERE email_address = ?; ";

        $params = array($email);

        $res = sqlsrv_query($conn, $quer, $params);

        if ($res === false) {
            echo "Error in statement execution.\n";
            die(print_r(sqlsrv_errors(), true));
        }

        if ($row = sqlsrv_fetch_array($res)) {
            $quer = "SELECT [password] FROM Student_Login_Details WHERE roll_no = ?; ";

            $params = array($row['roll_no']);

            $res = sqlsrv_query($conn, $quer, $params);

            if ($res === false) {
                echo "Error in statement excecution.\n";
                die(print_r(sqlsrv_errors(), true));
            }

            $row = sqlsrv_fetch_array($res);

            $sub = "Password Reset | Student Portal";
            $to = $email;
            $msg = "Your Student Portal Password is: " . $row['password'];
            $headers = "From: student_portal@our_domain.com" . "\r\n";

            // Following line needs a mail server running on machine
            #  mail($to, $sub, $msg, $headers) === false);

            $out_col = "rgb(162, 0, 255)";
            $err_dis = "none";
            $succ_dis = "inline-block";
            $tool_col = "#118b06";
            $sub_success = true;
        } else {
            $out_col = "#d93025";
            $err_dis = "inline-block";
            $tool_col = "#d93025";
            $succ_dis = "none";
            $sub_success = false;
        }

        sqlsrv_free_stmt($res);
    }

    function test_input($data)
    {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }

    ?>

    <div id="main_login">

        <div id="">
            <img src="assets/logo.png" width=100 height=50 alt="logo">
            <h2 class="heading_main" id="portal">Student Portal</h2>
        </div>

        <h2 class="heading_main">Recover Password</h2>
        <h3 class="heading_sub">Using Your Email Address</h3>

        <form action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="POST">

            <div id="text_input_div">
                <span class="input_tooltip" id="tt1" style="color: <?= $tool_col ?> ">Enter Your Personal Email Address</span>
                <input style="outline-color: <?= $out_col ?>; border-color: <?= $out_col ?>" class="input_text" name="em" title="Enter Your Personal Email Address Associated With Your Account" type="email" spellcheck="false" placeholder="Enter Your Personal Email Address" maxlength="100" autofocus required onfocus="changeDisplay(document.getElementById('tt1'), 'inline');" onblur="changeDisplay(document.getElementById('tt1'), 'none');">
            </div>

            <div class="msg" style="display: <?= $err_dis ?>">
                <img src="assets/error.svg" width=12 height=12 style="display: inline">
                <p class="error">Email does not exists in our record. Please try again!</p>
            </div>

            <div class="msg" style="display: <?= $succ_dis ?>">
                <img src="assets/success.svg" width=12 height=12 style="display: inline">
                <p class="success">Your password has been sent. Check your mail!</p>
            </div>


            <a class="link" href="login.php" title="Reset Forgotten Password">Back To Log In?</a>

            <div id="button_input_div">
                <input class="input_button" id="input_button_left" title="Press To Proceed" type="submit" value="Proceed" <?= ($sub_success) ? "disabled" : "enabled" ?> >
                <input class="input_button" id="input_button_right" title="Press To Reset Input" type="reset" value="Reset">
            </div>

            <p class="info">Having trouble? Contact <span class="link" style="width:auto">ERP</span> if you are having any issues.</p>

        </form>

    </div>

</body>

<?php if ($sub_success) { header("Refresh: 3; url= login.php"); } ?>

<script>
    let changeDisplay = function(element, displayType) {
        element.style.display = displayType;
    }
</script>

</html>