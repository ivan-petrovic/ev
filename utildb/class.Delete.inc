<?php

require_once 'class.Query.inc';

/**
 * Klasa za brisanje rekorda u mysql bazi.
 */
class Delete extends Query {
   private $where;
   private $condition;   
   private $params;

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
         trigger_error("Delete::condition called with no array argument.");
      }
   }
   
   protected function makeQuery() {
      // 'DELETE FROM customers WHERE id > ?';
      $query  = $this->makeWherePart();
      $query .= $this->makeConditionPart();
      return $query;
   }
   
   private function makeWherePart() {
      $query  = "\nDELETE FROM " . $this->where . " ";
      return $query;
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
         trigger_error('Delete::prepare - Wrong SQL: ' . $query . ' Error: ' . $db->error, E_USER_ERROR);
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
