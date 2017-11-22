<?php

require_once 'class.VolonterDB.inc';
require_once 'class.VolonterPage.inc';

class VolonterDelete extends VolonterPage implements RenderHTML {
   function renderHTML() {
      $this->openSection();
      $this->sectionHeader("Брисање волонтера");
      $this->closeSection();
   }

   public function execute() {
      VolonterDB::delete($this->vid);
      $adr  = "Location: http://localhost/ev/volonter.php?opID=" . VolonterPageDispatcher::LIST_VOLONTER;
      header($adr);
      exit;
   }
}

class VolonterActivate extends VolonterPage implements RenderHTML {
   function renderHTML() {
      $this->openSection();
      $this->sectionHeader("Активирање волонтера");
      $this->closeSection();
   }

   public function execute() {
      VolonterDB::activate($this->vid);
      $adr  = "Location: http://localhost/ev/volonter.php?opID=" . VolonterPageDispatcher::LIST_VOLONTER;
      header($adr);
      exit;
   }
}
