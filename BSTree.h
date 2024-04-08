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
			int depth; //used for traversal
			////
			// Initialize class members from constructor arguments by using a 
			// member initializer list. This method uses direct initialization,
			// which is more efficient than using assignment operators inside 
			// the constructor body.
			////

			Pair( KeyComparable & key, Value & value )
				: value{ value },  key{ key }, depth{ 0 }
			{
				// empty constructor...member initializer is doing all the work
			}

	};   // end of Pair class

	// number of values stored in the tree
	int count = 0;
	// capacity of array holding the tree
	int size = 25;
	int height = 0; //height of the tree before initialzing

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

	void remove(int index) {
		/*
		* Removes a "subject" node and replaces it as needed with a predecessor
		* or sucessor. This helper function is "dumb" and assumes that the
		* subject node exists. Use with caution.
		*/


		//DETERMINE INDEX LOCATION OF sucessor
		//We will start with the index for the left and right branch
		int maxLeft = index*2; // subtree
		int minRight = (index*2)+1; //left subtree
		int parent = -1; // set to 0 as a fail safe (removing root?)
		bool isRight = (index % 2 == 1);
		int chosenNode = index;

		if (index != 0){ //are we root?
			//time to do some algorithmic bullcrap to mathematically determine
			// the parent

			parent = index; //copy our index

			if (index % 2 == 1) { // our node is on the right?
				parent -= 1; //subtract 1 
			}

			//now we can ascend the tree by removing a power of two

			parent /= 2; //hehe 

		}


		//check if branches exist, grab the indexes for applicable max/min
		//TODO: this isnt pretty :(
		if(root[index*2] != nullptr) {
			findMax(int maxLeft); 
		}
		else { //left node doesnt exist
			maxLeft = index;
		}

		if(root[(index * 2) + 1] != nullptr) {
			findMin(int minRight); 
		}
		else { //right node doesnt exist
			minRight = index; 
		}
		


		/*
		* The following code discreetly determines how many children the node
		* has. By the program logic, if the min/max indices match, this means
		* that they equal index. 
		* 
		* There is a ternary that returns the index to replace with, handling
		* the incident if there is no left node. We can then use copyNode 
		* recursively to overwrite the tree.
		*/

		if (maxLeft != minRight) { 
			chosenNode = (maxLeft == index) ? minRight : maxLeft;
		}

	

		//we now have the locations of the direct sucessor, predecessor and 
		//the node's parent

		copyNode()
	}

	void copyNode(int source, int destination, 
		const BinarySearchTree& sourceTree = this) {

		if (source == destination && sourceTree == this) {
			return; //no useless overwriting
		}
		//copies node from source to destination
		// destination is assumed to be this tree
		//assumes dynmemory exists
		root[source] = sourceTree->root[destination];
	}

	const Pair* findMin(int index) {
		//helper private to find minimum of a tree recursively
		if (root[index * 2] == nullptr) { return root[index]; }
		index = index * 2;
		return findMin(index * 2 ); //go a level deeper
	}

	/*
	const Pair* findPredecessor(int index, Pair& sucessor,
		int localHeight = -1) {
		/*
		* proof of concept that uses the hashmap-like structure of array BST
		* finds the direct sucessor/predecessor to a given node
		* sucessor will get assigned to the direct sucessor
		* 
		* if the function returns the same address contained at index, there is
		* no predecessor
		* 
		* sucessor expects to be set to root on initial run
		* 
		* Since this is tricky here is an explanation of the patterns: 
		* 1. The depth of the tree signifies the power of 2 that each layer has
		* in common
		* 2. In a layer, the corresponding window for each leaf is 2^(depth)
		* This can be extrapolated locally:
		* 
		* 3. Each subtree has a "window" of 2^(depth) * index
		* 
		* These properties creates a line of symmetry at the root node for the
		* tree or subtree between the predesessor/sucessor, this can be used to
		* find the predecessor with less recursion.
		* 
		* If the node that would be the immediate precesssor/sucesssor is empty
		* , then we need to ascend a level to test the line of symmetry there
		* 
		* 
		*
		*

		//First, determine the depth of the(sub)tree.
		//The variable should be correct here
		if (localHeight == -1) { //if this wasnt overridden
			localHeight = this->height - root[index].depth;
		}
		int localMin = this->index * pow(2, localHeight - 1);
		//any higher and it rolls over to the next local min, so using this:
		int localMax = localMin + pow(2, localHeight - 1) - 1; 

		//we now have the essentials to have the computer visualize the subtree
		//we need to test the axis of symmetry for the lowest level and rise

		if (root[localMax] == nullptr) { //check end
			findPredecessor(index, sucessor, (localHeight - 1) );
		}
		//the local max does exist WAIT SHIT DAMNIT I WAS DOING IT WRONG



		if (root[localMin] == nullptr) {
			return findPredecessor(index, sucessor, (localHeight - 1));
		}

	} 
	*/
	
	const Pair* findMax(int index) {
		//helper private to find max of a tree
		if (root[(index * 2)+1] == nullptr) { return root[index]; }
		index = (index * 2) + 1;
		return findMax((index * 2) + 1 ); //go a level deeper
	}

	int navigate(int index, int count, bool deleteNodes) {
		//recursively navigate to bottom of tree, incrementing an index
		//returns number of valid nodes encountered
		//deletion flag deletes the child node before returning
		//assumes tree is not empty
		
		count++; //we are here already, must be a valid node


		//check if children exist, then count *their* subtrees, report back.
		if (root[index * 2] != nullptr) {
			this->count += navigate(index * 2, count, deleteNodes);
		}
		if (root[(index * 2) + 1] != nullptr) { 
			this->count += navigate((index * 2) + 1, count, deleteNodes);
		}



		if (deleteNode) { delete root[index]; } //delete before we leave

		return count; //ascend the total count to main or recursive parent

	}

	void lateralNavigate(int layer) {
		//proof of concept to navigate across the same level
		//assumes it starts on the very left side
		//int anticipatedLeaves = 
	}
	
public:
	BinarySearchTree() 	{
		//  stub code: needs to be implemented
	}
	
	~BinarySearchTree() {
		makeEmpty();
	}

	/*
	* Finds the node with the smallest element in the tree	
	*/
	const Value findMin() const {
		return findMin(1)->value;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const {
		return findMax(1)->value;
	}

	void findMan() {
		std::cout << "Error detected between chair and monitor\n";
		exit(1);
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
		int index = 1;
		this->count = 1; //set count to be extra sure
		if (isEmpty()) { return; }

		navigate(index, this->count, true);
		this->count = 0;
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
		int index = 1;
		if (find(const KeyComparable & key, int index const) == nullptr) {
			return; //no match
		}

		//we now have a match and it's direct index
		//we need to enumerate the parent, enumerate the children
		//then we need to "promote" the children after killing the specific
		// node

		remove(index);


	}

	int getSize() {
		return this->size;
	}
	bool checkCount() {
		//false means size was incorrect, but has been fixed
		//true means size matched.

		//a double false means something is wrong!

		int index = 1;
		if (isEmpty && count != 0) {
			count = 0;
			return false;
		}
		else if (isEmpty) {
			return true;
		}


		int ourCount = 1; //we're not empty

		ourCount = navigate(index, ourCount, false); //update our count
		if (this->count == ourCount) {
			return true;
		}

		this->count = ourCount;
		return false;
	}

	int getCount() {
		return this->count;
	}



};	// end of BinarySearchTree class