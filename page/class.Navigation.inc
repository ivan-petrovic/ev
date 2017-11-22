<?php

require_once 'class.PageUtil.inc';

class Navigation implements RenderHTML {
   const MENU_VOLONTER = 110;
   const MENU_PACIJENT = 120;
   const MENU_POSETA = 130;
   
   // Aktivan menu u navigaciji.
   protected $activeMenu;
   
   /*
    * Konstruktor.
    */
   public function __construct($menu) {
      $this->activeMenu = $menu;
   }
   
   /**
    * Prikaz glavnog menija stranice.
    * @param string $aktivanMeni - ime menija koji je trenutno izabran.
    */
   public function renderHTML() {
      echo str_repeat("\t",3) . "<nav>\n";
      echo str_repeat("\t",4) . "<ul>\n";

      $menu_items = $this->getMenuDescription();
      $cnt = count($menu_items);
      for ($i = 0; $i < $cnt; $i += 3) {
         echo str_repeat("\t",5) . $this->menuItem($menu_items[$i], $menu_items[$i+1], $menu_items[$i+2]);
      }
      
      echo str_repeat("\t",4) . "</ul>\n";
      echo str_repeat("\t",3) . "</nav>\n";
   }

   protected function getMenuDescription() {
      return array(
          "volonter.php", self::MENU_VOLONTER, 'Волонтери',
          "pacijent.php", self::MENU_PACIJENT, 'Пацијенти',
          "poseta.php", self::MENU_POSETA, 'Посете'
      );
   }
   
   /**
    * Formiranje jedne meni stavke.
    * @param string $pageName - npr. firm.php
    * @param integer $menu
    * @param string $description - tekst u okviru linka
    */
   protected function menuItem($pageName, $menu, $description) {
      $output  = "";
      $output .= "<li><a href=\"". $pageName . "\"";
      $output .= ($this->activeMenu === $menu ? " class=\"menu-active\"" : "");
      $output .= ">" . $description . "</a></li>\n";
      return $output;
   }
}
