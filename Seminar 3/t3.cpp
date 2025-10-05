#include <iostream>
using namespace std;

int main() {
    double a[15]; for(int i=0;i<15;i++) cin>>a[i];
    int m=0,M=0; for(int i=1;i<15;i++){if(a[i]<a[m])m=i; if(a[i]>a[M])M=i;}
    swap(a[0],a[m]); if(M==0)M=m; swap(a[14],a[M]);
    for(int i=0;i<15;i++) cout<<a[i]<<" ";
}