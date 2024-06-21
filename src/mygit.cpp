#include "mygit.h"

#include <stdio.h>
#include <stdlib.h>
//#include <git2/global.h>
//#include <git2/errors.h>
//#include <git2/buffer.h>
//#include <git2/repository.h>

void check_error(int err);
void deinit(void);

void check_error(int err)
{
        if (err < 0) {
                const git_error *e = git_error_last();
                printf("Error %d/%d: %s\n", err, e->klass, e->message);
                exit(err);
        }
}

void deinit(void)
{
        std::cout << "libgit2: Shutting down\n";
        int error = git_libgit2_shutdown();
        check_error(error);
        std::cout << "libgit2: Shut down, times left: " << error << "\n";
}


        int error = git_libgit2_init();
        check_error(error);