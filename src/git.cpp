// clang-format off
#include "git.h"
#include <iostream>
#include <sstream>
#include <git2/errors.h>
#include <git2/global.h>
#include <git2/buffer.h>
#include <git2/repository.h>
// clang-format on

void check_error(int err) {
    if (err < 0) {
        const git_error *e = git_error_last();
        std::cerr << "\tError " << err << "/" << e->klass << ": " << e->message << "\n";
        exit(err);
    }
}

void init() {
    std::cout << "[libgit2] Initializing\n";
    int err = git_libgit2_init();
    check_error(err);
    std::cout << "[libgit2] Initialized with error: " << err << "\n";
}

void deinit(void) {
    std::cout << "[libgit2] Shutting down\n";
    int err = git_libgit2_shutdown();
    check_error(err);
    std::cout << "[libgit2] Shut down, times left: " << err << "\n";
}

void find_repo(std::string path, std::string max_path) {
    git_buf root = {};
    int error = git_repository_discover(&root, path.c_str(), 1, max_path.c_str());
    check_error(error);
    std::cout << "[libgit2] found repo at: " << root.ptr << "\n";
    git_buf_dispose(&root); /* returned path data must be freed after use */
}

static git_repository *repo{nullptr};
std::string repo_open(const char *path) {
    int error = git_repository_open(&repo, path);
    std::stringstream ss;
    if (error) {
        const git_error *e = git_error_last();
        ss << "Error, no repo found: " << error << " : " << e->klass << " : " << e->message;
        return ss.str();
    }
    return "";
}
void repo_close() {
    if (!repo) {
        git_repository_free(repo);
        repo = nullptr;
    }
}

int open_repo(char *path) {
    int error;
    git_repository *local_repo{nullptr};
    error = git_repository_open(&local_repo, path);
    if (error) {
        const git_error *e = git_error_last();
        std::cerr << "\tError " << error << "/" << e->klass << ": " << e->message << "\n";
    }
    git_repository_free(local_repo);
    return error;
}