<?php

/*
 * Abstraktna klasa za definiciju strukture klasa za interakciju sa DB.
 */
abstract class Structure {
   const DATA_TYPE = 0;
   const DATA_DEFAULT_VALUE = 1;

   const FORM_ELEMENT = 0;
   const FORM_LABEL = 1;

   /*
    * Abstraktni metod koji vraca niz opisa polja.
    * Kljuc u nizu je ime polja, a vrednost je niz sa tipom vrednosti u polju,
    * i pocetnom vrednoscu
    */
   abstract public function getDataDesc();

   /*
    * Funkcija vraca opis polja za zadato ime polja.
    * @return array
    */
   public function getFieldDesc($fieldName) {
      $arr = $this->getDataDesc();
      if( array_key_exists($fieldName, $arr) ) {
         return $arr[$fieldName];
      }      
      die("Structure::getFieldDescriptor(): $fieldName not found");
   }
   
   /*
    * Abstraktni metod koji vraca niz opisa polja formulara.
    * Svaki opis polja sadrzi naziv polja, tip vrednosti u polju,
    * pocetnu vrednost, koji element u formularu sluzi za unos,
    * i ogranicenja za polje.
    */
   abstract public function getFormDesc();

   /*
    * Abstraktni metod koji vraca opis validacije za dato polje.
    */
   abstract public function getValidateDesc();

   /*
    * Abstraktni metod koji vraca niz opisa polja za interakciju sa DB.
    */
   abstract public function getDBDesc();

   /*
    * Abstraktni metod koji vraca ime tabele u koju se smestaju.
    * rekordi koji odgovaraju strukturi.
    */
   abstract public function getTableName();
   
   /*
    * Funkcija vraca da li struktura sadrzi polje sa zadatim imenom.
    * @param string fieldName
    * @return bool
    */
   public function hasField($fieldName) {
      return array_key_exists($fieldName, $this->getDataDesc());
   }
}
