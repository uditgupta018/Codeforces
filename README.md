# Codeforces Problems Tutorials 
This repo contains problems solved on Codeforces (competitive programming).
Also to provide tutorials for these problems.

Mainly Focussing on Dynamic Programmings, Tree, Graphs Problems. 
Currently Div2- C.

## Problem Contents - 
### Div 2-C 
* [1) Subsequences](http://codeforces.com/problemset/problem/597/C) `Dp` `Segnment Tree`
* [2) Journey](http://codeforces.com/problemset/problem/721/C) `Dp` `Graphs` `Topological Sort`
* [3) Coloring Trees](http://codeforces.com/problemset/problem/711/C) `Dp`

## Tutorials - 
1) [1) Subsequences](http://codeforces.com/problemset/problem/597/C)
  ```
   This is DP type problem. Also requires segment trees/BIT. 
   O(nlogn).
  ```
  Consider for index ith <br />
	Now at each index we want to find number of subsequences ending at index i <br />
	of length 1 , 2 , 3 ... k+1 ; <br />
	How we can compute this ? <br />
	say arr[i] == 5 <br />
	if know number of subsequences which end at value either 1 or 2 or 3 or 4 <br />
		  from index 1 to index i+1 <br />
		  pls read above lines again if not clear. <br />
		so now wat the equation becomes <br />
		no of subsequences of length k+1 which end at index i= <br />
		number of subsequences of length k which end at [value 1] from index range 1  to (i-1) of given array  <br />
	+   number of subsequences of length k which end at [value 2] from index range 1  to (i-1) of given array <br />
	+   number of subsequences of length k which end at [value 3] from index range 1  to (i-1) of given array <br />
	+   number of subsequences of length k which end at [value 4] from index range 1  to (i-1) of given array 	<br />
	For this part we can use Segemnt Tree to compute sum of subsequences ...<br />
		Segment tree : we use tree[1] to store number of subsequences which end at value 1 <br />
		             : we use tree[2] to store number of subsequences which end at value 2 <br />
		But we want number of subsequences of length 1 , 2 ,3 .. (k+1)  <br />
		 So we will use 2-d Segment Tree   <br />
     
2) [2) Journey](http://codeforces.com/problemset/problem/721/C)
  - This is graphs problem with DP.
  - Also requires topological sort concept.
  - O(mn).


3)[3) Coloring Trees](http://codeforces.com/problemset/problem/711/C)
  ```
  This is  Dynamic Programming Problem.
  It has lot of corner cases, needs to consider many at each step.
  Whole beauty of problem lies in writing clean correct solution.
  ```

  Solution :-

  `*How to approach and think step wise :-*` <br />
  
  1) First think which values are required. ie *State of DP* <br />

  Say we are iterating from 1 to n th tree... `Complexity O(100)` <br />
  Now, we need to find answer for ith Tree. <br />
  This means we have calculated all answers for 1, 2, 3 .. (i-1) th tree.<br />
  Now think what all values are required at ith tree.<br />
  We need answer such that we have beauty 1, 2, 3, ...(i) ending at tree i. Hence comlexity now `*O(100*100)*`<br />
  <br />
  But for different colors, how we define value of beauty.<br />
  Hence for each color we will store value of beauty<br />
  
  Now , it should be clear that what should be `*DP STATES*`.
  
  * `dp_now[j][k]` will store min cost to color upto all trees till current tree such that
  min cost to color current tree with color j and such that beauty is k
  
  * Similarly `dp_prev[j][k]` will store to color prev tree with color j and such that beauty of all 
  trees ending at prev tree is k.
  
  now think if we have calculated `dp_prev[][]`, how we can calculate `dp_now[][]`.
  
  So think, we are at tree `(ith)` and <br />
  * now, we color with 1, <br />
    * what is min cost such beauty is 1 or 2 or 3 ... or i <br />
  * or if we color with 2,<br />
    * what is min cost such beauty is 1 or 2 or 3 ... or i <br />
   .<br />
   .<br />
   .<br />
  * or if we color with n,<br />
   * what is min cost such beauty is 1 or 2 or 3 ... or i <br />

  ```
  now how to calculate dp_now[j][k]
   1) see if we are coloring with same color as of prev tree then beauty will not increase. 
   take the value = dp_prev[j][k]  
   2) if we are coloring with different color, the beauty increase by 1..and for prev tree consider beauty k-1 and
      color values 1,2,3, ...,m except jth color (as we have to take a different color)
      in this case we have to take minimum of all these.
      
   finally take the minimum of step 1 and step 2. 
   
  ```
  *PlEASE DO HANDLE CORNER CASES AT EACH STEP.*
  * If current tree is colored or not.
  * what if dp_prev[j][k] do not exists.
  






