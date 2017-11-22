<?php

require_once 'class.VolonterDB.inc';
require_once 'class.VolonterPage.inc';

class VolonterDetail extends VolonterPage implements RenderHTML {

   protected $volonter;
   
   /*
    * Konstruktor.
    */
   public function __construct($op, $vid, $indent) {
      parent::__construct($op, $vid, $indent);
      $this->volonter = VolonterDB::load($this->vid);
   }
   
   function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Преглед волонтера");
      $this->sectionContent();

      $this->closeSection();
   }
   
   function sectionContent() {
      echo VolonterRender::display($this->volonter, 5);
      echo $this->backToListButton();
      echo $this->updateButton();
      echo $this->posetaButton();
   }
}

class VolonterRender extends CommonPage {

   /**
    * Funkcija za prikaz Volontera u HTML-u.
    * @param Volonter - volonter koji se prikazuje
    * @param integer indent - indentacija u ispisu
    * @return string
    */
   public static function display(Volonter $volonter, $indent) {
      $output = self::openTable("detalji", $indent);
      
      $nizel = self::displayElements();
      $cnt = count($nizel);
      for($i = 0; $i < $cnt; $i += 2) {
         $output .= self::makeRow($volonter, $nizel[$i], $nizel[$i+1], $indent+4);
      }
      $output .= self::closeTable($indent);
      
      return $output;
   }

   protected static function displayElements() {
      return array(
          'id', 'Шифра', 'ime', 'Име', 'prezime', 'Презиме',
          'jmbg', 'ЈМБГ', 'adresa', 'Улица и број', 'mesto', 'Место',
          'opstinaID', 'Општина', 'drzavljanstvo', 'Држављанство',
          'telefon',  'Телефон', 'datumRodjenja', 'Датум рођења',
          'pol', 'Пол', 'tipUgovora', 'Врста уговора',
          'datumPocetka', 'Датум почетка уговора',
          'datumIsteka', 'Датум истека уговора',
          'status', 'Статус', 'opis', 'Напомена'
      );
   }

   protected static function specialElements() {
      return array(
          'status' => 'getStatusString',
          'opstinaID' => 'getOpstinaString',
          'pol' => 'getPolString',
          'tipUgovora' => 'getTipUgovorString',
          'opis' => 'getOpisString'
      );
   }

   protected static function makeRow(Volonter $volonter, $el, $label, $indent) {
      $output  = str_repeat("\t", $indent);
      
      $specel = self::specialElements();
      if( array_key_exists($el, $specel) ) {
         $output .= "<tr><th>{$label}</th><td>" . self::$specel[$el]($volonter) . "</td></tr>\n";
      } else {
         $output .= "<tr><th>{$label}</th><td>" . $volonter->getValue($el) . "</td></tr>\n";
      }

      return $output;
   }

   /**
    * Funkcija za prikaz statusa volontera.
    * @return string
    */
   protected static function getStatusString(Volonter $volonter) {
      return StatusFormElement::getName($volonter->getValue('status'));
   }
   
   /**
    * Funkcija za prikaz opstine volontera.
    * @return string
    */
   public function getOpstinaString(Volonter $volonter) {
      return Municipality::getName($volonter->getValue('opstinaID'));
   }

   /**
    * Funkcija za prikaz pola volontera.
    * @return string
    */
   public function getPolString(Volonter $volonter) {
      return PolFormElement::getName($volonter->getValue('pol'));
   }

   /**
    * Funkcija za prikaz tipa ugovora volontera.
    * @return string
    */
   public function getTipUgovorString(Volonter $volonter) {
      return TipUgovorFormElement::getName($volonter->getValue('tipUgovora'));
   }

   /**
    * Funkcija za prikaz opisa volontera. Vraca CR u ispis.
    * @return string
    */
   public function getOpisString(Volonter $volonter) {
      $opis = $volonter->getValue('opis');
      // mixed str_replace ( mixed $search , mixed $replace , mixed $subject [, int &$count ] )
      return str_replace("&#38;#13;&#38;#10;", "<br/>", $opis);
   }
}
