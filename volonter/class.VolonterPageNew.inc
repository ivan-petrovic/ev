<?php

require_once 'class.VolonterDB.inc';
require_once 'class.VolonterPage.inc';
require_once 'util/class.Validator.inc';

class VolonterNew extends VolonterPage implements RenderHTML {
   // Message generated after processing form;
   protected $message = "";
   
   function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Унос новог волонтера");
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
      $volonter = new Volonter();
      echo FormMaker::make($volonter, "volonter.php?opID=" . $this->op, "Упис", self::$indent+2);
      echo $this->backToListButton();
   }

   function processForm() {
      $volonter = new Volonter();
      $volonter->setData($_POST);

      $v = new Validator;
      $v->validate($volonter);

      if($v->is_valid()) {
         $this->save($volonter);
      } else {
         $this->message .= FormMaker::printErrors($v->getErrors(), self::$indent+2);
         $this->message .= FormMaker::make($volonter, "volonter.php?opID=" . $this->op, "Упис", self::$indent+2);
      }
   }

   protected function save(Volonter $volonter) {
      $rez = VolonterDB::insert($volonter); // return value is array(insert_id, affected_rows)
      $adr  = "Location: http://localhost/ev/volonter.php?opID=" . VolonterPageDispatcher::DETAILS_VOLONTER;
      $adr .= "&volonterID=" . $rez[0];
      header($adr);
      exit;
   }
}
