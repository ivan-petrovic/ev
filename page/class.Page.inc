<?php

require_once 'class.PageUtil.inc';

/*
 * Klasa koja definise html stranicu.
 * Sadrzi header, navigaciju, sadrzaj strane (content) i futer.
 */
class Page implements RenderHTML {
   // Page header.
   protected $header;
   // Main page navigation.
   protected $navigation;
   // Content of the page.
   protected $content;
   // Page footer.
   protected $footer;

   /*
    * Konstruktor.
    */
   public function __construct(RenderHTML $h, RenderHTML $n, RenderHTML $c, RenderHTML $f ) {
      $this->header = $h;
      $this->navigation = $n;
      $this->content = $c;
      $this->footer = $f;
   }

   function renderHTML() {
      $this->header->renderHTML();
      $this->navigation->renderHTML();
      $this->content->renderHTML();
      $this->footer->renderHTML();
   }
}
