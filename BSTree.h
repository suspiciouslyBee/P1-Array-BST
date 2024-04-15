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
	int count;
	// capacity of array holding the tree
	int size;

	/*
	* The array that holds the pairs.
	* 
	* NOTE TO SELF: the first pointer is to dynamic memory where the array 
	* lives. The second pointer points to the start of the C array.
	*/

	Pair* *root;
	
	//TODO: shrink to fit function, call during printTree

	/*
	* Prints the data of the trea in order based on key to the output stream
	*/

	void printTree(int index, std::ostream & out) const {
		int count = 0;
		int returnIndex = index;

		navigate(index, count, out);
	}

	Pair* find(const KeyComparable& key, int &index) const {
		//Internal function to find a pair
		if (key == root[index]->key) { return root[index]; } //if a match

		if (key < root[index]->key) {
			if (root[index*2]) { //check left
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
	}

	void promote(int index) {
		/*
		* Promotes a node to a higher level, recursively checks for lower level
		* DO NOT CALL ON ROOT. Directly promotes, not smart
		*/

		
		//Determine Parent
		//Determine if we are on the left or right branch of the parent
		int parent = -1;


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

		if (root[index] == nullptr) {
			//if we have reached a leaf, we must then "free" the parent
			root[parent] = nullptr;
			return;
		}
		

		int promotion = parent + (index % 2 == 1); 
		
		/*
		* we have our source, our destination, time to actually raise
		* this will create a duplicate: we need to determine if the source has
		* children too
		*/
		root[promotion] = root[index];
		promote((index * 2)); //promote left node
		promote((index * 2) + 1); //promote right node

		
		return;


	}

	void reassign(int index) {
		/*
		* Replaces a subject node recursively as needed with a predecessor
		* or sucessor. This helper function is "dumb" and assumes that the
		* subject node exists. Use with caution.
		* 
		*/


		//DETERMINE INDEX LOCATION OF sucessor
		//We will start with the index for the left and right branch
		int maxLeft = index*2; // subtree
		int minRight = (index*2)+1; //left subtree
		int parent = -1; // set to 0 as a fail safe (removing root?)
		bool isRight = (index % 2 == 1);
		int chosenNode = index;
		Pair* hopper = nullptr;


		//check if branches exist, grab the indexes for applicable max/min
		//TODO: this isnt pretty :(

		/*
		* We need to determine both if the right and left nodes even exist. If
		* they do not, then we set it to index because of the implication that
		* the root node is infact the smallest or greatest node in the subtree
		* 
		* Should either branch exist
		*/

		if(root[index*2] != nullptr) {
			findMax(maxLeft); 
		} else if (root[(index * 2) + 1] != nullptr) { //left node doesnt exist
			maxLeft = index;
			findMin(minRight);
		}
		else { //oh god this sucks so bad
			maxLeft = minRight = index;
		}

		//we now know the direct sucessor and predecessor.


		if (minRight == maxLeft == index) {
			//we have no children on this subtree, there is nothing to reassign
			//we simply need to reassign to null
			root[index] = nullptr;
			return;
		}

		/*
		* The following code discreetly determines which node should suceed
		* the reassigned node. There is a preference towards the predecessor
		* here.
		* 
		* Reassigning a node with one child should be easy: shift up the child
		* and its children a level
		*/




		//this is where we may need to recurse to
		chosenNode = (maxLeft == index) ? minRight : maxLeft;
		
		if (maxLeft == index || minRight == index) {// one child
			promote((minRight == index ? (index * 2) : ((index * 2) + 1)));
			return;
		}

		//next case, two children. luckily we already have maxleft and minright
		
		/*
		* There are now two children. We already have the index for maxLeft,
		* and for minRight. Because of BST properties, this means that the 
		* index for both of these will have just 1 child.
		* 
		* This means that we recurse down to the chosenNode after copying the
		* pointer
		*/


		root[index] = root[chosenNode]; //move the ptr up
		reassign(chosenNode); //promote the one child branch
		return;


	}

	void copyNode(int source, int destination) {

		if (source == destination) {
			return; //no useless overwriting
		}
		//copies node from source to destination
		// destination is assumed to be this tree
		//assumes dynmemory exists
		root[desination] = root[source];
	}

	const Pair* findMax(int index) const {
		//helper private to find max of a tree
		if (root[(index * 2)+1] == nullptr) { return root[index]; }
		index = (index * 2) + 1;
		return findMax((index * 2) + 1 ); //go a level deeper
	}

	 const Pair* findMin(int index) const {
		//helper private to find minimum of a tree recursively
		if (root[index * 2] == nullptr) { return root[index]; }
		index = index * 2;
		return findMin(index * 2 ); //go a level deeper
	}

	//Note to self. RETURNS A POINTER TO A PAIR

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


	int navigate(int index, int count, std::ostream& out ) const {
		//recursively navigate to bottom of tree, incrementing an index
		//returns number of valid nodes encountered
		//deletion flag deletes the child node before returning
		//assumes tree is not empty
		
		 //we are here already, must be a valid node


		if (root[index] == nullptr) {
			cout << "WHOOPSIE\n";
		}

		//check if children exist, then count *their* subtrees, report back.
		if (((index * 2) <= this->size ) && (root[index * 2] != nullptr)) {
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
		Pair** newRoot = new Pair *[(newSize + 1)];

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
	BinarySearchTree() 	{
		//  stub code: needs to be implemented
		size = 25;
		count = 0;
		root = new Pair *[(size+1)];
		for (int i = 0; i <= this->size; i++) {
			root[i] = nullptr;
		}
	}
	
	~BinarySearchTree() {
		makeEmpty();
		delete root;
	}

	void printTreeStructure(std::ostream& out) const {
		/*
		* First, we need to determine the total height of the(sub)tree
		* The height is obtained by logging the size, truncating the decimal, then
		* adding 1. This should work for any allocated size
		*
		* index is our (sub)root.
		*/
		int height = log(this->size) / log(2); //base change

		// int localHeight = -((log(index) / log(2)) - height);

		//we now know the height and local height
		int marginTabs = height / 2;
		for (int layer = 0; layer <= height; layer++) {
			int i = marginTabs;
			for (; i >= 0; i--) {
				out << "\t";
			}
			for (i = pow(2, layer); i < 2 * pow(2, layer + 1); i++) {
				if (root[i] != nullptr) {
				out << root[i]->key << "\t";
				}
			}
			out << endl;
		}
			marginTabs--;
	
		

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
	bool find(const KeyComparable & argKey , Value & founditem) const 	{
		int index = 1;
	
		if (find(argKey,index) == nullptr) {
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
		out << "I'm printin the treeeeeee\n";
		printTree(1 , out);
		
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
		/*
		* Determine the index to insert to, if its a nullptr or greater than
		* the size, hold onto the index. clone the list with the new index.
		*/

		//this is where we start
		int index = 1;


		//are we inbounds?
		while (root[index] != nullptr && index <= this->size) {

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
	void remove(const KeyComparable & key) 	{
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