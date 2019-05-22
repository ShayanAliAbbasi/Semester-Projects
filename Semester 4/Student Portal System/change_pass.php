<?php require_once "scripts/header.php" ?>

<?php

    $msg = "";
    $disp_msg = "none";
    $pw_val = "";
    $pw_r_val = "";

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    { 
        $pw_val = test_input($_POST['new_pw']);
        $pw_r_val = test_input($_POST['new_pw_r']);

        if ($pw_val != $pw_r_val)
        {
            $disp_msg = "inherit";
            $msg = "Passwords do not match. Please try again!";
        }
        else if (strlen($pw_val) < 8) {
            $disp_msg = "inherit";
            $msg = "Password must be 8 characters long and must not have leading spaces";
        }
        else
        {
            $quer = "UPDATE Student_Login_Details SET [password] = ? WHERE roll_no = ?;";
            
            $params = array($pw_val, $_SESSION['id']);
            $res = sqlsrv_query($conn, $quer, $params); 

            if (!$res) {
                echo "Could not query the database.\n";  
                die (print_r(sqlsrv_errors(), true));
            }

            $disp_msg = "inherit";
            $msg = "Your password was changed successfully!";
        }
    }
?>

<div class="plac_centered">
    <span class="head_main"> Change Password </span>
    <span class="head_sub"> Change your portal's password to a stronger one to keep your account secure </span>
</div>


<div class="bordered margined_top">

    <form class="padded" id="ch_pw" action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="post">

        <label class="head_main_2" for="new_pw">Enter your new password</label>
        <input class="text_input" type="password" name="new_pw" value="<?=$pw_val?>" spellcheck="false" required maxlength="100" autofocus>
        <label class="margined_top head_main_2" for="new_pw_r">Confirm your new password</label>
        <input class="text_input" type="password" name="new_pw_r" value="<?=$pw_r_val?>" spellcheck="false" required maxlength="100">

    </form>

    <input class="button_bottom margined_top padded" form="ch_pw" type="submit">

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/".(preg_match("/(match)|(long)/", $msg) ? "error": "success").".svg" ?> width=12 height=12 style="display: inline">
        <p class=<?= preg_match("/(match)|(long)/", $msg) ? "error":"success"?>> <?= $msg ?> </p>
    </div>
</div>

<?php require_once "scripts/footer.php" ?>