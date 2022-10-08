# Implementation of Red-black trees in C
 
The idea of this project is to implement Red-Black trees. Red-black tree is a special case of binary search tree. It's aplication is vast because of efficient operation of inserting and deleting node. Worst case time complexity is O(logn)

The implementation of the Red-Black Tree is located in RedBlackTree.h. For the sake of simplicity, we assumed that the data in the nodes are integers.
The functions that are there for testing are inorder - which is used to print the value of nodes in ascending order, and InsertNode and DeleteNode, which are used to add and delete nodes, respectively. The user can test the specified functions using RBTTest.c by calling the functions as desired. In addition to the mentioned functions, there are also functions such as RRotation, LRotation, Repair... But their uncontrolled use could lead to a violation of the basic properties of the Red-Black trees, and therefore they are not recommended to the user.

For now I haven't fixed minor bug - in some case deletion of single node deletes two nodes instead. You are welcome to contact if you identify my error. 
