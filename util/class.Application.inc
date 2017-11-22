<?php

class Application {
   
   static public function getOp() {
      return filter_input(INPUT_GET, 'opID', FILTER_VALIDATE_INT, array('options' => array('default' => 0)));
   }

   static public function getVolonterID() {
      return filter_input(INPUT_GET, 'volonterID', FILTER_VALIDATE_INT, array('options' => array('default' => 0)));
   }

   static public function getPacijentID() {
      return filter_input(INPUT_GET, 'pacijentID', FILTER_VALIDATE_INT, array('options' => array('default' => 0)));
   }

   static public function getPosetaID() {
      return filter_input(INPUT_GET, 'posetaID', FILTER_VALIDATE_INT, array('options' => array('default' => 0)));
   }
}
