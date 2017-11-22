<?php

require_once 'class.VolonterPageList.inc';
require_once 'class.VolonterPageDetail.inc';
require_once 'class.VolonterPageUpdate.inc';
require_once 'class.VolonterPageNew.inc';
require_once 'class.VolonterPageDelete.inc';

class VolonterPageDispatcher {
   const LIST_VOLONTER = 1000;
   const DETAILS_VOLONTER = 1100;
   const NEW_VOLONTER = 1200;
   const UPDATE_VOLONTER = 1300;
   const DELETE_VOLONTER = 1400;
   const ACTIVATE_VOLONTER = 1500;

   /*
    * Na sifre osnovu operacije izaberi podstranu
    * (novi volonter, unos, izmena, lista, pregled).
    * @param integer $op - sifra operacije
    * @param integer $vid - sifra volontera tamo gde ima smisla, 0 inace
    * @param integer $indent - pocetna indentacija sadrzaja strane
    */
   static public function choosePage($op, $vid, $indent) {
      switch ($op) {
         case VolonterPageDispatcher::LIST_VOLONTER:
            return new VolonterList($op, 0, $indent);
         case VolonterPageDispatcher::DETAILS_VOLONTER:
            return new VolonterDetail($op, $vid, $indent);
         case VolonterPageDispatcher::NEW_VOLONTER:
            return new VolonterNew($op, 0, $indent);
         case VolonterPageDispatcher::UPDATE_VOLONTER:
            return new VolonterUpdate($op, $vid, $indent);
         case VolonterPageDispatcher::DELETE_VOLONTER:
            return new VolonterDelete($op, $vid, $indent);
         case VolonterPageDispatcher::ACTIVATE_VOLONTER:
            return new VolonterActivate($op, $vid, $indent);
         default:
            return new VolonterList($op, 0, $indent);
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
          VolonterPageDispatcher::LIST_VOLONTER => "spisak.css",
          VolonterPageDispatcher::DETAILS_VOLONTER => "detalji.css",
          VolonterPageDispatcher::NEW_VOLONTER => "formstyle.css",
          VolonterPageDispatcher::UPDATE_VOLONTER => "formstyle.css",
      );
   }
}
