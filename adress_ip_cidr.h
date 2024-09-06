typedef struct ip
{
    int a,b,c,d;
    int SR;
    int b1[8],b2[8],b3[8],b4[8];
}ip;

    typedef struct MSR
    {
        int a,b,c,d;
    }MSR;
void give_ip(char *add_ip , char *SR);
void get_ip(char *add_ip ,ip *address ,char *SR);
void objet();
void verifie(ip address);
void bin(int a );
void decoupe(int *decoupage);
void A_class(ip address , int decoupage);
void B_class(ip address , int decoupage);
void C_class(ip address , int decoupage);

