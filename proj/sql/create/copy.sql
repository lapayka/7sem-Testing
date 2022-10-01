\copy Artists(email, password, name) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\artists.csv' delimiter ';' csv;
\copy Albums(arId, name) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\albums.csv' delimiter ';' csv;
\copy Users(email, password) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\Users.csv' delimiter ';' csv;
\copy MusComps(name, duration, audrate, AlId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\muscomps.csv' delimiter ';' csv;
\copy Playlists(name) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\playlists.csv' delimiter ';' csv;
\copy UP(UsId, PlId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\up.csv' delimiter ';' csv;
\copy UC(UsId, MuId, audRate) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\uc.csv' delimiter ';' csv;
\copy ArtistRequest(usId, name, state) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\requests.csv' delimiter ';' csv;
\copy PM(PlId, MuId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data\pm.csv' delimiter ';' csv;
