<?php session_start() ?>
<?php require_once "scripts/connection.php" ?>

<!DOCTYPE html>

<html lang="en">

<head>

    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">

    <title>Login | Student Portal</title>

    <link href="assets/logo.png" rel="shortcut icon">
    <link href="styles/login.css" rel="stylesheet">

</head>

<body>

    <?php

    if (isset($_SESSION['id'])) { sleep(2); header("Location: home.php"); }

    $roll_no = $password = "";
    $out_col = "";
    $err_dis = "none";
    $tool_col = "";
    $rn_val = "";
    $succ_dis = "none";
    $login_success = false;

    if ($_SERVER["REQUEST_METHOD"] == "POST") {

        $rn_val = $rn = test_input($_POST["rn"]);
        $pw = test_input($_POST["pw"]);

        $quer = "SELECT * FROM Student_Login_Details WHERE (roll_no = ? AND [password] = ?); ";

        $params = array($rn, $pw);

        $res = sqlsrv_query($conn, $quer, $params);

        if ($res === false) {
            echo "Error in statement execution.\n";
            die(print_r(sqlsrv_errors(), true));
        }

        if ($row = sqlsrv_fetch_array($res)) {
            $_SESSION['id'] = $rn;
            $out_col = "rgb(162, 0, 255)";
            $err_dis = "none";
            $tool_col = "#118b06;";
            $succ_dis = "inline-block";
            $login_success = true;
            
        } else {
            $out_col = "#d93025";
            $err_dis = "inline-block";
            $tool_col = "#d93025";
            $succ_dis = "none";
            $login_success = false;
            $count = 0;
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

        <div>
            <img src="assets/logo.png" width=100 height=50 alt="logo">
            <h2 class="heading_main" id="portal">Student Portal</h2>
        </div>

        <h2 class="heading_main">Log In</h2>
        <h3 class="heading_sub">With Your Portal Account</h3>

        <form action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="POST">

            <div id="text_input_div">
                <span class="input_tooltip" id="tt1" style="color: <?= $tool_col ?> ">Enter Academy Provided Roll Number</span>
                <input style="outline-color: <?= $out_col ?>; border-color: <?= $out_col ?>" class="input_text" name="rn" title="Enter Complete Roll Number Provided By Academy" type="text" placeholder="Enter Academy Provided Roll Number" maxlength="20" autofocus spellcheck="false" required onfocus="changeDisplay(document.getElementById('tt1'), 'inline');" onblur="changeDisplay(document.getElementById('tt1'), 'none');" >
                <span class="input_tooltip" id="tt2" style="color: <?= $tool_col ?> ">Enter Password </span>
                <input style="outline-color: <?= $out_col ?>; border-color: <?= $out_col ?>" class="input_text" name="pw" title="Enter Your Password Provided By Academy" type="password" placeholder="Enter Password" maxlength="100" required onfocus="changeDisplay(document.getElementById('tt2'), 'inline');" onblur="changeDisplay(document.getElementById('tt2'), 'none');">
            </div>

            <div class="msg" style="display: <?= $err_dis ?>">
                <img src="assets/error.svg" width=12 height=12 style="display: inline">
                <p class="error">Roll Number or Password is incorrect. Please try again!</p>
            </div>

            <div class="msg" style="display: <?= $succ_dis ?>">
                <img src="assets/success.svg" width=12 height=12 style="display: inline">
                <p class="success">Login Successful! Please wait ...</p>
            </div>

            <a class="link" href="forgot_password.php" title="Reset Forgotten Password">Forgot Password?</a>

            <div id="button_input_div">
                <input class="input_button" id="input_button_left" title="Press To Proceed" type="submit" value="Proceed" <?= ($login_success) ? "disabled" : "enabled" ?> >
                <input class="input_button" id="input_button_right" title="Press To Reset Input" type="reset" value="Reset">
            </div>

            <p class="info">Having trouble? Contact <span class="link" style="width:auto">ERP</span> if you are having any issues.</p>
        </form>
    </div>

</body>

<?php if ($login_success) { header("Refresh: 3; url= home.php"); } ?>

<script>
    let changeDisplay = function(element, displayType) {
        element.style.display = displayType;
    }
</script>

</html>