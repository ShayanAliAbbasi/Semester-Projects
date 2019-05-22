<?php require_once "scripts/header.php" ?>

<?php

    $msg = "";
    $disp_msg = "none";
    $showPic = true;
    $name_first_letter = "";

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $file = $_FILES['new_im'];
        $file_name = $file['name'];
        $file_tmp_loc = $file['tmp_name'];
        
        $tokens = explode('.', $file_name);
        $exten = strtolower(end($tokens));

        $allowed_extension = 'png';

        if ($exten != $allowed_extension)
        {
            $msg = "Only png files are allowed";
            $disp_msg = "inherit";
        }
        else
        {
            $file_new_loc = "profile_pictures/".$_SESSION['id'].".".$exten;
            
            move_uploaded_file($file_tmp_loc, $file_new_loc);

            $quer = "UPDATE Students SET has_image = ? WHERE roll_no = ?;";
            
            $params = array(1, $_SESSION['id']);

            $res = sqlsrv_query($conn, $quer, $params);

            if (!$res)
            {
                echo "Unable to query the database.\n";
                die(print_r(sqlsrv_errors(), true));
            }
            
            $msg = "Your image was changed successfuly!";
            $disp_msg = "inherit";
        }
    }

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
    
    else {

        $showPic = false;

        $quer = "UPDATE Students SET has_image = ? WHERE roll_no = ?;";
            
        $params = array(0, $_SESSION['id']);

        $res = sqlsrv_query($conn, $quer, $params);
    }
?>


<div class="plac_centered">
    <span class="head_main"> Change Picture </span>
    <span class="head_sub"> Change your profile picture to a more recent one, to avoid any identification issues </span>
</div>

<div class="bordered margined_top">

    <div style="width: 78%; box-sizing: border-box; display: inline-block;" >
        <form class="padded" id="ch_im" action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="post" enctype="multipart/form-data">

            <label class="head_main_2" for="new_im">Choose your new picture</label>
            
            <div class="margined_top"></div>

            <input type="file" name="new_im" value="choose" required>

            <input class="input_button" type="reset" value="Reset">
            
        </form>
    </div>

    <div class="img_placeholder">
    
    <?php if ($showPic): ?>
        <img class="pic_b" src="profile_pictures/<?=$_SESSION['id']?>.png">
    <?php else: ?>
        <span class="no_pic_b"> <?= $name_first_letter ?> </span>
    <?php endif; ?>

    </div>

    <input class="button_bottom padded" form="ch_im" type="submit">

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/".(preg_match("/allowed/", $msg) ? "error": "success").".svg" ?> width=12 height=12 style="display: inline">
        <p class=<?= preg_match("/allowed/", $msg) ? "error":"success"?>> <?= $msg ?> </p>
    </div>
</div>

<?php require_once "scripts/footer.php" ?>