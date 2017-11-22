<?php

require_once 'class.PosetaDB.inc';
require_once 'class.PosetaPage.inc';

class PosetaDetail extends PosetaPage implements RenderHTML {

   protected $poseta;
   
   /*
    * Konstruktor.
    */
   public function __construct($op, $posid, $vid, $pid, $indent) {
      parent::__construct($op, $posid, $vid, $pid, $indent);
      // echo $this->posid; exit();
      $this->poseta = PosetaDB::load($this->posid);
   }
   
   function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Преглед посета");
      $this->sectionContent();

      $this->closeSection();
   }
   
   function sectionContent() {
      echo PosetaRender::display($this->poseta, 5);
      echo $this->backToListButton();
      echo $this->updateButton();
   }
}

class PosetaRender extends CommonPage {

   /**
    * Funkcija za prikaz Posete u HTML-u.
    * @param Poseta - poseta koji se prikazuje
    * @param integer indent - indentacija u ispisu
    * @return string
    */
   public static function display(Poseta $poseta, $indent) {
      $output = self::openTable("detalji", $indent);
      
      $nizel = self::displayElements();
      $cnt = count($nizel);
      for($i = 0; $i < $cnt; $i += 2) {
         $output .= self::makeRow($poseta, $nizel[$i], $nizel[$i+1], $indent+4);
      }
      $output .= self::closeTable($indent);
      
      return $output;
   }

   protected static function displayElements() {
      return array(
          'id', 'Шифра посете',
          'volonter', 'Волонтер',
          'pacijent', 'Пацијент',
          'brojSati', 'Трајање [сати]',
          'datumPosete', 'Датум посете (гггг-мм-дд)'
      );
   }

   protected static function specialElements() {
      return array(
          'volonter' => 'makeVolonterLink',
          'pacijent' => 'makePacijentLink'
      );
   }

//   protected static function specialElements() {
//      return array(
//          'volonter' => 'getVolonterString',
//          'pacijent' => 'getPacijentString'
//      );
//   }

   protected static function makeRow(Poseta $poseta, $el, $label, $indent) {
      $output  = str_repeat("\t", $indent);
      
      $specel = self::specialElements();
      if( array_key_exists($el, $specel) ) {
         $output .= "<tr><th>{$label}</th><td>" . self::$specel[$el]($poseta) . "</td></tr>\n";
      } else {
         $output .= "<tr><th>{$label}</th><td>" . $poseta->getValue($el) . "</td></tr>\n";
      }

      return $output;
   }

   /**
    * Funkcija za prikaz imena volontera.
    * @return string
    */
   protected static function getVolonterString(Poseta $poseta) {
      return VolonterFormElement::getName($poseta->getValue('volonterID'));
   }

   protected static function makeVolonterLink(Poseta $poseta) {
      $id = $poseta->getValue('volonterID');
      // $ref = "volonter.php?opID=" . VolonterPageDispatcher::DETAILS_VOLONTER . "&volonterID=" . $id;
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&volonterID=" . $id;
      $ime = VolonterFormElement::getName($id);
      return self::makeLink1($ref, $ime);
   }

   /**
    * Funkcija za prikaz imena pacijenta.
    * @return string
    */
   public static function getPacijentString(Poseta $poseta) {
      return PacijentFormElement::getName($poseta->getValue('pacijentID'));
   }

   protected static function makePacijentLink(Poseta $poseta) {
      $id = $poseta->getValue('pacijentID');
      // $ref = "pacijent.php?opID=" . PacijentPageDispatcher::DETAILS_PACIJENT . "&pacijentID=" . $id;
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&pacijentID=" . $id;
      $ime = PacijentFormElement::getName($id);
      return self::makeLink1($ref, $ime);
   }
   
   protected function makeLink1($ref, $label) {
      $output  = str_repeat("\t", self::$indent+4);
      $output .=  "<a href=\"{$ref}\">{$label}</a>";
      return $output;
   }
}
