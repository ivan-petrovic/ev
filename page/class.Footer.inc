<?php

require_once 'class.PageUtil.inc';

class Footer implements RenderHTML {
   /**
    * Prikaz futera stranice.
    */
   public function renderHTML() {
      echo str_repeat("\t",3) . "<footer>\n";
      echo str_repeat("\t",4) . "<p><small>&copy; Иван Петровић 2013 | Дизајн Роки</small></p>\n";
      echo str_repeat("\t",3) . "</footer>\n";
      echo str_repeat("\t",2) . "</div> <!-- end of page -->\n";
      echo str_repeat("\t",1) . "</body>\n";
      echo "</html>\n";
   }
}
