<?php

require_once 'class.PosetaDB.inc';
require_once 'class.PosetaPage.inc';
require_once 'util/class.Validator.inc';

class PosetaUpdate extends PosetaPage implements RenderHTML {
   // Message generated after processing form;
   protected $message = "";
   
   public function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Измена посете");
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
      $poseta = PosetaDB::load($this->posid);
      echo FormMaker::make($poseta, "poseta.php?opID=" . $this->op, "Упис", self::$indent+2);
      echo $this->backToListButton();
   }

   protected function processForm() {
      $poseta = new Poseta();
      $poseta->setData($_POST);

      $v = new Validator;
      $v->validate($poseta);

      if($v->is_valid()) {
         $this->save($poseta);
      } else {
         $this->message .= FormMaker::printErrors($v->getErrors(), self::$indent + 2);
         $this->message .= FormMaker::make($poseta, "poseta.php?opID=" . $this->op, "Упис", self::$indent + 2);
      }
   }

   protected function save(Poseta $poseta) {
      $posid = $poseta->getValue('id');
      PosetaDB::update($poseta);
      // $adr  = "Location: http://localhost/ev/poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA;
      $adr  = "Location: http://localhost/ev/poseta.php?opID=" . PosetaPageDispatcher::DETAILS_POSETA;
      $adr .= "&posetaID=" . $posid;
      header($adr);
      exit;
   }
}
