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
	class Pair {
	public:
		KeyComparable key;
		Value value;
		////
		// Initialize class members from constructor arguments by using a 
		// member initializer list. This method uses direct initialization,
		// which is more efficient than using assignment operators inside 
		// the constructor body.
		////

		Pair(KeyComparable& key, Value& value)
			: value{ value }, key{ key }
		{
			// empty constructor...member initializer is doing all the work
		}

	};   // end of Pair class

	// number of values stored in the tree
	int count;
	// capacity of array holding the tree
	int size;

	/*
	* The array that holds the pairs.
	*
	* NOTE TO SELF: the first pointer is to dynamic memory where the array
	* lives. The second pointer points to the start of the C array.
	*/

	Pair** root;

	//TODO: shrink to fit function, call during printTree

	/*
	* Prints the data of the trea in order based on key to the output stream
	*/

	void printTree(int index, std::ostream& out) const {
		int count = 0;
		int returnIndex = index;
		navigate(index, count, out);
	}

	Pair* find(const KeyComparable& key, int& index) const {
		//Internal function to find a pair

		if ((root[index] == nullptr) || (index > this->size)) {
			return nullptr;
		}


		if (key == root[index]->key) {

			if (key == 104) {
				std::cout << "AAAAAAAAA\n";
			}
			return root[index];
		} //if a match




		if (key < root[index]->key) {
			if (root[index * 2]) { //check left
				index = index * 2; //set to left
				return find(key, index); //call itself again
			}
		}

		if (key > root[index]->key) { //check right
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
	void promote(int index, const bool& startingfromRight) {

		/*
		* Promotes a node to a higher level, recursively checks for lower level
		* DO NOT CALL ON ROOT.
		*/

		if (index <= 0) {
			std::cout << "Cannot Promote Invalid Index!\n";
			exit(index);
		}
		/*
		* since the parent is stored as some power of 2, we can bitshift
		* indiscriminately to grab the index, it will auto discard the LSB in
		* the process, which is what we would have done anyways, saving some
		* resources.
		*
		* we then need to determine "chirality" (stole this word from a friend)
		* then compare it with the direction we are trying to move, we have to
		* do some screwery
		*
		* moving up right, but our node is on the right: after shift, sub 1
		*
		* moving up left
		*
		*/


		//garbage that will be calculated every recursion to get a quick and
		// dirty orientation. we need to know 

		int parent = (index >> 1);
		bool LSB = (index & 1);
		int flow = 0;
		int promotion = parent;
		Pair* keepSake = nullptr;

		//this code calculates if we need to be a sibling of the parent

		if (startingfromRight && !LSB) {
			//if we are moving a left from lower left 
			//if theyre odd (root is from right), but we're not (left node)
			flow = -1;
		}
		else if (!startingfromRight && LSB) {
			flow = 1;
		}

		//we can now get the direct index to go to
		promotion += flow;

		//can assume promotion is addressable because it is a lower power of 2

		if ((index > this->size) || (root[index] == nullptr)) {
			//If the index doesn't exist, set parent to nullptr and leave
			root[promotion] = nullptr;
			return;
		}
		else {
			keepSake = root[index];
		}

		promote((index << 1), startingfromRight); //promote left node
		promote((index << 1) + 1, startingfromRight); //promote right node



		root[promotion] = keepSake;

		return;


	}

	void yeet(int index) {
		/*
		* There is something special about this array, its an array of pointers
		* We're going to take advantage of this. Instead of merely copying the
		* data, we are going to actually reassign the pointers to potentially
		* save on resources.
		*
		* This is a dumb function that assumes whatever is calling it knows
		* what it's doing. Use with caution.
		*/

		Pair* subjectNode = root[index]; //store the current memory address
		reassign(index);
		delete subjectNode; //free this dyn mem
		subjectNode = nullptr;
		this->count--;
	}



	void reassign(int index) {
		/*
		* Replaces a subject node recursively as needed with a predecessor
		* or sucessor. This helper function is "dumb" and assumes that the
		* subject node exists. Use with caution.
		*
		*/
		//is this dumb? maybe
		//this reps a node that doesnt exist for clarity: a placeholder

		constexpr int nodeDNE = -5000;



		//DETERMINE INDEX LOCATION OF predecessor


		int maxLeft = nodeDNE;
		int minRight = nodeDNE;
		int parent = nodeDNE;
		int chosenNode = nodeDNE;


		int leftNode = (index << 1);
		int rightNode = (index << 1) + 1;

		bool parentfromRight = false;

		//test Right and Left
		if (leftNode > this->size || root[leftNode] == nullptr) {
			leftNode = nodeDNE;
		}
		if (rightNode > this->size || root[rightNode] == nullptr) {
			rightNode = nodeDNE;
		}



		Pair* hopper = nullptr;


		//check if branches exist, grab the indexes for applicable max/min

		if (leftNode > 0) {
			maxLeft = findMaxIndex(leftNode);
		}
		else if (rightNode > 0) { //left node doesnt exist
			minRight = findMinIndex(rightNode);
		}
		else {
			//no children
			root[index] = nullptr;
			return;
		}

		if (maxLeft != nodeDNE) {
			chosenNode = maxLeft;

			parentfromRight = false;
		}
		else {
			chosenNode = minRight;
			parentfromRight = true;
		}

		//we now know the direct sucessor or predecessor's exact location
		//get a backup of the ptr so we dont lose it

		hopper = root[chosenNode];

		//we now want to navigate to the succ/pred node's only child
		//remember, LSB: 0 -> left, 1 -> right
		//so in this case, if we are on the right, go left. vice versa

		if (!parentfromRight) {
			chosenNode = (chosenNode << 1);
		}
		else {
			chosenNode = (chosenNode << 1) + 1;
		}

		//now, we want to "promote" that child and all decendants to the next
		//layer up

		promote(chosenNode, parentfromRight);

		// our current node is overwritten now, its time to push the saved ptr
		root[index] = hopper;

		return;


	}


	const Pair* findMax(int index) const {
		//helper private to find max of a tree
		if ((((index * 2) + 1) > this->size)
			|| root[(index * 2) + 1] == nullptr) {
			return root[index];
		}
		index = (index * 2) + 1;
		return findMax((index * 2) + 1); //go a level deeper
	}
	const Pair* findMin(int index) const {
		//helper private to find minimum of a tree recursively
		if (((index * 2) > this->size)
			|| root[index * 2] == nullptr) {
			return root[index];
		}
		index = index * 2;
		return findMin(index); //go a level deeper

	}

	//same thing but gives me an index
	int findMaxIndex(int index) {
		//helper private to find max of a tree
		if ((((index * 2) + 1) > this->size)
			|| root[(index * 2) + 1] == nullptr) {
			return index;
		}
		index = (index * 2) + 1;
		return findMaxIndex(index); //go a level deeper
	}

	
	int findMinIndex(int index) {
		//helper private to find minimum of a tree recursively
		if (((index * 2) > this->size)
			|| root[index * 2] == nullptr) {
			return index;
		}
		index = index * 2;
		return findMinIndex(index); //go a level deeper
	}

	//Note to self. RETURNS A POINTER TO A PAIR



	int navigate(int index, int count, std::ostream& out) const {
		//recursively navigate to bottom of tree, incrementing an index
		//returns number of valid nodes encountered
		//deletion flag deletes the child node before returning
		//assumes tree is not empty

		 //we are here already, must be a valid node


		if (root[index] == nullptr) {
			cout << "WHOOPSIE\n";
		}

		//check if children exist, then count *their* subtrees, report back.
		if (((index * 2) <= this->size) && (root[index * 2] != nullptr)) {
			count += navigate(index * 2, count, out);
			count++;
		}



		out << *(root[index]->value) << endl;

		if ((((index * 2) + 1) <= this->size)
			&& (root[(index * 2) + 1] != nullptr)) {
			count += navigate((index * 2) + 1, count, out);
			count++;
		}

		return count; //ascend the total count to main or recursive parent

	}
	//overload without ostream
	int navigate(int index, int count, bool deleteNodes) {
		//recursively navigate to bottom of tree, incrementing an index
		//returns number of valid nodes encountered
		//deletion flag deletes the child node before returning
		//assumes tree is not empty
		//this is not a safe function

		count++; //we are here already, must be a valid node


		//check if children exist, then count *their* subtrees, report back.
		if (root[index * 2] != nullptr && (index * 2) < this->size) {
			count += navigate(index * 2, count, deleteNodes);
			count++;
		}

		if (root[(index * 2) + 1] != nullptr
			&& ((index * 2) + 1) < this->size) {
			count += navigate((index * 2) + 1, count, deleteNodes);
			count++;
		}



		if (deleteNodes) { delete root[index]; } //delete before we leave

		return count; //ascend the total count to main or recursive parent

	}



	void reallocate(int newSize) {
		//reallocates to new size, copies over, fills rest with nullptr

		int i = 0;
		Pair** newRoot = new Pair * [(newSize + 1)];

		//fill newarray with nullptr
		for (; i <= newSize; i++) {
			newRoot[i] = nullptr;
		}


		for (i = 0; i <= this->size; i++) {
			newRoot[i] = root[i];
		}




		delete root; //delete the ptr array
		root = newRoot; //its now safe to assign root
		this->size = newSize;
		return;
	}


public:
	BinarySearchTree() {
		//  stub code: needs to be implemented
		size = 25;
		count = 0;
		root = new Pair * [(size + 1)];
		for (int i = 0; i <= this->size; i++) {
			root[i] = nullptr;
		}
	}

	~BinarySearchTree() {
		makeEmpty();
		delete root;
	}

	void debugPrint() {
		std::cout << "printing entire array, skipping nullptrs\n";
		for (int i = 0; i <= this->size; i++) {

			if (root[i] != nullptr) {
				std::cout << i << ": " << root[i]->key;
				if (root[i]->key < 0) {
					std::cout << " Invalid Index, memory uninitialized!";
				}
				std::cout << endl;
			}
		}
	}
	void printTreeStructure(std::ostream& out) const {
		/*
		* First, we need to determine the total height of the(sub)tree
		* The height is obtained by logging the size, truncating the decimal, then
		* adding 1. This should work for any allocated size
		*
		* index is our (sub)root.
		*/


		// int localHeight = -((log(index) / log(2)) - height);

		int i = 0;
		int layer = 0;
		int cachedSize = this->size;

		for (layer = 0; cachedSize > 0; layer++) {
			cachedSize >> 1;
		}

		//we now know layers.

		int localKey = 0;

		while (layer > 0) {



			if (index > this->size) {
				localKey = -2;
			}
			else if (root[index] == nullptr) {
				localKey = -1;
			}
			else {
				localKey = root[index]->key;
			}

			for (i = 0; i <= layers; i++) {
				out << "   ";
			}
			out << setw(6) << localKey;



		}


		//loop through margin tab
	}

	/*
	* Finds the node with the smallest element in the tree
	*/
	const Value findMin() const {
		int index = 1;
		return findMin(index)->value;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const {
		//when templatized value becomes computerscientist pointer

		int index = 1;
		return findMax(index)->value;
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
	bool find(const KeyComparable& argKey, Value& founditem) const {
		int index = 1;

		if (find(argKey, index) == nullptr) {
			return false;
		}

		founditem = root[index]->value; //We have a match, store it.

		return true;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable& argKey) const {
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
	void printTree(std::ostream& out = cout) const {
		out << "I'm printin the treeeeeee\n";
		printTree(1, out);

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
	bool insert(Value value, KeyComparable key) {
		/*
		* Determine the index to insert to, if its a nullptr or greater than
		* the size, hold onto the index. clone the list with the new index.
		*/

		//this is where we start
		int index = 1;


		//are we inbounds?
		while ((index <= this->size) && (root[index] != nullptr)) {

			if (root[index]->key == key) {
				std::cout << "DUPLICATE BLOCKED\n";
				return false;
			}

			//mini navigate
			//note to self
			//go right (greater than -> index * 2 + 1
			//go left -> index *2
			/*if (key > root[index]->key) {
				std::cout << key << " IS GREATER THAN " << root[index]->key
					<< " ... Moving Right\n";
			}
			else {
				std::cout << key << " IS LESS THAN " << root[index]->key
					<< " ... Moving LEFT\n";
			}
			*/
			index = (index * 2) + (key > root[index]->key);

		}

		if (index > this->size) {

			reallocate(index);
		}

		/*if (key == 10) {
			std:cout << "AAAAAAAAAA\n";
		}*/

		root[index] = new Pair(key, value);
		this->count++;
		return true;
	}

	/*
	* Removes the nodes if it contains the given item
	* Start at root.
	*/
	void remove(const KeyComparable& key) {
		//PHASE 1: Identify a match
		int index = 1;
		if (find(key, index) == nullptr) {
			return; //no match
		}

		//we now have a match and it's direct index
		//we need to enumerate the parent, enumerate the children
		//then we need to "promote" the children after killing the specific
		// node

		yeet(index); //compiler was screaming when i had this as remove()


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


};
// end of BinarySearchTree class