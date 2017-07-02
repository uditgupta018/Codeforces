# Codeforces Problems Tutorials  
This repo contains problems solved on Codeforces (competitive programming).
Also to provide tutorials for these problems.

Mainly Focussing on Dynamic Programmings, Tree, Graphs Problems. 
Currently Div2- C.

## Problem Contents - 
### Div 2-C 
* [1) Subsequences](http://codeforces.com/problemset/problem/597/C) `Dp` `Segment Tree`
* [2) Journey](http://codeforces.com/problemset/problem/721/C) `Dp` `Graphs` `Topological Sort`
* [3) Coloring Trees](http://codeforces.com/problemset/problem/711/C) `Dp`
* [4) Mister B and PR Shifts](http://codeforces.com/problemset/problem/820/D) `Segment Tree` `Lazy Update`
## Tutorials - 
[4) Mister B and PR Shifts](http://codeforces.com/problemset/problem/820/D)
```
If your are familier with concept of Segment Trees with Lazy Update, Please go ahead and read the solution. 
If not, please do these two classic simple problems of Segment Trees with Lazy Update on Codchef. 
Then come back to this problem. This problem is a classic implementation of Segment Trees. 
Purpose of this tutorial is to help you find your solution and not just giving the solutions.
```
* [Flipcoin Codechef](https://www.codechef.com/problems/FLIPCOIN) <br/>
  You can read my commented code for this flipcoin (https://www.codechef.com/viewsolution/4341486)
* [MultQ3 Codechef](https://www.codechef.com/problems/MULTQ3)  <br/>
  You can read my commented code for this MultQ3 (https://www.codechef.com/viewsolution/4342905)
  
  ![Alt text](https://user-images.githubusercontent.com/26462566/27768658-46f17eb6-5f36-11e7-8c24-d1ff7072dcd8.jpg) <br/>
 Now we will consider with above example. Hope this example is self explanatory.
 Now think how you can exploit this concept of adding a value in a range. Try yourself. Think in terms of segment tree.
 
 Now step two - Thinking how actually this problem is adding in a range problem. 
 
 ![Text](https://user-images.githubusercontent.com/26462566/27768833-3209fb0a-5f3a-11e7-8a84-e5a520a56c97.jpg) <br/>
 <br/>
 ```
 Consider example -  <br/>
          P1 P2 P3 P4 P5 P6 P7 P8 P9 P10<br/>
	  8  3  5  7  4  9  10 1  2  6   <br />
 Think all the case i.e. in what range we add to what values. ? Try yourself. <br/>	  
 Case 1. p[i] >= i <br/>
         Take p[4] = 7<br/>
	 for shift id             Id0   Id1  Id2  Id3  Id4  Id5 Id6  Id7  Id8  Id9<br/>
	 value which is to be <br/>
	 added  -->               3     2    1    0    1    2   3    6    5    4<br/>
	 <br/>
	 (hope you understands this. !!!!)   bingo go ahead...<br/>
	 deduction now <br/>
	  <br/>
	  Case 1.1   We have to add values (3, 2, 1, 0) for shift id range (0, 1, 2, 3)<br/>
	  Case 1.2   We have to add values (1, 2, 3, 0) for shift id range (4, 5, 6)<br/>
	  Case 1.3   We have to add values (6, 5, 4) for shift id range (7, 8, 9)<br/>
 Case 2. p[i] < i <br/>
         Try yourself. Code will help. Code is commented. Please see if you are struck. <br/>
	  

```	  
 
 ```
 So now we have to add a arithmetic progression in some range in a segment tree.
  ```
 Adding some value to Segment tree is direct problem. Now think how we can add AP to ST.
 Before going to this, please evaluate what must be final answer and time complexity.
 
 ```
 Since leaves store the value which are added to a particular shift. 
 	Like 1st leave store value to be added for 0 shift.
	     2nd leave store value to be added for 1st shift.
 Hence we need to take the minimum of all leaves.
 Therefore query segment tree once in the end. 
 Updating Segment tree is O(Logn)
 Total time complexity O(nLogn).
 ```
 <b> Step 3 - Adding Arithmetic Progression to Segment Tree using Segment Tree with Lazy propogation. </b>  
 
 

[1) Subsequences](http://codeforces.com/problemset/problem/597/C)
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
     
[2) Journey](http://codeforces.com/problemset/problem/721/C)
  - This is graphs problem with DP.
  - Also requires topological sort concept.
  - O(mn).


[3) Coloring Trees](http://codeforces.com/problemset/problem/711/C)
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
  






