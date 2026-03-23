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
void get_qian(int n){
	int qian=n/1000;
	int bai=n/100%10;
	int shi=n/10%10;
	int ge=n%10;
	printf("%s仟%s佰%s拾%s",hanzi[qian],hanzi[bai],hanzi[shi],hanzi[ge]);
}
int main()
{
	int n;
	scanf("%d",&n);
	int yi,wan;
	if(get_digit(n)==9){
		yi=n/100000000;
		printf("%s亿",hanzi[yi]);
		n-=yi*100000000;
		// printf("%d",n);
	}
	if(get_digit(n)>=5){
		wan=n/10000;
		get_qian(wan);
		printf("万");
		n-=wan*10000;
	}
	get_qian(n);
	printf("元\n");
	return 0;
 } 
