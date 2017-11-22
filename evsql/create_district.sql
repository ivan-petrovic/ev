# Napravi tabelu okruga

DROP TABLE IF EXISTS district;

CREATE TABLE district (
   id SMALLINT UNSIGNED NOT NULL,
   naziv VARCHAR(70) NOT NULL,
   PRIMARY KEY (id)
);

INSERT INTO district (id, naziv) VALUES (0, 'Град Београд');                           
INSERT INTO district (id, naziv) VALUES (1, 'Севернобачки управни округ ');                
INSERT INTO district (id, naziv) VALUES (2, 'Средњобанатски управни округ');             
INSERT INTO district (id, naziv) VALUES (3, 'Севернобанатски управни округ ');           
INSERT INTO district (id, naziv) VALUES (4, 'Јужнобанатски управни округ');                 
INSERT INTO district (id, naziv) VALUES (5, 'Западнобачки управни округ');             
INSERT INTO district (id, naziv) VALUES (6, 'Јужнобачки управни округ');               
INSERT INTO district (id, naziv) VALUES (7, 'Сремски управни округ');                          
INSERT INTO district (id, naziv) VALUES (8, 'Мачвански управни округ');                       
INSERT INTO district (id, naziv) VALUES (9, 'Колубарски управни округ');                       
INSERT INTO district (id, naziv) VALUES (10, 'Подунавски управни округ');                       
INSERT INTO district (id, naziv) VALUES (11, 'Браничевски управни округ');                  
INSERT INTO district (id, naziv) VALUES (12, 'Шумадијски управни округ');                      
INSERT INTO district (id, naziv) VALUES (13, 'Поморавски управни округ');                     
INSERT INTO district (id, naziv) VALUES (14, 'Борски управни округ');                        
INSERT INTO district (id, naziv) VALUES (15, 'Зајечарски управни округ');                     
INSERT INTO district (id, naziv) VALUES (16, 'Златиборски управни округ');             
INSERT INTO district (id, naziv) VALUES (17, 'Моравички управни округ');                       
INSERT INTO district (id, naziv) VALUES (18, 'Рашки управни округ');                               
INSERT INTO district (id, naziv) VALUES (19, 'Расински управни округ');                         
INSERT INTO district (id, naziv) VALUES (20, 'Нишавски управни округ');                           
INSERT INTO district (id, naziv) VALUES (21, 'Топлички управни округ');                          
INSERT INTO district (id, naziv) VALUES (22, 'Пиротски управни округ');                         
INSERT INTO district (id, naziv) VALUES (23, 'Јабланички управни округ');                    
INSERT INTO district (id, naziv) VALUES (24, 'Пчињски управни округ');                          
INSERT INTO district (id, naziv) VALUES (25, 'Косовски управни округ');                          
INSERT INTO district (id, naziv) VALUES (26, 'Пећки управни округ');                           
INSERT INTO district (id, naziv) VALUES (27, 'Призренски управни округ');                      
INSERT INTO district (id, naziv) VALUES (28, 'Косовско-митровачки управни округ');     
INSERT INTO district (id, naziv) VALUES (29, 'Косовско-поморавски управни округ');     
