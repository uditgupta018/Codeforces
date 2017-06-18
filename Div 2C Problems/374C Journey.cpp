#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>

#define pb push_back
#define mp make_pair

using namespace std;

vector<pair<int,int> > vec[50005];
queue<int> q;
int  visited[5005],dp[5005][5005],n;

void bfs(){
	int num,src,ver,i,cost;
	while(!q.empty()){
		src = q.front();
		q.pop();
		visited[src] = 1;
		num=vec[src].size();
		for(i=0;i<num;i++){
			ver = vec[src][i].first;
			cost = vec[src][i].second;
			
			for(j=1;j<n;j++){
				if(dp[ver][j+1]==-1){
					dp[ver][j+1] = dp[src][j] + cost;
				}else{
					dp[ver][j+1] = min(dp[ver][j+1],dp[src][j] + cost);
				}
			}
			
			if(!visited[ver]){
				q.push(ver);
			}
		}
	}
}

int main(){
	int i,m,time_limit,x,y,cost,j,ans;
	cin>>n>>m>>time_limit;
	for(i=1;i<=n;i++){
		cin>>x>>y>>cost;
		vec[x].pb(mp(y,cost));
	}
	q.push(1);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			dp[i][j]=0;
		}
		visited[i]=0;
	}
	visited[1]=1;
	dp[1][1]=1;
	bfs();
	
	for(i=1;i<=n;i++){
		if((dp[n][i] != -1)&&(dp[n][i] <= time_limit)){
			ans = i;		
		}
	}
	cout<<ans;
	return 0;
}
