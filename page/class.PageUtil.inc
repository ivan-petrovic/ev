<?php

interface RenderHTML {
   function renderHTML();
}

class CommonPage {
   // Pocetna identacija pri ispisu HTML koda
   protected static $indent;

   protected static function openSection() {
      echo str_repeat("\t", self::$indent) . "<section>\n";
      echo str_repeat("\t", self::$indent + 1) . "<article>\n";
   }

   protected static function closeSection() {
      echo str_repeat("\t", self::$indent + 1) . "</article>\n";
      echo str_repeat("\t", self::$indent) . "</section>\n";
   }

   protected static function sectionHeader($str) {
      echo str_repeat("\t", self::$indent + 2) . "<h3>{$str}</h3>\n";
   }

   protected static function button($ref, $label) {
      $output  = str_repeat("\t", self::$indent+2);
      $output .= "<p class=\"button\"><a href=\"{$ref}\">{$label}</a></p>\n";
      return $output;
   }
   
   protected static function openTable($className, $addindent) {
      $output  = str_repeat("\t", self::$indent + $addindent);
      if(empty($className)) {
         $output .= "<table>\n";
      } else {
         $output .= "<table class=\"{$className}\">\n";
      }
      return $output;
   }
   
   protected static function closeTable($addindent) {
      return str_repeat("\t", self::$indent + $addindent) . "</table>\n";
   }

   protected function makeLink($ref, $label) {
      $output  = str_repeat("\t", self::$indent+4);
      $output .=  "<td><a href=\"{$ref}\">{$label}</a></td>\n";
      return $output;
   }
   
   protected function makeLinkNonPrint($ref, $label) {
      $output  = str_repeat("\t", self::$indent+4);
      $output .=  "<td class=\"non_print\"><a href=\"{$ref}\">{$label}</a></td>\n";
      return $output;
   }
}
