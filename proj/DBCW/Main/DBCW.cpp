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
#include "ConConfig.h"


int main(int argc, char** argv)
{
    ConConfig conf;
    Login log(conf);
    log.create()->work();

    return 0;
}