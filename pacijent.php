<?php

require_once 'util/class.Application.inc';
require_once 'page/class.Page.inc';
require_once 'page/class.Header.inc';
require_once 'page/class.Navigation.inc';
require_once 'page/class.Footer.inc';
require_once 'pacijent/class.PacijentPageDispatcher.inc';
require_once 'poseta/class.PosetaPageDispatcher.inc';

$op = Application::getOp();
$pageContent = PacijentPageDispatcher::choosePage($op, Application::getPacijentID(), 3);
$css = PacijentPageDispatcher::getCSSFileName($op);
$pageContent->execute();

$p = new Page(
        new Header($css),
        new Navigation(Navigation::MENU_PACIJENT),
        $pageContent,
        new Footer());

$p->renderHTML();
