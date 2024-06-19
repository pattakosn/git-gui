#include "mygit.h"
#include <iostream>
#include <git2/errors.h>
#include <git2/global.h>
#include <git2/buffer.h>
#include <git2/repository.h>

void check_error(int err)
{
        if (err < 0) {
                const git_error *e = git_error_last();
                std::cerr << "\t\tError " << err << "/" << e->klass << ": " << e->message << "\n";
                exit(err);
        }
}

void deinit(void)
{
        std::cout << "\tlibgit2: Shutting down\n";
        int err = git_libgit2_shutdown();
        check_error(err);
        std::cout << "\tlibgit2: Shut down, times left: " << err << "\n";
}

void init()
{
        std::cout << "\tlibgit2: Initializing\n";
        int err = git_libgit2_init();
        check_error(err);
        std::cout << "\tlibgit2: Initialized with error: " << err << "\n";
}

void find_repo(std::string path, std::string max_path)
{
        git_buf root = {0};
        int error = git_repository_discover(&root, path.c_str(), 1, max_path.c_str());
        check_error(error);
        std::cout << "\tfound repo at: " << root.ptr << "\n";
        git_buf_dispose(&root); /* returned path data must be freed after use */
}
