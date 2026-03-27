#include<stdio.h>
char *hanzi[]={"零","壹","贰","叁","肆","伍","陆","柒","捌","玖","拾","佰","仟","万","亿"};
int get_digit(int n){
	int cnt=0;
	while(n>0){
		n/=10;
		cnt++;
	}
	return cnt;
}
void get_qian(int started,int dgt,int n){
	int qian=n/1000;
	int bai=n/100%10;
	int shi=n/10%10;
	int ge=n%10;
	if(!started){
		switch (dgt)
		{
		case 4:
			goto tag1;
			break;
		case 3:
			goto tag2;
			break;
		case 2:
			goto tag3;
			break;
		case 1:
			goto tag4;
			break;
		default:
			break;
		}
	}
	tag1:
	printf("%s仟",hanzi[qian]);
	tag2:
	printf("%s佰",hanzi[bai]);
	tag3:
	printf("%s拾",hanzi[shi]);
	tag4:
	printf("%s",hanzi[ge]);
}
int main()
{
	int n,started=0,dgt;//qian:4 bai:3 shi:2 ge:1
	scanf("%d",&n);
	int yi,wan;
	if(get_digit(n)==9){
		yi=n/100000000;
		printf("%s亿",hanzi[yi]);
		n-=yi*100000000;
		started=1;
		// printf("%d",n);
	}
	if(get_digit(n)>=5){
		wan=n/10000;
		if(!started){
			dgt=get_digit(wan);
		}
		get_qian(started,dgt,wan);
		printf("万");
		started=1;
		n-=wan*10000;
	}
	if(!started){
		dgt=get_digit(n);
	}
	get_qian(started,dgt,n);
	printf("元\n");
	return 0;
 } 
