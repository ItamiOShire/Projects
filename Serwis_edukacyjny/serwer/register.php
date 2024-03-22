<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL &~ E_NOTICE &~ E_DEPRECATED);
    
    require '../vendor/autoload.php';
    include 'mongo.php';

    $db = new db();
    $email=$_REQUEST["email"];
    $pass=$_REQUEST["pass"];

    $flag = $db->register($email,$pass);
    if($flag) {

        echo "Udalo sie zarejestrowac";

    }
    else {
        echo "blad rejestracji - dany email istnieje";
    }
?>