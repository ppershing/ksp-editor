#include <stdio.h>

int main(){
	char s[50] ;
	scanf("%s", &s);
	int i=0;
	while (s[i]!=0) i++;
	while (i>0)
	{
		i--;
		printf("%c", s[i]);
	}
	printf("\n");
}
