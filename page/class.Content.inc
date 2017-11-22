<?php

require_once 'class.PageUtil.inc';

/*
 * Ova klasa samo 'drzi mesto' pravom sadrzaju strane.
 * Sluzi prilikom postavljanja strukture aplikacije.
 * Radi testiranja.
 */
class Content implements RenderHTML {
   // Title for display.
   protected $title;
   // Simple message for display.
   protected $message;
   // Pocetna identacija pri ispisu HTML koda.
   protected $indent;

   /*
    * Konstruktor.
    */
   public function __construct($t, $m, $indent = 3) {
      $this->title = $t;
      $this->message = $m;
      $this->indent = $indent;
   }
   
   public function renderHTML() {
      echo str_repeat("\t", $this->indent) . "<section>\n";
      echo str_repeat("\t", $this->indent+1) . "<article>\n";
      echo str_repeat("\t",$this->indent+2) . "<h3>{$this->title}</h3>\n";
      echo str_repeat("\t",$this->indent+2) . "<p>{$this->message}</p>\n";
      echo str_repeat("\t", $this->indent+1) . "</article>\n";
      echo str_repeat("\t",$this->indent) . "</section>\n";
   }
}
