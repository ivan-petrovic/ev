<?php

require_once 'class.Data.inc';

class Validator {
   protected $errors = array();
   
   public function getErrors() {
      return $this->errors;
   }
   
   public function is_valid() {
      return ( count($this->errors) ? false : true );
   }
   
   public function validate(Data $d) {
      $valDesc = $d->getStructure()->getValidateDesc();
      foreach ($valDesc as $fieldName => $constraints) {
         $this->validateField($fieldName, $constraints, $d->getValue($fieldName));
      }
   }
   
   protected function validateField($fieldName, $constraints, $value) {
      foreach ($constraints as $constraint) {
         $this->validateConstraint($fieldName, $constraint, $value);   
      }
   }

   protected function validateConstraint($fieldName, $constraint, $value) {
      $method = $constraint . "Validate";
      return $this->$method($fieldName, $value);

//      switch ($constraint) {
//         case "not_negative":
//            $this->validateNotNegative($fieldDescriptor, $value); break;
//         case "positive":
//            $this->validatePositive($fieldDescriptor, $value); break;
//         case "not_empty":
//            $this->validateNotEmpty($fieldDescriptor, $value); break;
//         case "donet_minuli":
//            $this->validateDonetMinuli($fieldDescriptor, $value); break;
//         case "datum":
//            $this->validateDate($fieldDescriptor, $value); break;
//         default:
//            // $this->errors[] = "Nepoznat tip ogranicenja za polje.";
//            break;
//      }
   }

   protected function not_negativeValidate($fieldName, $value) {
      if( $value < 0 ) {
         $this->addError($fieldName, "Поље треба да буде позитиван број или нула.");
      }
   }

   protected function positiveValidate($fieldName, $value) {
      if( $value <= 0 ) {
         $this->addError($fieldName, "Поље треба да буде позитиван број.");
      }
   }
   
   protected function not_emptyValidate($fieldName, $value) {
      if( empty($value) ) {
         $this->addError($fieldName, "Поље не сме да буде празно.");
      }
   }

   protected function donet_minuliValidate($fieldName, $value) {
      $filtered_var = filter_var($value, FILTER_VALIDATE_REGEXP,
              array("options"=>array("regexp"=>"/\d{1,2}-\d{1,2}-\d{1,2}/")));

      if( is_null($filtered_var) ) {
         $this->addError($fieldName, "Поље је обавезно.");
      } elseif( $filtered_var === false ) {
         $this->addError($fieldName, "Поље није у одговарајућем формату.");
      }
   }
   
   protected function datumValidate($fieldName, $value) {
      $filtered_var = filter_var($value, FILTER_VALIDATE_REGEXP,
              array("options"=>array("regexp"=>"/^[0-9]{4}-(0[0-9]|1[0-2])-(0[0-9]|[1-2][0-9]|3[0-1])$/")));
              // array("options"=>array("regexp"=>"/\d{4}-[01]\d-[0-3]\d/")));

      if( is_null($filtered_var) ) {
         $this->addError($fieldName, "Датумско поље је обавезно.");
      } elseif( $filtered_var === false ) {
         $this->addError($fieldName, "Датумско поље није у одговарајућем формату 0.");
      }
   }

   //$date="2012-09-12"; sa nedozvoljenim 0000-00-00
   // if (preg_match("/^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$/",$date))
   //$date="12.09.2012" sa dozvoljenim 00.00.0000;
   // "/^(0[0-9]|[1-2][0-9]|3[0-1]).(0[0-9]|1[0-2]).[0-9]{4}$/"

   protected function addError($fieldName, $errDesc) {
      if(!array_key_exists($fieldName, $this->errors)) {
         $this->errors[$fieldName] = array();
      }
      $this->errors[$fieldName][] = $errDesc;
   }
}
