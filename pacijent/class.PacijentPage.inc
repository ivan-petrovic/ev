<?php

require_once 'page/class.PageUtil.inc';
require_once 'util/class.FormMaker.inc';

class PacijentPage extends CommonPage {
   // Sifra operacije za stranu, prosledjuje je page dipecer
   protected $op;
   // sifra pacijenta, tamo gde ima smisla inace 0
   protected $pid;

   /*
    * Konstruktor.
    */
   public function __construct($op, $pid, $indent) {
      $this->op = $op;
      $this->pid = $pid;
      self::$indent = $indent;
   }

   protected function backToListButton() {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::LIST_PACIJENT;
      return $this->button($ref, "Листа пацијената");
   }

   protected function newButton() {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::NEW_PACIJENT;
      return $this->button($ref, "Нови");
   }

   protected function updateButton() {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::UPDATE_PACIJENT . "&pacijentID=" . $this->pid;
      return $this->button($ref, "Измени");
   }

   protected function deleteButton() {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::DELETE_PACIJENT . "&pacijentID=" . $this->pid;
      return $this->button($ref, "Обриши");      
   }

   protected function posetaButton() {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&pacijentID=" . $this->pid;
      return $this->button($ref, "Посете");
   }

   public function execute() {
      return;
   }
}
