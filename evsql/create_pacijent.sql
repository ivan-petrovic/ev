# Napravi tabelu pacijenta

DROP TABLE IF EXISTS pacijent;

CREATE TABLE pacijent (
   id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
   ime VARCHAR(60) NOT NULL,
   prezime VARCHAR(60) NOT NULL,
   jmbg CHAR(13) NOT NULL DEFAULT '',
   adresa VARCHAR(100) NOT NULL DEFAULT '',
   mesto VARCHAR(60) NOT NULL DEFAULT '',
   opstinaID MEDIUMINT UNSIGNED NOT NULL DEFAULT 0,
   telefon VARCHAR(40) NOT NULL DEFAULT '',
   pol ENUM ('m', 'f') NOT NULL DEFAULT 'm',
   datumRodjenja DATE,
   datumSmrti DATE,
   status ENUM ('Aktivan', 'Pasivan', 'Obrisan') NOT NULL DEFAULT 'Aktivan',
   opis TEXT,
   PRIMARY KEY (id)
);
