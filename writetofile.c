#include<stdio.h>
#include<stdlib.h>

void writetofile(char *s)
{
	FILE *fp;
	int i;
	fp=fopen("data.xls","a");
	if(fp==NULL)
	{
		printf("file not opened\n");
		exit(0);
	}
	fprintf(fp,"%s",s);
	fclose(fp);
}
