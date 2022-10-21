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

    ENDPOINT_ASYNC("GET", "/api/v1/users", GUserPoint)
    {
        
        ENDPOINT_ASYNC_INIT(GUserPoint)

            Action act() override
            {
                String tail = request->getPathTail();
                auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

                if ((queryParams.get("login") == nullptr) || (queryParams.get("password") == nullptr) || (queryParams.get("type") == nullptr))
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
        info->queryParams.add<oatpp::String>("login");
        info->queryParams["login"].required = true;

        info->queryParams.add<oatpp::String>("password");
        info->queryParams["password"].required = true;

        info->queryParams.add<oatpp::Int32>("type");
        info->queryParams["type"].required = true;

        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
    }

    ENDPOINT_ASYNC("PUT", "/api/v1/users", PUserPoint)
    {
        ENDPOINT_ASYNC_INIT(PUserPoint)

            Action act() override
        {
            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            if ((queryParams.get("login") == nullptr) || (queryParams.get("password") == nullptr))
                return _return(controller->createResponse(Status::CODE_400));

            bool registered = (*getFacadeMap())[ADMIN_CONNECT]->loginUser(queryParams.get("login"), queryParams.get("password"));

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
        info->queryParams.add<oatpp::String>("login");
        info->queryParams["login"].required = true;

        info->queryParams.add<oatpp::String>("password");
        info->queryParams["password"].required = true;


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
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->queryParams.add<oatpp::String>("userName");
        info->queryParams["userName"].required = true;


        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
        info->addResponse<Object<PlaylistsDTO>>(Status::CODE_200, "application/json");
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
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->queryParams["musid"].required = true;

        info->queryParams.add<oatpp::Int32>("musid");
        info->queryParams["musid"].required = true;


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
        info->headers.add<oatpp::String>("X-token");
        info->headers["X-token"].required = true;

        info->pathParams.add<oatpp::Int32>("id");
        info->queryParams["musid"].required = true;

        info->addResponse(Status::CODE_400).description = "BAD PARAMS";
        info->addResponse(Status::CODE_401).description = "LOGIN FAILED";
        info->addResponse<Object<MusicCompsDto>>(Status::CODE_200, "application/json");
    }

    static int incAndGetCurUserId()
    {
        return ++cur_user;
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
};

#include OATPP_CODEGEN_BEGIN(ApiController)