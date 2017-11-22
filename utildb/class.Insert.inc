<?php

require_once 'class.Query.inc';

/**
 * Klasa za upis rekorda u mysql bazu.
 */
class Insert extends Query {
   private $what;
   private $where;
   private $params;

   public function what($fields = array()) {
      if( is_array($fields) ) {
         $this->what = $fields;
      } else {
         trigger_error("Insert::what called with no array argument.");
      }
   }
   
   public function where($table) {
      $this->where = $table;
   }

   public function values($val = array()) {
      if( is_array($val) ) {
         $this->params = $val;
      } else {
         trigger_error("Insert::condition called with no array argument.");
      }
   }

   protected function makeQuery() {
      $query  = $this->makeWherePart();
      $query .= $this->makeWhatPart();
      $query .= $this->makeValuesPart();
      return $query;
   }
   
   private function makeWherePart() {
      $query  = "\nINSERT INTO " . $this->where . " ";
      return $query;
   }
   
   private function makeWhatPart() {
      // 'INSERT INTO customers (firstname, lastname) VALUES (?,?)';
      $query = "(";
      foreach ($this->what as $field) {
         $query .= $field . ", ";
      }
      return substr_replace($query ,") ",-2);
   }

   private function makeValuesPart() {
      $query = "VALUES (";
      $numValues = count($this->params);
      $query .= str_repeat("?,", $numValues);
      return substr_replace($query ,")",-1);
   }

   protected function runQuery($db, $query) {
      $stmt = $this->prepare($db, $query);

      $args = $this->prepareArgs();
      call_user_func_array(array($stmt, 'bind_param'), $args);
      
      $stmt->execute();
      $ret = array($stmt->insert_id, $stmt->affected_rows);
      $stmt->close();
      return $ret;
   }

   private function prepare($db, $query) {
      $stmt = $db->prepare($query);
      if($stmt === false) {
         trigger_error('Insert::prepare - Wrong SQL: ' . $query . ' Error: ' . $db->error, E_USER_ERROR);
      }
      return $stmt;
   }

   private function prepareArgs() {
      $args[] = $this->getTypeString($this->params);
      for($i = 0; $i < count($this->params); ++$i) {
         $args[] = &$this->params[$i];
      }
      // var_dump($args);
      return $args;
   }
}
