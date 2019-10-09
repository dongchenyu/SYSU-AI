#include <iostream>
#include<fstream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
int num[9][9];
int candi[9]; 
vector< vector<int> > suduko;
vector<int> can_choose[81];
int try_num[81];
void Output(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<num[i][j]<<' ';
        }
        cout<<endl;
    }
}
void candinum(int a[][9],int row,int column){
    for(int i=0;i<9;i++){
        candi[i]=i+1;
    }
    for(int i=0;i<9;i++){
        candi[a[row][i]-1]=0;
        candi[a[i][column]-1]=0;
    }
    int r=row/3*3;
    int c=column/3*3;
    for(int i=r;i<r+3;i++){
        for(int j=c;j<c+3;j++){
            candi[a[i][j]-1]=0;
        }
    }
    for(int i=0;i<9;i++){
        if(candi[i]!= 0){
            can_choose[row * 9 + column].push_back(candi[i]);
        }
    }
}

int min_choice(){
    int min=9;
    int V=80;
    for(int i=0;i<81;i++)
    if(try_num[i]==0 && can_choose[i].size()<min){
        min=can_choose[i].size();
        V=i;
    }
    return V;
}

bool delete_num(int index, int num){
    for(vector<int>::iterator it=can_choose[index].begin();it!=can_choose[index].end();it++){
        if(*it==num){
            can_choose[index].erase(it);
            return true;
        }
    }
    return false;
}
vector<int> delete_tar(int index, int tar){
    int row=index/9;
    int col=index%9;
    int square_row=row/3*3;
    int square_col=col/3*3;
    vector<int>temp;
    for(int i=0;i<9;i++){
        int row_index=row*9+i;
        if(try_num[row_index]==0&&delete_num(row_index, tar)){
            temp.push_back(row_index);
        }
        int col_index=i * 9 + col;
        if(try_num[col_index]==0 && delete_num(col_index, tar)){
            temp.push_back(col_index);
        }
    }
    for(int i=square_row;i<square_row+3;i++){
        for(int j=square_col;j<square_col+3;j++){
            int square_index=i*9+j;
            if(try_num[square_index]==0 && delete_num(square_index, tar)){
                temp.push_back(square_index);
            } 
        }
    }
    return temp;

}

bool is_suc(){
    for(int i=0;i<81;i++){
        if(try_num[i]==0 && can_choose[i].size()==0)
            return false;
    }
    return true;
}
bool fill_blank(int blank){
    if(blank==0){
        return true;
    }
    int V=min_choice();
    int row=V/9;
    int col=V%9;
    for(int k=0;k<can_choose[V].size();k++){
        int now=can_choose[V][k];
        try_num[V]=now;
        vector<int> list_=delete_tar(V, now);
        vector<int> step;
        step.push_back(row);
        step.push_back(col);
        step.push_back(now);
        suduko.push_back(step);
        if(is_suc()==true){
            if(fill_blank(blank - 1)){
                return true;
            }
        }
        for(int i=0;i<list_.size();i++){
            can_choose[list_[i]].push_back(now);
        }
        try_num[V]=0;
        suduko.pop_back();

    }
    return false;
}

void solve(int num[9][9]){
    int num_blank=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            int index=i*9+j;
            if(num[i][j]==0){
                num_blank++;
                candinum(num, i, j);
            }
            else{
                try_num[i * 9 + j] = 1;
            }
        }
    }
    fill_blank(num_blank);
    for(int i=0;i<suduko.size();i++){
        num[suduko[i][0]][suduko[i][1]]=suduko[i][2];
    }
    Output();
    for(int i=0;i<suduko.size();i++){
        num[suduko[i][0]][suduko[i][1]]=0;
    }
    suduko.clear();
    for(int i=0;i<81;i++){
        can_choose[i].clear();
        try_num[i]=0;
    }
}

int main(){
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
    solve(num);
    finish=clock();
    cout << finish-start   << "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
}