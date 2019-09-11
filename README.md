# Running-Median-via-AVL-Tree

In a sorted array of integers , median of the array is defined as follows
  ● If there are odd numbers of elements in an array , median element is the middle
of that array E.x [ 1 , 2 , 3] median is 2 and for [ 1 , 3 , 3] median is 3

  ● If there are even numbers of elements in an array , median element is average of
two middle elements of that array E.x [ 1 , 2 , 3 , 4 ] median is ( 2 + 3 ) / 2 and for
[ 1 , 3 , 3 , 5 ] median is 3.

Problem Description : Given a stream of integers , after occurrence of every
number , output the median of array.

Example: Given sequence is 5 , 7 , 1 , 6 , 2 , 3
Explanation: [ 5 ] median is 5 [ 5 , 7] median is (5+7)/2 [ 5 7 1 ] sorted array is
[1 5 7 ] median is 5 [5 7 1 6] sorted array is [1 5 6 7] median is (5 + 6)/2.

This problem has alternative approaches using heap, priority queue etc., but this implementation has been done using 
AVL tree only.

Some insertion sequence to check correctness of LeftLeft, RightRight, LeftRight and RightLeft Rotations:
-14,17,11,7,53,4,13,12,8
-24,30,34,13,8,18,32,22,19,14,6,7,11
