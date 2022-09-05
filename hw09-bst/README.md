# Homework 9

This is the starting readme for this assignment.  Please edit the following information by removing the "*edit me*" and replace it with appropriate information your assignment. If it is asking you a question, please provide a response.

- Name: Prasun Surana

- Description: HW09 - BST. The task was the implement a functioning Binary Search tree using recursive functions.

- How many hours did it take you to complete this assignment? 7 Hours. 

- Did you collaborate with any other students/TAs/Professors? If so, tell us who and in what capacity.
  - I collaborated with my TA Theresa. I had some trouble writing the add function due to the function's parameter taking in a tree instead of a node. Because of this, I found it difficult to call the function recursively, as ordinarily, you would implement it with the parameter being a pointer to a node, so you could call the function using bst_add(root, 15), for instance. Since the root node is clearly not the tree structure itself, the recursive calls did not work. My solution was to create sub-tree structures, and for each node's leftChild and rightChild fields to point to a new subtree, so I could call the function recursively on the subtree. This was cumbersome, and Theresa assisted me in writing a helper function to bypass this problem.

- Did you use any external resources? (Cite them below)
  - https://www.techiedelight.com/insertion-in-bst/

- (Optional) What was your favorite part of the assignment? 
  - The whole assignment was enjoyable.

- (Optional) How would you improve the assignment? 
  - This is not necessarily an improvement to the assignment, but it would be interesting to also implement a 'remove node' function.

## Logistics

For this assignment (and every assignment/lab), you must login into the servers through `your_khoury_name@login.khoury.neu.edu` to complete and test your work. The reason is the examples I will provide below are compiled strictly for our machines architecture, and this is a consistent architecture where your submission will be graded.

## Important notes

* Your code **must compile and run** on the Khoury machines to earn credit. Make sure you test your programs on these machines, as this is where we grade your assignments.
* You must commit any additional files(if any) into your repository so we can test your code.
  * Points will be lost if you forget!
* Do not forget, once you have pushed your changes to your repo make sure that you **submit them to Gradescope before the assignment deadline!**

