GRANT select on uc, artists, users, pm, up, albums, artists, muscomps, playlists to stock_user;
grant usage on playlists_id_seq, up_id_seq, uc_id_seq, pm_id_seq, artistrequest_id_seq to stock_user;
grant delete on pm, up, playlists to stock_user;
Grant update (audrate) on uc to stock_user;
Grant update (audrate) on muscomps to stock_user;
grant insert on uc, ArtistRequest, playlists, pm, up to stock_user;

Grant all on muscomps, albums to artist;

grant usage on albums_id_seq, muscomps_id_seq, muscomps_id_seq to artist;
grant select on artists to artist;