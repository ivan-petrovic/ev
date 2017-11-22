<?php

require_once 'class.Pacijent.inc';
require_once 'utildb/class.Select.inc';
require_once 'utildb/class.Update.inc';
require_once 'utildb/class.Insert.inc';

/*
 * Klasa koja ucitava i snima objekte tipa Pacijent u mysql bazu.
 */
class PacijentDB {
   /*
    * Ucitaj pacijenta iz baze.
    * @param integer $id - id pacijenta.
    * @return Pacijent
    */
   static public function load($id) {
      $select = new Select();
      $select->from('pacijent');
      $select->condition('id = ?', array($id));
      $result = $select->execute();
      $row = $result->fetch_assoc();

      return self::make($row);
   }

   protected static function make($row) {
      if($row) {
         $pacijent = new Pacijent();
         $pacijent->setData($row);
         return $pacijent;
      }
      trigger_error("PacijentDB::make(): not found.");
   }

   /*
    * Vrati ime pacijenta sa datim id.
    * @param integer id - sifra pacijenta
    * @return string - ime i prezime pacijenta
    */
   static public function name($id) {
      $select = new Select();
      $select->what(array('ime', 'prezime'));
      $select->from('pacijent');
      $select->condition('id = ?', array($id));
      $result = $select->execute();
      $row = $result->fetch_assoc();

      if($row) {
         return $row['prezime'] . ' ' . $row['ime'];
      } else
      trigger_error("Pacijent with id $id not found.");
   }
   
   /*
    * Ucitaj sve pacijente iz baze.
    * @return array Pacijent
    */
   static public function loadAll() {
      $select = new Select();
      $select->from('pacijent');
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      usort($niz, array('PacijentDB', 'pacijentSort'));
      return $niz;
   }

   /*
    * Ucitaj sve aktivne volontere iz baze.
    * @return array Volonter
    */
   static public function loadAllAktivni() {
      $select = new Select();
      $select->from('pacijent');
      $select->condition("status = ?", array('Aktivan'));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      usort($niz, array('PacijentDB', 'pacijentSort'));
      return $niz;
   }

   /*
    * Ucitaj sve pasivne volontere iz baze.
    * @return array Volonter
    */
   static public function loadAllPasivni() {
      $select = new Select();
      $select->from('pacijent');
      $select->condition("status = ?", array('Pasivan'));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      usort($niz, array('PacijentDB', 'pacijentSort'));
      return $niz;
   }

   // usort() comparison function for Pacijent objects
   protected function pacijentSort(Pacijent $a, Pacijent $b) {
      return strcmp($a->getValue('prezime'), $b->getValue('prezime'));
   }

   /*
    * Izmeni pacijenta u bazi.
    * @param Pacijent.
    * @return boolean
    */
   static public function update(Pacijent $pacijent) {
      $update = new Update();
      $update->what( $pacijent->getFieldNames('u') );
      $update->where('pacijent');
      $update->condition('id = ?');
      $update->values( array_merge($pacijent->getFieldValues('u'), array($pacijent->getValue('id'))) );
      $updresult = $update->execute();
      return $updresult;
   }

   /*
    * Upis novog pacijenta u bazu.
    * @param Pacijent.
    * @return boolean
    */
   static public function insert(Pacijent $pacijent) {
      $insert = new Insert();
      $insert->what( $pacijent->getFieldNames('i') );
      $insert->where('pacijent');
      $insert->values( $pacijent->getFieldValues('i') );
      $insresult = $insert->execute();
      return $insresult;
   }
   
   /*
    * Brisanje pacijenta iz baze. Ne radi se fizicko brisanje,
    * vec se samo status postavlja na 'Pasivan'
    * @param integer $id - id pacijenta.
    * @return bool
    */
   static public function delete($id) {
      $update = new Update();
      $update->what( array('status') );
      $update->where('pacijent');
      $update->condition('id = ?');
      $update->values( array('Pasivan', $id) );
      $updresult = $update->execute();
      return ($updresult > 0 ? true : false);
   }

   /*
    * Aktiviranje pacijenta u bazi.
    * Status se postavlja na 'Aktivan'
    * @param integer $id - id pacijenta.
    * @return bool
    */
   static public function activate($id) {
      $update = new Update();
      $update->what( array('status') );
      $update->where('pacijent');
      $update->condition('id = ?');
      $update->values( array('Aktivan', $id) );
      $updresult = $update->execute();
      return ($updresult > 0 ? true : false);
   }
}
