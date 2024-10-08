#include <stdio.h>
#include <stdlib.h>
#include "adress_ip_cidr.h"

/*----------------------------------------------------------------------------------------------------------------------------*/

void give_ip(char *add_ip , char *SR)
{
    printf("Entrer l'adresse ip :");
    scanf("%s",add_ip);
}


/*----------------------------------------------------------------------------------------------------------------------------*/


void objet()
{
    printf("Verifie si c'est un address ip\n\n");
}


/*----------------------------------------------------------------------------------------------------------------------------*/


void get_ip(char *add_ip ,ip *address ,char *SR)
{
    address->a = -1,address->b = -1,address->c = -1, address->d =-1;
    sscanf(add_ip,"%d.%d.%d.%d\n\n",&address->a,&address->b,&address->c,&address->d);
    sscanf(SR , "%d",&address->SR);
    while(address->a == -1 || address->b == -1  ||  address->c == -1 || address->d ==-1)
    {
        scanf("%s",add_ip);
        sscanf(add_ip,"%d.%d.%d.%d\n\n",&address->a,&address->b,&address->c,&address->d);
        sscanf(SR , "%d",&address->SR);
    }
    printf("%s\n\n",add_ip);
    if(address->a > 255 || address->b > 255 || address->c > 255 || address->d > 255 || address->a < 0 || address->b < 0 || address->c < 0 || address->d < 0)
    {
        printf("Ce n'est pas un adresse ip\n\n");
        exit(EXIT_SUCCESS);
    }

    printf("Affichage en binaire de l'adresse ip : \n");
    printf("_________________ ________________ ________________ _______________\n");
    bin(address->a);
    printf(".");
    bin(address->b);
    printf(".");
    bin(address->c);
    printf(".");
    bin(address->d);
    printf("\n");
    printf("`````````````````` ````````````````` ```````````````` ````````````````\n");

    int i;
    MSR msr;   
    char MSR1[20];
    int power[8];
    int temp  ;
    power[0] = 128 ;
    for(i = 1 ; i < 8 ; i++)
    {
        power[i] = power[i - 1]  / 2;
    }

    msr.a = -1,msr.b = -1,msr.c = -1,msr.d = -1 ;

        int a , b , c;
        do
        {
            a=0 , b=0 , c=0;
            printf("Saisissez le MSR : ");
            scanf("%s",MSR1);
            sscanf(MSR1, "%d.%d.%d.%d",&msr.a,&msr.b,&msr.c,&msr.d);            
            temp = 0 ;
            for(i=0 ; i < 8 ; i++)
            {
                temp += power[i] ;
                if(msr.a  < 255 &&  ((msr.b != temp && msr.b != 0 )|| (msr.c != temp && msr.c != 0 )|| (msr.d != 0 && msr.d != 0)))
                {
                    a++;
                }
                else if(msr.b  < 255 && ((msr.c != temp && msr.c != 0) || (msr.d != temp && msr.d != 0 )))
                {
                    b++;
                }                
                else if(msr.c  < 255 &&  (msr.d != temp && msr.d != 0) )
                {
                    c++;
                }
                printf("%d ",temp);
                printf("\n");
            }
        }while(a != 0 || b != 0 || c != 0);

    printf("Affichage en binaire du MSR : \n");
    printf("_________________ ________________ ________________ _______________\n");
    bin(msr.a);
    printf(".");
    bin(msr.b);
    printf(".");
    bin(msr.c);
    printf(".");
    bin(msr.d);
    printf("\n");
    printf("`````````````````` ````````````````` ```````````````` ````````````````\n");
}


/*----------------------------------------------------------------------------------------------------------------------------*/


void verifie(ip address)
{

    if(address.a >= 0 && address.a < 128)
    {
        A_class(address , decoupage);
    }

    else if(address.a >= 128 && address.a < 192)
    {
        B_class(address , decoupage);
    }

    else if(address.a >= 192 && address.a < 224)
    {
        C_class(address , decoupage);
    }
    

    else if(address.a >= 224 && address.a < 240)
    {
        printf("                              ___ \n");
        printf("L'adresse ip est de class D \n\n");
        printf("                              ___ \n");
        printf("Le masque de sous reseau est 255.255.255.255");
    }

    else if(address.a >= 240 && address.a < 255)
    {
        printf("                              ___ \n");
        printf("L'adresse ip est de class E \n\n");
        printf("                              ___ \n");
        printf("Le masque de sous reseau est 255.255.255.255");
    }
}
/*----------------------------------------------------------------------------------------------------------------------------*/

void bin(int a)
{
    int rest[8];
    int power[8];
    int temp = 0;
    int i;
    power[0] = 128 ;
    for(i = 1 ; i < 8 ; i++)
    {
        power[i] = power[i - 1]  / 2;
    }
    for(i = 0 ; i < 8 ; i++)
    {
        rest[i] = 0 ; 
    }
    for(i = 0 ; i < 8 ; i++)
    {
        temp += power[i] ;
            if(a > temp)
            {
                    rest[i] = 1;
            }
            else if(temp > a)
            {
                temp -= power[i] ;
            }
            else if (temp == a)
            {
                rest[i] = 1 ;
            }
    }

    if(a % 2 == 0)
    {
        rest[7] = 0 ;
    }
    
    else if(a % 2 == 1)
    {
        rest[7] = 1 ;
    }

    for(i = 0 ; i < 8 ; i++)
    {
        printf("%d ",rest[i]);
    }
}



/*----------------------------------------------------------------------------------------------------------------------------*/


void decoupe(int *decoupage)
{
    printf("Donner le nombre de decoupage\n");
    scanf("%d",decoupage);
}


/*----------------------------------------------------------------------------------------------------------------------------*/


void B_class(ip address , int decoupage)
{
                int i;
                decoupage = -1;
                address.SR = 16;
                printf("                              ___ \n");
                printf("L'adresse ip est de class  : | B |\n\n");
                printf("                                  __________\n");
                printf("Le masque de sous reseau est  : | 255.0.0.0 |");
                printf("                            _________ \n");
                printf("L'adresse du Reseau est  : |%d.%d.0.0|\n\n",address.a,address.b);
                printf("                               _____________ \n");
                printf("L'adresse du broadcast est  : |%d.%d.255.255|\n\n",address.a,address.b);
                printf("                                                             _______ \n");
                printf("Le nombre de machine disponible sur ce reseau est alors  : | 65.534 |\n\n");
                printf("Le CIDR(Classless Inter Domain Routing ) est %d.%d.%d.%d/%d \n",address.a,address.b,address.c,address.d,address.SR);

                decoupe(&decoupage);
                int sousReseau = 0;
                int broadcast = 0;
                    if(decoupage == 1 )
                    {
                        for(i=0 ; i < 2 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau+127);
                                printf("\n");
                        sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.128.0\n");                     
                    }

                    else if(decoupage == 2 )
                    {
                        for(i=0 ; i < 4 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau + 63);
                                printf("\n");
                                sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.192.0\n");                     
                        }

                    else if(decoupage == 3 )
                    {
                        for(i=0 ; i < 8 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau + 31);
                                printf("\n");
                                sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.224.0\n");                    
                        }

                    else if(decoupage == 4 )
                    {
                        printf("Les adresses reseaux apres decoupage est  :\n");
                        printf("\t | adresse  ip |\n\n");
                        for(i=0 ; i < 16 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau + 15);
                                printf("\n");
                                sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.240.0\n");
                    }
                    else if(decoupage == 5 )
                    {
                        printf("Les adresses reseaux apres decoupage est  :\n");
                        printf("\t | adresse  ip |\n\n");
                        for(i=0 ; i < 32 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau+7);
                                printf("\n");
                                sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.248.0\n");
                    }
                    else if(decoupage == 6 )
                    {
                        printf("Les adresses reseaux apres decoupage est  :\n");
                        printf("\t | adresse  ip |\n\n");
                        for(i=0 ; i < 64 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau + 3);
                                printf("\n");
                                sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.252.0\n");
                    }
                    else if(decoupage == 7 )
                    {
                        printf("Les adresses reseaux apres decoupage est  :\n");
                        printf("\t | adresse  ip |\n\n");
                        for(i=0 ; i < 128 ; i++)
                        {
                                printf("\t | sous-reseau |: %d.%d.%d.0 \n",address.a,address.b,sousReseau);
                                printf("\t ---------------\n");                  
                                printf("\t | broadcast   |: %d.%d.%d.0 \n\n",address.a,address.b,broadcast = sousReseau + 1);
                                printf("\n");
                                sousReseau = broadcast + 1 ;
                        }
                        printf("On a donnee  %d-bits au reseaux\n",decoupage);
                        printf("Le masque de sous-reseau est : 255.255.253.0\n");
                    }
}


/*----------------------------------------------------------------------------------------------------------------------------*/



void C_class(ip address , int decoupage)
{
    int i;
    address.SR = 24;
    printf("                              ___ \n");
    printf("L'adresse ip est de class  : | C |\n\n");
    printf("                            _______________\n");
    printf("Le masque de reseau est  : | 255.255.255.0 |\n");
    printf("                            ____________ \n");
    printf("L'adresse du Reseau est  : | %d.%d.%d.0 |\n\n",address.a,address.b,address.c);
    printf("                               ______________ \n");
    printf("L'adresse du broadcast est  : | %d.%d.%d.255 | \n\n",address.a,address.b,address.c);
    printf("                                                           ___ \n");
    printf("Le nombre de machine disponible sur ce reseau est alors : |254|\n\n");
    printf("Le CIDR(Classless Inter Domain Routing ) est %d.%d.%d.%d/%d \n",address.a,address.b,address.c,address.d,address.SR);

    decoupe(&decoupage);
    int sousReseau = 0;
    int broadcast = 0;
        if(decoupage == 1 )
        {
            for(i=0 ; i < 2 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau+127);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.128\n");                     
        }

        else if(decoupage == 2 )
        {
            for(i=0 ; i < 4 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau + 63);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.192\n");                     
            }

        else if(decoupage == 3 )
        {
            for(i=0 ; i < 8 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau + 31);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.224\n");                    
            }

        else if(decoupage == 4 )
        {
            printf("Les adresses reseaux apres decoupage est  :\n");
            printf("\t | adresse  ip |\n\n");
            for(i=0 ; i < 16 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau + 15);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.240\n");
        }
        else if(decoupage == 5 )
        {
            printf("Les adresses reseaux apres decoupage est  :\n");
            printf("\t | adresse  ip |\n\n");
            for(i=0 ; i < 32 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau + 7);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.248\n");
        }
        else if(decoupage == 6 )
        {
            printf("Les adresses reseaux apres decoupage est  :\n");
            printf("\t | adresse  ip |\n\n");
            for(i=0 ; i < 64 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau + 3);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.252\n");
        }   
        else if(decoupage == 7 )
        {
            printf("Les adresses reseaux apres decoupage est  :\n");
            printf("\t | adresse  ip |\n\n");
            for(i=0 ; i < 128 ; i++)
            {
                    printf("\t | sous-reseau |: %d.%d.%d.%d \n",address.a,address.b,address.c,sousReseau);
                    printf("\t ---------------\n");                  
                    printf("\t | broadcast   |: %d.%d.%d.%d \n\n",address.a,address.b,address.c,broadcast = sousReseau + 1);
                    printf("\n");
                        sousReseau = broadcast + 1 ;
            }
            printf("On a donnee  %d-bits au reseaux\n",decoupage);
            printf("Le masque de sous-reseau est : 255.255.255.253\n");
        }

}

void A_class(ip address , int decoupage)
{

    int i;
    if(address.a >= 0 && address.a < 128)
    {
        address.SR = 8;
        printf("                              ___ \n");
        printf("L'adresse ip est de class  : | A | \n\n");
        printf("                                 ___________\n");
        printf("Le masque de sous reseau est  : | 255.0.0.0 |\n\n");
        printf("                           _________ \n");
        printf("L'adresse du Reseau est : |%d.0.0.0 |\n\n",address.a);
        printf("                               ________________ \n");
        printf("L'adresse du broadcast est  : | %d.255.255.255 |\n\n",address.a);
        printf("                                                            ____________\n");
        printf("Le nombre de machine disponible sur ce reseau est alors  : | 16.777.214 |\n\n");
        printf("Le CIDR(Classless Inter Domain Routing ) est %d.%d.%d.%d/%d \n",address.a,address.b,address.c,address.d,address.SR);

        decoupe(&decoupage);
        int sousReseau = 0;
        int broadcast = 0;
            if(decoupage == 1 )
            {
                for(i=0 ; i < 2 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 127);
                        sousReseau = broadcast + 1 ;
                }
                    printf("\n");
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.128.0.0\n");                     
            }

            else if(decoupage == 2 )
            {
                for(i=0 ; i < 4 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 63);
                        sousReseau = broadcast + 1 ;
                }
                    printf("\n");
                
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.192.0.0\n");                     
                }

            else if(decoupage == 3 )
            {
                for(i=0 ; i < 8 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 31);
                        sousReseau = broadcast + 1 ;
                }
                    printf("\n");
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.224.0.0\n");                    
            }

            else if(decoupage == 4 )
            {
                printf("Les adresses reseaux apres decoupage est  :\n");
                printf("\t | adresse  ip |\n\n");
                for(i=0 ; i < 16 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 15);
                        sousReseau = broadcast + 1 ;
                    printf("\n");
                }
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.240.0.0\n");
            }
            else if(decoupage == 5 )
            {
                printf("Les adresses reseaux apres decoupage est  :\n");
                printf("\t | adresse  ip |\n\n");
                for(i=0 ; i < 32 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 7);
                        sousReseau = broadcast + 1 ;
                    printf("\n");
                }
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.248.0.0\n");
            }
            else if(decoupage == 6 )
            {
                printf("Les adresses reseaux apres decoupage est  :\n");
                printf("\t | adresse  ip |\n\n");
                for(i=0 ; i < 64 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 3);
                        sousReseau = broadcast + 1 ;
                        printf("\n");
                }
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.252.0.0\n");
            }   
            else if(decoupage == 7 )
            {
                printf("Les adresses reseaux apres decoupage est  :\n");
                printf("\t | adresse  ip |\n\n");
                for(i=0 ; i < 128 ; i++)
                {
                        printf("\t | sous-reseau |: %d.%d.0.0 \n",address.a,sousReseau);
                        printf("\t ---------------\n");                  
                        printf("\t | broadcast   |: %d.%d.0.0 \n\n",address.a,broadcast = sousReseau + 1);
                        sousReseau = broadcast + 1 ;
                    printf("\n");
                }
                printf("On a donnee  %d-bits au reseaux\n",decoupage);
                printf("Le masque de sous-reseau est : 255.253.0.0\n");
                    }
    }
}
