#include<stdio.h>
#include<string.h>
int main()
{
    char str_a[1005],str_b[1005];
    int cnt=0;
    gets(str_a);
    gets(str_b);
    int len_a=strlen(str_a);
    int len_b=strlen(str_b);
    for(int i=0;i<len_a;i++)
        {
            if(str_a[i]>='A'&&str_a[i]<='Z')
            {
                str_a[i]+=32;
            }
        }
    for(int i=0;i<len_b;i++)
        {
            if(str_b[i]>='A'&&str_b[i]<='Z')
            {
                str_b[i]+=32;
            }
        }
    for(int i=0;i<len_a;i++)
        {
            if(str_a[i]>='a'&&str_a[i]<='z')
            {
                int start=i;
                while(i<len_a&&(str_a[i]>='a'&&str_a[i]<='z'))
                    i++;
                int end=i-1;//from str_a[start] to str_a[end]
                int isFound=0;
                int word_len = end-start+1;
                if(word_len>=len_b)
                {
                    for(int j=start;j<=end-len_b+1;j++)
                        {
                            int match=1;
                            for(int k=0;k<len_b;k++)
                                {
                                    if(str_a[j+k]!=str_b[k])
                                    {
                                        match=0;
                                        break;
                                    }
                                    
                                }
                            if(match)
                                    {
                                        isFound=1;
                                        break;
                                    }
                        }
                    
                }
                if(isFound)
                    {
                        cnt++;
                    }
                i--;
            }
        }
    printf("%d\n",cnt);
    return 0;
}