#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const LL INF=1e18;
int n,m,C,h[M],tot=0;
struct edge{
	int nxt,to,co;
}G[M<<2];
void Add(int a,int b,int c){
	G[++tot]=(edge){h[a],b,c};
	h[a]=tot;
}
struct node{
	int x;LL ds;
	bool operator < (const node& res) const{
		return ds>res.ds;
	}
}A[M];
bool cmp(node a,node b){return a.ds<b.ds;}
priority_queue<node>Q;
LL dis[M];
bool vis[M];
LL sum[M];
void Dij(){
	memset(vis,0,sizeof(vis));
	fill(dis+1,dis+n+1,INF);dis[1]=0;
	Q.push((node){1,0});
	while(!Q.empty()){
		node e=Q.top();Q.pop();
		if(vis[e.x])continue;
		vis[e.x]=1;
		for(int i=h[e.x];i;i=G[i].nxt){
			int u=G[i].to,v=G[i].co;
			if(dis[u]>dis[e.x]+v){
				dis[u]=dis[e.x]+v;
				Q.push((node){u,dis[u]});
			}
		}
	}
}
LL res=0;
int main(){
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	scanf("%d%d%d",&n,&m,&C);
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
		res+=c;
	}
	Dij();
	for(int i=1;i<=n;i++)A[i]=(node){i,dis[i]};
	sort(A+1,A+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=h[i];j;j=G[j].nxt){
			int u=G[j].to,co=G[j].co;
			if(dis[u]==dis[i]&&u>i)continue;
			if(dis[u]<=dis[i])sum[i]+=co;
		}
	}
	A[n+1].ds=-1;
	LL ans=INF;
	for(int i=1;i<=n;i++){
		res-=sum[A[i].x];
		if(A[i].ds!=A[i+1].ds)
			ans=min(ans,A[i].ds*C+res);
	}
	printf("%lld\n",ans);
	return 0;
}
