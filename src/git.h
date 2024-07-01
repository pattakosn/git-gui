#ifndef _GIT_H
#define _GIT_H
#include <string>
void init(void);
void deinit(void);
void check_error(int err);
void find_repo(std::string path = ".", std::string max_path = "../../../");
int open_repo(char* path);
#endif