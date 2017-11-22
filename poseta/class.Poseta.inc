<?php

require_once 'util/class.Data.inc';

/*
 * Klasa definise strukturu entiteta koji opisuje Posetu.
 */
class PosetaStructure extends Structure {
   /*
    * Definise abstraktni metod roditeljske klase i vraca opis strukture.
    */
   public function getDataDesc() {
      return array(
          'id' => array('integer', 0),
          'volonterID' => array('integer', 0),
          'pacijentID' => array('integer', 0),
          'brojSati' => array('double', 0),
          'datumPosete' => array('string', '0000-00-00')
      );
   }
   
   public function getFormDesc() {
      return array(
          'id' => array('hidden', ''),
          'volonterID' => array('volonter', 'Волонтер'),
          'pacijentID' => array('pacijent', 'Пацијент'),
          'brojSati' => array('text', 'Трајање посете [сати]'),
          'datumPosete' => array('text', 'Датум посете (гггг-мм-дд)'),
      );
   }

   public function getValidateDesc() {
      return array(
          'id' => array('not_negative'),
          'volonterID' => array('not_negative'),
          'pacijentID' => array('not_negative'),
          'brojSati' => array('not_negative'),
          'datumPosete' => array('datum')
      );
   }

   public function getDBDesc() {
      return array(
          'id' => 'sw',
          'volonterID' => 'siu',
          'pacijentID' => 'siu',
          'brojSati' => 'siu',
          'datumPosete' => 'siu'
      );
   }
   
   /*
    * Definise abstraktni metod roditeljske klase i vraca naziv strukture.
    */
   public function getTableName() {
      return 'POSETA';
   }
}

/*
 * Klasa koja definise entitet za jednu Posetu.
 * Koristi opstiju Data klasu,
 * kao i klasu za opis strukture entiteta Posete.
 */
class Poseta extends Data {
   
   public function __construct() {
      parent::__construct(new PosetaStructure);
   }
}
