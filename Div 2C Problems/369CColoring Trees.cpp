#include<iostream>
#include<stdio.h>
#include<algorithm>

using namespace std;

int main(){

	int trees, num_color, beauty;
	int color[105], cost[105][105];
	int dp_prev[105][105], dp_now[105][105];
	int min_beauty[105][2];
	int i, j, k, min1, min2, take_value, ans;
	
	//taking input
	cin>>trees>>num_color>>beauty;
	for(i=1; i<=trees; i++)
		cin>>color[i];
	
	for(i=1; i<=trees; i++){
		for(j=1; j<=num_color; j++){
			cin>>cost[i][j];  //cost is to color ith tree with jth color;
		}
	}
	
	//dp_prev is stores value for the previous tree
	//dp_now stores values for the current tree.
	//dp_now[j][k] -> means to color this tree with color j, such that beauty is k
	//dp_now[j][k] will store the minimum value.
	
	//for 1st tree, initialize, we need init dp_now,which will store value for 1st tree
	//
	for(j=1; j<=num_color; j++){
		for(k=1; k<=1; k++){             // since for 1st tree, beauty can be only 1.
			dp_now[j][k] = cost[1][j]; // hence k <= 1;	
			//for 1st tree , to fill with color j, cost is cost[1][j]
		}
	}
	
	for(i=2; i<=trees; i++){
		//now iterating over all trees.
		//1) transfer the dp_now to dp_prev...since for the new tree we will calculate dp_now[][]
		// using all dp values of prev tree
		
		for(j=1; j<=num_color; j++){
			for(k=1; k<=trees; k++){
				dp_prev[j][k] = dp_now[j][k];
			}
		}
		
		//now init dp_now with -1
		for(j=1; j<=num_color; j++){
			for(k=1; k<=1; k++){             // since for 1st tree, beauty can be only 1.
				dp_now[j][k] = -1; // hence k <= 1;	
				//for 1st tree , to fill with color j, cost is cost[1][j]
			}
		}
		
		//for prev tree , for each columns means for each beauty we need to find minimum value
		//two minimum value in each column
		//taking n==1 as edge case ; will consider it seperately
		
		//finding two minimums in each column
		//
		min1 = -1;
		min2 = -1;
		for(k=1; k<=i; k++){     //beauty will not be greater than ith tree (i.e i value)
			for(j=1; j<=num_color; j++){
				if(dp_prev[j][k] != -1){
					
					//i.e we can color (i-1) the tree with color j such that beauty ending at tree is "k"
					
					if(min1 == -1){  //none of min1,min2 exists till now
						min1 = dp_prev[j][k]; 
					}else if(min2 == -1){ //if min1 exists but not min2.
						min2 = dp_prev[j][k]; 
					}else{ //both exists , then compare logically
						
						if(min2 < dp_prev[j][k]){
						}else if(dp_prev[j][k] < min1){
							min2 = min1;
							min1 = dp_prev[j][k];
						}else{
							min2 = dp_prev[j][k];
						}
					}
														
				}	
			}
			min_beauty[k][0] = min1;
			min_beauty[k][1] = min2;
		}
		
		
		//now we need to calc dp_now[][] table for the ith tree (current tree )
		for(j=1; j<=num_color; j++){
			for(k=1; k<=beauty; k++){
				//if filling with same color beauty is same
				//or filling with diff color form prev tree beauty inc by 1
				//in this case take min of all dp_prev[j'][k-1] where consider j' as all values j'!=j
				if(k != 1){
					min1 = min_beauty[k-1][0];
					min2 = min_beauty[k-1][1];
				}else{
					min1 = min2 = -1;
				}
				
				if(color[i] != 0){
					if(k != -1){
									
						if(dp_prev[j][k-1] != min1){
							take_value = min1;
						}else {
							take_value = min2;
						}
						
					}else {
						take_value = -1;
					}
					
					//consider all cases carefullyy..special when value dont exist for prev treee
					if((dp_prev[j][k] != -1) && (take_value != -1)){
						dp_now[j][k] = min(take_value, dp_prev[j][k] + cost[i][j]);	
					}else if(take_value != -1){
						dp_now[j][k] = take_value;
					}else if(dp_prev[j][k] != -1){
						dp_now[j][k] = dp_prev[j][k] + cost[i][j];
					}else{
						dp_now[j][k] = -1;
					}
				}else if(color[i] && j == color[i]){
					
					if(k != -1){
									
						if(dp_prev[j][k-1] != min1){
							take_value = min1;
						}else {
							take_value = min2;
						}
						
					}else {
						take_value = -1;
					}
					
					//consider all cases carefullyy..special when value dont exist for prev treee
					if((dp_prev[j][k] != -1) && (take_value != -1)){
						dp_now[j][k] = min(take_value, dp_prev[j][k]);	
					}else if(take_value != -1){
						dp_now[j][k] = take_value;
					}else if(dp_prev[j][k] != -1){
						dp_now[j][k] = dp_prev[j][k] + cost[i][j];
					}else{
						dp_now[j][k] = -1;
					}
							
				}else {
					
					dp_now[j][k] = -1;
				
				}
			}
		}
	}
	
	ans = -1;
	for(i=1; i<=num_color; i++){
		if(dp_now[i][beauty] != -1){
			ans = min(ans,dp_now[i][beauty]);
		}
	}
	cout<<ans;
	return 0;
}
