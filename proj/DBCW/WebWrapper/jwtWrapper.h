#pragma once

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/core/Types.hpp"

#include <jwt-cpp/jwt.h>
#include "Facade.h"

class JWT {
public:

struct SignPayload : public oatpp::web::server::handler::AuthorizationObject 
{
  int userId;
  Role role;
};

struct Payload : public oatpp::web::server::handler::AuthorizationObject 
{
  int userId;
};

private:
  std::string m_secret;
  std::string m_issuer;
  jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> m_verifier;
public:

    JWT()
     :  m_secret("MaxerLox"),
        m_issuer("Denis"),
        m_verifier(jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256{ m_secret })
                            .with_issuer(m_issuer))
    {}

    std::string createToken(const std::shared_ptr<SignPayload>& payload);

    std::shared_ptr<Payload> readAndVerifyToken(const std::string& token);

};