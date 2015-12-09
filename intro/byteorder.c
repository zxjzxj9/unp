// code to test the byte order of a system
// i.e. whether to be big or little endian

#include <stdio.h>
#define CPU_VENDOR_OS "x86_64-ubuntu-linux-gnu"

int main(int argc,char** argv)
{

    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0123;
    printf("%s: ",CPU_VENDOR_OS);
    if(sizeof(short) == 2)
    {
        if(un.c[0] == 0x01 && un.c[1] == 0x23)
        {
            printf("big-endian machine \n");
        }
        else if(un.c[0] == 0x23 && un.c[1] == 0x01)
        {
            printf("little-endian machine \n");
        }
        else printf("unknown machine \n");
    }
    else printf("sizeof short here is: %d",sizeof(short));

    return 0;
}
