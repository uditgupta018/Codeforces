#include<iostream>
#include<stdio.h>

using namespace std;

int main(){
	int trees,num_color,beauty;
	int color[105];
	int dp_prev[105][105],dp_now[105][105];
	int min_beauty[105];
	
	//taking input
	cin>>trees>>num_color>>beauty;
	for(i=1;i<=trees;i++)
		cin>>color[i];
	for(i=1;i<=trees;i++){
		for(j=1;j<=num_color;j++){
			cin>>cost[i][j];
		}
	}
	//dp_prev is stores value for the previous tree
	//dp_now stores values for the current tree.
	//dp_now[j][k] -> means to color this tree with color j, such that beauty is k
	//dp_now[j][k] will store the minimum value.
	
	//for 1st tree, initialize, we need init dp_now,which will store value for 1st tree
	//
	for(j=1;j<=num_color;j++){
		for(k=1;k<=1;k++){             // since for 1st tree, beauty can be only 1.
			dp_now[j][k] = cost[1][j]; // hence k <= 1;	
			//for 1st tree , to fill with color j, cost is cost[1][j]
		}
	}
	
	for(i=2;i<=trees;i++){
		//now iterating over all trees.
		//1) transfer the dp_now to dp_prev...since for the new tree we will calculate dp_now[][]
		// using all dp values of prev tree
		
		for(j=1;j<=num_color;j++){
			for(k=1;k<=trees;k++){
				dp_prev[j][k] = dp_now[j][k];
			}
		}
		
		//now init dp_now with -1
		for(j=1;j<=num_color;j++){
			for(k=1;k<=1;k++){             // since for 1st tree, beauty can be only 1.
				dp_now[j][k] = -1; // hence k <= 1;	
				//for 1st tree , to fill with color j, cost is cost[1][j]
			}
		}
		
		//for prev tree , for each columns means for each beauty we need to find minimum value
		//two minimum value in each column
		for(k=1;k<=i;k++){
			for(j=1;j<=num_color){
				
			}
		}
		
		
	}
	return 0;
}
