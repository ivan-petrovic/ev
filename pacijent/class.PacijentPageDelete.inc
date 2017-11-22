<?php

require_once 'class.PacijentDB.inc';
require_once 'class.PacijentPage.inc';

class PacijentDelete extends PacijentPage implements RenderHTML {
   function renderHTML() {
      $this->openSection();
      $this->sectionHeader("Брисање пацијента");
      $this->closeSection();
   }

   public function execute() {
      PacijentDB::delete($this->pid);
      $adr  = "Location: http://localhost/ev/pacijent.php?opID=" . PacijentPageDispatcher::LIST_PACIJENT;
      header($adr);
      exit;
   }
}

class PacijentActivate extends PacijentPage implements RenderHTML {
   function renderHTML() {
      $this->openSection();
      $this->sectionHeader("Активирање пацијента");
      $this->closeSection();
   }

   public function execute() {
      PacijentDB::activate($this->pid);
      $adr  = "Location: http://localhost/ev/pacijent.php?opID=" . PacijentPageDispatcher::LIST_PACIJENT;
      header($adr);
      exit;
   }
}
