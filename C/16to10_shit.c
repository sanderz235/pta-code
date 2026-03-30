#include <stdio.h>
int main(){
    int minus=0,begin=0;
    long long num=0;
    char ch;
    scanf("%c",&ch);
    while(ch!='#'){
        if((ch=='-'&&begin==0)||(ch>='0'&&ch<='9')||(ch>='a'&&ch<='f')||(ch>='A'&&ch<='F')){
            if(ch=='-'&&begin==0){
                minus=-1;
                goto tag;
            }
		if(!minus&&ch>='0'&&ch<='9')num=num*16+(ch-'0');
        if(minus==-1&&ch>='0'&&ch<='9')num=num*16-(ch-'0');
        if(!minus&&ch>='a'&&ch<='f')num=num*16+(ch-'a'+10);
        if((minus==-1)&&ch>='a'&&ch<='f')num=num*16-(ch-'a'+10);
        if(!minus&&ch>='A'&&ch<='F')num=num*16+(ch-'A'+10);
        if((minus==-1)&&ch>='A'&&ch<='F')num=num*16-(ch-'A'+10);
            begin=1;
        }
		tag:
        scanf("%c",&ch);
    }
    printf("%lld",num);
    return 0;
}