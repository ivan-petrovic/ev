<?php

require_once 'class.PacijentDB.inc';
require_once 'class.PacijentPage.inc';

class PacijentList extends PacijentPage implements RenderHTML {
   const AKTIVNI_PACIJENTI = 2050;
   const PASIVNI_PACIJENTI = 2060;
   const SVI_PACIJENTI = 2070;
   
   protected $aktivan;
   protected $count = 0;

   /*
    * Konstruktor.
    */
   public function __construct($op, $pid, $indent) {
      parent::__construct($op, $pid, $indent);

      $this->aktivan = self::AKTIVNI_PACIJENTI;
   }
   
   public function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Листа пацијената");
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
         $niz = $this->getPacijenti();
		 $this->count = count($niz);
         if( count($niz) === 0) {
            echo $this->makeForm();
            echo $this->getNemaPacijentString();
            echo $this->backToListButton();
         } else {
            echo $this->renderList($niz);
         }
         echo $this->newButton();
   }

   protected function getPacijenti() {
      if($this->aktivan === self::AKTIVNI_PACIJENTI) {
         return PacijentDB::loadAllAktivni();
      }
      if($this->aktivan === self::PASIVNI_PACIJENTI) {
         return PacijentDB::loadAllPasivni();
      }
      return PacijentDB::loadAll();
   }

   protected function processForm() {
      $this->aktivan = filter_input(INPUT_POST, 'aktivni', FILTER_VALIDATE_INT);
   }

   protected function renderList($nizPacijenata) {
      $output  = "";
      $output .= $this->makeForm();
      $output .= $this->makeZaglavlje();
      
      foreach ($nizPacijenata as $pacijent) {
         $output .= $this->makeRow($pacijent->getValue('id'), $pacijent->getName());
      }

      $output .= $this->closeTable(2);
      return $output;
   }

   protected function makeZaglavlje() {
      $output  = "";
      $output .= $this->getImaPacijentString();
      $output .= $this->openTable("spisak", 2);
      $output .= $this->makeTableZaglavlje();
      return $output;
   }

   protected function getNemaPacijentString() {
      if($this->aktivan === self::AKTIVNI_PACIJENTI) {
         return str_repeat("\t", self::$indent+2) . "<p>Нема унетих активних пацијената.</p>\n";
      }
      if($this->aktivan === self::PASIVNI_PACIJENTI) {
         return str_repeat("\t", self::$indent+2) . "<p>Нема унетих пасивизираних пацијената.</p>\n";
      }
      return str_repeat("\t", self::$indent+2) . "<p>Нема унетих пацијената.</p>\n";
   }

   protected function getImaPacijentString() {
      if($this->aktivan === self::AKTIVNI_PACIJENTI) {
         return str_repeat("\t", self::$indent+2) . "<p>Унето је " . $this->count . " следећих пацијената:</p>\n";;
      }
      if($this->aktivan === self::PASIVNI_PACIJENTI) {
         return str_repeat("\t", self::$indent+2) . "<p>Унето је " . $this->count . " следећих пасивизираних пацијената:</p>\n";
      }
      return str_repeat("\t", self::$indent+2) . "<p>Унето је " . $this->count . " следећих пацијената:</p>\n";
   }

   protected function makeForm() {
      $output  = "";
      $scriptName = "pacijent.php?opID=" . $this->op;
      $output .= FormMaker::openForm($scriptName, 5);

      $output .= self::makeRadio($this->aktivan);

      $output .= FormMaker::submitElement('Примени', 6);
      
      $output .= FormMaker::closeForm(5);
      return $output;
   }

   protected static function makeRadio($aktivan) {
      $output  = "";
      $output .= str_repeat("\t", self::$indent+3);
      $output .= "<label><input type=\"radio\" name=\"aktivni\" value=\"" . self::AKTIVNI_PACIJENTI . "\"";
      $output .= ($aktivan === self::AKTIVNI_PACIJENTI ? " checked" : "") . ">Активни</label>\n";

      $output .= str_repeat("\t", self::$indent+3);
      $output .= "<label><input type=\"radio\" name=\"aktivni\" value=\"" . self::PASIVNI_PACIJENTI . "\"";
      $output .= ($aktivan === self::PASIVNI_PACIJENTI ? " checked" : "") . ">Пасвизирани</label>\n";
      
      $output .= str_repeat("\t", self::$indent+3);
      $output .= "<label><input type=\"radio\" name=\"aktivni\" value=\"" . self::SVI_PACIJENTI . "\"";
      $output .= ($aktivan === self::SVI_PACIJENTI ? " checked" : "") . ">Сви</label>\n";
              
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

   protected function makeRow($pid, $naz) {
      $output  = str_repeat("\t", self::$indent+3) . "<tr>\n";
      $output .= $this->makeDetailsLink($pid, $naz);
      $output .= $this->makeUpdateLink($pid);
      $output .= $this->makePosetaLink($pid);
      $output .= $this->makeDeleteLink($pid);
      $output .= $this->makeActivateLink($pid);
      $output .= str_repeat("\t", self::$indent+3) . "</tr>\n";
      return $output;
   }

   protected function makeDetailsLink($pid, $naz) {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::DETAILS_PACIJENT . "&pacijentID=" . $pid;
      return $this->makeLink($ref, $naz);
   }

   protected function makeUpdateLink($pid) {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::UPDATE_PACIJENT . "&pacijentID=" . $pid;
      return $this->makeLinkNonPrint($ref, "Измени");
   }

   protected function makePosetaLink($pid) {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&pacijentID=" . $pid;
      return $this->makeLinkNonPrint($ref, "Посете");
   }

   protected function makeDeleteLink($pid) {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::DELETE_PACIJENT . "&pacijentID=" . $pid;
      return $this->makeLinkNonPrint($ref, "Пасивизирај");
   }
   
   protected function makeActivateLink($pid) {
      $ref = "pacijent.php?opID=" . PacijentPageDispatcher::ACTIVATE_PACIJENT . "&pacijentID=" . $pid;
      return $this->makeLinkNonPrint($ref, "Активирај");
   }
}
