#include<stdio.h>
#include<string.h>
void my_strcpy(char*dest,char*src,int len)
{
	for(int i=0;i<len;i++)
	{
		dest[i]=src[i];
	}
	dest[len]='\0';
}
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	getchar();
	char name[101][11];
	char relation[22],temp_name1[11],temp_name2[11];
	int arr[101][101]={0};
	int cnt=0;
	for (int i = 0; i < m; i++)//m组关系
	{
		gets(relation);
		int len=strlen(relation);
		int len1=0,appear1=0,appear2=0;
		int locate1=0,locate2=0;
		while(relation[len1++]!=' ');
		my_strcpy(temp_name1,relation,len1);
		my_strcpy(temp_name2,relation+len1+1,len-len1-1);
		for(int j=0;j<cnt;j++)
		{
			if(!strcmp(temp_name1,name[j]))
			{
				appear1=1;
				locate1=j;
			}
			if(!strcmp(temp_name2,name[j]))
			{
				appear2=1;
				locate2=j;
			}
		}
		if(!appear1)
		{
			strcpy(name[cnt],temp_name1);
			locate1=cnt;
			cnt++;
		}
		if(!appear2)
		{
			strcpy(name[cnt],temp_name2);
			locate2=cnt;
			cnt++;
		}
		arr[locate1][locate2]=1;
		arr[locate2][locate1]=1;
	}
	int max=0,num=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr[i][j]==1)
			num+=1;
		}
		if(num>max)max=num;
		num=0;
	}
	printf("%d",max);
	return 0;
} 
