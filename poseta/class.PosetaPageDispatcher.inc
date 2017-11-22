<?php

require_once 'class.PosetaPageList.inc';
require_once 'class.PosetaPageDetail.inc';
require_once 'class.PosetaPageUpdate.inc';
require_once 'class.PosetaPageNew.inc';
require_once 'class.PosetaPageDelete.inc';

class PosetaPageDispatcher {
   const LIST_POSETA = 3000;
   const DETAILS_POSETA = 3100;
   const NEW_POSETA = 3200;
   const UPDATE_POSETA = 3300;
   const DELETE_POSETA = 3400;

   /*
    * Na sifre osnovu operacije izaberi podstranu
    * (novi poseta, unos, izmena, lista, pregled).
    * @param integer $op - sifra operacije
    * @param integer $posid - sifra posete tamo gde ima smisla, 0 inace
    * @param integer $vid - sifra volontera ili 0
    * @param integer $pid - sifra pacijenta ili 0
    * @param integer $indent - pocetna indentacija sadrzaja strane
    */
   static public function choosePage($op, $posid, $vid, $pid, $indent) {
      switch ($op) {
         case PosetaPageDispatcher::LIST_POSETA:
            return new PosetaList($op, 0, $vid, $pid, $indent);
         case PosetaPageDispatcher::DETAILS_POSETA:
            return new PosetaDetail($op, $posid, $vid, $pid, $indent);
         case PosetaPageDispatcher::NEW_POSETA:
            return new PosetaNew($op, 0, $vid, $pid, $indent);
         case PosetaPageDispatcher::UPDATE_POSETA:
            return new PosetaUpdate($op, $posid, $vid, $pid, $indent);
         case PosetaPageDispatcher::DELETE_POSETA:
            return new PosetaDelete($op, $posid, $vid, $pid, $indent);
         default:
            return new PosetaList($op, 0, $vid, $pid, $indent);
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
          PosetaPageDispatcher::LIST_POSETA => "spisak.css",
          PosetaPageDispatcher::DETAILS_POSETA => "detalji.css",
          PosetaPageDispatcher::NEW_POSETA => "formstyle.css",
          PosetaPageDispatcher::UPDATE_POSETA => "formstyle.css",
      );
   }
}
