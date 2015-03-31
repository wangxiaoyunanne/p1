// Author: Xiaoyun Wang

#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include "permissions.h"

typedef struct Dir 
{
private:
    char*        name;
    int          mod_time;
    struct Dir** sub_dirs;
    struct Dir*  parent_dir;
    int          num_sub_dirs;
    Permission   permission;

public:
    Dir();
    ~Dir();

    void        createDirectory(const char* name, Dir* parent, short umask, int time);
    void        showPath();
    void        ls             (int argCount, const char* arguments[]);
    void        mkdir          (int argCount, const char* arguments[], short umask, int time);
    struct Dir* cd             (int argCount, const char* arguments[]);
} Directory;

#endif // DIRECTORY_H

