#include <bits/stdc++.h>
using namespace std;
int main(){
    int num,isinput=0;
    char c;
    while (1)
    {
        num=0;
        isinput=0;
        while (1)
        {
            c=getchar();
            if(c=='\n'||c==EOF)break;
            num=num*2+(c-'0');
            isinput=1;
        }
        if(isinput)
        cout<<num<<endl;
        else break;
    }
    
    return 0;
}