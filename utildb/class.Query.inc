<?php

require_once 'class.DB.inc';

/**
 * Klasa koja obuhvata zajednicke funkcije
 * za izvedene klase Select, Insert, Update i Delete
 */
abstract class Query {
   abstract protected function makeQuery();
   abstract protected function runQuery($db, $query);
   
   public function execute() {
      $db = DB::getInstance()->getConnection();
      $query  = $this->makeQuery();
      $result = $this->runQuery($db, $query);
      return $result;
   }

   public function __toString() {
      return $this->makeQuery();
   }
   
   protected function determineType($value) {
      $type = gettype($value); $abbr = "s";
      switch ($type) {
         case "integer":
            $abbr = "i"; break;
         case "double":
            $abbr = "d"; break;
         case "blob":
            $abbr = "b"; break;
      }
      return $abbr;
   }
   
   protected function getTypeString($params) {
      $typestr = "";
      for($i = 0; $i < count($params); ++$i) {
         $typestr .= $this->determineType($params[$i]);
      }
      return $typestr;
   }
}
