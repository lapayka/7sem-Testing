#include "WebWrapper.h"
#include "Facade.h"
#include "PasCon.h"
#include "Token.h"
#include "jwtWrapper.h"

#include "DTO.h"

#include <map>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#define CREATE_RESULT_WITH_CORS(json)  \
auto response = controller->createResponse(Status::CODE_200, json); \
response->putHeaderIfNotExists("Access-Control-Allow-Methods", "GET, POST, PUT, OPTIONS, DELETE");\
response->putHeaderIfNotExists("Access-Control-Allow-Origin", "*");\
response->putHeaderIfNotExists("Access-Control-Max-Age", "1728000");\

#include OATPP_CODEGEN_BEGIN(ApiController)

class ServerController : public oatpp::web::server::api::ApiController
{
protected:
    ServerController(std::shared_ptr<ObjectMapper> objectMapper)
        :
        oatpp::web::server::api::ApiController(objectMapper)
    {}

public:
    static shared_ptr<ServerController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) 
    {
        return shared_ptr<ServerController>(new ServerController(objectMapper));
    }

    ENDPOINT_ASYNC("POST", "/api/v1/singin", GUserPoint)
    {
        
        ENDPOINT_ASYNC_INIT(GUserPoint)

            Action act() override
            {
                OATPP_LOGD("Server", "Response count: %d...", incAndGetCurRespCount());
                String tail = request->getPathTail();
                auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

                if ((request->getHeader("login") == nullptr) || (request->getHeader("password") == nullptr) || (queryParams.get("type") == nullptr))
                    return _return(controller->createResponse(Status::CODE_400));

                auto payload = shared_ptr<JWT::SignPayload>(new JWT::SignPayload);
                payload->role = Role(std::atoi(std::string(queryParams.get("type")).c_str()));
                payload->userId = incAndGetCurUserId();
                (*getUsersMap())[payload->userId] = payload->role;
                std::string token = m_jwt->createToken(payload);

                return _return(controller->createResponse(Status::CODE_200, token));
            }
    };

    ENDPOINT_INFO(GUserPoint)
    {
        info->tags.push_back("Login");
        info->headers.add<oatpp::String>("login");
        info->headers["login"].required = true;

        info->headers.add<oatpp::String>("password");
        info->headers["password"].required = true;

        info->queryParams.add<oatpp::Int32>("type");
        info->queryParams["type"].required = true;

        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
    }

    ENDPOINT_ASYNC("POST", "/api/v1/singup", PUserPoint)
    {
        ENDPOINT_ASYNC_INIT(PUserPoint)

            Action act() override
        {
            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            if ((request->getHeader("login") == nullptr) || (request->getHeader("password") == nullptr))
                return _return(controller->createResponse(Status::CODE_400));

            bool registered = (*getFacadeMap())[ADMIN_CONNECT]->loginUser(request->getHeader("login"), request->getHeader("password"));

            auto payload = shared_ptr<JWT::SignPayload>(new JWT::SignPayload);
            payload->role = USER_CONNECT;
            payload->userId = incAndGetCurUserId();
            (*getUsersMap())[payload->userId] = payload->role;
            std::string token = m_jwt->createToken(payload);
            return _return(controller->createResponse(Status::CODE_200, token));
        }
    };

    ENDPOINT_INFO(PUserPoint)
    {
        info->tags.push_back("Login");
        info->headers.add<oatpp::String>("login");
        info->headers["login"].required = true;

        info->headers.add<oatpp::String>("password");
        info->headers["password"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
    }


    ENDPOINT_ASYNC("GET", "/api/v1/muscomps", MusPoint ) 
    {
    ENDPOINT_ASYNC_INIT(MusPoint)

        Action act() override 
        {
            if (request->getHeader("X-token") == nullptr)
                return _return(controller->createResponse(Status::CODE_403));

            std::string token = string(request->getHeader("X-token"));

            cout << token << std::endl;

            auto it = getUsersMap()->end();

            if ( (it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
            {
                return _return(controller->createResponse(Status::CODE_401));
            }

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            if ((queryParams.get("selfName") != nullptr) + (queryParams.get("albumName") != nullptr) + (queryParams.get("artistName") != nullptr) !=1 )
                return _return(controller->createResponse(Status::CODE_400));

            
            if (queryParams.get("selfName") != nullptr)   
            {
                auto ret = createJSON((*getFacadeMap())[it->second]->getMusicByName(queryParams.get("selfName")));
                
                return _return(controller->createResponse(Status::CODE_200, ret.c_str()));
            }

            if (queryParams.get("albumName") != nullptr)
            {
                auto ret = createJSON((*getFacadeMap())[it->second]->getMusicByAlbum(queryParams.get("albumName")));

                return _return(controller->createResponse(Status::CODE_200, ret.c_str()));
            }

            if (queryParams.get("artistName") != nullptr)
            {
                auto ret = createJSON((*getFacadeMap())[it->second]->getMusicByArtist(queryParams.get("artistName")));

                return _return(controller->createResponse(Status::CODE_200, ret.c_str()));
            }

            return _return(controller->createResponse(Status::CODE_400));
        }


    };

    ENDPOINT_INFO(MusPoint)
    {
        info->tags.push_back("MusComps");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->queryParams.add<oatpp::String>("selfName");
        info->queryParams["selfName"].description = "Only one param required";
        info->queryParams["selfName"].required = false;

        info->queryParams.add<oatpp::String>("albumName");
        info->queryParams["albumName"].required = false;

        info->queryParams.add<oatpp::String>("artistName");
        info->queryParams["artistName"].required = false;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
        info->addResponse<Object<MusicCompsDto>>(Status::CODE_200, "application/json");
    }

    ENDPOINT_ASYNC("GET", "/api/v1/playlists", plstPoint)
    {
        ENDPOINT_ASYNC_INIT(plstPoint)

            Action act() override
            {
                std::string token = request->getHeader("X-token");

                auto it = getUsersMap()->end();

                if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
                {
                    return _return(controller->createResponse(Status::CODE_401));
                }

                String tail = request->getPathTail();
                auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

                //PlaylistsDTO pDTO = initPlstsDTO((*getFacadeMap())[it->second]->getPlstByUser(std::string(queryParams.get("username"))));
                

                if (queryParams.get("userName") != nullptr)
                {
                    std::string tmp = std::string(queryParams.get("userName"));
                    auto iter = tmp.find("%40");
                    tmp.replace(iter, 3, "@");
                    return _return(controller->createResponse(
                        Status::CODE_200,
                        createJSON((*getFacadeMap())[it->second]->getPlstByUser(tmp))));
                }
                    

                return _return(controller->createResponse(Status::CODE_400));
            }


    };

    ENDPOINT_INFO(plstPoint)
    {
        info->tags.push_back("Playlists");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->queryParams.add<oatpp::String>("userName");
        info->queryParams["userName"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
        info->addResponse<Object<PlaylistsDTO>>(Status::CODE_200, "application/json");
    }

     ENDPOINT_ASYNC("PATCH", "/api/v1/playlists/{id}", patplstPoint)
    {
        ENDPOINT_ASYNC_INIT(patplstPoint)

            Action act() override
            {
                std::string token = request->getHeader("X-token");

                auto it = getUsersMap()->end();

                if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
                {
                    return _return(controller->createResponse(Status::CODE_401));
                }
                

                if (request->getPathVariable("id") != nullptr)
                {
                    int tmp = std::atoi(std::string(request->getPathVariable("id")).c_str());
                    std::string json = std::string(request->getHeader("musIds"));

                    Json::Value root;
                    Json::Reader reader;


                    reader.parse(json, root);

                    const Json::Value ids = root["musIds"];
                    vector<int> iids;

                    for (int i = 0; i < ids.size(); i++ )
                    {
                        auto jid = ids[i];
                        iids.push_back(std::atoi(std::string(jid.asString()).c_str()));
                    }

                    (*getFacadeMap())[it->second]->setPlstOrder(tmp, iids);


                    return _return(controller->createResponse(Status::CODE_200));
                }
                    

                return _return(controller->createResponse(Status::CODE_400));
            }


    };

    ENDPOINT_INFO(patplstPoint)
    {
        info->tags.push_back("Playlists");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->pathParams["id"].required = true;

        info->headers.add<oatpp::String>("musIds");
        info->headers["musIds"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
    }

    ENDPOINT_ASYNC("PUT", "/api/v1/playlists/{id}/muscomps/{musid}", pplstPoint)
    {
        ENDPOINT_ASYNC_INIT(pplstPoint)

            Action act() override
            {
                std::string token = request->getHeader("X-token");

                auto it = getUsersMap()->end();

                if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
                {
                    return _return(controller->createResponse(Status::CODE_401));
                }

                String tail = request->getPathTail();
                auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

                if (request->getPathVariable("id") != nullptr && request->getPathVariable("musid") != nullptr)
                {
                    (*getFacadeMap())[it->second]->updatePlaylist(
                                                        std::atoi(std::string(request->getPathVariable("id")).c_str()),
                                                        MusItem(std::atoi(std::string(request->getPathVariable("musid")).c_str()), string(), string(), string(), string()));
                    return _return(controller->createResponse(Status::CODE_200));
                        
                }

                return _return(controller->createResponse(Status::CODE_400));
            }


    };

    ENDPOINT_INFO(pplstPoint)
    {
        info->tags.push_back("Playlists/MusComps");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->pathParams["id"].required = true;

        info->pathParams.add<oatpp::Int32>("musid");
        info->pathParams["musid"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
        info->addResponse<Object<MusicCompDto>>(Status::CODE_200, "application/json");
    }

    ENDPOINT_ASYNC("GET", "/api/v1/playlists/{id}/muscomps", GplstPoint)
    {
        ENDPOINT_ASYNC_INIT(GplstPoint)

            Action act() override
            {
                std::string token = request->getHeader("X-token");

                auto it = getUsersMap()->end();

                if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
                {
                    return _return(controller->createResponse(Status::CODE_401));
                }

                auto id = request->getPathVariable("id");

                if (request->getPathVariable("id") != nullptr)
                    return _return(controller->createResponse(
                        Status::CODE_200,
                        createJSON((*getFacadeMap())[it->second]->getMusicByPlaylist(std::atoi((request->getPathVariable("id")->c_str()))))));

                return _return(controller->createResponse(Status::CODE_400));
            }


    };

    ENDPOINT_INFO(GplstPoint)
    {
        info->tags.push_back("Playlists/MusComps");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->pathParams["musid"].required = true;

        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
        info->addResponse<Object<MusicCompsDto>>(Status::CODE_200, "application/json");
    }

    ENDPOINT_ASYNC("DELETE", "api/v1/playlists/{id}/muscomps/{musid}", DplstPoint)
    {
        ENDPOINT_ASYNC_INIT(DplstPoint)

        Action act() override
        {
            std::string token = request->getHeader("X-token");

            auto it = getUsersMap()->end();

            if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
            {
                return _return(controller->createResponse(Status::CODE_401));
            }

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            if (request->getPathVariable("id") != nullptr && request->getPathVariable("musid") != nullptr)
            {
                (*getFacadeMap())[it->second]->deleteMusFromPlaylist(
                                                std::atoi(std::string(request->getPathVariable("musid")).c_str()), 
                                                std::atoi(std::string(request->getPathVariable("id")).c_str()));
                return _return(controller->createResponse(Status::CODE_200));
            }

            return _return(controller->createResponse(Status::CODE_400));
        }
    };

    ENDPOINT_INFO(DplstPoint)
    {
        info->tags.push_back("Playlists/MusComps");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->pathParams["id"].required = true;

        info->pathParams.add<oatpp::Int32>("musid");
        info->pathParams["musid"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
    }

    ENDPOINT_ASYNC("DELETE", "api/v1/playlists/{id}", DaplstPoint)
    {
        ENDPOINT_ASYNC_INIT(DaplstPoint)

        Action act() override
        {
            std::string token = request->getHeader("X-token");

            auto it = getUsersMap()->end();

            if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
            {
                return _return(controller->createResponse(Status::CODE_401));
            }

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            if (request->getPathVariable("id") != nullptr)
            {
                (*getFacadeMap())[it->second]->deletePlaylist(std::atoi(std::string(request->getPathVariable("id")).c_str()));
                return _return(controller->createResponse(Status::CODE_200));
            }

            return _return(controller->createResponse(Status::CODE_400));
        }
    };

    ENDPOINT_INFO(DaplstPoint)
    {
        info->tags.push_back("Playlists");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->pathParams["id"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
    }

    ENDPOINT_ASYNC("PUT", "api/v1/playlists", PpplstPoint)
    {
        ENDPOINT_ASYNC_INIT(PpplstPoint)

        Action act() override
        {
            std::string token = request->getHeader("X-token");

            auto it = getUsersMap()->end();

            if ((it = getUsersMap()->find(getJWT()->readAndVerifyToken(token)->userId)) == getUsersMap()->end())
            {
                return _return(controller->createResponse(Status::CODE_401));
            }

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            if (queryParams.get("userName") != nullptr && queryParams.get("plstName") != nullptr)
            {
                (*getFacadeMap())[it->second]->createPlaylist(std::string(queryParams.get("userName")), std::string(queryParams.get("plstName")));
                return _return(controller->createResponse(Status::CODE_200));
            }

            return _return(controller->createResponse(Status::CODE_400));
        }
    };

    ENDPOINT_INFO(PpplstPoint)
    {
        info->tags.push_back("Playlists");
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->queryParams.add<oatpp::String>("plstName");
        info->queryParams["plstName"].required = true;

        info->queryParams.add<oatpp::String>("userName");
        info->queryParams["userName"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
    }


    static int incAndGetCurUserId()
    {
        return ++cur_user;
    }
    static int incAndGetCurRespCount()
    {
        return ++response_count;
    }
    static void setUsersMap(const shared_ptr<map<int, Role>> & _mfac)
    {
        mUsers = _mfac;
    }
    static void setFacadeMap(const shared_ptr<map<Role, shared_ptr<Facade>>> & _mfac)
    {
        mfac = _mfac;
    }
    static void setJWT(const shared_ptr<JWT> & _mfac)
    {
        m_jwt = _mfac;
    }
    static shared_ptr<map<int, Role>> &getUsersMap()
    {
        return mUsers;
    }
    static shared_ptr<map<Role, shared_ptr<Facade>>> &getFacadeMap()
    {
        return mfac;
    }
    static shared_ptr<JWT> getJWT()
    {
        return m_jwt;
    }

public:
    static shared_ptr<map<Role, shared_ptr<Facade>>> mfac;
    static shared_ptr<map<int, Role>> mUsers;
    static shared_ptr<JWT> m_jwt;
    static int cur_user;
    static int response_count;
};

#include OATPP_CODEGEN_BEGIN(ApiController)