<?php

require_once 'class.Query.inc';
// http://www.pontikis.net/blog/how-to-use-php-improved-mysqli-extension-and-why-you-should
// http://codular.com/php-mysqli

/**
 * Klasa za ucitavanje rekorda iz mysql baze.
 */
class Select extends Query {
   private $what;
   private $from;
   private $condition;
   private $params;

   public function what($fields = null) {
      $this->what = $fields;
   }
   
   public function from($tables) {
      $this->from = $tables;
   }

   public function condition($cond, $parameters = array()) {
      $this->condition = $cond;
      if( is_array($parameters) ) {
         $this->params = $parameters;
      } else {
         trigger_error("Select::condition called with no array argument.");
      }
   }
  
   protected function makeQuery() {
      $query  = $this->makeWhatPart();
      $query .= $this->makeFromPart();
      $query .= $this->makeConditionPart();
      // echo $query; exit();
      return $query;
   }

   private function makeWhatPart() {
      if(is_null($this->what) ) { return "SELECT * "; }
      
      if( is_array($this->what) ) {
         $query = "SELECT ";
         foreach ($this->what as $field) {
            $query .= $field . ", ";
         }
         return substr_replace($query ," ",-2);
      } else {
         return "SELECT " . $this->what . " ";
      }
   }
   
   private function makeFromPart() {
      return "\nFROM " . $this->from . " ";
   }

   private function makeConditionPart() {
      $query = "";
      if( !empty($this->condition) ) {
         $query .= !empty($this->params)? "\nWHERE " : "";
         $query .= $this->condition;
         $query .= " ";
      }
      return $query;
   }

   protected function runQuery($db, $query) {
      if(empty($this->params)) {
         if(!$result = $db->query($query)) {
            trigger_error('There was an error running the query [' . $db->error . ']');
         }
      } else {
         $result = $this->queryWithParameters($db, $query);
      }
      return $result;
   }
   
   private function queryWithParameters($db, $query) {
      $args[] = $this->getTypeString($this->params);
      for($i = 0; $i < count($this->params); ++$i) {
         $args[] = &$this->params[$i];
      }
      $stmt = $db->prepare($query);
      // var_dump($args);
      call_user_func_array(array($stmt, 'bind_param'), $args);
      $stmt->execute();
      return $stmt->get_result();
   }
}
