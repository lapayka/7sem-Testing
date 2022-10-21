#include "jwtWrapper.h"

string JWT::createToken(const std::shared_ptr<JWT::SignPayload>& payload)
{
    auto token = jwt::create()
                            .set_issuer(m_issuer)
                            .set_type("JWS")
                            .set_payload_claim("userId", jwt::claim(std::to_string(payload->userId)))
                            .set_payload_claim("role", jwt::claim(std::to_string(payload->role)))
                            .sign(jwt::algorithm::hs256{m_secret});
    return token;
}


std::shared_ptr<JWT::Payload> JWT::readAndVerifyToken(const std::string& token)
{
    std::error_code ec;
    auto decoded = jwt::decode(token);
    m_verifier.verify(decoded);

    auto payload = std::make_shared<Payload>();
    payload->userId = std::atoi(std::string(decoded.get_payload_claims().at("userId").as_string()).c_str());

    return payload;
}