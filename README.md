# Generic Programming Project
## Implementation of Treaps

### Team Members:

* Darshan D
* Karan Kumar G
* Mayur Peshve

### Abstract

A project aimed at implementing Treap as a generic data structure along with the different functionalities of a treap. Treap is a data structure that stores pairs (say [X,Y]) in a binary tree such that it is a binary search tree by X and a binary heap by Y. In such an implementation, the X values are the keys while the Y values are the priorities that specify how the tree is constructed. In this project, the priorities are randomized, thereby using Randomization and the Binary Heap property (specifically, the max heap property in our implementation) to construct a randomized balanced binary search tree that maintains balance with high probability. The entire treap and its individual nodes were built as generic canonical classes, thereby supporting all the different data types. The project involved the implementation of multiple operations such as insert node, delete node, split treap, merge two treaps, union, intersection, difference, and traversal of treaps. A bidirectional iterator was implemented as a nested class within the treap class. Multiple member algorithms such as find and replace were implemented for treaps. This project was developed and implemented as part of the Generic Programming Course during our Undergraduate Study.

### Operations supported for a Treap

* Insert node
  * Function signature: void insert(key_t key)
  * Inserts the key as a node into the treap

* Delete node
  * Function signature: void delete_(key_t key)
  * Deletes the node with the key passed as argument
 
* Split treap
  * Function signature: void split(key_t key, Treap_t *left_sub_treap, Treap_t *right_sub_treap)
  * Splits the treap into two subtrees based on the key passed. The two subtrees are stored in the left_sub_treap and right_sub_treap respectively

* Merge treaps
  * Function signature: void merge(Treap_t *left_sub_treap, Treap_t *right_sub_treap)
  * Merges the two treaps left_sub_treap and right_sub_treap into one treap and modifies this pointer(object through which the function is called) to point to this new merged treap

* Union
  * Function signature: void union_treaps(Treap_t *treap1, Treap_t *treap2)
  * Finds the union of the two treaps treap1 and treap2. Duplicates are handled such that the final treap only considers one copy of the key. The object through which the function is called is made to point to this new treap generated after performing the union operation.

* Intersection
  * Function signature: void intersect_treaps(Treap_t *treap1, Treap_t *treap2)
  * Finds the intersection of the two treaps treap1 and treap2. The object through which the function is called is made to point to this new treap generated after performing the intersection operation

* Difference
  * Function signature: void diff_treap(Treap_t *treap1, Treap_t *treap2)
  * Finds the difference of the two treaps treap1 and treap2. The object through which the function is called is made to point to this new treap generated after performing the difference operation

* Traversals
  * Inorder
    * Function signature: void inorder()
    * Performs inorder traversal of the treap
  * Preorder
    * Function signature: void preorder()
    * Performs preorder traversal of the treap
  * Postorder
    * Function signature: void postorder()
    * Performs postorder traversal of the treap
  
* Member Find
  * Function signature: Iterator find(Iterator first, Iterator last, key_t search_key)
  * Finds and returns an iterator pointing to the node containing the key passed as argument. The find operation is performed in O(logn) time.
  * If the key is not found, the end iterator is returned
 
* Member Replace
  * Function signature: void replace(Iterator first, Iterator last, key_t old_value, key_t new_value)
  * Finds and replaces the node containing the old_value with the new_value

### Details about running the Software

* The implementation file consisting of all the implementation code and functions with respect to treaps has been provided as a header file that the client can include in their programs
* This header file (**treap.h**) has been placed inside the **Source_Code** folder of this repository
* The way to include it is as follows: ```#include “treap.h”```
* Once this is included, clients can create treaps and call functions to perform different operations as explained above using the provided interfaces
* The client file is then compiled using the g++ utility:
```g++ client.cpp -o exec```
* The **Source_Code** folder of this repository contains multiple client files that check for different implemented functionalities of the treap
  * **client1.cpp** - Checks for insertion and deletion of nodes and copying treaps
  * **client2.cpp** - Checks for split and merge operations on the treaps
  * **client3.cpp** - Checks for Union, Intersection, and Difference set operations
  * **client4.cpp** - Testing of Iterators on member and generic algorithms
  * **client5.cpp** - Checks for move constructor and move assignment operator
* The generated executable is then loaded and executed as follows:
```./exec```


