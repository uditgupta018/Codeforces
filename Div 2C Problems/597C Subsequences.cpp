//2-d Segment Tree
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<utility>
#include<cstring>
#include<cmath>
#define LL long long int
#define mod 1000000007
#define vi vector<int>
#define vvi vector < vi >
#define pii pair<int,int>
#define all(c) c.begin(),c.end()
#define sf(x) scanf("%d",&x);
#define sf2(x,y) scanf("%d%d",&x,&y);
#define mem(a,val) memset(a,val,sizeof(a))
#define nl printf("\n");
#define pb push_back
#define mp make_pair
//#define f first
//#define s second
#define cf I64
using namespace std;
//Creating Segment Tree :-
int tree[500000][12];
void build_segment_tree(int tree[],int node,int a,int b,int len){
	if(a>b) return ;
	if(a==b){
		for(int i=1;i<=len;i++){
			tree[node][i]=0;
		}
	}
	build_segment_tree(tree,2*node,a,(a+b)/2,len);
	build_segment_tree(tree,2*node,(a+b)/2+1,b,len);
	for(i=1;i<=len;i++){
		tree[node][i]=tree[2*node][i]+tree[2*node+1][i];
	}
	return ;
}
void update_segment_tree(int tree[],int node,int a,int b,int start,int end,int len,int val){
	if(a>b) return ;
	//Current segment not in range
	if(b<start||a>end) return ;
	if(a>=start&&b<=end){
		tree[node][len]+=val;
		return ;
	}
	update_segment_tree(tree,2*node,a,(a+b)/2,start,end,len,val);
	update_segment_tree(tree,2*node+1,(a+b)/2+1,b,start,end,len,val);
	return ;
}
int query_segment_tree(int tree[],int node,int a,int b,int start,int end,int len){
	//current segment not in range
	if(a>b||b<start||a>end) return 0;
	if(a>=start&&b<=end) return tree[node][len];
	ans=query_segment_tree(tree,2*node,a,(a+b)/2,start,end,len)+query_segment_tree(tree,2*node+1,(a+b)/2+1,b,start,end,len);
	return ans;
}
int main(){
	int n,len;
	//standard input
	cin>>n>>len;
	for(i=1;i<=n;i++){
		cin>>arr[i];
	}
	
	for(i=1;i<=n;i++){
		//Consider for index ith
		//Now at each index we want to find number of subsequences ending at index i 
		//of length 1 , 2 , 3 ... k+1 ; 
		//How we can compute this ?
		//say arr[i] == 5
		//if know number of subsequences which end at value either 1 or 2 or 3 or 4 
		//from index 1 to index i+1
		//pls read above lines again if not clear.
		//so now wat the equation becomes
		//no of subsequences of length k+1 which end at index i= 
		//									number of subsequences of length k which end at [value 1] from index range 1  to (i-1) of given array
		//  							+   number of subsequences of length k which end at [value 2] from index range 1  to (i-1) of given array 
		//								+   number of subsequences of length k which end at [value 3] from index range 1  to (i-1) of given array 
		//								+   number of subsequences of length k which end at [value 4] from index range 1  to (i-1) of given array 	
		//For this part we can use Segemnt Tree to compute sum of subsequences ...
		//Segment tree : we use tree[1] to store number of subsequences which end at value 1
		//             : we use tree[2] to store number of subsequences which end at value 2
		//But we want number of subsequences of length 1 , 2 ,3 .. (k+1)
		// So we will use 2-d Segment Tree
		
		

	}
	return 0;
}
