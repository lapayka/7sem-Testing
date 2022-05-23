\copy Users(email, password) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy MusComps(name, AlId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy Artists(name) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy Albums(name, arId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy Playlists(id, name) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy UP(UsId, PlId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy PM(MuId, PlId) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
\copy UC(UsId, MuId, audRate) from 'C:\Users\Denis\Desktop\3sem-DBCW\proj\sql\create\data' delimiter ':' csv;
