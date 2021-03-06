<?php

require_once 'class.PosetaDB.inc';
require_once 'class.PosetaPage.inc';

class PosetaDelete extends PosetaPage implements RenderHTML {
   function renderHTML() {
      $this->openSection();
      $this->sectionHeader("Брисање посете");
      $this->closeSection();
   }

   public function execute() {
      PosetaDB::delete($this->posid);
      $adr  = "Location: https://vast-spire-24114.herokuapp.com/poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA;
      header($adr);
      exit;
   }
}
