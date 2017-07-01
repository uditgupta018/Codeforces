//Segment tree with lazy update
#include<iostream>
#include<stdio.h>
#define LL long long int
using namespace std;

struct seg{
	LL leftmost, rightmost;
}lazy_tree[7000005];
int p[1000005];
int curShift, shiftAns;
LL ans;

void build_segment_tree(int node, int a, int b){
	if(b<a){
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
void update_segment_tree(int node, int a, int b, int l ,int r, LL valLeft, LL valRight){
	LL range, leftRange, rightRange, totalNode;
	//debug
	/*cout<<"a b l r valL val R"<<endl;
	cout<<a<<" "<<b<<" "<<l<<" "<<r<<" "<<valLeft<<" "<<valRight<<endl<<endl;
	*/
	if(b<a){
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
		range = r-l+(LL)1;
		leftRange = (a+b)/2-l+(LL)1;
		rightRange = range - leftRange;
		
	                  
		if(valLeft <= valRight){
			totalNode = valRight-valLeft+(LL)1;
			update_segment_tree(2*node, a, (a+b)/2, l, (a+b)/2, valLeft , valLeft - (LL)1 + (leftRange* totalNode)/range );
			update_segment_tree(2*node+1, (a+b)/2+1, b, (a+b)/2+1, r, valRight + (LL)1 - ( rightRange*totalNode)/range, valRight) ;	
		}else{
			totalNode = -valRight+valLeft+(LL)1;
			update_segment_tree(2*node, a, (a+b)/2, l, (a+b)/2, valLeft, valLeft + (LL)1 - (leftRange* totalNode)/range );
			update_segment_tree(2*node+1, (a+b)/2+1, b, (a+b)/2+1, r, valRight - (LL)1 + ( rightRange*totalNode)/range, valRight) ;				
		}
	}
	return ;
}

void query_segment_tree(int node, int a, int b){
	LL range, leftRange, rightRange, totalNode, leftNode, rightNode;
	LL ansLeft = -1, ansRight = -1, diff;
	if(b < a){
		return ;
	}

	if(a != b){ //not a leaf node;
		
		totalNode = b-a+(LL)1;
		leftNode = (a+b)/2-a+(LL)1;
		rightNode = totalNode - leftNode;
		
		diff = (lazy_tree[node].rightmost - lazy_tree[node].leftmost)/(b-a);
		lazy_tree[2*node].leftmost += lazy_tree[node].leftmost; 
		lazy_tree[2*node].rightmost += lazy_tree[node].leftmost + ((b+a)/2-a)*diff;
		lazy_tree[2*node+1].leftmost += lazy_tree[node].leftmost + ((a+b)/2-a+(LL)1)*diff;
		lazy_tree[2*node+1].rightmost += lazy_tree[node].rightmost;
		
		
		/*
		if(lazy_tree[node].leftmost <= lazy_tree[node].rightmost){
			range = lazy_tree[node].rightmost - lazy_tree[node].leftmost;
			leftRange = lazy_tree[node].leftmost + ((leftNode-1)/totalNode)*range;
			rightRange = lazy_tree[node].rightmost - ((rightNode-1)/totalNode)*range;
			lazy_tree[2*node].leftmost += lazy_tree[node].leftmost; 
			lazy_tree[2*node].rightmost += leftRange;
			lazy_tree[2*node+1].leftmost += rightRange;
			lazy_tree[2*node+1].rightmost += lazy_tree[node].rightmost;
		}else{
			range = lazy_tree[node].leftmost - lazy_tree[node].rightmost;
			leftRange = lazy_tree[node].leftmost - ((leftNode-1)/totalNode)*range;
			rightRange = lazy_tree[node].rightmost + ((rightNode-1)/totalNode)*range;
			lazy_tree[2*node].leftmost += lazy_tree[node].leftmost; 
			lazy_tree[2*node].rightmost += leftRange;
			lazy_tree[2*node+1].leftmost += rightRange;
			lazy_tree[2*node+1].rightmost += lazy_tree[node].rightmost;
		}*/
		
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

void debug(){
	for(int i=1; i<=19; i++){
		cout<<"node";
		cout<<i<<"range "<<lazy_tree[i].leftmost<<" "<<lazy_tree[i].rightmost<<endl;
	}
}
int main(){
	int n, i, lastIdx;
	cin>>n;
	for(i=1; i<=n; i++){
		//cin>>p[i];
		scanf("%d",&p[i]);
	}
	build_segment_tree(1, 0, n-1);
	for(i=1; i<=n; i++){
		if(p[i] >= i){
			//range value (p[i]-i,0)
			//range indexes (0,p[i]-i)
			lastIdx = p[i]-i;
			update_segment_tree(1, 0, n-1, 0, p[i]-i, p[i]-i, 0);
	//		cout<<"came back 1.1"<<endl;
			if(p[i] < n){
				//range value (1, n-p[i])
				//range indexes (p[i]-i+1,-i+ n)`
				lastIdx = n-i;
				update_segment_tree(1, 0, n-1, p[i]-i+1, n-i, 1, n-p[i]);
			}
			if(i > 1){
				//range value (p[i]-1,p[i]-(i-1))
				//range indexes (lastIdx+1,n-1)
				update_segment_tree(1, 0, n-1, lastIdx+1, n-1, p[i]-1,p[i]-(i-1));
			}
		
		}else if(p[i] < i){
			//range value (-p[i]+i,n-p[i])
			//range indexes (0,n-i)
			update_segment_tree(1, 0, n-1, 0, n-i, i-p[i], n-p[i]);
			
			//range value (p[i]-1,0)
			//range indexes (n-i+1,n-i+p[i])
			update_segment_tree(1, 0, n-1, n-i+1, n-i+p[i], p[i]-1, 0);
			
			if(i-p[i]>1){
				//range value (1,i-1-p[i]);
				//range indexes (n-i+1+p[i],n)
				update_segment_tree(1, 0, n-1, n-i+1+p[i], n-1, 1, i-1-p[i]);
			}
		}
		/*debug();
		cout<<endl<<endl;*/
	}
	
	ans = curShift = shiftAns = -1;
	//cout<<endl;debug();
	query_segment_tree(1, 0, n-1);
	//cout<<endl;debug();
	cout<<ans<<" "<<shiftAns;
	
	return 0;
}
