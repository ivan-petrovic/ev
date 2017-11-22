# Napravi tabelu volontera

DROP TABLE IF EXISTS volonter;

CREATE TABLE volonter (
   id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
   ime     VARCHAR(60) NOT NULL,
   prezime VARCHAR(60) NOT NULL,
   jmbg CHAR(13) NOT NULL DEFAULT '',
   adresa VARCHAR(100) NOT NULL DEFAULT '',
   mesto VARCHAR(60) NOT NULL DEFAULT '',
   opstinaID MEDIUMINT UNSIGNED NOT NULL DEFAULT 0,
   drzavljanstvo VARCHAR(60) NOT NULL DEFAULT '',
   telefon VARCHAR(40) NOT NULL DEFAULT '',
   datumRodjenja DATE,
   pol ENUM ('m', 'f') NOT NULL DEFAULT 'm',
   tipUgovora TINYINT NOT NULL DEFAULT 1,
   datumPocetka DATE,
   datumIsteka DATE,
   status ENUM ('Aktivan', 'Pasivan', 'Obrisan') NOT NULL DEFAULT 'Aktivan',
   opis TEXT,
   PRIMARY KEY (id)
);
