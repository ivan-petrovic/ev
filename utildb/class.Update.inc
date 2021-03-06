<?php

require_once 'class.Query.inc';

/**
 * Klasa za izmenu rekorda u mysql bazi.
 */
class Update extends Query {
   private $what;
   private $where;
   private $condition;   
   private $params;

   public function what($fields = array()) {
      if( is_array($fields) ) {
         $this->what = $fields;
      } else {
         trigger_error("Update::what called with no array argument.");
      }
   }
   
   public function where($table) {
      $this->where = $table;
   }

   public function condition($cond) {
      $this->condition = $cond;
   }
   
   public function values($val = array()) {
      if( is_array($val) ) {
         $this->params = $val;
      } else {
         trigger_error("Update::condition called with no array argument.");
      }
   }
   
   protected function makeQuery() {
      // $sql='UPDATE customers SET firstname = ?, lastname = ? WHERE id > ?';
      $query  = $this->makeWherePart();
      $query .= $this->makeWhatPart();
      $query .= $this->makeConditionPart();
      return $query;
   }
   
   private function makeWherePart() {
      $query  = "\nUPDATE " . $this->where . " ";
      return $query;
   }
   
   private function makeWhatPart() {
      $query = "\nSET ";
      foreach ($this->what as $field) {
         $query .= $field . " = ?, ";
      }
      return substr_replace($query ," ",-2);
   }
   
   private function makeConditionPart() {
      $query = "";
      if( !empty($this->condition) ) {
         $query = "\nWHERE ";
         $query .= $this->condition;
         $query .= " ";
      }
      return $query;
   }

   protected function runQuery($db, $query) {
      $stmt = $this->prepare($db, $query);

      $args = $this->prepareArgs();
      call_user_func_array(array($stmt, 'bind_param'), $args);
      
      $stmt->execute();
      $ret = $stmt->affected_rows;
      $stmt->close();
      return $ret;
   }

   private function prepare($db, $query) {
      $stmt = $db->prepare($query);
      if($stmt === false) {
         trigger_error('Update::prepare - Wrong SQL: ' . $query . ' Error: ' . $db->error, E_USER_ERROR);
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
