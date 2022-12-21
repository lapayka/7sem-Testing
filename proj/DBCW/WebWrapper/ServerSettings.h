#pragma once
#include <oatpp-swagger/ControllerPaths.hpp>
#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"

#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

#include "oatpp/web/server/interceptor/AllowCorsGlobal.hpp"


extern int port;
/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class ServerSettings {
public:
    
    /**
     * Create Async Executor
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)([] {
        return std::make_shared<oatpp::async::Executor>(
                9 /* Data-Processing threads */,
                2 /* I/O threads */,
                1 /* Timer threads */
        );
    }());

    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        /* non_blocking connections should be used with AsyncHttpConnectionHandler for AsyncIO */
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", v_uint16(port), oatpp::network::Address::IP_4});
    }());


   /* OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        OATPP_LOGD("oatpp::libressl::Config", "pem='%s'", CERT_PEM_PATH);
        OATPP_LOGD("oatpp::libressl::Config", "crt='%s'", CERT_CRT_PATH);
        auto config = oatpp::libressl::Config::createDefaultServerConfigShared(CERT_CRT_PATH,
                                                                               CERT_PEM_PATH);

        return oatpp::libressl::server::ConnectionProvider::createShared(config, {"0.0.0.0", 8000, oatpp::network::Address::IP_4});
    }()); */

    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component

        auto connectionHandler = oatpp::web::server::AsyncHttpConnectionHandler::createShared(router);
        connectionHandler->addRequestInterceptor(std::make_shared<oatpp::web::server::interceptor::AllowOptionsGlobal>());
        connectionHandler->addResponseInterceptor(std::make_shared<oatpp::web::server::interceptor::AllowCorsGlobal>());
        OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor); // get Async executor component
        return connectionHandler;
    }());

    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
        auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
        deserializerConfig->allowUnknownFields = false;
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
        return objectMapper;
    }());

/**
 *  General API docs info
 */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {

        oatpp::swagger::DocumentInfo::Builder builder;

        builder
                .setTitle("MusicComps system API")
                .setDescription("CRUD API")
                .setVersion("1.0")
                .setContactName("Lapaev Denis")
                .addServer("http://localhost:" + to_string(port), "server on localhost")
                .addServer("http://localhost:80", "nginx proxy");

        return builder.build();

    }());


/**
 *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
 */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
        // Make sure to specify correct full path to oatpp-swagger/res folder !!!
        return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::ControllerPaths>, controllerPaths)([] {
        auto paths = std::make_shared<oatpp::swagger::ControllerPaths>();
        paths->ui = "api/v1/swagger/";
        paths->uiResources = "api/v1/swagger/{filename}";
        paths->apiJson = "api/v1/api-docs/oas-3.0.0.json";
        return paths;
    }());


};