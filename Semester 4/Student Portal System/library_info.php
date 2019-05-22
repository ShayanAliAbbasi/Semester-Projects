<?php require_once "scripts/header.php" ?>

<div class="plac_centered">
    <span class="head_main"> Library Information </span>
    <span class="head_sub">  View information about library books that were issued to you, due date etc. </span>
</div>

<div class="margined_top bordered padded">

    <span class="head_main_2">Lent Books Details </span>
    <span class="head_sub_2">Here are details of all books you have lent out from library </span>
    
    <div class="margined_top">
    
    <?php
    
    $msg = "";
    $disp_msg = "none";
    $hasDetails = false;

    $quer = "SELECT * FROM Student_Library_Details WHERE roll_no = ? ORDER BY issue_date DESC;";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }


    echo "<table>";

    echo "<tr> 
          <th style='width:35%'> Book Name </th>
          <th style='width:25%'> Issue Date
          <th style='width:25%'> Due Date </th>          
          <th style='width:10%'> Returned </th>  
         </tr>";

    while($row = sqlsrv_fetch_array($res))
    {
       echo "<tr>";
    
       echo "<td style='width:35%'>" . $row['book_name'] . "</td>";

       echo "<td style='width:20%'>" . $row['issue_date']->format('d/m/Y h:i') . "</td>";

       echo "<td style='width:20%'>" . $row['due_date']->format('d/m/Y h:i') . "</td>";

       echo "<td style='width:20%'>";

       echo  $row['returned'] ? " <img src='assets/success.svg' width=12 height=12> <p class='success'> Yes </p>  " 
                              :  "<img src='assets/error.svg' width=12 height=12> <p class='error'> No </p> " . "</td>";

       echo "</tr>";

       if (!$hasDetails) $hasDetails = true;
    }

    echo "</table>";

    if (!$hasDetails) {
        $disp_msg = "inherit";
        $msg = "No books were issued to you";
    }
    
    ?>

    </div>

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/error.svg" ?> width=12 height=12 style="display: inline">
        <p class="error"> <?= $msg ?> </p>
    </div>
</div>

<?php require_once "scripts/footer.php" ?>
