#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
// strsplit - split string in to array of char[] with separators
// Warning this function modifies src!
// Written by Tomasz Nowak
//
int strsplit(char *src, char ***dst, char *sep) {
	char **arr;
    char defsep[]=" \t\n\r\f";

    if(!sep)
        sep=defsep;

	char *src_org = src;
	char *c;
	int n = 0;

	while (c = strpbrk(src, sep))
	{
		while (c == src)
		{
			src++;
			c = strpbrk(src, sep);
		}
		if (c == NULL) break;

		src = c + 1;
		n++;
	}

	int nelem = n + 1;
	arr = (char **)malloc(sizeof(char *) * nelem);
	memset(arr, 0, sizeof(char *) * nelem);

	src = src_org;
	n = 0;

	while (c = strpbrk(src, sep))
	{
		while (c == src)
		{
			src++;
			c = strpbrk(src, sep);
		}
		if (c == NULL) break;

		*c = 0;
		arr[n] = src;

		src = c + 1;
		n++;
	}

	arr[n] = src;

	*dst = arr;
	return nelem;
}

int main(int argc, char **argv) {
	char **arr;
	int len, n;
	char tmp[256]={0};

	strcpy(tmp, "The quick       brown\tfox\t\t\t\tjumps\t \t \t \t \t over\r\nthe\n\n\n\nlazy\fdog\f \f\f");

    len = strsplit(tmp, &arr, 0);

	for (n = 0; n<len; n++)
		printf("%s\n", arr[n]);

	free(arr);


	strcpy(tmp, "/var/lib///my/./broken/.../app/././././path///");

    len = strsplit(tmp, &arr, "/.");

	for (n = 0; n<len; n++)
		printf("%s\n", arr[n]);

	free(arr);

	return 0;
}