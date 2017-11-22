<?php

require_once 'class.PosetaDB.inc';
require_once 'class.PosetaPage.inc';

class PosetaList extends PosetaPage implements RenderHTML {
   protected $datumOd;
   protected $datumDo;
   
   /*
    * Konstruktor.
    */
   public function __construct($op, $posid, $vid, $pid, $indent) {
      parent::__construct($op, $posid, $vid, $pid, $indent);

      $today = new DateTime('now');
      $this->datumOd = $today->format('Y') . '-01-01';
      $this->datumDo = $today->format("Y-n-j");
   }
   
   public function renderHTML() {
      $this->openSection();
      
      $this->sectionHeader("Листа посета");
      $this->sectionContent();

      $this->closeSection();
   }
   
   protected function sectionContent() {
      if ($_SERVER['REQUEST_METHOD'] == 'POST') {
         $this->processForm();
      } else {
         $this->renderForm();
      }
   }

   protected function renderForm() {
         $niz = $this->getPosete();
         if( count($niz) === 0) {
            echo $this->makeForm();
            echo $this->getNemaPosetaString();
            echo $this->backToListButton();
         } else {
            echo $this->renderList($niz);
         }
         echo $this->backToListButton();
         echo $this->newButton();
   }

   protected function processForm() {
      $datumOd = $_POST['datumOd'];
      $validOd = $this->datumValidate($datumOd);
      $datumDo = $_POST['datumDo'];
      $validDo = $this->datumValidate($datumOd);
      
      if($validOd && $validDo) {
         $this->datumOd = $datumOd;
         $this->datumDo = $datumDo;
      } else {
         echo "<p class=\"error\">Датумска поља нису у добром формату</p>\n";
      }
      $this->renderForm();
   }

   protected function datumValidate($value) {
      $filtered_var = filter_var($value, FILTER_VALIDATE_REGEXP,
              array("options"=>array("regexp"=>"/\d{4}-[01]\d-[0-3]\d/")));

      if( is_null($filtered_var) ) {
         return false;
      } elseif( $filtered_var === false ) {
         return false;
      }
      return true;
   }

   protected function getPosete() {
      if($this->vid !== 0) {
         return PosetaDB::loadAllForVolonter($this->vid, $this->datumOd, $this->datumDo);
      }
      if($this->pid !== 0) {
         return PosetaDB::loadAllForPacijent($this->pid, $this->datumOd, $this->datumDo);
      }
      return PosetaDB::loadAll($this->datumOd, $this->datumDo);
   }

   protected function getNemaPosetaString() {
      if($this->vid !== 0) {
         $ime = VolonterDB::name($this->vid);
         return str_repeat("\t", self::$indent+2) . "<p>Нема унетих посета за волонтера {$ime} у задатом периоду.</p>\n";
      }
      if($this->pid !== 0) {
         $ime = PacijentDB::name($this->pid);
         return str_repeat("\t", self::$indent+2) . "<p>Нема унетих посета за пацијента {$ime}  у задатом периоду.</p>\n";
      }
      return str_repeat("\t", self::$indent+2) . "<p>Нема унетих посета у задатом периоду.</p>\n";
   }

   protected function getImaPosetaString() {
      if($this->vid !== 0) {
         $ime = VolonterDB::name($this->vid);
         return str_repeat("\t", self::$indent+2) . "<p>Унете су следеће посете за волонтера {$ime}:</p>\n";
      }
      if($this->pid !== 0) {
         $ime = PacijentDB::name($this->pid);
         return str_repeat("\t", self::$indent+2) . "<p>Унете су следеће посете за пацијента {$ime}:</p>\n";
      }
      return str_repeat("\t", self::$indent+2) . "<p>Унете су следеће посете:</p>\n";
   }

   protected function renderList($nizPoseta) {
      $output  = "";
      $output .= $this->makeForm();
      $output .= $this->makeZaglavlje();
      
      $uk = 0;
      foreach ($nizPoseta as $poseta) {
         $output .= $this->makeRow($poseta);
         $uk += $poseta->getValue('brojSati');
      }
      $output .= $this->makeZbir($uk);
      $output .= $this->closeTable(2);
      return $output;
   }

//      if($datum == '0000-00-00') {
//         $output .= "___________________</p>\n";
//      } else {
//         $di = new DateTime($datum);
//         $output .= $di->format("j.n.Y") . ". године</p>\n";
//      }
   
   protected function makeForm() {
      $output  = "";
      $scriptName = "poseta.php?opID=" . $this->op . "&volonterID=" . $this->vid . "&pacijentID=" . $this->pid;
      $output .= FormMaker::openForm($scriptName, 5);

      $output .= FormMaker::textElement('Од датума', 'datumOd', $this->datumOd, 6);

      // $today = new DateTime('now');
      // $datum = $today->format("Y-n-j");
      $output .= FormMaker::textElement('до датума', 'datumDo', $this->datumDo, 6);
      $output .= FormMaker::submitElement('Примени', 6);
      
      $output .= FormMaker::closeForm(5);
      return $output;
   }
   
   protected function makeZaglavlje() {
      $output  = "";
      $output .= $this->getImaPosetaString();
      $output .= $this->openTable("spisak", 2);
      $output .= $this->makeTableZaglavlje();
      return $output;
   }

   protected function makeTableZaglavlje() {
      $output  = "";

      $output  = str_repeat("\t", self::$indent+3) . "<tr>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th>Волонтер</th>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th>Пацијент</th>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th>Трајање</th>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th>Датум</th>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<th colspan=\"2\" class=\"non_print\">Акција</th>\n";
      $output .= str_repeat("\t", self::$indent+3) . "</tr>\n";
      return $output;
   }

   
   protected function makeZbir($zbir) {
      $fzbir = $this->formatSatiMinuti($zbir);
      $output  = str_repeat("\t", self::$indent+3) . "<tr class=\"sati-ukupno\">\n";
      $output .= str_repeat("\t", self::$indent+4) . "<td colspan=\"2\">УКУПНО</td>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<td class=\"desno\">$fzbir</td>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<td></td>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<td class=\"non_print\"></td>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<td class=\"non_print\"></td>\n";
      $output .= str_repeat("\t", self::$indent+3) . "</tr>\n";
      return $output;
   }
   
   protected function formatSatiMinuti($satidec) {
      $sati = floor($satidec);
      // return $satidec;
      $minuti = ($satidec - $sati) * 60;
      $fminuti = str_pad(number_format($minuti), 2, " ", STR_PAD_LEFT);
      // echo $satidec . "-" . $sati; exit();
      // number_format($zbir, 0, ',', '.');
      $satistr = ($sati == 1 ? "сат " : ($sati > 4 ? "сати" : "сата") );
      // return "<pre>{$sati} {$satistr} {$fminuti} мин.</pre>";
      return "{$sati} <span class=\"sati\">{$satistr}</span><span class=\"min\">{$fminuti}</span> мин.</pre>";
   }
   
   protected function makeRow(Poseta $poseta) {
      $output  = str_repeat("\t", self::$indent+3) . "<tr>\n";
      
      $fsati = $this->formatSatiMinuti($poseta->getValue('brojSati'));
      $output .= $this->makeVolonterLink($poseta->getValue('volonterID'));
      $output .= $this->makePacijentLink($poseta->getValue('pacijentID'));
      $output .= str_repeat("\t", self::$indent+4) . "<td class=\"desno\">" . $fsati . "</td>\n";
      $output .= str_repeat("\t", self::$indent+4) . "<td class=\"desno\">" . $poseta->getValue('datumPosete') . "</td>\n";
      $output .= $this->makeDeleteLink($poseta->getValue('id'));
      $output .= $this->makeUpdateLink($poseta->getValue('id'));
      
      $output .= str_repeat("\t", self::$indent+3) . "</tr>\n";
      return $output;
   }

   protected function makeVolonterLink($id) {
      // $ref = "volonter.php?opID=" . VolonterPageDispatcher::DETAILS_VOLONTER . "&volonterID=" . $id;
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&volonterID=" . $id;
      $ime = VolonterFormElement::getName($id);
      return $this->makeLink($ref, $ime);
   }

   protected function makePacijentLink($id) {
      // $ref = "pacijent.php?opID=" . PacijentPageDispatcher::DETAILS_PACIJENT . "&pacijentID=" . $id;
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::LIST_POSETA . "&pacijentID=" . $id;
      $ime = PacijentFormElement::getName($id);
      return $this->makeLink($ref, $ime);
   }

//   protected function makeDetailsLink($posid) {
//      $ref = "poseta.php?opID=" . PosetaPageDispatcher::DETAILS_POSETA . "&posetaID=" . $posid;
//      return $this->makeLink($ref, "Прегледај");
//   }
//
   protected function makeUpdateLink($posid) {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::UPDATE_POSETA . "&posetaID=" . $posid;
      return $this->makeLinkNonPrint($ref, "Измени");
   }

   protected function makeDeleteLink($posid) {
      $ref = "poseta.php?opID=" . PosetaPageDispatcher::DELETE_POSETA . "&posetaID=" . $posid;
      return $this->makeLinkNonPrint($ref, "Обриши");
   }
}
