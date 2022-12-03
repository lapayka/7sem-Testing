#include "libpq-fe.h"

int PQntuples(const PGresult* res) {
	return res->_tup;
}

PGconn* PQconnectdb(const char* conninfo) {
	return nullptr;
}

ConnStatusType PQstatus(const PGconn* conn) {
	return ConnStatusType();
}

char* PQerrorMessage(const PGconn* conn) {
	return nullptr;
}

PGresult* PQexec(PGconn* conn, const char* query) {
	conn;
	return new PGresult(query);
}

int PQfnumber(const PGresult* res, const char* field_name) {
	res;
	if(strcmp(field_name, "id"))
		return 40;
	else if(strcmp(field_name, "name"))
		return 41;
	else if (strcmp(field_name, "duration"))
		return 42;
	else if (strcmp(field_name, "albumName"))
		return 43;
	else if (strcmp(field_name, "artistName"))
		return 44;
	
	return 45;
}

char* PQgetvalue(const PGresult* res, int tup_num, int field_num) {
	if (strstr(res->alb, "vga11")) {

		return res->execute();
	}
	if (strstr(res->alb, "6")) {
		if (tup_num == 0 && field_num == 41) {
			strcpy(res->_req, !six ? "vgm322" : "vgm322");
			return res->_req;
		}
		if (tup_num == 1 && field_num == 41) {
			strcpy(res->_req, !six ? "vgm323" : "vgm123");
			return res->_req;
		}
		if (tup_num == 2 && field_num == 41) {
			strcpy(res->_req, !six ? "vgm321" : "vgm111");
			return res->_req;
		}
	}
	if (strstr(res->alb, "abc123@mail.ru") && res->_tup == 6) {
		if (tup_num == 0 && field_num == 41) {
			strcpy(res->_req, "vgm322");
			return res->_req;
		}
		if (tup_num == 1 && field_num == 41) {
			strcpy(res->_req, "vgm323");
			return res->_req;
		}
		if (tup_num == 2 && field_num == 41) {
			strcpy(res->_req, "vgm411");
			return res->_req;
		}
		if (tup_num == 3 && field_num == 41) {
			strcpy(res->_req, "vgm413");
			return res->_req;
		}
		if (tup_num == 4 && field_num == 41) {
			strcpy(res->_req, "vgm321");
			return res->_req;
		}
		if (tup_num == 5 && field_num == 41) {
			strcpy(res->_req, "vgm412");
			return res->_req;
		}
	}
	if (strstr(res->alb, "abc123@mail.ru") && res->_tup == 2) {
		if (tup_num == 0 && field_num == 41) {
			strcpy(res->_req, "vgp3");
			return res->_req;
		}
		if (tup_num == 1 && field_num == 41) {
			strcpy(res->_req, "vgp11");
			return res->_req;
		}
	}
	if (strstr(res->alb, "abc123@mail.ru") && res->_tup == 1) {
		if (tup_num == 0 && field_num == 40) {
			strcpy(res->_req, "70");
			return res->_req;
		}
	}
	if (strstr(res->alb, "70") && res->_tup == 2) {
		if (tup_num == 0 && field_num == 40) {
			strcpy(res->_req, "1");
			return res->_req;
		}
		if (tup_num == 1 && field_num == 40) {
			strcpy(res->_req, "2");
			return res->_req;
		}
	}	
	
	return res->_req;
}

void PQclear(PGresult* res) {
	if(res)
		delete res;
}
