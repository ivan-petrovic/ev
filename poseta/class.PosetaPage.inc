<?php

require_once 'page/class.PageUtil.inc';
require_once 'util/class.FormMaker.inc';

class PosetaPage extends CommonPage {
   // Sifra operacije za stranu, prosledjuje je page dipecer
   protected $op;
   // Sifra posete, tamo gde ima smisla inace 0
   protected $posid;
   // Sifra volontera ili 0
   protected $vid;
   // Sifra pacijenta ili 0
   protected $pid;

   /*
    * Konstruktor.
    */
   public function __construct($op, $posid, $vid, $pid, $indent) {
      $this->op = $op;
      $this->posid = $posid;
      $this->vid = $vid;
      $this->pid = $pid;
      self::$indent = $indent;
   }

   protected function backToListButton() {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA;
      return $this->button($ref, "Листа посета");
   }

   protected function newButton() {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::NEW_POSETA;
      return $this->button($ref, "Нова");
   }

   protected function updateButton() {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::UPDATE_POSETA . "&posetaID=" . $this->posid;
      return $this->button($ref, "Измени");
   }

   protected function deleteButton() {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::DELETE_POSETA . "&posetaID=" . $this->posid;
      return $this->button($ref, "Обриши");      
   }
   
   public function execute() {
      return;
   }
}
