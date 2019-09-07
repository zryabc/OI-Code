#include<bits/stdc++.h>
#define M 2000005
using namespace std;
void read(int &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
int n,m,ans[M],h[M],tt,now[M];
struct edge{
	int nxt,to;
}G[M*3];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct Pbl{
	int ans[25];
	void solve(){
		for(int i=0;i<1<<n;i++){
			for(int j=1;j<=n;j++){
				if(i&1<<j-1)ans[j]=2;
				else ans[j]=1;
			}
			bool fl=1;
			for(int j=1;j<=n;j++){
				int c=0;
				for(int k=h[j];k;k=G[k].nxt){
					int u=G[k].to;
					if(ans[u]==ans[j])c++;
				}
				if(c>1){fl=0;break;}
			}
			if(fl){
				for(int j=1;j<=n;j++)
					printf("%d ",ans[j]);
				cout<<endl;
				return;
			}
		}
		puts("-1");
	}
}pbl;
int main(){
	freopen("group.in","r",stdin);
	freopen("group.out","w",stdout);
	read(n);read(m);
	for(int i=1,a,b;i<=m;i++){
		read(a);read(b);
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=n;i++){
		int c1=0,c2=0,n1=0,n2=0;
		for(int j=h[i];j;j=G[j].nxt){
			int u=G[j].to;
			if(ans[u]==1)c1++,n1=u;
			else if(ans[u]==2)c2++,n2=u;
		}
		if(c1==0){
			ans[i]=1;
			now[i]=0;
		}
		else if(c2==0){
			ans[i]=2;
			now[i]=0;
		}
		else if(c1==1&&now[n1]==0){
			now[n1]++;
			ans[i]=1;
			now[i]=1;
		}
		else if(c2==1&&now[n2]==0){
			now[n2]++;
			ans[i]=2;
			now[i]=1;
		}
		else {puts("-1");return 0;}
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}