//bfs
#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

vector<int> vec[200005], path;
queue<int> q;
int vis[200005], par[200005], child[200005];
int bob_node, n;

//this bfs is to find.
//consider each node and for each node to find a path from node to leaves which has max nodes
//child[i] it stores for ith node max nodes it has from cur node to leaves(taking max path) 
void dfs1(int src){
	int ver, i, j, num;
	num = vec[src].size();
	if(vis[src]){
		return ;	
	}
	//cout<<"src "<<src<<endl;
	vis[src] = 1;
	if((num == 0 && n == 1)||(n > 1 && num == 1 && src != 1)){
		child[src] = 0;
		return ;
	}
		
	for(i=0; i<num; i++){
		ver = vec[src][i];
		if(!vis[ver]){
			dfs1(ver);
			child[src] = max(child[src], child[ver] + 1);
			//cout<<"src child "<<src<<" "<<child[src]<<" "<<child[ver]<<endl;
		}
	} 
	return ;
}

//this dfs is to construct the path from ver 1 to ver x. 
//dfs will construct in bottom to top.
//reversing it we will get top to bottom
bool dfs2(int src){
	int x, y;
	bool bob_exists = false;
	int ver, i, j, num;
	if(vis[src]){
		return true;
	}
	
	if(src == bob_node){
		return true;
	}
	//cout<<"src "<<src<<endl;
	vis[src] = true;
	num = vec[src].size();
		
	for(i=0; i<num; i++){
		ver = vec[src][i];
		if(!vis[ver]){
			bob_exists = dfs2(ver);
			//cout<<"bob exists"<<bob_exists<<endl;
			if(!bob_exists){
				
			}else{
				par[ver] = src;
				return true;
			}
		}
			
	} 
	return false;
}

int main(){
	int ans=0;
	int i, j, k, x, y;
	int alice_path_idx, alice_node, alice_next_node;
	cin>>n>>bob_node;
	
	for(i=1; i<n; i++){
		cin>>x>>y;	
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	
	for(i=1; i<=n; i++){
		vis[i] = 0;
		child[i] = 0;
	}
	dfs1(1);
	
	for(i=1; i<=n; i++){
		vis[i] = 0;
	}
	dfs2(1);
	
	x = bob_node;
	
	//path is top to bottom set of nodes to reach from 1 to bob_node in minimum distance
	//ie it represents direct distance.
	while(x!=1){
		path.push_back(x);
	//	cout<<x<<" ";
		x=par[x];
	}
	path.push_back(1);
	reverse(path.begin(), path.end()); //since we are calculating bottom to top path in above loop
	//hence we need to reverse it.
	//cout<<"\nchild nodes";
	
	/*for(i=1;i<=n;i++)
	{	cout<<child[i]<<" ";
	}
	cout<<endl;*/
	//now we need algo to find the ans.
	alice_node = 1;
	alice_path_idx = 0;
	//we will move alice down 1 step acc to path found in path vector
	//we will move bob move up 1 step acc to par array.
	//set nodes covering in both alice and bob paths are same.
	//try to visualize above situation. things will get clearer.
	while(1){
		alice_node = path[alice_path_idx];
		alice_next_node = path[alice_path_idx + 1];
		
		//bob turn
		if(par[bob_node] == alice_node){
			//find ans here
			ans = ans + 2*child[bob_node] + 2;
			break;
		}else if(par[bob_node] == alice_next_node){
			ans = ans + 2*child[bob_node] + 4;
			break;
		}else{
			ans++;
			bob_node = par[bob_node];
		}
		
		
		//alice turn 
		//if bob is staying at child of alice
		//game is finished.
		if(bob_node == alice_next_node){
			ans++;
			alice_path_idx++;
			break;
		}else{
			ans++;
			alice_path_idx++;
		}
	}
	cout<<ans;
	return 0;
}
