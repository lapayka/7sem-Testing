#include "Facade.h"

vector<MusItem> Facade::getMusicByAlbum(const string& AlbumName)
{
    vector<MusItem> res;

    std::vector<int> ids = repos.albRepPtr->getAlbumsByName(AlbumName);

    for (const auto& elem : ids)
    {
        vector<MusItem> tmp = getMusicByAlbum(elem);
        res.insert(res.end(), tmp.begin(), tmp.end());
    }

    return res;
}

vector<MusItem> Facade::getMusicByAlbum(int id)
{
    return repos.tabRepPtr->getMusByAlbum(id);
}

vector<MusItem> Facade::getMusicByArtist(const string& ArtistName)
{
    vector<MusItem> res;

    std::vector<std::string> ids = repos.artRepPtr->getArtistsByName(ArtistName);

    for (const auto& elem : ids)
    {
        vector<MusItem> tmp = repos.tabRepPtr->getMusByArtist(elem);
        res.insert(res.end(), tmp.begin(), tmp.end());
    }

    return res;
}
