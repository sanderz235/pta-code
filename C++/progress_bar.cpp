#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	srand(n);
	for(int i=0;i<n;i++){
		int ran=1+rand()%35;
		int rate=round(ran/35.0*100);
		for(int j=0;j<ran;j++){
			cout<<">";
		}
		for(int k=ran;k<35;k++){
			cout<<".";
		}
		cout<<" "<<rate<<"%"<<endl;
	}
	return 0;
 } 
