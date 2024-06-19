// https://libgit2.org/docs/guides/101-samples/
#include <iostream>
#include <git2/global.h>

int main()
{
        std::cout << "git gui\n";

        std::cout << "libgit2: Initializing\n";
        git_libgit2_init();
        std::cout << "libgit2: Initializes\n";

        std::cout << "libgit2: Shutting down\n";
        git_libgit2_shutdown();
        std::cout << "libgit2: Shut down\n";
        
        return EXIT_SUCCESS;
}
