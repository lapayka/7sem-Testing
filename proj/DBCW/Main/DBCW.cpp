/*
 * src/test/examples/testlibpq.c
 *
 *
 * testlibpq.c
 *
 *      Test the C version of libpq, the PostgreSQL frontend library.
 */

#include "AdminInterface.h"
#include "ArtistInterface.h"
#include "UserInterface.h"
#include "Login.h"
#include "ConfigFactory.h"

#include <iostream>
#include "iostream"
using namespace std;

#include "jwt-cpp/jwt.h"

int port;

int main(int argc, const char** argv) {
    ConfigFactory factory;

    bool is_web = argc == 2;
    if (is_web)
        port = std::atoi(argv[1]);

    Login log(factory.create("../../config.txt"));
    log.create(is_web)->work();

    return 0;
}