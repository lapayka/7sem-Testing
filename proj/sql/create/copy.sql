\copy Artists(email, password, name) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/artists.csv' delimiter ';' csv;
\copy Albums(arId, name) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/albums.csv' delimiter ';' csv;
\copy Users(email, password) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/users.csv' delimiter ';' csv;
\copy MusComps(name, duration, audrate, AlId) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/muscomps.csv' delimiter ';' csv;
\copy Playlists(name) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/playlists.csv' delimiter ';' csv;
\copy UP(UsId, PlId) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/up.csv' delimiter ';' csv;
\copy UC(UsId, MuId, audRate) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/uc.csv' delimiter ';' csv;
\copy ArtistRequest(usId, name, state) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/requests.csv' delimiter ';' csv;
\copy PM(PlId, MuId) from '/home/lapayka/study/3cbdcw/proj/sql/create/data/pm.csv' delimiter ';' csv;
