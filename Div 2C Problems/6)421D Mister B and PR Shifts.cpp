//Segment tree with lazy update
#include<iostream>
#include<stdio.h>

using namespace std;

struct seg{
	int leftmost, rightmost;
}lazy_tree[5000005];
int p[1000005];
int ans, curShift, shiftAns;

void build_segment_tree(int node, int a, int b){
	if(a<b){
		return ;
	}
	if(a == b){
		lazy_tree[node].leftmost = 0;
		lazy_tree[node].rightmost = 0;
		return ;
	}
	lazy_tree[node].leftmost = lazy_tree[node].rightmost = 0;
	build_segment_tree(2*node, a, (a+b)/2);
	build_segment_tree(2*node,(a+b)/2+1, b);
	return ;
} 

//a & b represents current range of segment tree.
//l & r is range into which we want to update.
void update_segment_tree(int node, int a, int b, int l ,int r, int valLeft, int valRight){
	int range, leftRange, rightRange, totalNode;
	
	if(a<b){
		return ;
	}	
	if(b < l || a > r){
		return ;
	}
	if(a == l && b == r){
		lazy_tree[node].leftmost += valLeft;
		lazy_tree[node].rightmost += valRight;
		return ;
	}
	
	if(r <= (a+b)/2){ //if our range (l,r) lies completely on Left Tree.
		update_segment_tree(2*node, a, (a+b)/2, l, r, valLeft, valRight);	
	}else if((a+b)/2 < l){ //if our range (l,r) lies completely on Right Tree
		update_segment_tree(2*node+1, (a+b)/2+1, b, l, r, valLeft, valRight);
	}else{ //if our range lies on both Left and Right tree.
		range = r-l+1;
		leftRange = (a+b)/2-l+1;
		rightRange = range - leftRange;
		
	
		if(valLeft <= valRight){
			totalNode = valRight-valLeft+1;
			update_segment_tree(2*node, a, (a+b)/2, l, (a+b)/2, valLeft , valLeft - 1 + (leftRange/range )* totalNode );
			update_segment_tree(2*node+1, (a+b)/2+1, b, (a+b)/2+1, r, valRight + 1 - ( rightRange/range )*totalNode, valRight) ;	
		}else{
			totalNode = -valRight+valLeft+1;
			update_segment_tree(2*node, a, (a+b)/2, l, (a+b)/2, valLeft, valRight + 1 - (leftRange/range )* totalNode );
			update_segment_tree(2*node+1, (a+b)/2+1, b, (a+b)/2+1, r, valLeft - 1 + ( rightRange/range )*totalNode, valRight) ;				
		}
	}
	return ;
}

void query_segment_tree(int node, int a, int b){
	int range, leftRange, rightRange, totalNode, leftNode, rightNode;
	int ansLeft = -1, ansRight = -1;
	if(a < b){
		return ;
	}

	if(a != b){ //not a leaf node;
		
		totalNode = b-a+1;
		leftNode = (a+b)/2-a+1;
		rightNode = totalNode - leftNode;
		
		if(lazy_tree[node].leftmost <= lazy_tree[node].rightmost){
			range = lazy_tree[node].rightmost - lazy_tree[node].leftmost + 1;
			leftRange = lazy_tree[node].leftmost + (leftNode/totalNode)*range - 1;
			rightRange = lazy_tree[node].rightmost - (rightNode/totalNode)*range + 1;
			lazy_tree[2*node].leftmost += lazy_tree[node].leftmost; 
			lazy_tree[2*node].rightmost += leftRange;
			lazy_tree[2*node+1].leftmost += rightRange;
			lazy_tree[2*node+1].rightmost += lazy_tree[node].rightmost;
		}else{
			range = lazy_tree[node].leftmost - lazy_tree[node].rightmost + 1;
			leftRange = lazy_tree[node].rightmost - (leftNode/totalNode)*range + 1;
			rightRange = lazy_tree[node].leftmost + (rightNode/totalNode)*range - 1;
			lazy_tree[2*node].leftmost += lazy_tree[node].leftmost; 
			lazy_tree[2*node].rightmost += leftRange;
			lazy_tree[2*node+1].leftmost += rightRange;
			lazy_tree[2*node+1].rightmost += lazy_tree[node].rightmost;
		}
		
	}
	
	if(a == b){
		curShift++;
		if(ans == -1){
			shiftAns = curShift;
			ans = lazy_tree[node].leftmost;
		}else{
			if(ans > lazy_tree[node].leftmost){
				ans = lazy_tree[node].leftmost;
				shiftAns = curShift;
			}
		}
		return;
	}
	
	query_segment_tree(2*node, a, (a+b)/2);
	query_segment_tree(2*node+1, (a+b)/2+1, b);
	return ;
}
int main(){
	int n, i, lastIdx;
	cin>>n;
	for(i=1; i<=n; i++){
		cin>>p[i];
	}
	
	for(i=1; i<=n; i++){
		if(p[i] >= i){
			//range value (p[i]-i,0)
			//range indexes (0,p[i]-i)
			lastIdx = p[i]-i;
			update_segment_tree(1, 1, n, i-1, p[i]-i, p[i]-i, 0);
			if(p[i] < n){
				//range value (1, n-p[i])
				//range indexes (p[i]-i+1,-i+ n)`
				lastIdx = n-i;;
				update_segment_tree(1, 1, n, p[i]-i+1, n-i, 1, n-p[i]);
			}
			if(i > 1){
				//range value (p[i]-1,p[i]-(i-1))
				//range indexes (lastIdx+1,n-1)
				update_segment_tree(1, 1, n, lastIdx+1, n-1, p[i]-1,p[i]-(i-1));
			}
		
		}else if(p[i] < i){
			//range value (-p[i]+i,n-p[i])
			//range indexes (0,n-i)
			update_segment_tree(1, 1, n, 0, n-i, i-p[i], n-p[i]);
			
			//range value (p[i]-1,0)
			//range indexes (n-i+1,n-i+p[i])
			update_segment_tree(1, 1, n, n-i+1, n-i+p[i], p[i]-1, 0);
			
			if(i-p[i]>1){
				//range value (1,i-1-p[i]);
				//range indexes (n-i+1+p[i],n)
				update_segment_tree(1, 1, n, n-i+1+p[i], n, 1, i-1-p[i]);
			}
		}
	}
	ans = curShift = shiftAns = -1;
	query_segment_tree(1, 1, n);
	cout<<ans<<" "<<shiftAns;
	
	return 0;
}
