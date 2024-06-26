#ifndef _MYGIT_H
#define _MYGIT_H
#include<string>
void init(void);
void deinit(void);
void check_error(int err);
void find_repo(std::string path = ".", std::string max_path = "../../../");
#endif