#ifndef _GIT_H
#define _GIT_H
// clang-format off
#include <string>
#include <git2/types.h>
// clang-format on
void init(void);
void deinit(void);
void check_error(int err);
std::string find_repo(std::string path = ".", std::string max_path = "../../../");
std::string repo_open(const char *path);
void repo_close();
int open_repo(char *path);
#endif