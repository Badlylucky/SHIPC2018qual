#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
#include <functional>
typedef long long ll;


using namespace std;

typedef pair<ll,int> P;

class Edge
{
	public:
	ll cost;
	int from;
	int to;

	Edge(int n,ll c)
	{
		to=n;
		cost=c;
	}

	Edge(int f,int t,int c)
	{
		from=f;
		to=t;
		cost=c;
	}
};

vector<Edge> eng[100000];
vector<Edge> snug[100000];
ll endd[100000];
ll snud[100000];
bool used[100000];

void dijk(int s,ll d[],vector<Edge> g[])
{
	priority_queue<P,vector<P>,greater<P>> que;
	fill(d,d+100000,1e9-1);
	d[s]=0;
	que.push(P(0,s));
	while(!que.empty())
	{
		P p=que.top();
		que.pop();
		int v=p.second;
		if(d[v]<p.first)
			continue;
		for(int i=0;i<g[v].size();i++)
		{
			Edge e=g[v][i];
			if(d[e.to]>d[v]+e.cost)
			{
				d[e.to]=d[v]+e.cost;
				que.push(P(d[e.to],e.to));
			}
		}
	}
}

int main()
{
	int n,m,s,t;
	P best;//最もスヌークが多くなるときに経由する両替所とコスト
	vector<ll> ans;
	cin>>n>>m>>s>>t;
	s--;t--;
	for(int i=0;i<m;i++)
	{
		int u,v;
		ll a,b;
		cin>>u>>v>>a>>b;
		u--;v--;
		eng[u].push_back(Edge(v,a));
		eng[v].push_back(Edge(u,a));
		snug[u].push_back(Edge(v,b));
		snug[v].push_back(Edge(u,b));
	}

	dijk(s,endd,eng);//あらかじめ円のほうは最短路を求めておく
	dijk(t,snud,snug);//snuの方はゴールからの最短路を求めておく
	//後ろからスタート
	//i以上の頂点は使える
	best.second=n-1;
	best.first=1e15-endd[best.second]-snud[best.second];
	ans.push_back(best.first);
	for(int i=n-2;i>-1;i--)
	{
		int r=i;
		ll co=1e15-endd[r]-snud[r];
		best=max(best,P(co,r));
		ans.push_back(best.first);
	}
	reverse(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}