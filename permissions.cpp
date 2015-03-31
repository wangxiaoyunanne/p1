// Author: Xiaoyun Wang

#include "permissions.h"

Perm::Perm()
{
}

Perm::~Perm()
{
}

void Perm::get_str(char* prem_str)
{
    if ((oct_perm & 4) ==0) prem_str[0]='-'; else prem_str[0]='r';
    if ((oct_perm & 2) ==0) prem_str[1]='-'; else prem_str[1]='w';
    if ((oct_perm & 1) ==0) prem_str[2]='-'; else prem_str[2]='x';
}

