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