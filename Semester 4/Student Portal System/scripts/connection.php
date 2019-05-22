<?php

    $serverName = "DESKTOP-HOB0G5A";
    $connInfo = array("Database"=>"PortalDB");

    $conn = sqlsrv_connect($serverName, $connInfo);

    if( $conn === false )  
    {  
        echo "Could not connect.\n";  
        die( print_r( sqlsrv_errors(), true));  
    }   
?>