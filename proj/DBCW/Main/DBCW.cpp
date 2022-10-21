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

int main(int argc, const char** argv) {
    ConfigFactory factory;
    Login log(factory.create("../../config.txt"));
    log.create(true)->work();

    return 0;
}