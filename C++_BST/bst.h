#include<iostream>
using namespace std;

#include "tnode.h"
#ifndef BST_H
#define BST_H

class BST{
        public:
                BST():  root(NULL) {};
                ~BST(){ clean(root); root = NULL; };
 
				void insert(string akey, string aval){ 
					if(root == NULL){
						root = new Tnode(akey, aval);
					}
					else{
						root = insert(root, akey, aval); 
					}
				};
				
				void remove(string akey){
					root = remove(root, akey);
				};

				void print_inorder(){ 
					print_inorder(root);
                    cout << endl;
				};

				void findPrint(string akey){
					findPrint(root, akey);
				};

				void heightPrint(){
					heightPrint(root);
				};

				void printSize(){
					printSize(root);
				};

				void printBF(){
					printBF(root);
				};

				void findLCA(string akey1, string akey2){
					findLCA(root, akey1, akey2);
				};

				void printLongestPath(){
					printLongestPath(root);
				};

				void findKthSmallest(int k){
					findKthSmallest(root, k);
				};

				void collectSubtree(string akey){
					return;
				};
		private:
				Tnode* insert(Tnode* cur, string akey, string aval);
				void print_inorder(Tnode *cur);
				Tnode *root = NULL;
				void clean(Tnode* cur);
				void findPrint(Tnode *cur, string akey);
				void heightPrint(Tnode *cur);
				void printSize(Tnode *cur);

				int getHeight(Tnode *cur){
					if(cur == NULL){
						return -1;
					}
					else{
						return cur->height;
					}
				}

				int getSize(Tnode *cur){
					if(cur == NULL){
						return 0;
					}
					else{
						return cur->size;
					}
				}

				Tnode* restoreBalance(Tnode *cur);
				Tnode* leftRotation(Tnode *cur);
				int balanceFactor(Tnode *cur);
				void updateHeight(Tnode *cur);
				void updateSize(Tnode *cur);
				void printBF(Tnode *cur);
				Tnode* rightRotation(Tnode *cur);
				Tnode* remove(Tnode *cur, string akey);
				Tnode* getLeftmost(Tnode *cur){
					Tnode* node = cur;
					while(node->left != NULL){
						node = node->left;
					}
					return node;
				}
				
				Tnode* findMin(Tnode *cur);
				void findLCA(Tnode *cur, string akey1, string akey2);
				void printLongestPath(Tnode *cur);
				Tnode* findKthSmallest(Tnode *cur, int &k);		
};


#endif
