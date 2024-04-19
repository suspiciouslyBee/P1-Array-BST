// BSTStartProject.cpp : Defines the entry point for the console application.
//

////
// Part of Array Based BSTree.
// Programmer: June
// Instructor provided unit test for BSTree, tests construction, manipulation, 
// and destruction.
////


#include "BSTree.h"
#include "ComputerScientist.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>


// Helper funcion to break the argument string into parts by the delimiter
vector<string> split(const string& s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

// Helper function to Read in the CStist info and puts it into vector of CStist* and then shuffled thier order
vector<ComputerScientist*> load(const string& filename) {
	vector<ComputerScientist*> list;
	std::ifstream file(filename);

	std::string str;
	while (std::getline(file, str))
	{
		vector<string> tokens = split(str, ',');

		list.push_back(new ComputerScientist(tokens[1], tokens[2], tokens[3], stoi(tokens[0])));
	}

	auto rng = default_random_engine{};
	//I wonder why I need this?
	std::shuffle(std::begin(list), std::end(list), rng);
	return list;
}

int main() {

	BinarySearchTree<int, ComputerScientist*> tree2;
	vector<ComputerScientist*> list = load("csListMed.txt"); 
	for (int i = 0; i < list.size(); i++)
	{
		tree2.insert(list[i], list[i]->getID());
	}


	cout << "\n\nPRINTING TREE:\n";
	tree2.printTree();
	cout << "Tree2 count: " << tree2.getCount() << endl;
	cout << "Tree2 size: " << tree2.getSize() << endl << endl;


	for (int i = 101; i <= 110; ++i) {		// for turn-in uncomment these lines
		tree2.remove(i);
	}


	cout << "\n\nPRINTING TREE AFTER REMOVING 101-110:\n"; 
	tree2.printTree();
	cout << "Tree2 count: " << tree2.getCount() << endl;
	cout << "Tree2 size: " << tree2.getSize() << endl << endl;

	BinarySearchTree<int, ComputerScientist*> tree;
	tree.insert(new ComputerScientist("Robert", "Ward", "Education", 50), 50);
	tree.insert(new ComputerScientist("Grace", "Hopper", "Compilers", 40), 40);
	tree.insert(new ComputerScientist("Alan", "Turing", "Cryptogarphy", 60), 60);
	tree.insert(new ComputerScientist("John", "von Neumann", "Hardware", 45), 45);
	tree.insert(new ComputerScientist("Dennis", "Ritchie", "Compilers", 55), 55);
	tree.insert(new ComputerScientist("Ada", "Lovelace", "Programming", 30), 30);
	tree.insert(new ComputerScientist("Edsger", "Dikstra", "Algorithms", 80), 80);
	tree.insert(new ComputerScientist("Ken", "Thompson", "OS", 70), 70);
	tree.insert(new ComputerScientist("Lonnie", "Heinke", "Education", 58), 58);

	cout << "\n\nPRINTING TREE:\n";
	tree.printTree();
	cout << "Tree count: " << tree.getCount() << endl;
	cout << "Tree size: " << tree.getSize() << endl << endl;

	

	ComputerScientist* find;
	if (tree.find(80, find))
	{
		cout << *find << endl;
	}
	else
	{
		cout << "Not Found" << endl;
	}

	tree.remove(50);						
	cout << "\n\nPRINTING TREE AFTER REMOVING 50:\n";
	tree.printTree();
	cout << "Tree count: " << tree.getCount() << endl;
	cout << "Tree size: " << tree.getSize() << endl << endl;


	tree.remove(60);						
	cout << "\n\nPRINTING TREE AFTER REMOVING 60:\n";
	tree.printTree();
	cout << "Tree count: " << tree.getCount() << endl;
	cout << "Tree size: " << tree.getSize() << endl << endl;

	system("pause");
	return 0;
}

///OUTPUT

/*


PRINTING TREE:
I'm printin the treeeeeee
(Bryan Cantrill, id: 62, speciality:  inventor of DTrace)
(Luca Cardelli, id: 63, speciality:  objects)
(Edwin Catmull, id: 64, speciality:  computer graphics)
(Vinton Cerf, id: 65, speciality:  Internet  TCP/IP)
(Zhou Chaochen, id: 66, speciality:  duration calculus)
(Peter Chen, id: 67, speciality:  entity-relationship model  data modeling  conceptual model)
(Alonzo Church, id: 68, speciality:  mathematics of combinators  lambda calculus)
(Edmund Clarke, id: 69, speciality:  model checking)
(John Cocke, id: 70, speciality:  RISC)
(Edgar Codd, id: 71, speciality: formulated the database relational model )
(Jacques Cohen, id: 72, speciality:  computer science professor)
(Simon Colton, id: 73, speciality:  computational creativity)
(Alain Colmerauer, id: 74, speciality:  Prolog)
(Paul Compton, id: 75, speciality:  Ripple Down Rules)
(Gordon Cormack, id: 76, speciality:  co-inventor of dynamic Markov compression)
(Stephen Cook, id: 77, speciality:  NP-completeness)
(James Cooley, id: 78, speciality:  Fast Fourier transform (FFT))
(Danese Cooper, id: 79, speciality:  Open Source Software)
(Fernando Corbat≤, id: 80, speciality:  Compatible Time-Sharing System (CTSS)  Multics)
(Patrick Cousot, id: 81, speciality:  abstract interpretation)
(Ingemar Cox, id: 82, speciality:  digital watermarking)
(Seymour Cray, id: 83, speciality:  Cray Research  supercomputer)
(Nello Cristianini, id: 84, speciality:  machine learning  pattern analysis  artificial intelligence)
(Jon Crowcroft, id: 85, speciality:  networking)
(Glen Culler, id: 86, speciality:  interactive computing  computer graphics  high performance computing)
(Luigi Dadda, id: 87, speciality:  designer of the Dadda multiplier)
(Ole-Johan Dahl, id: 88, speciality:  Simula)
(Ryan Dahl, id: 89, speciality:  founder of node.js project)
(Andries van Dam, id: 90, speciality:  computer graphics  hypertext)
(Samir Das, id: 91, speciality:  Wireless Networks  Mobile Computing  Vehicular ad hoc network  Sensor Networks  Mesh networking  Wireless ad hoc network)
(Christopher Date, id: 92, speciality:  proponent of database relational model)
(Jeff Dean, id: 93, speciality:  Bigtable  MapReduce  Spanner of Google)
(Erik Demaine, id: 94, speciality:  computational origami)
(Richard DeMillo, id: 95, speciality:  computer security  software engineering  educational technology)
(Dorothy Denning, id: 96, speciality:  computer security)
(Peter Denning, id: 97, speciality:  identified the use of an operating system's working set and balance set  President of ACM)
(Michael Dertouzos, id: 98, speciality:  Director of Massachusetts Institute of Technology (MIT) Laboratory for Computer Science (LCS) from 1974 to 2001)
(Vinod Dham, id: 99, speciality:  P5 Pentium processor)
(Jan Dietz, id: 100, speciality:  information systems theory and Design & Engineering Methodology for Organizations)
(Whitfield Diffie, id: 101, speciality:  public key cryptography  Diffie)
(Edsger Dijkstra, id: 102, speciality:  algorithms  Goto considered harmful  semaphore (programming))
(Alan Dix, id: 103, speciality:  literally wrote the book on human)
(Jack Dongarra, id: 104, speciality:  linear algebra high performance computing (HCI))
(Marco Dorigo, id: 105, speciality:  ant colony optimization)
(Paul Dourish, id: 106, speciality:  human computer interaction)
(Susan Dumais, id: 107, speciality:  information retrieval)
(Peter Eades, id: 108, speciality:  graph drawing)
(Wim Ebbinkhuijsen, id: 109, speciality:  COBOL)
(John Eckert, id: 110, speciality:  ENIAC)
(Brendan Eich, id: 111, speciality:  JavaScript  Mozilla)
(Philip Emeagwali, id: 112, speciality:  supercomputing)
(E. Emerson, id: 113, speciality:  model checking)
(Douglas Engelbart, id: 114, speciality:  tiled windows  hypertext  computer mouse)
(Oren Etzioni, id: 115, speciality:  MetaCrawler  Netbot)
(David Evans, id: 116, speciality:  computer graphics)
(Edward Feigenbaum, id: 117, speciality:  intelligence)
(Edward Felten, id: 118, speciality:  computer security)
(Tommy Flowers, id: 119, speciality:  Colossus computer)
(Robert Floyd, id: 120, speciality:  NP-completeness)
(Sally Floyd, id: 121, speciality:  Internet congestion control)
(Lawrence Fogel, id: 122, speciality:  Evolutionary programming)
(Bernard Galler, id: 123, speciality:  MAD (programming language))
(Michael Garey, id: 124, speciality:  NP-completeness)
(Bill Gates, id: 125, speciality:  co-founder of Microsoft)
(Juan Gilbert, id: 126, speciality:  Human-Centered Computing)
(Lee Giles, id: 127, speciality:  CiteSeer)
(Seymour Ginsburg, id: 128, speciality:  formal languages  automata theory  AFL theory  database theory)
(Kurt G÷del, id: 129, speciality:  computability )
(Adele Goldberg, id: 130, speciality:  Smalltalk)
(Ian Goldberg, id: 131, speciality:  cryptographer  off-the-record messaging)
(Oded Goldreich, id: 132, speciality:  cryptography  computational complexity theory)
(Shafi Goldwasser, id: 133, speciality:  cryptography  computational complexity theory)
(Gene Golub, id: 134, speciality:  Matrix computation)
(Leonard Kleinrock, id: 196, speciality:  ARPANET  queueing theory  packet switching  hierarchical routing)
(Donald Knuth, id: 197, speciality:  The Art of Computer Programming  MIX/MMIX  TeX  literate programming)
(Andrew Koenig, id: 198, speciality:  C++)
(Daphne Koller, id: 199, speciality:  Artificial intelligence  bayesian network)
(Michael K÷lling, id: 200, speciality:  BlueJ)
(Andrey Kolmogorov, id: 201, speciality:  algorithmic complexity theory)
(Janet Kolodner, id: 202, speciality:  case-based reasoning)
(David Korn, id: 203, speciality:  Korn shell)
(Kees Koster, id: 204, speciality:  ALGOL 68)
(Robert Kowalski, id: 205, speciality:  logic programming)
(John Koza, id: 206, speciality:  genetic programming)
(John Krogstie, id: 207, speciality:  SEQUAL framework)
(Joseph Kruskal, id: 208, speciality:  Kruskal's algorithm)
(Thomas Kurtz, id: 209, speciality:  BASIC programming language; Dartmouth College computer professor)
(Leslie Lamport, id: 210, speciality:  algorithms for distributed computing  LaTeX)
(Marshall McKusick, id: 235, speciality:  BSD  Berkeley Fast File System)
(Lambert Meertens, id: 236, speciality:  ALGOL 68  ABC (programming language))
(Bertrand Meyer, id: 237, speciality:  Eiffel (programming language))
(Silvio Micali, id: 238, speciality:  cryptography)
(Robin Milner, id: 239, speciality:  ML (programming language))
(Jack Minker, id: 240, speciality:  database logic)
(Marvin Minsky, id: 241, speciality:  artificial intelligence  perceptrons  Society of Mind)
(Paul Mockapetris, id: 242, speciality:  Domain Name System (DNS))
(Cleve Moler, id: 243, speciality:  numerical analysis  MATLAB)
Tree2 count: 97
Tree2 size: 4607



PRINTING TREE AFTER REMOVING 101-110:
I'm printin the treeeeeee
(Bryan Cantrill, id: 62, speciality:  inventor of DTrace)
(Luca Cardelli, id: 63, speciality:  objects)
(Edwin Catmull, id: 64, speciality:  computer graphics)
(Vinton Cerf, id: 65, speciality:  Internet  TCP/IP)
(Zhou Chaochen, id: 66, speciality:  duration calculus)
(Peter Chen, id: 67, speciality:  entity-relationship model  data modeling  conceptual model)
(Alonzo Church, id: 68, speciality:  mathematics of combinators  lambda calculus)
(Edmund Clarke, id: 69, speciality:  model checking)
(John Cocke, id: 70, speciality:  RISC)
(Edgar Codd, id: 71, speciality: formulated the database relational model )
(Jacques Cohen, id: 72, speciality:  computer science professor)
(Simon Colton, id: 73, speciality:  computational creativity)
(Alain Colmerauer, id: 74, speciality:  Prolog)
(Paul Compton, id: 75, speciality:  Ripple Down Rules)
(Gordon Cormack, id: 76, speciality:  co-inventor of dynamic Markov compression)
(Stephen Cook, id: 77, speciality:  NP-completeness)
(James Cooley, id: 78, speciality:  Fast Fourier transform (FFT))
(Danese Cooper, id: 79, speciality:  Open Source Software)
(Fernando Corbat≤, id: 80, speciality:  Compatible Time-Sharing System (CTSS)  Multics)
(Patrick Cousot, id: 81, speciality:  abstract interpretation)
(Ingemar Cox, id: 82, speciality:  digital watermarking)
(Seymour Cray, id: 83, speciality:  Cray Research  supercomputer)
(Nello Cristianini, id: 84, speciality:  machine learning  pattern analysis  artificial intelligence)
(Jon Crowcroft, id: 85, speciality:  networking)
(Glen Culler, id: 86, speciality:  interactive computing  computer graphics  high performance computing)
(Luigi Dadda, id: 87, speciality:  designer of the Dadda multiplier)
(Ole-Johan Dahl, id: 88, speciality:  Simula)
(Ryan Dahl, id: 89, speciality:  founder of node.js project)
(Andries van Dam, id: 90, speciality:  computer graphics  hypertext)
(Samir Das, id: 91, speciality:  Wireless Networks  Mobile Computing  Vehicular ad hoc network  Sensor Networks  Mesh networking  Wireless ad hoc network)
(Christopher Date, id: 92, speciality:  proponent of database relational model)
(Jeff Dean, id: 93, speciality:  Bigtable  MapReduce  Spanner of Google)
(Erik Demaine, id: 94, speciality:  computational origami)
(Richard DeMillo, id: 95, speciality:  computer security  software engineering  educational technology)
(Dorothy Denning, id: 96, speciality:  computer security)
(Peter Denning, id: 97, speciality:  identified the use of an operating system's working set and balance set  President of ACM)
(Michael Dertouzos, id: 98, speciality:  Director of Massachusetts Institute of Technology (MIT) Laboratory for Computer Science (LCS) from 1974 to 2001)
(Vinod Dham, id: 99, speciality:  P5 Pentium processor)
(Jan Dietz, id: 100, speciality:  information systems theory and Design & Engineering Methodology for Organizations)
(Brendan Eich, id: 111, speciality:  JavaScript  Mozilla)
(Philip Emeagwali, id: 112, speciality:  supercomputing)
(E. Emerson, id: 113, speciality:  model checking)
(Douglas Engelbart, id: 114, speciality:  tiled windows  hypertext  computer mouse)
(Oren Etzioni, id: 115, speciality:  MetaCrawler  Netbot)
(David Evans, id: 116, speciality:  computer graphics)
(Edward Feigenbaum, id: 117, speciality:  intelligence)
(Edward Felten, id: 118, speciality:  computer security)
(Tommy Flowers, id: 119, speciality:  Colossus computer)
(Robert Floyd, id: 120, speciality:  NP-completeness)
(Sally Floyd, id: 121, speciality:  Internet congestion control)
(Lawrence Fogel, id: 122, speciality:  Evolutionary programming)
(Bernard Galler, id: 123, speciality:  MAD (programming language))
(Michael Garey, id: 124, speciality:  NP-completeness)
(Bill Gates, id: 125, speciality:  co-founder of Microsoft)
(Juan Gilbert, id: 126, speciality:  Human-Centered Computing)
(Lee Giles, id: 127, speciality:  CiteSeer)
(Seymour Ginsburg, id: 128, speciality:  formal languages  automata theory  AFL theory  database theory)
(Kurt G÷del, id: 129, speciality:  computability )
(Adele Goldberg, id: 130, speciality:  Smalltalk)
(Ian Goldberg, id: 131, speciality:  cryptographer  off-the-record messaging)
(Oded Goldreich, id: 132, speciality:  cryptography  computational complexity theory)
(Shafi Goldwasser, id: 133, speciality:  cryptography  computational complexity theory)
(Gene Golub, id: 134, speciality:  Matrix computation)
(Leonard Kleinrock, id: 196, speciality:  ARPANET  queueing theory  packet switching  hierarchical routing)
(Donald Knuth, id: 197, speciality:  The Art of Computer Programming  MIX/MMIX  TeX  literate programming)
(Andrew Koenig, id: 198, speciality:  C++)
(Daphne Koller, id: 199, speciality:  Artificial intelligence  bayesian network)
(Michael K÷lling, id: 200, speciality:  BlueJ)
(Andrey Kolmogorov, id: 201, speciality:  algorithmic complexity theory)
(Janet Kolodner, id: 202, speciality:  case-based reasoning)
(David Korn, id: 203, speciality:  Korn shell)
(Kees Koster, id: 204, speciality:  ALGOL 68)
(Robert Kowalski, id: 205, speciality:  logic programming)
(John Koza, id: 206, speciality:  genetic programming)
(John Krogstie, id: 207, speciality:  SEQUAL framework)
(Joseph Kruskal, id: 208, speciality:  Kruskal's algorithm)
(Thomas Kurtz, id: 209, speciality:  BASIC programming language; Dartmouth College computer professor)
(Leslie Lamport, id: 210, speciality:  algorithms for distributed computing  LaTeX)
(Marshall McKusick, id: 235, speciality:  BSD  Berkeley Fast File System)
(Lambert Meertens, id: 236, speciality:  ALGOL 68  ABC (programming language))
(Bertrand Meyer, id: 237, speciality:  Eiffel (programming language))
(Silvio Micali, id: 238, speciality:  cryptography)
(Robin Milner, id: 239, speciality:  ML (programming language))
(Jack Minker, id: 240, speciality:  database logic)
(Marvin Minsky, id: 241, speciality:  artificial intelligence  perceptrons  Society of Mind)
(Paul Mockapetris, id: 242, speciality:  Domain Name System (DNS))
(Cleve Moler, id: 243, speciality:  numerical analysis  MATLAB)
Tree2 count: 87
Tree2 size: 4607



PRINTING TREE:
I'm printin the treeeeeee
(Ada Lovelace, id: 30, speciality: Programming)
(Grace Hopper, id: 40, speciality: Compilers)
(John von Neumann, id: 45, speciality: Hardware)
(Robert Ward, id: 50, speciality: Education)
(Dennis Ritchie, id: 55, speciality: Compilers)
(Lonnie Heinke, id: 58, speciality: Education)
(Alan Turing, id: 60, speciality: Cryptogarphy)
(Ken Thompson, id: 70, speciality: OS)
(Edsger Dikstra, id: 80, speciality: Algorithms)
Tree count: 9
Tree size: 25

(Edsger Dikstra, id: 80, speciality: Algorithms)


PRINTING TREE AFTER REMOVING 50:
I'm printin the treeeeeee
(Ada Lovelace, id: 30, speciality: Programming)
(Grace Hopper, id: 40, speciality: Compilers)
(John von Neumann, id: 45, speciality: Hardware)
(Dennis Ritchie, id: 55, speciality: Compilers)
(Lonnie Heinke, id: 58, speciality: Education)
(Alan Turing, id: 60, speciality: Cryptogarphy)
(Ken Thompson, id: 70, speciality: OS)
(Edsger Dikstra, id: 80, speciality: Algorithms)
Tree count: 8
Tree size: 25



PRINTING TREE AFTER REMOVING 60:
I'm printin the treeeeeee
(Ada Lovelace, id: 30, speciality: Programming)
(Grace Hopper, id: 40, speciality: Compilers)
(John von Neumann, id: 45, speciality: Hardware)
(Dennis Ritchie, id: 55, speciality: Compilers)
(Lonnie Heinke, id: 58, speciality: Education)
(Ken Thompson, id: 70, speciality: OS)
(Edsger Dikstra, id: 80, speciality: Algorithms)
Tree count: 7
Tree size: 25

Press any key to continue . . .

*/