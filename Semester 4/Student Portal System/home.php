<?php require_once "scripts/header.php" ?>

<?php

$showPic = true;
$name_first_letter = "";

$quer = "SELECT name FROM Students WHERE roll_no = ?;";
        
$params = array($_SESSION['id']);

$res = sqlsrv_query($conn, $quer, $params);

if (!$res)
{
    echo "Unable to query the database.\n";
    die(print_r(sqlsrv_errors(), true));
}

$arr = sqlsrv_fetch_array($res);

$name = $arr[0];

$name_first_letter = $name[0];

if (file_exists("profile_pictures/".$_SESSION['id'].".png")) $showPic = true;
else $showPic = false;

?>

<div class="plac_centered">
    
    <a href="change_pic.php" title="change picture">
    <?php if ($showPic): ?>
        <img class="pic_s" src="profile_pictures/<?=$_SESSION['id']?>.png" t>
    <?php else: ?>
        <span class="no_pic_s"> <?= $name_first_letter ?> </span>
    <?php endif; ?>
    </a>

    <span class="head_main"> Welcome, <?= $name ?> </span>
    <span class="head_sub"> Explore your student portal, view your current standing at the academy and enroll different courses  </span>
</div>

<div class = "plac_centered margined_top" style="min-width: 875px">

    
    <div class="card">
        <div class="card_plac_left padded">
            <span class="head_main_2">Personal Information</span>
            <span class="head_sub_2">View information about yourself stored in our record, your contact details etc.
        </div>
        <div class="card_plac_right">
            <img src="assets/person.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="personal_info.php">View Personal Info</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Academic Information</span>
            <span class="head_sub_2">View information about your academic performance, grade    , attendence etc.
        </div>
        <div class="card_plac_right">
            <img src="assets/academy.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="academic_info.php">View Acadmic Info</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Financial Information</span>
            <span class="head_sub_2">View information about your financial status, course fee, fines due etc.
        </div>
        <div class="card_plac_right">
            <img src="assets/finance.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="financial_info.php">View Financial Info</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Library Information</span>
            <span class="head_sub_2">View information about library books that were issued to you, due date etc.
        </div>
        <div class="card_plac_right">
            <img src="assets/library.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="library_info.php">View Library Info</a>
    </div>
    

    <div class="plac_centered"><hr style="display:inline-block; border:none; border-bottom: 1px solid rgba(0, 0, 0, 0.15); margin: 40px 0px; width: 80%;"></div>

    <div class="card">
        <div class="card_plac_left padded">
            <span class="head_main_2">Change Email</span>
            <span class="head_sub_2">Change your email where important notices and forgotten password will be send.
        </div>
        <div class="card_plac_right">
            <img src="assets/email.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="change_email.php">Change Email</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Change Password</span>
            <span class="head_sub_2">Change your portal's password to a stronger one to keep your account secure.
        </div>
        <div class="card_plac_right">
            <img src="assets/password.png" width=96 height=96>
        </div>
        <a class="button_bottom padded" href="change_pass.php">Change Password</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Change Profile Picture</span>
            <span class="head_sub_2">Change your profile picture to a more recent one, to avoid any identification issues.
        </div>
        <div class="card_plac_right">
            <img src="assets/picture.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="change_pic.php">Change Profile Pic</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Update Personal Info</span>
            <span class="head_sub_2">Update your personal information stored in our record, like contact details, address etc.
        </div>
        <div class="card_plac_right">
            <img src="assets/edit.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="update_info.php">Update Personal Info</a>
    </div>

    <div class="margined_top"></div>

</div>


<div class="margined_top padded plac_centered">
        <span class="head_sub" style="display:inline-block;">Copyright &copy; </span> 2019-<?= date('y ') ?><span class="head_sub_2" style="display: inline-block;">All Rights Reserved</span>
</div>


<?php require_once "scripts/footer.php" ?>