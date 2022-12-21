#include "WebWrapper.h"

shared_ptr<map<Role, shared_ptr<Facade>>> ServerController::mfac = (shared_ptr<map<Role, shared_ptr<Facade>>>(new map<Role, shared_ptr<Facade>>));
shared_ptr<map<int, Role>> ServerController::mUsers = (shared_ptr<map<int, Role>>(new map<int, Role>()));
shared_ptr<JWT> ServerController::m_jwt = (shared_ptr<JWT>(new JWT()));
int ServerController::cur_user = 0;
int ServerController::response_count = 0;

void WebWrapper::work()
{
    oatpp::base::Environment::init();
    ServerSettings components; // Create scope Environment components
    /* create ApiControllers and add endpoints to router */

    auto router = components.httpRouter.getObject();

    router->addController(oatpp::swagger::AsyncController::createShared(ServerController::createShared()->getEndpoints()));
    router->addController(ServerController::createShared());

    ServerController::setFacadeMap(shared_ptr<map<Role, shared_ptr<Facade>>> (new map<Role, shared_ptr<Facade>>(
                                            {
                                                {USER_CONNECT, shared_ptr<Facade>(new Facade(config, "defuser", "123", USER_CONNECT))}, 
                                                {ADMIN_CONNECT, shared_ptr<Facade>(new Facade(config, "", PassConfig().getPass(), ADMIN_CONNECT))}
                                            })));

    /* create server */
    oatpp::network::Server server(components.serverConnectionProvider.getObject(),
        components.serverConnectionHandler.getObject());

    OATPP_LOGD("Server", "Running on port %s...", components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
    server.run();
}

