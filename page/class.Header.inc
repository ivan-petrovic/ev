<?php

require_once 'class.PageUtil.inc';

class Header implements RenderHTML {
   // Dodatni CSS file koji treba da se ukljuci u head element.
   protected $cssfile;

   /*
    * Konstruktor.
    */
   public function __construct($cssfile = null) {
      $this->cssfile = $cssfile;
   }
   
   /**
    * Prikaz zaglavlja stranice.
    */
   public function renderHTML() {
      $this->htmlHead();
      $this->bodyHeader();
   }

   /**
    * Ispis head elementa stranice. Nema parametara, sve je fiksno.
    */
   protected function htmlHead() {
      echo "<!DOCTYPE html>\n";
      echo "<html>\n";
      echo str_repeat("\t",1) . "<head>\n";
      echo str_repeat("\t",2) . "<title>Евиденција волонтера</title>\n";
      echo str_repeat("\t",2) . "<meta charset=\"UTF-8\">\n";
      echo str_repeat("\t",2) . "<link rel=\"stylesheet\" href=\"css/style.css\">\n";
      if( !is_null($this->cssfile) ) {
         echo str_repeat("\t",2) . "<link rel=\"stylesheet\" href=\"css/{$this->cssfile}\">\n";
      }
      echo str_repeat("\t",1) . "</head>\n";
   }

   /**
    * Ispis pocetka body elementa stranice.
    */
   protected function bodyHeader() {
      echo str_repeat("\t",1) . "<body>\n";
      echo str_repeat("\t",2) . "<div id=\"page\">\n";
      echo str_repeat("\t",3) . "<header>\n";
      echo str_repeat("\t",4) . "<h1>Евиденција волонтера</h1>\n";
      echo str_repeat("\t",3) . "</header>\n";
   }
}
