<?php

require_once 'util/class.Application.inc';
require_once 'page/class.Page.inc';
require_once 'page/class.Header.inc';
require_once 'page/class.Navigation.inc';
require_once 'page/class.Footer.inc';
require_once 'poseta/class.PosetaPageDispatcher.inc';
require_once 'volonter/class.VolonterPageDispatcher.inc';
require_once 'pacijent/class.PacijentPageDispatcher.inc';

$op = Application::getOp();
$pageContent = PosetaPageDispatcher::choosePage($op, Application::getPosetaID(),
        Application::getVolonterID(), Application::getPacijentID(), 3);
$css = PosetaPageDispatcher::getCSSFileName($op);
$pageContent->execute();

$p = new Page(
        new Header($css),
        new Navigation(Navigation::MENU_POSETA),
        $pageContent,
        new Footer());

$p->renderHTML();
