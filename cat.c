#include <stdio.h>
int main(int argc, char const *argv[])
{
	FILE* fin = fopen(argv[1], "r");
	
	int c;
	while ((c = fgetc(fin)) != EOF){
		fputc(c, stdout);
	}	
	return 0;

}
