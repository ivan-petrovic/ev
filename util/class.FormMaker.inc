<?php

require_once 'class.Data.inc';

class FormMaker {
   public static function make(Data $d, $scriptName, $submitLabel, $indent) {
      $output  = self::openForm($scriptName, $indent);
      $output .= self::formCore($d, $indent + 1);
      $output .= self::submitElement($submitLabel, $indent + 1);
      $output .= self::closeForm($indent);
      
      return $output;
   }
   
   public static function formCore(Data $d, $indent) {
      $output = "";
      
      foreach ($d->getStructure()->getFormDesc() as $fieldName => $fieldDesc) {
         $output .= str_repeat("\t", $indent) . "<p>\n";
         $output .= self::makeElement($fieldDesc[Structure::FORM_ELEMENT],
                 $fieldDesc[Structure::FORM_LABEL], $fieldName,
                 $d->getValue($fieldName), $indent);
         $output .= str_repeat("\t", $indent) . "</p>\n";
      }

      return $output;
   }

   public static function openForm($scriptName, $indent) {
      $output  = str_repeat("\t", $indent);
      $output .= "<form action=\"$scriptName\" method=\"POST\">\n";
      return $output;
   }

   public static function closeForm($indent) {
      $output = str_repeat("\t", $indent) . "</form>\n";
      return $output;
   }

   protected static function makeElement($formElement, $label, $nameAndID, $value, $indent) {
      $method = $formElement . "Element";
      return static::$method($label, $nameAndID, $value, $indent);
   }

   public static function submitElement($label, $indent) {
      return str_repeat("\t", $indent) . "<input type=\"submit\" value=\"{$label}\">\n";
   }

   public static function textElement($label, $nameAndID, $value, $indent) {
      $output  = str_repeat("\t", $indent) . "<label for=\"{$nameAndID}\">{$label}:</label>\n";
      $output .= str_repeat("\t", $indent) . "<input type=\"text\" name=\"{$nameAndID}\" ";
      $output .= "id=\"{$nameAndID}\" value=\"{$value}\" />\n";
      return $output;
   }

   public static function textareaElement($label, $nameAndID, $value, $indent) {
      $value = str_replace("&#38;#13;&#38;#10;", "\r\n", trim($value));
      $output  = str_repeat("\t", $indent) . "<label for=\"{$nameAndID}\">{$label}:</label>\n";
      $output .= str_repeat("\t", $indent) . "<textarea name=\"{$nameAndID}\" ";
      $output .= "id=\"{$nameAndID}\" rows=\"8\" cols=\"50\">\n";
      $output .= $value;
      $output .= "</textarea>\n";
      return $output;
   }

   public static function hiddenElement($label, $nameAndID, $value, $indent) {
      $output  = str_repeat("\t", $indent);
      $output .= "<input type=\"hidden\" name=\"{$nameAndID}\" ";
      $output .= "id=\"{$nameAndID}\" value=\"{$value}\" />\n";
      return $output;
   }

   public static function statusElement($label, $nameAndID, $value, $indent) {
      return StatusFormElement::make($label, $nameAndID, $value, $indent);
   }

   public static function polElement($label, $nameAndID, $value, $indent) {
      return PolFormElement::make($label, $nameAndID, $value, $indent);
   }

   public static function opstinaElement($label, $nameAndID, $value, $indent) {
      return Municipality::make($label, $nameAndID, $value, $indent);
   }

   public static function tip_ugovorElement($label, $nameAndID, $value, $indent) {
      return TipUgovorFormElement::make($label, $nameAndID, $value, $indent);
   }

   public static function volonterElement($label, $nameAndID, $value, $indent) {
      return VolonterFormElement::make($label, $nameAndID, $value, $indent);
   }

   public static function pacijentElement($label, $nameAndID, $value, $indent) {
      return PacijentFormElement::make($label, $nameAndID, $value, $indent);
   }

   public static function printErrors($errorsMap, $indent) {
      $output = str_repeat("\t", $indent) . "<div class=\"error\">\n";
      
      foreach ($errorsMap as $fieldName => $errors) {
         $output .= self::printErrorForField($fieldName, $errors, $indent+1);
      }
      
      $output .= str_repeat("\t", $indent) . "</div>\n";
      return $output;
   }
   
   protected static function printErrorForField($fieldName, $errors, $indent) {
      $output = "";
      foreach ($errors as $error) {
         $output .= str_repeat("\t", $indent) . "<p>{$fieldName}: {$error}</p>\n";
      }
      return $output;
   }
}

class FormElement {
   static protected function openSelectElement($label, $nameAndID, $indent) {
      $output  = str_repeat("\t", $indent) . "<label for=\"{$nameAndID}\">{$label}:</label>\n";
      $output .= str_repeat("\t", $indent) . "<select id=\"{$nameAndID}\" name=\"{$nameAndID}\">\n";
      return $output;
   }

   static protected function openSelectElementArr($nameAndID, $indent) {
      $output = str_repeat("\t", $indent) . "<select id=\"{$nameAndID}\" name=\"{$nameAndID}[]\">\n";
      return $output;
   }

   static protected function closeSelectElement($indent) {
      $output  = str_repeat("\t", $indent) . "</select>\n";
      return $output;
   }
}

class Municipality extends FormElement {
   /*
    * Ucitaj sve opstine iz baze.
    * @return msqli $result object
    */
   static protected function loadAll() {
      $select = new Select();
      $select->what(array('id', 'naziv'));
      $select->from('municipality');
      $result = $select->execute();
      return $result;
   }
   
   static public function make($label, $nameAndID, $value, $indent) {
      $output  = self::openSelectElement($label, $nameAndID, $indent);
      
      $rows = self::loadAll();
      while($row = $rows->fetch_assoc()) {
         $output .= str_repeat("\t", $indent+1);
         $output .= "<option value=\"{$row['id']}\" " . ($value === (int)$row['id'] ? "selected" : "");
         $output .= ">{$row['naziv']}</option>\n";
      }

      $output .= self::closeSelectElement($indent);
      return $output;
   }
   
   static public function getName($id) {
      $select = new Select(); $select->what(array('naziv'));
      $select->from('municipality');
      $select->condition("id = ?", array($id));
      $result = $select->execute();
      $row = $result->fetch_assoc();
      if($row) {
         return $row['naziv'];
      } else {
         trigger_error("Municipality::getName(): $id not found.");
      }
   }
}

class StatusFormElement extends FormElement {
   public static function make($label, $nameAndID, $value, $indent) {
      $output  = self::openSelectElement($label, $nameAndID, $indent);
      $output .= self::core($value, $indent);
      $output .= self::closeSelectElement($indent);
      return $output;
   }
   
   public static function core($value, $indent) {
      $output  = "";
      $output .= str_repeat("\t", $indent+1) . "<option value=\"Aktivan\" ";
      $output .= ($value === "Aktivan" ? "selected" : "") . ">Активан</option>\n";      
      $output .= str_repeat("\t", $indent+1) . "<option value=\"Pasivan\" ";
      $output .= ($value === "Pasivan" ? "selected" : "") . ">Пасиван</option>\n";      
      return $output;
   }

   public static function getName($id) {
      $desc = array( 'Aktivan' => 'Активан', 'Pasivan' => 'Пасиван');
      return array_key_exists($id, $desc) ? $desc[$id] : "НИЈЕ ПРОНАЂЕН";
   }
}

class TipUgovorFormElement extends FormElement {
   public static function make($label, $nameAndID, $value, $indent) {
      $output  = self::openSelectElement($label, $nameAndID, $indent);
      $output .= self::core($value, $indent);
      $output .= self::closeSelectElement($indent);
      return $output;
   }
   
   public static function core($value, $indent) {
      $output  = "";
      $output .= str_repeat("\t", $indent+1) . "<option value=\"1\" ";
      $output .= ($value === 1 ? "selected" : "") . ">Краткорочни уговор</option>\n";
      $output .= str_repeat("\t", $indent+1) . "<option value=\"2\" ";
      $output .= ($value === 2 ? "selected" : "") . ">Дугорочни уговор</option>\n";      
      return $output;
   }

   public static function getName($id) {
      $desc = array( 1 => 'Краткорочни уговор', 2 => 'Дугорочни уговор');
      return array_key_exists($id, $desc) ? $desc[$id] : "НИЈЕ ПРОНАЂЕН";
   }
}

class PolFormElement extends FormElement {
   public static function make($label, $nameAndID, $value, $indent) {
      $output  = self::openSelectElement($label, $nameAndID, $indent);
      $output .= self::core($value, $indent);
      $output .= self::closeSelectElement($indent);
      return $output;
   }
   
   public static function core($value, $indent) {
      $output  = "";
      $output .= str_repeat("\t", $indent+1) . "<option value=\"m\" ";
      $output .= ($value === "m" ? "selected" : "") . ">Мушки</option>\n";      
      $output .= str_repeat("\t", $indent+1) . "<option value=\"f\" ";
      $output .= ($value === "f" ? "selected" : "") . ">Женски</option>\n";      
      return $output;
   }

   public static function getName($id) {
      $desc = array( 'm' => 'Мушки', 'f' => 'Женски');
      return array_key_exists($id, $desc) ? $desc[$id] : "НИЈЕ ПРОНАЂЕН";
   }
}

class VolonterFormElement extends FormElement {
   static public function make($label, $nameAndID, $value, $indent) {
      $output  = self::openSelectElement($label, $nameAndID, $indent);
      $output .= self::core($value, $indent);
      $output .= self::closeSelectElement($indent);
      return $output;
   }

   protected static function core($value, $indent) {
      $output  = "";
      $rows = VolonterDB::loadAll();
      
      foreach($rows as $volonter) {
         $output .= self::makeRow($volonter, $value, $indent+1);
      }
      return $output;
   }
   
   protected static function makeRow(Volonter $volonter, $value, $indent) {
      $id = $volonter->getValue('id');
      $ime = $volonter->getName();
      
      $output = str_repeat("\t", $indent+1);
      $output .= "<option value=\"{$id}\" " . ($value === $id ? "selected" : "") . ">{$ime}</option>\n";
      return $output;
   }

   public static function getName($volonterID) {
      $volonter = VolonterDB::load($volonterID);
      return $volonter->getName();
   }
}

class PacijentFormElement extends FormElement {
   static public function make($label, $nameAndID, $value, $indent) {
      $output  = self::openSelectElement($label, $nameAndID, $indent);
      $output .= self::core($value, $indent);
      $output .= self::closeSelectElement($indent);
      return $output;
   }

   protected static function core($value, $indent) {
      $output  = "";
      $rows = PacijentDB::loadAll();
      
      foreach($rows as $pacijent) {
         $output .= self::makeRow($pacijent, $value, $indent+1);
      }
      return $output;
   }
   
   protected static function makeRow(Pacijent $pacijent, $value, $indent) {
      $id = $pacijent->getValue('id');
      $ime = $pacijent->getName();
      
      $output = str_repeat("\t", $indent+1);
      $output .= "<option value=\"{$id}\" " . ($value === $id ? "selected" : "") . ">{$ime}</option>\n";
      return $output;
   }

   public static function getName($pacijentID) {
      $pacijent = PacijentDB::load($pacijentID);
      return $pacijent->getName();
   }
}
