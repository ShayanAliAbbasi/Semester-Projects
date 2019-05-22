<?php require_once "scripts/header.php" ?>

<?php

    $msg = "";
    $disp_msg = "none";

    $em = "";
    $em_r = "";

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $em = test_input($_POST['new_em']);
        $em_r = test_input($_POST['new_em_r']);

        if ( $em != $em_r)
        {
            $disp_msg = "inherit";
            $msg = "Emails do not match. Please try again!";
        }
        else
        {
            $quer = "SELECT email_address FROM Student_Contact_Details WHERE email_address = ?; ";

            $params = array($em);
            
            $res = sqlsrv_query($conn, $quer, $params);

            if (!$res) {
                echo "Could not query the database.\n";  
                die (print_r(sqlsrv_errors(), true));
            }

            if ($row = sqlsrv_fetch_array($res)) {
                $disp_msg = "inherit";
                $msg = "Email already exists. Please choose a different email.";
            }

            else {
                $quer = "UPDATE Student_Contact_Details SET email_address = ? WHERE roll_no = ?;";

                array_push($params, $_SESSION['id']);

                $res = sqlsrv_query($conn, $quer, $params);

                if (!$res) {
                    echo "Could not query the database.\n";  
                    die (print_r(sqlsrv_errors(), true));
                }

                $disp_msg = "inherit";
                $msg = "Your email was changed successfully!";
            }
        }
    }
?>


<div class="plac_centered">
    <span class="head_main"> Change Email </span>
    <span class="head_sub"> Change your email where important notices and forgotten password will be send </span>
</div>


<div class="bordered margined_top">

    <form class="padded" id="ch_em" action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="post">

        <label class="head_main_2" for="new_em">Enter your new email</label>
        <input class="text_input" type="email" name="new_em" value="<?=$em?>" spellcheck="false" required autofocus>
        <label class="margined_top head_main_2" for="new_em_r">Confirm your new email</label>
        <input class="text_input" type="email" name="new_em_r" value="<?=$em_r?>" spellcheck="false" required>

    </form>

    <input class="button_bottom margined_top padded" form="ch_em" type="submit">

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/".(preg_match("/(match)|(exist)/", $msg) ? "error": "success").".svg" ?> width=12 height=12 style="display: inline">
        <p class=<?= preg_match("/(match)|(exist)/", $msg) ? "error":"success"?>> <?= $msg ?> </p>
    </div>
</div>


<?php require_once "scripts/footer.php" ?>