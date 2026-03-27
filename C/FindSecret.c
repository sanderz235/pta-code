#include <stdio.h>
#include<string.h>
int main()
{
    char str[81],temp[81];
    gets(str);
    int n=0,num = 1,FindSecret=0;
    while(str[n]!='\0')
    {
        while (str[n]==' ')
        {
            n++;
        }
    int j=0;
    while(str[n]!=' ')
    {
        if(str[n]=='\0')break;
        temp[j]=str[n];
        j++;
        n++;
    }
    temp[j]='\0';
    if(strcmp("secret",temp)==0)
    {
        FindSecret=1;
        printf("\"secret\" is pos %d\n",num);
    }
    num++;
    }
    if(!FindSecret)
    printf("No \"secret\"");
    return 0;
}
