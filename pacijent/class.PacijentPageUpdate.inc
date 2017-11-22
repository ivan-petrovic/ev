<?php

require_once 'class.PacijentDB.inc';
require_once 'class.PacijentPage.inc';
require_once 'util/class.Validator.inc';

class PacijentUpdate extends PacijentPage implements RenderHTML {
   // Message generated after processing form;
   protected $message = "";
   
   public function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Измена пацијента");
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
      $pacijent = PacijentDB::load($this->pid);
      echo FormMaker::make($pacijent, "pacijent.php?opID=" . $this->op, "Упис", self::$indent+2);
      echo $this->backToListButton();
   }

   protected function processForm() {
      $pacijent = new Pacijent();
      $pacijent->setData($_POST);

      $v = new Validator;
      $v->validate($pacijent);

      if($v->is_valid()) {
         $this->save($pacijent);
      } else {
         $this->message .= FormMaker::printErrors($v->getErrors(), self::$indent + 2);
         $this->message .= FormMaker::make($pacijent, "pacijent.php?opID=" . $this->op, "Упис", self::$indent + 2);
      }
   }

   protected function save(Pacijent $pacijent) {
      $pid = $pacijent->getValue('id');
      PacijentDB::update($pacijent);
      $adr  = "Location: https://vast-spire-24114.herokuapp.com/pacijent.php?opID=" . PacijentPageDispatcher::DETAILS_PACIJENT;
      $adr .= "&pacijentID=" . $pid;
      header($adr);
      exit;
   }
}
