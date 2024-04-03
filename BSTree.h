#include "BSTInterface.h"
#include <string>

using namespace std;
template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >
{
private:
	
	/*
	* Private "Node" Class...for this implementation, the Pair is the Node
	*/
	class Pair 	{
		public:
			KeyComparable key;
			Value value;
						
			////
			// Initialize class members from constructor arguments by using a 
			// member initializer list. This method uses direct initialization,
			// which is more efficient than using assignment operators inside 
			// the constructor body.
			////

			Pair( KeyComparable & key, Value & value )
				: value{ value },  key{ key }
			{
				// empty constructor...member initializer is doing all the work
			}

	};   // end of Pair class

	// number of values stored in the tree
	int count = 0;
	// capacity of array holding the tree
	int size = 25;

	/*
	* The array that holds the pairs.
	* 
	* NOTE TO SELF: the first pointer is to dynamic memory where the array 
	* lives. The second pointer points to the start of the C array.
	*/

	Pair* *root = new Pair*[size];
		
	/*
	* Prints the data of the trea in order based on key to the output stream
	*/

	void printTree(int index, std::ostream & out) const {
		//  stub code: needs to be implemented
	}

	Pair* find(const KeyComparable& key, int index const) {
		//Internal function to find a pair
		if (key == root[index]->key) { return root[index]; } //if a match

		if (key > root[index]->key) {
			if (root[index*2]) { //check left
				index = index * 2; //set to left
				return find(key, index); //call itself again
			}
		}

		if (key < root[index]->key) { //check right
			if (root[(index * 2) + 1]) {
				index = (index * 2) + 1; // set to right
				return find(key, index);
			}
		}

		////
		// When here: if node has a value, and the value is greater or less 
		// than all other values, we can then take node and use that for insert
		////

		return nullptr;
	}
	
public:
	BinarySearchTree() 	{
		//  stub code: needs to be implemented
	}
	
	~BinarySearchTree() {
		//  stub code: needs to be implemented
	}

	/*
	* Finds the node with the smallest element in the tree	
	*/
	const Value findMin() const {
		//  stub code: needs to be implemented
		return nullptr;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const {
		//  stub code: needs to be implemented
		return nullptr;
	}

	/*
	* Finds the node with a key that matches the argKey 
	* updates the founditem refrerence if found
	* returns true if it was found 
	* returns false if it was not 
	*/
	bool find(const KeyComparable & argKey , Value & founditem) const 	{
		int index = 1;
	
		if (find(const KeyComparable & key, int index const) == nullptr) {
			return false; 
		}
		
		founditem = root[index]->value; //We have a match, store it.

		return true;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable & argKey) const {
		return false;
	}

	/*
	* Returns true if tree has no nodes
	*/
	bool isEmpty() const {
		//  stub code: needs to be implemented
		return root == nullptr;
	}

	/*
	* Prints all the data from the tree in order based on key
	*/
	void printTree(std::ostream & out = cout) const {
		printTree(0 , out);
		//  stub code: needs to be implemented
	}

	/*
	* Removes all nodes from the tree
	*/
	void makeEmpty() {
		//  stub code: needs to be implemented
	}

	/*
	* Inserts a node into the tree
	* maintains this property of the tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater
	*/
	bool insert( Value value,  KeyComparable key) 	{
		//  stub code: needs to be implemented
		return false;
	}

	/*
	* Removes the nodes if it contains the given item
	* Start at root.
	*/
	void remove(const KeyComparable & key) 	{
		//PHASE 1: Identify a match

		int match = 1; //set to 1 to start at root


	}

	int getSize() {
		//  stub code: needs to be implemented
		return 0;
	}

	int getCount() {
		//  stub code: needs to be implemented
		return 0;
	}

};	// end of BinarySearchTree class