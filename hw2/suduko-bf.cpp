#include<iostream>
#include<fstream>
using namespace std;
bool sign=false;
int num[9][9];
void Output(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<num[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
bool Check(int n,int key){
    int row=n/9;
    int column=n%9;
    for(int i=0;i<9;i++){
        if(num[row][i]==key||num[i][column]==key){
            return false;
        }
    }
    return true;
}
bool ok(int r,int c){
    int row=r/3*3;
    int column=c/3*3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(num[r][c]==num[row+i][column+j]&&((row+i!=r)||(column+j!=c))){
                return false;
            }
        }
    }
    return true;
}
void DFS(int n){
    int row=n/9;
    int column=n%9;
    bool now=true;
    if(n>80){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(ok(i,j)==false){
                    now=false;
                }
            }
        }
        if(now){
            sign=true;
            Output();
        }
        return;
    }
    else{
        if(num[row][column]!=0){
            DFS(n+1);
        }
        else{
            for(int i=1;i<=9;i++){
                if(Check(n,i)){
                    num[row][column]=i;
                    DFS(n+1);
                    if(sign) return;
                    num[row][column]=0;
                }
            }
        }
    }
}
int main(){
    memset(num,0,sizeof(num));
    int row=0;
    int column=0;
    string s;
    ifstream in("/Users/dongchenyu/Documents/data1.txt");
    while(getline(in,s)){
        column=0;
        int len=s.size();
        for(int i=0;i<len;i++){
            if(s[i]>='0'&&s[i]<='9'){
                num[row][column++]=s[i]-'0';
            }
        }
        row++;
    }
    clock_t start,finish;
    start=clock();
    DFS(0);
    finish=clock();
    cout << finish-start   << "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
}