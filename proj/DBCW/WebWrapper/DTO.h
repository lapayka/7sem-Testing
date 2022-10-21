#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "Facade.h"

#include "json/json.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MusicCompDto : public oatpp::DTO 
{
    DTO_INIT(MusicCompDto, DTO)
    DTO_FIELD(String, name);
    DTO_FIELD(Int64, id);
    DTO_FIELD(String, albumName);
    DTO_FIELD(String, artistName);
    DTO_FIELD(String, duration);
};

class MusicCompsDto : public oatpp::DTO 
{
    DTO_INIT(MusicCompsDto, DTO)

    DTO_FIELD(Vector<Object<MusicCompDto>>, MusicCompositions);
};

class PlaylistDTO : public oatpp::DTO
{
    DTO_INIT(PlaylistDTO, DTO)
    DTO_FIELD(String, name);
    DTO_FIELD(Int64, id);
};

class PlaylistsDTO : public oatpp::DTO 
{
    DTO_INIT(PlaylistsDTO, DTO)

    DTO_FIELD(Vector<Object<PlaylistDTO>>, Playlists);
};

class TokenDTO : public oatpp::DTO
{
    DTO_INIT(TokenDTO, DTO)

    DTO_FIELD(String, token);
};

#include OATPP_CODEGEN_END(DTO)

inline auto initTokenDTO(const string& token)
{
    auto tokenDTO = TokenDTO::createShared();

    tokenDTO->token = token;

    return tokenDTO;
}

inline auto initPlstDTO(const PlstItem &mit)
{
    auto plstDTO = PlaylistDTO::createShared();

    plstDTO->name = mit.name;
    plstDTO->id = mit.id;

    return  plstDTO;
}

inline auto initPlstsDTO(const vector<PlstItem> &mit)
{
    oatpp::Vector<oatpp::Object<PlaylistDTO>> playlistsVector ({});
    auto plstsDTO = PlaylistsDTO::createShared();
    for (const auto &elem : mit)
    {
        playlistsVector->push_back(initPlstDTO(elem));
    }

    plstsDTO->Playlists = playlistsVector;
    return  plstsDTO;
}

inline std::string createJSON(const vector<MusItem> &mit)
{
    Json::Value root;
    Json::Value arr = Json::arrayValue;
    for (const auto & elem : mit)
    {
        Json::Value data;
        data["name"] = elem.name;
        data["id"] = elem.id;
        data["albumName"] = elem.alName;
        data["artistName"] = elem.arName;
        data["duration"] = elem.duration;

        arr.append(data);
    }
    root["MusicCompositions"] = arr;
    Json::FastWriter writer;
    return writer.write(root);
}

inline std::string createJSON(const vector<PlstItem>& pit)
{
    Json::Value root;
    Json::Value arr = Json::arrayValue;
    for (const auto& elem : pit)
    {
        Json::Value data;
        data["name"] = elem.name;
        data["id"] = elem.id;

        arr.append(data);
    }
    root["Playlists"] = arr;
    Json::FastWriter writer;
    return writer.write(root);
}

inline auto initMusDTO(const MusItem &mit)
{
    auto musDTO = MusicCompDto::createShared();

    musDTO->name = mit.name;
    musDTO->id = mit.id;
    musDTO->albumName = mit.alName;
    musDTO->artistName = mit.arName;
    musDTO->duration = mit.duration;

    return  musDTO;
}

inline auto initMusicsDTO(const vector<MusItem> &mit)
{
    auto musDTO = MusicCompsDto::createShared();
    musDTO->MusicCompositions = {};
    for (const auto &elem : mit)
    {
        musDTO->MusicCompositions->push_back(initMusDTO(elem));
    }

    return  musDTO;
}