#pragma once
#include "C:\Users\Denis\Desktop\3sem-DBCW\proj\DBCW\DBCW\IConnect.h"
#include <sqlite3.h>
#include "LtAlRepo.h"
#include "LtArRepo.h"
#include "LtGraphRepo.h"
#include "LtMusRepo.h"
#include "LtPlstRepo.h"
#include "LtTbRepo.h"
#include "LtUsRepo.h"

class LiteConnect :
    public IConnect
{
private:
    sqlite3* connect;
public:
    LiteConnect(const string& email, const string& password)
    {    
        sqlite3_open("db.sql3", &connect);
        sqlite3_exec(connect, "create table if not exists Users(			id serial,			email varchar(30) primary key,			password varchar(30)		);		create table if not exists ArtistRequest(			id serial primary key,			UsId varchar(30) REFERENCES Users(email),			name VARCHAR(50),			state varchar(10),			UNIQUE(UsId)		);		create table if not exists Artists(			name VARCHAR(50),			email varchar(30) primary key,			password varchar(30)		);		create table if not exists Albums(			id serial primary key,			name VARCHAR(50),			ArId varchar(30) REFERENCES Artists(email)		);		create table if not exists MusComps(			id serial primary key,			name VARCHAR(50),			audRate int,			duration varchar(10),			AlId int REFERENCES Albums(id)		);		create table if not exists Playlists(			id serial primary key,			name VARCHAR(50)		);		create table if not exists UP(			id serial primary key,			UsId varchar(30) REFERENCES Users(email),			PlId int REFERENCES Playlists(id)		);		create table if not exists PM(			id serial primary key,			MuId int  REFERENCES MusComps(id),			PlId int  REFERENCES Playlists(id)		);		create table if not exists UC(			id serial primary key,			UsId varchar(30) REFERENCES Users(email),			MuId int REFERENCES MusComps(id),			audRate int,			UNIQUE(UsId, MuId)		); ", nullptr, nullptr, nullptr);
    }

    virtual Repositories getRepos() override
    {
        return Repositories(shared_ptr<IAlbumsRepository>(new LtAlRepo(connect)),
            shared_ptr<IMusRepository>(new LtMusRepo(connect)),
            shared_ptr<IPlaylistRepository>(new LtPlstRepo(connect)),
            shared_ptr<ITablesRepository>(new LtTbRepo(connect)),
            shared_ptr<IArtistRepository>(new LtArRepo(connect)),
            shared_ptr<IGraphRepo>(new LtGraphRepo(connect)),
            shared_ptr<IUserRepo>(new LtUsRepo(connect)));
    };

    virtual ~LiteConnect() { sqlite3_close(connect); };
};

