select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName
from MusComps m join Albums al on m.AlId = al.id 
						join Artists ar on al.ArId = ar.email
where ar.email = '';

select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName
from Playlists pl join PM pc on pl.id = pc.PlId
               join MusComps m on pc.MuId = m.id
               join Albums al on m.AlId = al.id
               join Artists ar on al.ArId = ar.email
               where pl.id = 0;
			   
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


CREATE OR REPLACE FUNCTION FN_FIND_CORRELATION(id1 varchar(30), id2 varchar(30))
RETURNS TABLE (correlation 	integer)
AS $$
BEGIN
RETURN QUERY
    with temp(mid1) as(
		(select uc.muid as mid1 from uc where uc.usid = id1)
		intersect
		(select uc.muid as mid1 from uc where uc.usid = id2))
		
	select case	  when sqrt(var_samp(t1.audrate) * (var_samp(t2.audrate))) = 0 then 0
				  when abs(covar_samp(t1.audrate, t2.audrate)) / sqrt(var_samp(t1.audrate) * (var_samp(t2.audrate))) = 1 then 1 
				  else 0 end as correlation
	from
		(select * 
		from temp join uc on temp.mid1 = uc.muid
		where uc.usid = id1) as t1
	join 
		(select * 
		from temp join uc on temp.mid1 = uc.muid
		where uc.usid = id2) as t2
	on t1.muid = t2.muid;
	
END
$$ LANGUAGE PLPGSQL;



select id1, id2 from (select u1.id as id1, u2.id as id2, FN_FIND_CORRELATION(u1.email,  u2.email) as correlation from users u1 join users u2 on u1.email > u2.email) as tmp where tmp.correlation = 1;
