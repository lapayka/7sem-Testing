#include "PgPlaylistRepository.h"

void PgPlaylistRepository::create(const string& name, const string & user)
{
	string query("CALL PR_ADD_PLAYLIST('" + name + "', '" + user +"');");
	PGresult* res = PQexec(connPtr, query.c_str());
	PQclear(res);
}

void PgPlaylistRepository::del(int id)
{
	string query("BEGIN; "
				 "DELETE from PM where PlId = " + to_string(id) + "; "
				 "DELETE from UP where PlId = " + to_string(id) + "; "
				 "DELETE from PLAYLISTS where id = " + to_string(id) + "; "
				 "COMMIT;"
		);
	PGresult* res = PQexec(connPtr, query.c_str());
	PQclear(res);
}

void PgPlaylistRepository::aUpdate(const MusItem& item, int id)
{
	string query("insert into pm(PlId, MuId) values (" +  to_string(id) + ", " + to_string(item.id) + ");");
	PGresult* res = PQexec(connPtr, query.c_str());
	PQclear(res);
}
