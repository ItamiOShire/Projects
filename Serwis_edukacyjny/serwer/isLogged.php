<?php

    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL &~ E_NOTICE &~ E_DEPRECATED);

    require '../vendor/autoload.php';
    include 'mongo.php';

    $db = new db();

    if($flag = $db->isLogged()) {
        echo "1";
    }
    else {
        echo "0";
    }

?>