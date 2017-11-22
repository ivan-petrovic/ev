<?php

require_once 'class.Poseta.inc';
require_once 'utildb/class.Select.inc';
require_once 'utildb/class.Update.inc';
require_once 'utildb/class.Insert.inc';
require_once 'utildb/class.Delete.inc';

/*
 * Klasa koja ucitava i snima objekte tipa Poseta u mysql bazu.
 */
class PosetaDB {
   /*
    * Ucitaj posetu iz baze.
    * @param integer $id - id posete.
    * @return Poseta
    */
   static public function load($id) {
      $select = new Select();
      $select->from('poseta');
      $select->condition('id = ?', array($id));
      $result = $select->execute();
      $row = $result->fetch_assoc();

      return self::make($row);
   }

   protected static function make($row) {
      if($row) {
         $poseta = new Poseta();
         $poseta->setData($row);
         return $poseta;
      }
      trigger_error("PosetaDB::make(): not found.");
   }

   /*
    * Ucitaj sve posete iz baze.
    * @return array Poseta
    */
   static public function loadAll($datumOd, $datumDo) {
      $select = new Select();
      $select->from('poseta');
      $select->condition('WHERE ' . self::makeDatumCondition($datumOd, $datumDo));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      return $niz;
   }

   /*
    * Ucitaj sve posete iz baze za datog volontera.
    * @return array Poseta
    */
   static public function loadAllForVolonter($volonterID, $datumOd, $datumDo) {
      $select = new Select();
      $select->from('poseta');
      $select->condition('volonterID = ? AND ' . self::makeDatumCondition($datumOd, $datumDo), array($volonterID));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      return $niz;
   }

   /*
    * Ucitaj sve posete iz baze za datog pacijenta.
    * @return array Poseta
    */
   static public function loadAllForPacijent($pacijentID, $datumOd, $datumDo) {
      $select = new Select();
      $select->from('poseta');
      $select->condition('pacijentID = ? AND ' . self::makeDatumCondition($datumOd, $datumDo), array($pacijentID));
      $result = $select->execute();
      
      $niz = array();
      while($row = $result->fetch_assoc()) {
         $niz[] = self::make($row);
      }
      return $niz;
   }

   static public function makeDatumCondition($datumOd, $datumDo) {
      return "datumPosete BETWEEN \"{$datumOd}\" AND \"{$datumDo}\" ORDER BY datumPosete DESC";
   }
   
   /*
    * Izmeni posete u bazi.
    * @param Poseta.
    * @return boolean
    */
   static public function update(Poseta $poseta) {
      $update = new Update();
      $update->what( $poseta->getFieldNames('u') );
      $update->where('poseta');
      $update->condition('id = ?');
      $update->values( array_merge($poseta->getFieldValues('u'), array($poseta->getValue('id'))) );
      $updresult = $update->execute();
      return $updresult;
   }

   /*
    * Upis novog posete u bazu.
    * @param Poseta.
    * @return boolean
    */
   static public function insert(Poseta $poseta) {
      $insert = new Insert();
      $insert->what( $poseta->getFieldNames('i') );
      $insert->where('poseta');
      $insert->values( $poseta->getFieldValues('i') );
      $insresult = $insert->execute();
      return $insresult;
   }
   
   /*
    * Fizicko brisanje posete iz baze.
    * @param integer $id - id posete.
    * @return bool
    */
   static public function delete($id) {
      $delete = new Delete();
      $delete->where('poseta');
      $delete->condition('id = ?');
      $delete->values( array($id) );
      $delresult = $delete->execute();
      return ($delresult > 0 ? true : false);
   }
}
