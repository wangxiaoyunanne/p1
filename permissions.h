// Author: Xiaoyun Wang
#ifndef PERMISSION_H
#define PERMISSION_H

typedef struct Perm
{
public:
    short oct_perm;
    Perm();
    ~Perm();

    void get_str(char *prem_str);
} Permission;

#endif // PERMISSION_H
