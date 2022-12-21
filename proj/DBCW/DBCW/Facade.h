#pragma once
#include<memory>
#include<iostream>
#include <string>
#include <vector>
#include "MusItem.h"
#include "IConnect.h"
#include "Config.h"

using namespace std;

class Facade
{
private:
	shared_ptr<IConnect> connect;
	Repositories repos;
public:
	Facade(shared_ptr<Config> config, const string& email, const string& pass, Role role)
		:
		connect(config->getConnectionMap()[role](email, pass)),
		repos(connect->getRepos())
	{
	}

	vector<MusItem> getMusicByName(const string& MusName) { return repos.musRepPtr->getMusByName(MusName); };
	vector<MusItem> getMusicByAlbum(const string &AlbumName);
	vector<MusItem> getMusicByAlbum(int id);

	vector<MusItem> getMusicByArtist(const string& ArtistName);
	vector<MusItem> getMusicByPlaylist(int id) { return repos.tabRepPtr->getMusByPlaylist(id); };

	vector<MusItem> getMusicByRegex(const string& name) { return repos.tabRepPtr->getMusByRegex(name); }

	vector<PlstItem> getPlstByUser(const string& id) { return repos.tabRepPtr->getPlaylistsByUser(id); }

	void createPlaylist(const string& userId, const string& name) { repos.plstRepPtr->create(name, userId); };
	void updatePlaylist(int id, const MusItem& item) {repos.plstRepPtr->aUpdate(item, id); }
	void deletePlaylist(int id) { repos.plstRepPtr->del(id); };
	void setPlstOrder(int id, const vector<int> & orders) { repos.plstRepPtr->setOrder(id, orders); }

	void deleteMusFromPlaylist(int mid, int pid) { repos.plstRepPtr->delCompFromPlst(mid, pid); }


	void createAlbum(const string& id, const string& name, const vector<MusItem>& items) { repos.albRepPtr->create(items, name, id); };
	void createArtist(const string& uId, const string& name)
	{
		std::pair<string, string> info = repos.usRepo->UserInfo(uId);
		repos.artRepPtr->createArtist(uId, info.second, name);
	};
	void createRequest(const string& uId, const string &name) { repos.artRepPtr->createRequest(uId, name); }
	vector<pair<string, string>> checkRequests() { return repos.artRepPtr->getAllRequests(); }

	void listenMusic(const MusItem& item, const string &uId) { repos.musRepPtr->update(uId, item.id); }
	void listenMusic(const vector<MusItem>& items, const string& uId) 
	{ 
		for (const auto& item : items) 
			this->listenMusic(item, uId); 
	};

	bool loginUser(const string& email, const string& password) { return repos.usRepo->login(email, password); }

	vector<std::pair<int, int>> getGraph() { return repos.grRepo->getGraph(); };
};

