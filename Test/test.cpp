#include<bits/stdc++.h>
#define M 405
using namespace std;
const int inf=1e9;
int n,m,s,t,h[M],tt=1;
struct node{int x1,y1,x2,y2;}A[M];
int B1[M*15],b1,B2[M*15],b2;
struct edge{int nxt,to,co;}G[M*15];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
int dep[M],cur[M];
queue<int>Q;
bool bfs(){
    memset(dep,-1,sizeof(dep));
    for(int i=s;i<=t;i++)cur[i]=h[i];
    while(!Q.empty())Q.pop();
    Q.push(s);dep[s]=0;
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(dep[u]!=-1||!c)continue;
            dep[u]=dep[x]+1;
            if(u==t)return 1;
            Q.push(u);
        }
    }
    return 0;
}
int dfs(int x,int mi){
    if(x==t||!mi)return mi;
    int rlow=0,used=0;
    for(int& i=cur[x];i;i=G[i].nxt){
        int u=G[i].to,c=G[i].co;
        if(dep[u]!=dep[x]+1||!c)continue;
        if(rlow=dfs(u,min(c,mi-used))){
            used+=rlow;
            G[i].co-=rlow;
            G[i^1].co+=rlow;
            if(used==mi)break;
        }
    }
    return used;
}
int ans=0;
void Dinic(){
    while(bfs())ans+=dfs(s,inf);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
        B1[++b1]=A[i].x1;B1[++b1]=A[i].x2;
        B2[++b2]=A[i].y1;B2[++b2]=A[i].y2;
    }
    sort(B1+1,B1+b1+1);sort(B2+1,B2+b2+1);
    b1=unique(B1+1,B1+b1+1)-B1-1;
    b2=unique(B2+1,B2+b2+1)-B2-1;
    s=0,t=b1+b2+1;
    for(int i=1;i<=m;i++){
        A[i].x1=lower_bound(B1+1,B1+b1+1,A[i].x1)-B1;
        A[i].x2=lower_bound(B1+1,B1+b1+1,A[i].x2)-B1;
        A[i].y1=lower_bound(B2+1,B2+b2+1,A[i].y1)-B2;
        A[i].y2=lower_bound(B2+1,B2+b2+1,A[i].y2)-B2;
        for(int x=A[i].x1;x<A[i].x2;x++)
            for(int y=A[i].y1;y<A[i].y2;y++)
                Add(x,y+b1,inf),Add(y+b1,x,0);
    }
    for(int i=1;i<b1;i++){Add(s,i,B1[i+1]-B1[i]);Add(i,s,0);}
    for(int i=1;i<b2;i++){Add(i+b1,t,B2[i+1]-B2[i]);Add(t,i+b1,0);}
    Dinic();printf("%d\n",ans);
    return 0;
}