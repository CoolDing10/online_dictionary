#include<stdio.h>

union data{
    int i;
    char c;
};

int main(int argc, char const *argv[])
{
    union data d;
    // int *num ;
    int buf[124];
    printf("%ld\n", sizeof(buf));
    // printf("%d", *num);
    // *num = 100;
    // printf("%d", *num);
    // d.c = 'a';
    d.i = 65;
    printf("data.i = %d\n", d.i);
    printf("data.c = %c\n", d.c); 
    printf("%zu\n", sizeof(d));
    return 0;
}
