#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
// strsplit - split string in to array of char[] with separators
// Warning this function modifies src!
// Written by Tomasz Nowak
//
int strsplit(char *inp, char ***dst, char *sep) {
    char **arr;
    char *src;
    char *src_org;
    char *c;
    int n;
    
    char defsep[]=" \t\n\r\f";

    if(!sep)
        sep=defsep;

    src=calloc((strlen(inp) + 1), sizeof(char));
    strcpy(src, inp);
    src_org = src;
    n = 0;

    while (c = strpbrk(src, sep)) {
        while (c == src) {
            src++;
            c = strpbrk(src, sep);
        }

        if (c == NULL) 
            break;

        src = c + 1;
        n++;
    }

    int nelem = n + 1;
    arr = (char **)malloc(sizeof(char *) * nelem);
    memset(arr, 0, sizeof(char *) * nelem);

    src = src_org;
    n = 0;

    while (c = strpbrk(src, sep)) {
        while (c == src) {
            src++;
            c = strpbrk(src, sep);
        }
        
        if (c == NULL) 
            break;

        *c = 0;
        arr[n] = src;

        src = c + 1;
        n++;
    }

    arr[n] = src;

    *dst = arr;

    if(!*arr[n])
        return nelem-1;
    else
        return nelem;
}

int main(int argc, char **argv) {
    char **arr;
    int len, n;

    // example 1 - default separator
    len = strsplit("The quick       brown\tfox\t\t\t\tjumps\t \t \t \t \t over\r\nthe\n\n\n\nlazy\fdog\f \f\f", &arr, 0);

    for (n = 0; n<len; n++)
        printf("%s\n", arr[n]);

    free(arr);

    // example 2 - custom separators
    len = strsplit("/var/lib///my/./broken/.../app/././././path///", &arr, "/.");

    for (n = 0; n<len; n++)
        printf("%s\n", arr[n]);

    free(arr);

    // test - only separators
    len = strsplit("\r\n\t\f", &arr, 0);

    for (n = 0; n<len; n++)
        printf("%s\n", arr[n]);

    free(arr);

    // test - no separators
    len = strsplit("foo", &arr, 0);

    for (n = 0; n<len; n++)
        printf("%s\n", arr[n]);

    free(arr);

    // test - empty string
    len = strsplit("", &arr, 0);

    for (n = 0; n<len; n++)
        printf("%s\n", arr[n]);

    free(arr);

    return 0;
}