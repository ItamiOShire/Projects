<?php
  header('Access-Control-Allow-Origin: *');
//require '../vendor/autoload.php' ;
  
class db {
    private $user = "****" ;
    private $pass = "****";
    private $host = "****";
    private $base = "****";
    private $coll = "users";
    private $conn;
    private $dbase;
    private $collection;
  
  
  
    function __construct() {
      
      $this->conn = new MongoDB\Client("mongodb://{$this->user}:{$this->pass}@{$this->host}/{$this->base}");    
      $this->collection = $this->conn->{$this->base}->{$this->coll};
      session_start();
    }

    function login($email,$pass) {
        
        $document = $this->collection->findOne(['email' => $email]);

        if ($document && password_verify($pass, $document['password'])) {
            $_SESSION['email'] = (string)$document['email'];
            setcookie("email", $_SESSION['email'], time() + 3600, "/");

            return true;
        }
    }

    function register($email, $pass) {
      // Check if the email already exists
      $existingDocument = $this->collection->findOne(['email' => $email]);
  
      if ($existingDocument) {
          // Email already exists, return false or handle the situation accordingly
          return false;
      }
  
      // Hash the password
      $hashedPassword = password_hash($pass, PASSWORD_DEFAULT);
  
      // Create the document to be inserted
      $document = [
          'email' => $email,
          'password' => $hashedPassword,
          'speed' => ""
      ];
  
      // Insert the document into the collection
      $result = $this->collection->insertOne($document);
  
      // Check if the insertion was successful
      return $result->getInsertedCount() > 0;
  }
  

    function logout()
    {
        session_destroy();
        setcookie("email", "", time() - 3600, "/");
    }

    function isLogged()
    {
        return isset($_SESSION['email']);
    }

    function save($email,$speed) {

        $update = array( '$set' => array('speed' => $speed));
        $filter = array('email' => $email);

        $res = $this->collection->updateOne($filter,$update);
        $count = $res->getModifiedCount();
        return $count;
    }
  
}
?>
