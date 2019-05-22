<?php require_once "scripts/header.php" ?>

<div class="plac_centered">
    <span class="head_main"> Update Personal Information </span>
    <span class="head_sub"> Update your personal information like contact details etc.</span>
</div>

<?php

    $msg = "";
    $disp_msg = "none";
    $add_val = "";
    $phn_val = "";
    $lnd_val = "";
    $changes_made = false;

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    { 
        $add_val = test_input($_POST['new_add']);
        $phn_val = test_input($_POST['new_phn']);
        $lnd_val = test_input($_POST['new_lnd']);

        if ($add_val)
        {
            $quer = "UPDATE Student_Contact_Details SET postal_address = ? WHERE roll_no = ?;";
            
            $params = array($add_val, $_SESSION['id']);
            $res = sqlsrv_query($conn, $quer, $params); 

            if (!$res) {
                echo "Could not query the database.\n";  
                die (print_r(sqlsrv_errors(), true));
            }

            $changes_made = true;
        }

        if ($phn_val)
        {
            $quer = "UPDATE Student_Contact_Details SET phone_num1 = ? WHERE roll_no = ?;";
            
            $params = array($phn_val, $_SESSION['id']);
            $res = sqlsrv_query($conn, $quer, $params); 

            if (!$res) {
                echo "Could not query the database.\n";  
                die (print_r(sqlsrv_errors(), true));
            }

            $changes_made = true;
        }

        if ($lnd_val)
        {
            $quer = "UPDATE Student_Contact_Details SET phone_num2 = ? WHERE roll_no = ?;";
            
            $params = array($lnd_val, $_SESSION['id']);
            $res = sqlsrv_query($conn, $quer, $params); 

            if (!$res) {
                echo "Could not query the database.\n";  
                die (print_r(sqlsrv_errors(), true));
            }
            
            $changes_made = true;
        }

        if ($changes_made)
        {
            $disp_msg = "inherit";
            $msg = "Required Changes were made successfuly!";
        }
        else
        {
            $disp_msg = "inherit";
            $msg = "No changes were made";
        }
    }
?>

<div class="bordered margined_top">

    <div class="padded">
    
    <span class="head_main_2" style="text-align: left">Update Contact Details</span>
    <span class="head_sub_2">Fill in the contact fields you want to update and submit</span>

    <div class="margined_top"></div>

    <form id="ch_pw" action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="post">

    <table>

        <tr>
            <th style="width: 25%;">New Address</th>
            <td style="width: 75%;"> <input class="text_input" placeholder="Enter new address or leave blank" type="text" name="new_add" value="<?=$add_val?>" spellcheck="false" maxlength="100"> </td>
        </tr>
        
        <tr>
            <th style="width: 25%;">New Phone Number </th>
            <td style="width: 75%;"> <input class="text_input" placeholder="Enter new phone number or leave blank" type="text" name="new_phn" value="<?=$phn_val?>" spellcheck="false" maxlength="100"> <td>
        </tr>

        <tr>
            <th style="width: 25%;">New Landline Number</th>
            <td style="width: 75%;"> <input class="text_input" placeholder="Enter new landline number or leave blank" type="text" name="new_lnd" value="<?=$lnd_val?>" spellcheck="false" maxlength="100"> <td>
        </tr>

    </table>
    
    </form>
    
    </div>

    <input class="button_bottom margined_top padded" form="ch_pw" type="submit">

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/".(preg_match("/No/", $msg) ? "error": "success").".svg" ?> width=12 height=12 style="display: inline">
        <p class=<?= preg_match("/No/", $msg) ? "error":"success"?>> <?= $msg ?> </p>
    </div>
</div>

<div class="bordered margined_top padded plac_centered" style="box-sizing:border-box;">

    <span class="head_main_2" style="text-align: left">Others</span>
    <span class="head_sub_2" style="text-align: left"> Update other details like picture, password, email </span>

    <div class="margined_top"></div>

    <div class="card">
        <div class="card_plac_left padded">
            <span class="head_main_2">Change Email</span>
            <span class="head_sub_2">Change your email where important notices and forgotten password will be send.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/email.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="change_email.php">Change Email</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Change Profile Picture</span>
            <span class="head_sub_2">Change your profile picture to a more recent one, to avoid any identification issues.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/picture.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="change_pic.php">Change Profile Pic</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Change Password</span>
            <span class="head_sub_2">Change your portal's password to a stronger one to keep your account secure.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/password.png" width=96 height=96>
        </div>
        <a class="button_bottom padded" href="change_pass.php">Change Password</a>
    </div>


</div>


<?php require_once "scripts/footer.php" ?>