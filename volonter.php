<?php

require_once 'util/class.Application.inc';
require_once 'page/class.Page.inc';
require_once 'page/class.Header.inc';
require_once 'page/class.Navigation.inc';
require_once 'page/class.Footer.inc';
require_once 'volonter/class.VolonterPageDispatcher.inc';
require_once 'poseta/class.PosetaPageDispatcher.inc';

$op = Application::getOp();
$pageContent = VolonterPageDispatcher::choosePage($op, Application::getVolonterID(), 3);
$css = VolonterPageDispatcher::getCSSFileName($op);
$pageContent->execute();

$p = new Page(
        new Header($css),
        new Navigation(Navigation::MENU_VOLONTER),
        $pageContent,
        new Footer());

$p->renderHTML();
