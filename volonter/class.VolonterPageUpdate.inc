<?php

require_once 'class.VolonterDB.inc';
require_once 'class.VolonterPage.inc';
require_once 'util/class.Validator.inc';

class VolonterUpdate extends VolonterPage implements RenderHTML {
   // Message generated after processing form;
   protected $message = "";
   
   public function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Измена волонтера");
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
      if ($_SERVER['REQUEST_METHOD'] == 'POST') {
         $this->processForm();
      }
   }
   
   protected function renderForm() {
      $volonter = VolonterDB::load($this->vid);
      echo FormMaker::make($volonter, "volonter.php?opID=" . $this->op, "Упис", self::$indent+2);
      echo $this->backToListButton();
   }

   protected function processForm() {
      $volonter = new Volonter();
      $volonter->setData($_POST);

      $v = new Validator;
      $v->validate($volonter);

      if($v->is_valid()) {
         $this->save($volonter);
      } else {
         $this->message .= FormMaker::printErrors($v->getErrors(), self::$indent + 2);
         $this->message .= FormMaker::make($volonter, "volonter.php?opID=" . $this->op, "Упис", self::$indent + 2);
      }
   }

   protected function save(Volonter $volonter) {
      $vid = $volonter->getValue('id');
      VolonterDB::update($volonter);
      $adr  = "Location: http://localhost/ev/volonter.php?opID=" . VolonterPageDispatcher::DETAILS_VOLONTER;
      $adr .= "&volonterID=" . $vid;
      header($adr);
      exit;
   }
}
