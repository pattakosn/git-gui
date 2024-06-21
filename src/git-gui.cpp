// https://libgit2.org/docs/guides/101-samples/
#include <iostream>




int main()
{
        std::cout << "git gui\n";

        std::cout << "libgit2: Initializing\n";
        int error = git_libgit2_init();
        check_error(error);
        std::cout << "libgit2: Initialized with error: " << error << "\n";

        std::cout << "libgit2: Initializing again\n";
        error = git_libgit2_init();
        check_error(error);
        std::cout << "libgit2: Initialized again with error: " << error << "\n";

        
        git_buf root = {0};
        error = git_repository_discover(&root, ".", 1, "../../../");
        check_error(error);
        printf("found repo at: %s\n", root.ptr);
        git_buf_dispose(&root); /* returned path data must be freed after use */


        atexit(deinit);
       
        return EXIT_SUCCESS;
}
