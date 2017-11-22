<?php

require_once 'class.VolonterDB.inc';
require_once 'class.VolonterPage.inc';

class VolonterList extends VolonterPage implements RenderHTML {
   const AKTIVNI_VOLONTERI = 1050;
   const PASIVNI_VOLONTERI = 1060;
   const SVI_VOLONTERI = 1070;
   
   protected $aktivan;
   protected $count = 0;

   /*
    * Konstruktor.
    */
   public function __construct($op, $vid, $indent) {
      parent::__construct($op, $vid, $indent);

      $this->aktivan = self::AKTIVNI_VOLONTERI;
   }

   public function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Листа волонтера");
      $this->sectionContent();

      $this->closeSection();
   }

   protected function sectionContent() {
      if ($_SERVER['REQUEST_METHOD'] == 'POST') {
         $this->processForm();
      }
      $this->renderForm();
   }

   protected function renderForm() {
         $niz = $this->getVolonteri();
		 $this->count = count($niz);
         if( count($niz) === 0) {
            echo $this->makeForm();
            echo $this->getNemaVolonterString();
            echo $this->backToListButton();
         } else {
            echo $this->renderList($niz);
         }
         echo $this->newButton();
   }

   protected function getVolonteri() {
      if($this->aktivan === self::AKTIVNI_VOLONTERI) {
         return VolonterDB::loadAllAktivni();
      }
      if($this->aktivan === self::PASIVNI_VOLONTERI) {
         return VolonterDB::loadAllPasivni();
      }
      return VolonterDB::loadAll();
   }

   protected function processForm() {
      $this->aktivan = filter_input(INPUT_POST, 'aktivni', FILTER_VALIDATE_INT);
      // $this->renderForm();
   }

   protected function renderList($nizVolontera) {
      $output  = "";
      $output .= $this->makeForm();
      $output .= $this->makeZaglavlje();
      
      foreach ($nizVolontera as $volonter) {
         $output .= $this->makeRow($volonter->getValue('id'), $volonter->getName());
      }

      $output .= $this->closeTable(2);
      return $output;
   }

   protected function makeZaglavlje() {
      $output  = "";
      $output .= $this->getImaVolonterString();
      $output .= $this->openTable("spisak", 2);
      $output .= $this->makeTableZaglavlje();
      return $output;
   }

   protected function getNemaVolonterString() {
      if($this->aktivan === self::AKTIVNI_VOLONTERI) {
         return str_repeat("\t", self::$indent+2) . "<p>Нема унетих активних волонтера.</p>\n";
      }
      if($this->aktivan === self::PASIVNI_VOLONTERI) {
         return str_repeat("\t", self::$indent+2) . "<p>Нема унетих пасивизираних волонтера.</p>\n";
      }
      return str_repeat("\t", self::$indent+2) . "<p>Нема унетих волонтера.</p>\n";
   }

   protected function getImaVolonterString() {
      if($this->aktivan === self::AKTIVNI_VOLONTERI) {
         return str_repeat("\t", self::$indent+2) . "<p>Унето је " . $this->count . " следећих волонтера:</p>\n";
      }
      if($this->aktivan === self::PASIVNI_VOLONTERI) {
         return str_repeat("\t", self::$indent+2) . "<p>Унето је " . $this->count . " следећих пасивизираних волонтера:</p>\n";
      }
      return str_repeat("\t", self::$indent+2) . "<p>Унето је " . $this->count . " следећих волонтера:</p>\n";
   }

   protected function makeForm() {
      $output  = "";
      $scriptName = "volonter.php?opID=" . $this->op;
      $output .= FormMaker::openForm($scriptName, 5);

      $output .= self::makeRadio($this->aktivan);

      $output .= FormMaker::submitElement('Примени', 6);
      
      $output .= FormMaker::closeForm(5);
      return $output;
   }

   protected static function makeRadio($aktivan) {
      $output  = "";
      $output .= str_repeat("\t", self::$indent+3);
      $output .= "<label><input type=\"radio\" name=\"aktivni\" value=\"" . self::AKTIVNI_VOLONTERI . "\"";
      $output .= ($aktivan === self::AKTIVNI_VOLONTERI ? " checked" : "") . ">Активни</label>\n";

      $output .= str_repeat("\t", self::$indent+3);
      $output .= "<label><input type=\"radio\" name=\"aktivni\" value=\"" . self::PASIVNI_VOLONTERI . "\"";
      $output .= ($aktivan === self::PASIVNI_VOLONTERI ? " checked" : "") . ">Пасвизирани</label>\n";
      
      $output .= str_repeat("\t", self::$indent+3);
      $output .= "<label><input type=\"radio\" name=\"aktivni\" value=\"" . self::SVI_VOLONTERI . "\"";
      $output .= $aktivan === self::SVI_VOLONTERI ? " checked>Сви</label>\n" : ">Сви</label>\n";
      // $output .= ">Сви\n";
              
      return $output;
   }

   protected function makeTableZaglavlje() {
      $output  = "";
      $output  = str_repeat("\t", self::$indent+3) . "<tr>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th>Презиме и име</th>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th colspan=\"4\" class=\"non_print\">Акција</th>\n";
      $output .= str_repeat("\t", self::$indent+3) . "</tr>\n";
      return $output;
   }

   protected function makeRow($vid, $naz) {
      $output  = str_repeat("\t", self::$indent+3) . "<tr>\n";
      $output .= $this->makeDetailsLink($vid, $naz);
      $output .= $this->makeUpdateLink($vid);
      $output .= $this->makePosetaLink($vid);
      $output .= $this->makeDeleteLink($vid);
      $output .= $this->makeActivateLink($vid);
      $output .= str_repeat("\t", self::$indent+3) . "</tr>\n";
      return $output;
   }

   protected function makeDetailsLink($vid, $naz) {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::DETAILS_VOLONTER . "&volonterID=" . $vid;
      return $this->makeLink($ref, $naz);
   }

   protected function makeUpdateLink($vid) {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::UPDATE_VOLONTER . "&volonterID=" . $vid;
      return $this->makeLinkNonPrint($ref, "Измени");
   }

   protected function makePosetaLink($vid) {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&volonterID=" . $vid;
      return $this->makeLinkNonPrint($ref, "Посете");
   }

   protected function makeDeleteLink($vid) {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::DELETE_VOLONTER . "&volonterID=" . $vid;
      return $this->makeLinkNonPrint($ref, "Пасивизирај");
   }

   protected function makeActivateLink($vid) {
      $ref = "volonter.php?opID=" . VolonterPageDispatcher::ACTIVATE_VOLONTER . "&volonterID=" . $vid;
      return $this->makeLinkNonPrint($ref, "Активирај");
   }
}
