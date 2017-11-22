<?php

require_once 'util/class.Data.inc';

/*
 * Klasa definise strukturu entiteta koji opisuje Pacijenta.
 */
class PacijentStructure extends Structure {
   /*
    * Definise abstraktni metod roditeljske klase i vraca opis strukture.
    */
   public function getDataDesc() {
      return array(
          'id' => array('integer', 0),
          'ime' => array('string', ''),
          'prezime' => array('string', ''),
          'jmbg' => array('string', ''),
          'adresa' => array('string', ''),
          'mesto' => array('string', ''),
          'opstinaID' => array('integer', 0),
          'telefon' => array('string', ''),
          'pol' => array('string', 'm'),
          'datumRodjenja' => array('string', '0000-00-00'),
          'datumSmrti' => array('string', '0000-00-00'),
          'status' => array('string', 'Aktivan'),
          'opis' => array('string', '')
      );
   }
   
   public function getFormDesc() {
      return array(
          'id' => array('hidden', ''),
          'ime' => array('text', 'Име'),
          'prezime' => array('text', 'Презиме'),
          'jmbg' => array('text', 'ЈМБГ'),
          'adresa' => array('text', 'Адреса'),
          'mesto' => array('text', 'Место'),
          'opstinaID' => array('opstina', 'Општина'),
          'telefon' => array('text', 'Телефон'),
          'pol' => array('pol', 'Пол'),
          'datumRodjenja' => array('text', 'Датум рођења (гггг-мм-дд)'),
          'datumSmrti' => array('text', 'Датум смрти (гггг-мм-дд)'),
          'status' => array('status', 'Статус'),
          'opis' => array('textarea', 'Напомена')
      );
      // 'opis' => array('text', 'Напомена')
   }

   public function getValidateDesc() {
      return array(
          'id' => array('not_negative'),
          'ime' => array('not_empty'),
          'prezime' => array('not_empty'),
          'opstinaID' => array('not_negative'),
          'datumRodjenja' => array('datum'),
          'datumSmrti' => array('datum'),
          'status' => array('not_empty')
      );
   }

   public function getDBDesc() {
      return array(
          'id' => 'sw',
          'ime' => 'siu',
          'prezime' => 'siu',
          'jmbg' => 'siu',
          'adresa' => 'siu',
          'mesto' => 'siu',
          'opstinaID' => 'siu',
          'telefon' => 'siu',
          'pol' => 'siu',
          'datumRodjenja' => 'siu',
          'datumSmrti' => 'siu',
          'status' => 'siu',
          'opis' => 'siu'
      );
   }
   
   /*
    * Definise abstraktni metod roditeljske klase i vraca naziv strukture.
    */
   public function getTableName() {
      return 'VOLONTER';
   }
}

/*
 * Klasa koja definise entitet za jednog Pacijenta.
 * Koristi opstiju Data klasu,
 * kao i klasu za opis strukture entiteta Pacijenta.
 */
class Pacijent extends Data {
   /*
    * Konstruktor.
    */
   public function __construct() {
      parent::__construct(new PacijentStructure);
   }
   
   public function getName() {
      return $this->getValue('prezime') . " " . $this->getValue('ime');
   }
}
