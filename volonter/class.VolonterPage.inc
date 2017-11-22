<?php

require_once 'page/class.PageUtil.inc';
require_once 'util/class.FormMaker.inc';

class VolonterPage extends CommonPage {
   // Sifra operacije za stranu, prosledjuje je page dipecer
   protected $op;
   // sifra volontera, tamo gde ima smisla inace 0
   protected $vid;

   /*
    * Konstruktor.
    */
   public function __construct($op, $vid, $indent) {
      $this->op = $op;
      $this->vid = $vid;
      self::$indent = $indent;
   }

   protected function backToListButton() {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::LIST_VOLONTER;
      return $this->button($ref, "Листа волонтера");
   }

   protected function newButton() {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::NEW_VOLONTER;
      return $this->button($ref, "Нови");
   }

   protected function updateButton() {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::UPDATE_VOLONTER . "&volonterID=" . $this->vid;
      return $this->button($ref, "Измени");
   }

   protected function deleteButton() {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::DELETE_VOLONTER . "&volonterID=" . $this->vid;
      return $this->button($ref, "Обриши");
   }

   protected function posetaButton() {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&volonterID=" . $this->vid;
      return $this->button($ref, "Посете");
   }

   public function execute() {
      return;
   }
}
