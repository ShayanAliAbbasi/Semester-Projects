<?php require_once "scripts/header.php" ?>

<div class="plac_centered">
    <span class="head_main"> Enroll Courses </span>
    <span class="head_sub"> Enroll into different courses available for you at the academy </span>
</div>


<div class="margined_top bordered">

    <div class="padded">
        <span class="head_main_2">Enroll</span>
        <span class="head_sub_2">Here are all the courses you can enroll </span>
        <div class="margined_top"></div>
    </div>

</div>  


<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/error.svg" ?> width=12 height=12 style="display: inline">
        <p class="error"> No courses are being offered to you right now! </p>
    </div>
</div>

<?php require_once "scripts/footer.php" ?>