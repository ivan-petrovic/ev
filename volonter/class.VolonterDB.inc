<?php

require_once 'class.Volonter.inc';
require_once 'utildb/class.Select.inc';
require_once 'utildb/class.Update.inc';
require_once 'utildb/class.Insert.inc';

/*
 * Klasa koja ucitava i snima objekte tipa Volonter u mysql bazu.
 */
class VolonterDB {
   /*
    * Ucitaj volontera iz baze.
    * @param integer $id - id volontera.
    * @return Volonter
    */
   static public function load($id) {
      $select = new Select();
      $select->from('volonter');
      $select->condition("id = ?", array($id));
      $result = $select->execute();
      $row = $result->fetch_assoc();

      return self::make($row);
   }

   protected static function make($row) {
      if($row) {
         $volonter = new Volonter();
         $volonter->setData($row);
         return $volonter;
      }
      trigger_error("VolonterDB::make(): not found.");
   }

   /*
    * Vrati ime volontera sa datim id.
    * @param integer id - sifra volontera
    * @return string - ime i prezime volontera
    */
   static public function name($id) {
      $select = new Select();
      $select->what(array('ime', 'prezime'));
      $select->from('volonter');
      $select->condition("id = ?", array($id));
      $result = $select->execute();
      $row = $result->fetch_assoc();

      if($row) {
         return $row['prezime'] . " " . $row['ime'];
      } else
      trigger_error('Volonter with id $id not found.');
   }
   
   /*
    * Ucitaj sve volontere iz baze.
    * @return array Volonter
    */
   static public function loadAll() {
      $select = new Select();
      $select->from('volonter');
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      usort($niz, array("VolonterDB", "volonterSort"));
      return $niz;
   }

   /*
    * Ucitaj sve aktivne volontere iz baze.
    * @return array Volonter
    */
   static public function loadAllAktivni() {
      $select = new Select();
      $select->from('volonter');
      $select->condition("status = ?", array('Aktivan'));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      usort($niz, array("VolonterDB", "volonterSort"));
      return $niz;
   }

   /*
    * Ucitaj sve pasivne volontere iz baze.
    * @return array Volonter
    */
   static public function loadAllPasivni() {
      $select = new Select();
      $select->from('volonter');
      $select->condition("status = ?", array('Pasivan'));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      usort($niz, array("VolonterDB", "volonterSort"));
      return $niz;
   }

   // usort() comparison function for Volonter objects
   protected function volonterSort(Volonter $a, Volonter $b) {
      return strcmp($a->getValue('prezime'), $b->getValue('prezime'));
   }

   /*
    * Izmeni volontera u bazi.
    * @param Volonter.
    * @return boolean
    */
   static public function update(Volonter $volonter) {
      $update = new Update();
      $update->what( $volonter->getFieldNames('u') );
      $update->where('volonter');
      $update->condition('id = ?');
      $update->values( array_merge($volonter->getFieldValues('u'), array($volonter->getValue('id'))) );
      $updresult = $update->execute();
      return $updresult;
   }

   /*
    * Upis novog volontera u bazu.
    * @param Volonter.
    * @return boolean
    */
   static public function insert(Volonter $volonter) {
      $insert = new Insert();
      $insert->what( $volonter->getFieldNames('i') );
      $insert->where('volonter');
      $insert->values( $volonter->getFieldValues('i') );
      $insresult = $insert->execute();
      return $insresult;
   }
   
   /*
    * Brisanje volontera iz baze. Ne radi se fizicko brisanje,
    * vec se samo status postavlja na 'Pasivan'
    * @param integer $id - id volontera.
    * @return bool
    */
   static public function delete($id) {
      $update = new Update();
      $update->what( array('status') );
      $update->where('volonter');
      $update->condition('id = ?');
      $update->values( array('Pasivan', $id) );
      $updresult = $update->execute();
      return ($updresult > 0 ? true : false);
   }
   
   /*
    * Aktiviranje volontera u bazi.
    * Status se postavlja na 'Aktivan'
    * @param integer $id - id volontera.
    * @return bool
    */
   static public function activate($id) {
      $update = new Update();
      $update->what( array('status') );
      $update->where('volonter');
      $update->condition('id = ?');
      $update->values( array('Aktivan', $id) );
      $updresult = $update->execute();
      return ($updresult > 0 ? true : false);
   }
}
