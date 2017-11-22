<?php

require_once 'util/class.Data.inc';

/*
 * Klasa definise strukturu entiteta koji opisuje Volontera.
 */
class VolonterStructure extends Structure {
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
          'drzavljanstvo' => array('string', ''),
          'telefon' => array('string', ''),
          'datumRodjenja' => array('string', '0000-00-00'),
          'pol' => array('string', 'm'),
          'tipUgovora' => array('integer', 1),
          'datumPocetka' => array('string', '0000-00-00'),
          'datumIsteka' => array('string', '0000-00-00'),
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
          'drzavljanstvo' => array('text', 'Држављанство'),
          'telefon' => array('text', 'Телефон'),
          'datumRodjenja' => array('text', 'Датум рођења (гггг-мм-дд)'),
          'pol' => array('pol', 'Пол'),
          'tipUgovora' => array('tip_ugovor', 'Тип уговора'),
          'datumPocetka' => array('text', 'Датум почетка уговора (гггг-мм-дд)'),
          'datumIsteka' => array('text', 'Датум истека уговора (гггг-мм-дд)'),
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
          'tipUgovora' => array('not_negative'),
          'datumPocetka' => array('datum'),
          'datumIsteka' => array('datum'),
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
          'drzavljanstvo' => 'siu',
          'telefon' => 'siu',
          'datumRodjenja' => 'siu',
          'pol' => 'siu',
          'tipUgovora' => 'siu',
          'datumPocetka' => 'siu',
          'datumIsteka' => 'siu',
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
 * Klasa koja definise entitet za jednog Volontera.
 * Koristi opstiju Data klasu,
 * kao i klasu za opis strukture entiteta Volontera.
 */
class Volonter extends Data {
   /*
    * Konstruktor.
    */
   public function __construct() {
      parent::__construct(new VolonterStructure);
   }
   
   public function getName() {
      return $this->getValue('prezime') . " " . $this->getValue('ime');
   }
}
