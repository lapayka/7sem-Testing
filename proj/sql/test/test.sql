create database test;

\connect test;

drop table UP;
drop table ArtistRequest;     
drop table PM;
drop table UC;
drop table Playlists;
drop table MusComps;
drop table Albums;
drop table Artists;
drop table Users;

create table if not exists Users(
	id serial,
	email varchar(30) primary key,
	password varchar(30)
);

create table if not exists ArtistRequest (
	id serial primary key,
	UsId varchar(30) REFERENCES Users(email),
	name VARCHAR(50),
	state varchar(10),
	
	UNIQUE(UsId)
);

create table if not exists Artists(
	name VARCHAR(50),
	email varchar(30) primary key,
	password varchar(30)
);

create table if not exists Albums(
	id serial primary key,
	name VARCHAR(50),
	ArId varchar(30) REFERENCES Artists (email)
);

create table if not exists MusComps(
	id serial primary key,
	name VARCHAR(50),
	audRate int,
	duration varchar(10),
	AlId int REFERENCES Albums (id)
);


create table if not exists Playlists(
	id serial primary key,
	name VARCHAR(50)
);


create table if not exists UP(
	id serial primary key,
	UsId varchar(30) REFERENCES Users(email),
	PlId int REFERENCES Playlists(id)
);

create table if not exists PM(
	id serial primary key,
	MuId int  REFERENCES MusComps(id),
	PlId int  REFERENCES Playlists(id)
);

create table if not exists UC(
	id serial primary key,
	UsId varchar(30) REFERENCES Users(email),
	MuId int REFERENCES MusComps (id),
	audRate int,
	
	UNIQUE(UsId, MuId)
);

insert into users(email, password) values 
('abc1@mail.ru', '1234'),
('abc12@mail.ru', '1234'),
('abc123@mail.ru', '1234'),
('abc1234@mail.ru', '1234'),
('abc12345@mail.ru', '1234'),
('abc123456@mail.ru', '1234'),
('abc1234567@mail.ru', '1234'),
('abc12345678@mail.ru', '1234');

insert into artists(name, email, password) values 
('vgg', 'abc1@mail.ru', '1234'),
('vgg2', 'abc12@mail.ru', '1234'),
('vgg3', 'abc123@mail.ru', '1234'),
('vgg4', 'abc1234@mail.ru', '1234');

insert into albums (name, arid) values 
('vga11', 'abc1@mail.ru'),
('vga12', 'abc1@mail.ru'),
('vga13', 'abc1@mail.ru'),
('vga11', 'abc12@mail.ru'),
('vga21', 'abc12@mail.ru'),
('vga31', 'abc123@mail.ru'),
('vga32', 'abc123@mail.ru'),
('vgg41', 'abc1234@mail.ru');

insert into muscomps (name, audrate, duration, alid) values 
('vgm111', 5, '3:40',  1),
('vgm112', 10, '2:40', 1),
('vgm113', 6, '5:40',  1),
('vgm121', 8, '3:40',  2),
('vgm122', 3, '2:40',  2),
('vgm123', 4, '5:40',  2),
('vgm131', 8, '3:40',  3),
('vgm132', 3, '2:40',  3),
('vgm133', 4, '5:40',  3),
('vgm134', 8, '3:40',  3),
('vgm135', 3, '2:40',  3),
('vgm136', 4, '5:40',  3),
('vgm211', 5, '3:40',  4),
('vgm212', 10, '2:40', 4),
('vgm213', 6, '5:40',  4),
('vgm311', 5, '3:40',  5),
('vgm312', 10, '2:40', 5),
('vgm313', 6, '5:40',  5),
('vgm321', 8, '3:40',  6),
('vgm322', 3, '2:40',  6),
('vgm323', 4, '5:40',  6),
('vgm411', 5, '3:40',  7),
('vgm412', 10, '2:40', 7),
('vgm413', 6, '5:40',  7);

insert into playlists (name) values 
('vgp1'),
('vgp2'),
('vgp3'),
('vgp4'),
('vgp5'),
('vgp6'),
('vgp7'),
('vgp8'),
('vgp9'),
('vgp10'),
('vgp11'),
('vgp12'),
('vgp13'),
('vgp14');

insert into UP (UsId, PlId) values
('abc1@mail.ru', 1),
('abc12@mail.ru', 2),
('abc123@mail.ru', 3),
('abc1234@mail.ru', 4),
('abc12345@mail.ru', 5),
('abc123456@mail.ru', 6),
('abc1234567@mail.ru', 7),
('abc12345678@mail.ru', 8),
('abc1@mail.ru', 9),
('abc12@mail.ru', 10),
('abc123@mail.ru', 11),
('abc1234@mail.ru', 12),
('abc12345@mail.ru', 13),
('abc123456@mail.ru', 14);

insert into UC (UsId, MuId, audRate) values
('abc1@mail.ru', 1, 10),
('abc12@mail.ru', 1, 3),
('abc12@mail.ru', 9, 5),
('abc12@mail.ru', 5, 3),
('abc123@mail.ru', 3, 6),
('abc1234@mail.ru', 4, 1),
('abc12345@mail.ru', 5, 2),
('abc123456@mail.ru', 6, 7),
('abc1234567@mail.ru', 7, 35),
('abc12345678@mail.ru', 8, 40),
('abc1@mail.ru', 9, 2),
('abc12@mail.ru', 10, 4),
('abc123@mail.ru', 11, 6),
('abc1234@mail.ru', 12, 8),
('abc12345@mail.ru', 13, 12),
('abc123456@mail.ru', 14, 78),
('abc1@mail.ru', 15, 2),
('abc12@mail.ru', 16, 4),
('abc123@mail.ru', 17, 6),
('abc1234@mail.ru', 18, 8),
('abc12345@mail.ru', 19, 12),
('abc123456@mail.ru', 20, 78),
('abc123456@mail.ru', 21, 7),
('abc1234567@mail.ru', 22, 35),
('abc12345678@mail.ru', 23, 40);

insert into PM (PlId, MuId) values
( 1, 1),
( 2, 2),
( 3, 3),
( 4, 4),
( 5, 5),
( 6, 6),
( 7, 7),
( 8, 8),
( 9, 9),
( 10, 10),
( 11, 11),
( 12, 12),
( 13, 13),
( 14, 14),
( 1, 15),
( 2, 16),
( 3, 17),
( 4, 18),
( 5, 19),
( 6, 20),
( 7, 21),
( 8, 22),
( 9, 23),
( 6, 1),
( 7, 2),
( 8, 3),
(9, 10),
(9, 1),
(13, 5);



CREATE OR REPLACE PROCEDURE PR_ADD_PLAYLIST(playlist_name VARCHAR(50), user_email varchar(30))
AS $$
DECLARE pl_id int4;
BEGIN
    INSERT INTO playlists(name)
    VALUES (playlist_name)
    RETURNING id INTO pl_id;
	
	INSERT INTO UP (UsId, PlId)
	VALUES (user_email, pl_id);
END
$$ LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION FN_ADD_ALBUM(al_name VARCHAR(50), aId varchar(50))
RETURNS TABLE (album_id int4)
AS $$
DECLARE pl_id int4;
BEGIN
    INSERT INTO albums(name, ArId)
    VALUES (al_name, aID)
    RETURNING id INTO pl_id;
	
	RETURN QUERY
        SELECT pl_id;
END
$$ LANGUAGE PLPGSQL;
