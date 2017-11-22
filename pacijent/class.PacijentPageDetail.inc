<?php

require_once 'class.PacijentDB.inc';
require_once 'class.PacijentPage.inc';

class PacijentDetail extends PacijentPage implements RenderHTML {

   protected $pacijent;
   
   /*
    * Konstruktor.
    */
   public function __construct($op, $pid, $indent) {
      parent::__construct($op, $pid, $indent);
      $this->pacijent = PacijentDB::load($this->pid);
   }
   
   function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Преглед пацијената");
      $this->sectionContent();

      $this->closeSection();
   }
   
   function sectionContent() {
      echo PacijentRender::display($this->pacijent, 5);
      echo $this->backToListButton();
      echo $this->updateButton();
      echo $this->posetaButton();
   }
}

class PacijentRender extends CommonPage {

   /**
    * Funkcija za prikaz Pacijenta u HTML-u.
    * @param Pacijent - pacijent koji se prikazuje
    * @param integer indent - indentacija u ispisu
    * @return string
    */
   public static function display(Pacijent $pacijent, $indent) {
      $output = self::openTable("detalji", $indent);
      
      $nizel = self::displayElements();
      $cnt = count($nizel);
      for($i = 0; $i < $cnt; $i += 2) {
         $output .= self::makeRow($pacijent, $nizel[$i], $nizel[$i+1], $indent+4);
      }
      $output .= self::closeTable($indent);
      
      return $output;
   }

   protected static function displayElements() {
      return array(
          'id', 'Шифра', 'ime', 'Име', 'prezime', 'Презиме',
          'jmbg', 'ЈМБГ', 'adresa', 'Улица и број', 'mesto', 'Место',
          'opstinaID', 'Општина', 'telefon',  'Телефон', 'pol', 'Пол',
          'datumRodjenja', 'Датум рођења (гггг-мм-дд)',
          'datumSmrti', 'Датум смрти (гггг-мм-дд)',
          'status', 'Статус', 'opis', 'Напомена'
      );
   }

   protected static function specialElements() {
      return array(
          'status' => 'getStatusString',
          'opstinaID' => 'getOpstinaString',
          'pol' => 'getPolString',
          'opis' => 'getOpisString'
      );
   }

   protected static function makeRow(Pacijent $pacijent, $el, $label, $indent) {
      $output  = str_repeat("\t", $indent);
      
      $specel = self::specialElements();
      if( array_key_exists($el, $specel) ) {
         $output .= "<tr><th>{$label}</th><td>" . self::$specel[$el]($pacijent) . "</td></tr>\n";
      } else {
         $output .= "<tr><th>{$label}</th><td>" . $pacijent->getValue($el) . "</td></tr>\n";
      }

      return $output;
   }

   /**
    * Funkcija za prikaz statusa pacijenta.
    * @return string
    */
   protected static function getStatusString(Pacijent $pacijent) {
      return StatusFormElement::getName($pacijent->getValue('status'));
   }
   
   /**
    * Funkcija za prikaz opstine pacijenta.
    * @return string
    */
   public function getOpstinaString(Pacijent $pacijent) {
      return Municipality::getName($pacijent->getValue('opstinaID'));
   }

   /**
    * Funkcija za prikaz pola pacijenta.
    * @return string
    */
   public function getPolString(Pacijent $pacijent) {
      return PolFormElement::getName($pacijent->getValue('pol'));
   }

   /**
    * Funkcija za prikaz opisa pacijenta. Vraca CR u ispis.
    * @return string
    */
   public function getOpisString(Pacijent $pacijent) {
      $opis = $pacijent->getValue('opis');
      // mixed str_replace ( mixed $search , mixed $replace , mixed $subject [, int &$count ] )
      return str_replace("&#38;#13;&#38;#10;", "<br/>", $opis);
   }
}
