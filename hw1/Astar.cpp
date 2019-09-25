#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<cmath>
#include<fstream>
using namespace std;
#define inf 999999
int pre[50];                        
bool vis[50];                           
int dis[50];                           
bool arrive[50];//标记是否到达索引所代表的结点                   
int n,m;
int start,end_;
int edgenum=0;
//边，这里用结构体来存储图
struct Edge{                        
    int to;
    int dis;
    int next;
}edg[100010];
vector<Edge>v[50];
//城市结点
struct Node{
    int f;
    int g;        
    int now;          
    Node(int f,int g,int now){
        this->f=f;
        this->g=g;
        this->now=now;
    }
};
//自定义排序方式，下面优先队列会用到
bool operator < (const Node &a,const Node &b){
        return a.f>b.f;
}
//添加边，由于是无向图，所以添加边要正反两面添加
void addEdge(int src,int des,int dis){
    edg[edgenum].to=des;
    edg[edgenum].dis=dis;
    edg[edgenum].next=pre[src];
    pre[src]=edgenum;
    edgenum++;
    edg[edgenum].to=src;
    edg[edgenum].dis=dis;
    edg[edgenum].next=pre[des];
    pre[des]=edgenum;
    edgenum++;
    Edge edge1;
    Edge edge2;
    edge1.to=src;
    edge1.dis=dis;
    edge2.to=des;
    edge2.dis=dis;
    v[des].push_back(edge1);
    v[src].push_back(edge2);
}
//对目的结点求单源最短路，用来求H(n)
void Dijkstra(int en){
    int i,j,k;
    dis[en]=0;
    for(i=1;i<=n;i++){
        k=-1;
        int min=inf;
        for(j=1;j<=n;j++){
            if(vis[j]==false&&min>dis[j]){
                k=j;
                min=dis[j];
            }
        }
        vis[k]=1;
        for(int u=pre[k];u!=-1;u=edg[u].next){
            int v;
            v=edg[u].to;
            if (vis[v]==false&&dis[v]>dis[k]+edg[u].dis){
                dis[v]=dis[k]+edg[u].dis;
            }
        }
    }
}
//使用优先队列的A*，将F(n)值最小的结点放在队首，一旦到达目的结点，则记录结果
int A_star(int start,int end_){                            
    priority_queue<Node>q;         
    Node t(dis[start],0,start);                      
    q.push(t);                             
    Node tmp(0,0,0);
    while(!q.empty()){
        Node top=q.top();
        q.pop();
        arrive[top.now]=true;
        if(arrive[end_]==true){                                   
            return top.f;
        }
        for(int i=pre[top.now];i!=-1;i=edg[i].next)
        {
            tmp.now=edg[i].to;                                  
            tmp.g=top.g+edg[i].dis;
            tmp.f=tmp.g+dis[edg[i].to];
            q.push(tmp);
        }
    }
    return -1;                                               
}
int main(){
    memset(v,0,sizeof(v));
    memset(pre,-1,sizeof(pre));
    memset(arrive,false,sizeof(arrive)); 
    memset(vis,false,sizeof(vis));
    memset(dis,inf,sizeof(dis));
    //读入文件，并对数据进行处理
    ifstream in("/Users/dongchenyu/Desktop/data.txt");
    string s;
    int line=1;
    string str;
    int from;
    int to;
    int length;
    int n;
    int m;
    vector<int>temp;
    while(getline(in,s)){
        int len=s.size();
        for(int i=0;i<len;i++){
            if(s[i]!=' '){
                str.push_back(s[i]);
            }
            if(s[i]==' '||i==len-1){
                int a = atoi(str.c_str());
                temp.push_back(a);
                str.clear();
            }    
        }
        if(temp.size()==2){
            n=temp[0];
            m=temp[1];
        }
        if(temp.size()==3){
            from=temp[0];
            to=temp[1];
            length=temp[2];
            addEdge(from,to,length);
        }
        temp.clear();
    }
    cin>>start>>end_;
    Dijkstra(end_);
    int ans=A_star(start,end_);
    cout<<ans<<endl;
}