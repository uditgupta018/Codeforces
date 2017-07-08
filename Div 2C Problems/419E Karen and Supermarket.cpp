#include<iostream>
#include<stdio.h>
#include<vector>
#include<utility>
#define pb push_back
#define mp make_pair

using namespace std;

vector<pair<int,pair<int,int> > > vec1[5005];
vector<int> vec2[50005];

int dp_nrml[5005][5005], dp_disc[5005][5005];
int sorted_array[5005][5005];

void dfs1(int src){
	
	int i, j, edges, child, cost, discount, child_cost, child_discount;
	int cur_sorted_array[5005], num1, num2;
	pair<int, pair<int,int> >p;
	edges = vec2[src].size();
	p = vec1[src][0];
	cost = p.second.first;
	discount  = p.second.second;
	
	//setting things for current root Node.
	sorted_array[src][0] = cur_sorted_array[0] = 1;   //size of subtree including root vertex.
	sorted_array[src][1] = cur_sorted_array[1] = cost;
	//leaf node
	if(edges == 0){
		
		dp_nrml[src][1] = cost;
	
		
		return ;
		
	}
	
	for(i=0; i<edges; i++){
	
		
		//first calc all dp values for all children.
		//then we will calc dp values for current node.
		
		
		child = vec2[src][i];
		dfs(child);
		
		//add children of child subtree with current node (root) tree:-
		//like merge sort 
		num1 = sorted_array[src][0];
		num2 = sorted_array[child][0];
		cur_sorted_array[0] = num1+num2;
		i=j=1;
		for(;i<=num1&&j<=num2;){
			if(sorted_array[src][i] < sorted_array[child][j]){
				cur_sorted_array[i+j-1] = sorted_array[src][i];
				i++;
			}else{
				cur_sorted_array[i+j-1] = sorted_array[child][j];
				j++;
			}
		}
		for(;i<=num1;i++){
			cur_sorted_array[i+j-1] = sorted_array[src][i];
		}
		for(;j<=num2;j++){
			cur_sorted_array[i+j-1] = sorted_array[src][j];
		}
		for(i=0;i<=num1+num2;i++){
			sorted_array[src][i] = cur_sorted_array[i];
		}
	
				
	}
	
	//after traversing all child elements update dp for current node
	for(i=1; i<=sorted_array[src][0];i++){
		dp_nrml[src][i] = ( (i!=1) ? dp_nrml[src][i-1] : 0 ) + sorted_array[src][i];
	}
	return ;
}

void dfs2(int src){
	int i,j,k,edges, child, cost, discount, child_cost, child_discount;
	pair<int, pair<int,int> >p;
	edges = vec2[src].size();
	p = vec1[src][0];
	cost = p.second.first;
	discount  = p.second.second;
	dp_discount[src][1] = cost-discount;
	if(edges == 0){
		dp_discount[src][1] = cost-discount;
		return ;
	}
	
	child_num=1;
	nodes = 0;
	for(i=0; i<edges; i++){
		child = vec2[src][i];
		dfs2(child);
		
		if(i==0){
			nodes = sorted_array[child][0];
			for(i=1;i<=nodes;i++){
				dp_temp[1] = min(dp_discount[child][i],dp_nrml[child][i]);
			}
		}else{
			n1 = nodes;
			n2 = sorted_array[child][0];
			for(i=1;i<=n1+n2;i++){
				for(j=0;j<=i&&j<=min(n1,n2);j++){
					temp1 = min(dp_discount[child][j],dp_nrml[child][j]);
					temp1 min(temp1, dp_temp[i-j]);
				}
			}
		}
	
	
	
}

void init(){
	int i, j;
	for(i=0; i<=5005; i++){
		for(j=0; j<=5005; j++){
			dp_nrml[i][j] = -1;
		}
	}
	
	for(i=0; i<=5005; i++){
		for(j=0; j<=5005; j++){
			dp_disc[i][j] = -1;
		}
	}
}
int main(){
	int i, j, k, n, budget, x = -1, cost, discount;
	cin>>n>>budget;
	
	//init
	init();
	
	for(i=1; i<=n; i++){
		cin>>cost>>discount;
		if(i>1) {
			cin>>x;
			vec2[x].pb(i);
		}
		vec1[i].pb(mp(x, mp(cost, discount)));
	}
	dfs(1);
	dfs2(1);
	return 0;
}
