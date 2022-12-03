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

    ifstream input("test.txt");
    if (input.is_open())
    {
        std::ifstream in("TESTS/e2e.txt");
        //установим новый буфер, очистим буфер и вернем старый
        std::streambuf* buf = cin.rdbuf(in.rdbuf());
        //теперь cin читает из буфера файлового потока
        log.create()->work();
        //установим старый
        cin.rdbuf(buf);
    }
    else
        log.create()->work();

    

    return 0;
}