<?php

require_once 'class.Structure.inc';

/*
 * Klasa koja sadrzi entitete opisane Strukturom.
 */
class Data {
   //Struktura koja opisuje entitet.
   protected $structure = null;
   // Podaci.
   protected $data = array();
   
   /*
    * Konstruktor.
    * @param Structure - defiise opis polja.
    */
   public function __construct(Structure $structure) {
      $this->structure = $structure;
      foreach ( $structure->getDataDesc() as $fieldName => $fieldDesc ) {
         $this->data[$fieldName] = $fieldDesc[Structure::DATA_DEFAULT_VALUE];
      }
   }

   /*
    * Funkcija vraca strukturu pridruzenu klasi Data.
    * @return Structure
    */
   public function getStructure() {
      return $this->structure;
   }

   /*
    * Vraca niz podataka.
    * @return array
    */
   public function getData() {
      return $this->data;
   }
   
   /*
    * Vraca sadrzaj jednog polja.
    * param string
    * @return mixed
    */
   public function getValue($fieldName) {
      if ( array_key_exists($fieldName, $this->data) ) {
         return $this->data[$fieldName];
      } else {
         die("Data::getValue(): $fieldName not found");
      }
   }

   /*
    * Postavlja podatke.
    * @param array
    */
   public function setData($values) {
      if( is_array($values) ) {
         foreach ($values as $key => $value) {
            $this->setValue($key, $value);
         }
      } else {
         trigger_error("Data::setData called with not array argument.");
      }
   }

   /*
    * Postavlja jedno polje na zadatu vrednost.
    * Predhodno proverava ispravnost prosledjene vrednosti.
    * @param string
    * @param mixed
    */
   public function setValue($fieldName, $value) {
      if ( array_key_exists($fieldName, $this->data) ) {
         $this->data[$fieldName] = $this->filter($fieldName, $value);
      } else {
         die("Data::setValue(): $fieldName not found");
      }
   }

   /*
    * Kontrolise ispravnost podataka koji pokusavaju da se upisu.
    * @param string
    * @param mixed
    */
   private function filter($fieldName, $value) {
      $fieldDesc = $this->structure->getFieldDesc($fieldName);
      
      switch ($fieldDesc[Structure::DATA_TYPE]) {
         case "integer":
            $validatedValue = $this->filterInteger($value, $fieldDesc[Structure::DATA_DEFAULT_VALUE]); break;
         case "double":
            $validatedValue = $this->filterDouble($value, $fieldDesc[Structure::DATA_DEFAULT_VALUE]); break;
         case "datum":
            $validatedValue = $this->filterDatum($value, $fieldDesc[Structure::DATA_DEFAULT_VALUE]); break;
         default:
            $validatedValue = filter_var($value, FILTER_SANITIZE_SPECIAL_CHARS); break;
      }
      return $validatedValue;
   }

   /*
    * Kontrolise ispravnost podataka za tip integer.
    * @param mixed
    * @param integer
    * @return integer
    */
   private function filterInteger($value, $defaultValue) {
      return filter_var($value, FILTER_VALIDATE_INT, array('options' => array(
                'default' => $defaultValue)));
   }

   /*
    * Kontrolise ispravnost podataka za tip float tj. double.
    * @param mixed
    * @param double
    * @return double
    */
   private function filterDouble($value, $defaultValue) {
      return filter_var($value, FILTER_VALIDATE_FLOAT, array('options' => array(
                  'default' => $defaultValue, 'decimal' => '.')));
   }

   /*
    * Kontrolise ispravnost podataka za tip datum.
    * Ocekivani ulaz je datum u formatu dd.mm.gggg
    * Izlaz je u formatu gggg-mm-dd koji odgovara sql bazi
    * @param string
    * @param string
    * @return string
    */
   private function filterDatum($value, $defaultValue) {
      $filtered_var = filter_var($value, FILTER_VALIDATE_REGEXP,
           array("options"=>array("regexp"=>"/^(0[0-9]|[1-2][0-9]|3[0-1]).(0[0-9]|1[0-2]).[0-9]{4}$/")));

      if( is_null($filtered_var) ) {
         return $defaultValue;
      } elseif( $filtered_var === false ) {
         return $defaultValue;
      }
      
      list($dan, $mesec, $godina) = explode(".", $value);
      return "{$godina}-{$mesec}-{$dan}";
   }

   /*
    * Funkcija vraca niz naziva polja za update i insert (bez id polja).
    * Flag za upis je 'u', za insert 'i'
    * Resiti malo bolje ovo!
    * @return array
    */
   public function getFieldNames($flag) {
      $names = array();
      foreach ( $this->structure->getDBDesc() as $fieldName => $fieldDesc) {
         $pos = strpos($fieldDesc, $flag);
         if($pos !== false) {
            $names[] = $fieldName;
         }
      }
      return $names;
   }

   /*
    * Funkcija vraca niz vrednosti polja  za update i insert (bez id polja).
    * Resiti malo bolje ovo!
    * Flag za upis je 'u', za insert 'i'
    * @return array
    */
   public function getFieldValues($flag) {
      $values = array();
      foreach ( $this->structure->getDBDesc() as $fieldName => $fieldDesc) {
         $pos = strpos($fieldDesc, $flag);
         if($pos !== false) {
            $values[] = $this->getValue($fieldName);
         }
      }
      return $values;
   }
}

/*
 * Klasa za ispis podataka i tipova koje sadrzi klasa Data.
 */
class DataWriter {
   /*
    * Ispis podataka i tipova podataka klase Data.
    */
   public static function write(Data $d) {
      foreach ( $d->getData() as $key => $value) {
         echo $key . ": " . $value . " -> " . gettype($value) . "<br />\n";
      }
   }
}
