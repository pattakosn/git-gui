// https://libgit2.org/docs/guides/101-samples/
#include <iostream>
#include "mygit.h"

int main()
{
        std::cout << "\n\tgit gui 0.0.0\n";
        atexit(deinit);
        atexit(deinit);
        atexit(deinit);
        init();
        init();

        find_repo();
       
        return EXIT_SUCCESS;
}
