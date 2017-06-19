#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>

#define pb push_back
#define mp make_pair
#define LL long long int 

using namespace std;

vector<pair<int,int> > vec[50005];
vector<int> path1;
queue<int> q;
int  visited[5005],n,path[5005][5005],indegree[5005]={0};
int dp[5005][5005];

void bfs(){
	int num,src,ver,i,cost,j;
	
	while(!q.empty()){
		src = q.front();
		q.pop();
		visited[src] = 1;
		num=vec[src].size();
		//cout<<"src num "<<src<<" "<<num<<endl;
		for(i=0;i<num;i++){
			ver = vec[src][i].first;
			cost = vec[src][i].second;
			//cout<<"ver cost "<<ver<<" "<<cost<<endl;
			for(j=1;j<n;j++){
				if((dp[ver][j+1] == -1) && (dp[src][j]!= -1)){
					dp[ver][j+1] = dp[src][j]+cost;
					path[ver][j+1] = src;
				}else if(dp[src][j] != -1){
					if(dp[ver][j+1] > dp[src][j] + (LL)cost){
						path[ver][j+1] = src;
					}
					dp[ver][j+1] = min(dp[ver][j+1],dp[src][j] + cost);
					
					
				}
				if(dp[ver][j+1]>=2*1000000000){
						dp[ver][j+1]=1000000001;
					}
				//cout<<dp[ver][j]<<" ";
			}
			cout<<dp[ver][j]<<" ";
			cout<<endl;
			indegree[ver]--;
			if(!visited[ver]&&indegree[ver]==0){
				q.push(ver);
			}
			else if(q.empty()&&!visited[n]&&i==num-1){
				q.push(ver);
			}
		}
	}
}

int main(){
	int i,m,time_limit,x,y,cost,j,ans;
	cin>>n>>m>>time_limit;
	for(i=1;i<=m;i++){
		cin>>x>>y>>cost;
		vec[x].pb(mp(y,cost));
		indegree[y]++;
	}
	q.push(1);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			dp[i][j] = -1;
			path[i][j] = -1;
		}
		visited[i]=0;
	}
	visited[1]=1;
	dp[1][1]=0;
	bfs();
	
	for(i=1;i<=n;i++){
		if((dp[n][i] != -1)&&(dp[n][i] <= time_limit)){
			ans = i;		
		}
	}
	cout<<ans;
	cout<<endl;
	for(i=ans;i>0;i--){
		//cout<<n;
		path1.pb(n);
		n=path[n][i];
		
		
	}
	for(i=0;i<ans;i++)
		cout<<path1[ans-i-1]<<" ";
	return 0;
}
