#include <iostream>
#include <fstream>

#include "bst.h"
using namespace std;

int main(int argc,  char* argv[]){
	BST tree;

	string command;
	while(cin >> command){
		if(command == "insert"){
			string word;
			int len;
			cin >> word >> len;
			tree.insert(word.substr(0,len), word);
		}
		if(command == "heightPrint"){
			tree.heightPrint();
			cout << endl;
			cout << endl;
		}
		if(command == "printSize"){
			tree.printSize();
			cout << endl;
			cout << endl;
		}
		if(command == "printBF"){
			tree.printBF();
			cout << endl;
			cout << endl;
		}
		if(command == "findPrint"){
			string akey;
			cin >> akey;
			tree.findPrint(akey);
		}
		if(command == "print_inorder"){
			tree.print_inorder();
			cout << endl;
		}
		if(command == "remove"){
			string akey;
			cin >> akey;
			tree.remove(akey);
		}
		if(command == "findLCA"){
			string akey1, akey2;
			cin >> akey1 >> akey2;
			tree.findLCA(akey1, akey2);
		}
		if(command == "printLongestPath"){
			tree.printLongestPath();
			cout << endl;
		}
		if(command == "findKthSmallest"){
			int k;
			cin >> k;
			tree.findKthSmallest(k);
		}
		if(command == "collectSubtree"){
			string akey;
			cin >> akey;
			tree.collectSubtree(akey);
		}
	}
	
	return 0;
}