<?php

require_once 'class.PosetaDB.inc';
require_once 'volonter/class.VolonterDB.inc';
require_once 'pacijent/class.PacijentDB.inc';
require_once 'class.PosetaPage.inc';
require_once 'util/class.Validator.inc';

class PosetaNew extends PosetaPage implements RenderHTML {
   // Message generated after processing form;
   protected $message = "";
   
   function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Унос новог пацијента");
      $this->sectionContent();

      $this->closeSection();
   }

   protected function sectionContent() {
      if ($_SERVER['REQUEST_METHOD'] == 'POST') {
         echo $this->message;
         echo $this->backToListButton();
      } else {
         $this->renderForm();
      }
   }

   public function execute() {
      if($_SERVER['REQUEST_METHOD'] == 'POST') {
         $this->processForm();
      }
   }

   function renderForm() {
      $poseta = new Poseta();
      echo FormMaker::make($poseta, "poseta.php?opID=" . $this->op, "Упис", self::$indent+2);
      echo $this->backToListButton();
   }

   function processForm() {
      $poseta = new Poseta();
      $poseta->setData($_POST);

      $v = new Validator;
      $v->validate($poseta);

      if($v->is_valid()) {
         $this->save($poseta);
      } else {
         $this->message .= FormMaker::printErrors($v->getErrors(), self::$indent+2);
         $this->message .= FormMaker::make($poseta, "poseta.php?opID=" . $this->op, "Упис", self::$indent+2);
      }
   }

   protected function save(Poseta $poseta) {
      $rez = PosetaDB::insert($poseta); // return value is array(insert_id, affected_rows)
      $adr  = "Location: https://vast-spire-24114.herokuapp.com/poseta.php?opID=" . PosetaPageDispatcher::DETAILS_POSETA;
      $adr .= "&posetaID=" . $rez[0];
      header($adr);
      exit;
   }
}
