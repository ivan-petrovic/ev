<?php

require_once 'class.PacijentPageList.inc';
require_once 'class.PacijentPageDetail.inc';
require_once 'class.PacijentPageUpdate.inc';
require_once 'class.PacijentPageNew.inc';
require_once 'class.PacijentPageDelete.inc';

class PacijentPageDispatcher {
   const LIST_PACIJENT = 2000;
   const DETAILS_PACIJENT = 2100;
   const NEW_PACIJENT = 2200;
   const UPDATE_PACIJENT = 2300;
   const DELETE_PACIJENT = 2400;
   const ACTIVATE_PACIJENT = 2500;
   
   /*
    * Na sifre osnovu operacije izaberi podstranu
    * (novi pacijent, unos, izmena, lista, pregled).
    * @param integer $op - sifra operacije
    * @param integer $pid - sifra pacijenta tamo gde ima smisla, 0 inace
    * @param integer $indent - pocetna indentacija sadrzaja strane
    */
   static public function choosePage($op, $pid, $indent) {
      switch ($op) {
         case PacijentPageDispatcher::LIST_PACIJENT:
            return new PacijentList($op, 0, $indent);
         case PacijentPageDispatcher::DETAILS_PACIJENT:
            return new PacijentDetail($op, $pid, $indent);
         case PacijentPageDispatcher::NEW_PACIJENT:
            return new PacijentNew($op, 0, $indent);
         case PacijentPageDispatcher::UPDATE_PACIJENT:
            return new PacijentUpdate($op, $pid, $indent);
         case PacijentPageDispatcher::DELETE_PACIJENT:
            return new PacijentDelete($op, $pid, $indent);
         case PacijentPageDispatcher::ACTIVATE_PACIJENT:
            return new PacijentActivate($op, $pid, $indent);
         default:
            return new PacijentList($op, 0, $indent);
      }
   }

   /*
    * Na sifre osnovu operacije bira CSS fajl koji treba da ucita zaglavlje strane.
    * @param integer $op - sifra operacije
    */
   static public function getCSSFileName($op) {
      $cssFiles = self::CSSFileNamesMap();
      if(array_key_exists($op, $cssFiles)) {
         return $cssFiles[$op];
      }
      return "spisak.css";
   }
   
   /*
    * Funkcija vraca niz koji mapira sifru operacije na naziv css fajla
    * pridruzenog toj operaciji.
    */
   static protected function CSSFileNamesMap() {
      return array(
          PacijentPageDispatcher::LIST_PACIJENT => "spisak.css",
          PacijentPageDispatcher::DETAILS_PACIJENT => "detalji.css",
          PacijentPageDispatcher::NEW_PACIJENT => "formstyle.css",
          PacijentPageDispatcher::UPDATE_PACIJENT => "formstyle.css",
      );
   }
}
