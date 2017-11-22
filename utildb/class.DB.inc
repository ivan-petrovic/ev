<?php

/**
 * MySQLi database; only one connection is allowed. 
 */
class DB {

   private $_connection;
   // Store the single instance.
   private static $_instance;

   /**
    * Get an instance of the Database.
    * @return Database 
    */
   public static function getInstance() {
      if (!self::$_instance) {
         self::$_instance = new self();
      }
      return self::$_instance;
   }

   /**
    * Constructor.
    */
   private function __construct() {
       $url = parse_url(getenv("CLEARDB_DATABASE_URL"));

        $server = $url["host"];
        $username = $url["user"];
        $password = $url["pass"];
        $db = substr($url["path"], 1);

        $this->_connection = new mysqli($server, $username, $password, $db);
        /*
	  $host = "ec2-54-75-225-143.eu-west-1.compute.amazonaws.com"; // localhost
	  $port = 5432;
	  $dbname = "d57m7p772t3f36";	// ev
	  $username = "lxtqwypoccnksi";	// root
	  $password = "b583d898643251002ea9e029a6a8b82ddb0588489ea858119ddb9c0e625827f5"; // ivan
      
	  $this->_connection = new mysqli($host, $username, $password, $dbname);
         */
      // Error handling.
      if (mysqli_connect_error()) {
	echo "GRESKA";
        trigger_error('Failed to connect to MySQL: ' . mysqli_connect_error(), E_USER_ERROR);
      } else {
          echo "POVEZAN: " . $server . "---" . $username . "---" . $password . "---" . $db;
      }
   }

   /**
    * Empty clone magic method to prevent duplication. 
    */
   private function __clone() {
   }

   /**
    * Get the mysqli connection. 
    */
   public function getConnection() {
      return $this->_connection;
   }
}
