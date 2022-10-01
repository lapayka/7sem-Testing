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
#include "../Main/ConfigFactory.h"


int main(int argc, char** argv)
{
    ConfigFactory factory;
    Login log(factory.create("../config.txt"));
    log.create()->work();

    return 0;
}