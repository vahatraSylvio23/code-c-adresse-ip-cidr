#include <stdio.h>
#include <stdlib.h>
#include "adress_ip_cidr.h"

int main()
{
    char add_ip[100];
    char SR[32];
    ip address;
    give_ip(add_ip , SR);
    objet();
    get_ip(add_ip ,&address ,SR);
    verifie(address);
    return 0;
}