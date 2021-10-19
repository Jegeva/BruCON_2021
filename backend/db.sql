drop database if exists bruconbadges2021;
create user if not exists 'jg'@'localhost' IDENTIFIED BY 'cj9q6a2EpMF1+TXJ7c4-X';
create user if not exists 'bruconbadges_php'@'localhost' IDENTIFIED by '9T8sxEiMC+q3lFzJWIy-2';
create database if not exists bruconbadges2021;
use bruconbadges2021;
select 'd badges' ;
drop table if exists badges;
select 'c badges' ;
create table badges (
mac varchar(17),
username varchar(256),
isgame boolean,
time_enroll datetime not null,
            primary key (mac)
);
insert into badges values ('0','placeholder',0,NOW());

GRANT ALL PRIVILEGES ON bruconbadges2021.*         TO 'jg'@'localhost' ;
GRANT SELECT on bruconbadges2021.*                 TO 'bruconbadges_php'@'localhost' ;
GRANT INSERT on bruconbadges2021.badges            TO 'bruconbadges_php'@'localhost';
GRANT UPDATE on bruconbadges2021.badges            TO 'bruconbadges_php'@'localhost';
GRANT INSERT on bruconbadges2021.beeromons         TO 'bruconbadges_php'@'localhost';
GRANT UPDATE on bruconbadges2021.beeromons         TO 'bruconbadges_php'@'localhost';
GRANT INSERT on bruconbadges2021.fights            TO 'bruconbadges_php'@'localhost';
GRANT DELETE on bruconbadges2021.fights            TO 'bruconbadges_php'@'localhost';
GRANT INSERT on bruconbadges2021.fight_history     TO 'bruconbadges_php'@'localhost';
GRANT UPDATE (username) on bruconbadges2021.badges TO 'bruconbadges_php'@'localhost';
