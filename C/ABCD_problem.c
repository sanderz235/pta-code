#include <stdio.h>
#include <string.h>
int main()
{
    char str[33];
	gets(str);
	long long ans1;scanf("%lld",&ans1);
	unsigned long long ans = (unsigned long long)ans1;
	int dans[64]={0},i=0,temp_answer=0,temp_guess=0,cnt=0;
	while (ans!=0)
	{
		dans[63-i++]=ans%2;
		ans/=2;
	}
	// for (int j = 0; j < 64; j++)
	// {
	// 	printf("%d",dans[j]);
	// }
	int len = strlen(str);
	int k=63;
	for(int j=0;j<len;j++)
	{
		switch (str[j])
		{
		case 'A':
			temp_guess=0;
			break;
		case 'B':
			temp_guess=10;
			break;
		case 'C':
			temp_guess=1;
			break;
		case 'D':
			temp_guess=11;
			break;
		default:
			break;
		}
		for (int l = 0; l < 2; l++)
		{
			temp_answer=temp_answer*10+dans[k];
			k--;
		}
		if(temp_answer==temp_guess)
		cnt++;
		temp_answer=0;
	}
	printf("%d",cnt);
    return 0;
}