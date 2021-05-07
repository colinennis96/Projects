#include<iostream>
using namespace std;
#include "bst.h"
/Users/colin/Documents/chico/fall2020/cs311/project2/bst.h
int BST::balanceFactor(Tnode *cur){
    return getHeight(cur->left) - getHeight(cur->right);
}//balanceFactor

void BST::print_inorder(Tnode *cur){
    if(cur == NULL){
        return;
    }
    print_inorder(cur->left);
    cout << "(" << cur->key << ')';
    int size = cur->value.size();
    if(size == 0){
            return;
    }
    else{
        cout << "{";
        for(int i = 0; i < size; i++){
            cout << cur->value[i] << " ";
        }
        cout << "} ";
    }
    print_inorder(cur->right);
}//print_inorder

void BST::clean(Tnode *cur){
    if(cur == NULL){
        return;
    }
    clean(cur->left);
    clean(cur->right);
    delete cur;
}//clean()

Tnode* BST::insert(Tnode* cur, string akey, string aval){
    if(akey < cur->key){
        if(cur->left == NULL){
            cur->left = new Tnode(akey, aval);
            updateSize(cur);
            updateHeight(cur);
            return cur;
        }
        else{
            cur->left = insert(cur->left, akey, aval);
            int bf = balanceFactor(cur);
            if(bf < -1 || bf > 1){
                cur = restoreBalance(cur);
            }
            updateSize(cur);
            updateHeight(cur);
            return cur;
        }
    }//if 
    else if(akey > cur->key){
        if(cur->right == NULL){      
            cur->right = new Tnode(akey, aval);
            updateSize(cur);
            updateHeight(cur);
            return cur;
        }
        else{
            cur->right = insert(cur->right, akey, aval);
            int bf = balanceFactor(cur);
            if(bf < -1 || bf > 1){
                cur = restoreBalance(cur);
            }
            updateSize(cur);
            updateHeight(cur);
            return cur;
        }
    }//else if
    else if(akey == cur->key){
        cur->value.push_back(aval);
    }
    return cur;
}//insert()

Tnode* BST::remove(Tnode *cur, string akey){
    if(cur == NULL){
        return NULL;
    }
    
    if(akey < cur->key){
        cur->left = remove(cur->left, akey);
    }
    else if(akey > cur->key){
        cur->right = remove(cur->right, akey);
    }
    else{
        if(cur->left == NULL && cur->right == NULL){
            delete cur;
            return NULL;
        }
        else if(cur->left == NULL || cur->right == NULL){
            Tnode* temp = cur->left;
            if(cur->left == NULL){
                temp = cur->right;
            }
            delete cur;
            return temp;
        }
        else{
            Tnode *sub = getLeftmost(cur->right);
            cur->key = sub->key;
            cur->value = sub->value;
            cur-> right = remove(cur->right, sub->key);
        }
    }

    int bf = balanceFactor(cur);
    if(bf < -1 || bf > 1){
        cur = restoreBalance(cur);
    }
    updateHeight(cur);
    updateSize(cur);
    
    return cur;
}//remove

void BST::findPrint(Tnode *cur, string akey){
    if(cur != NULL){
        if(cur->key == akey){
            int size = cur->value.size();
            for(int i = 0; i < size; i++){
                cout << cur->value[i] << " ";
            }
            cout << endl;
            return;
        }
        else if(akey < cur->key){
            findPrint(cur->left, akey);
        }
        else{
            findPrint(cur->right, akey);
        }
    }
}//findPrint

void BST::heightPrint(Tnode *cur){
    if(cur != NULL){
        heightPrint(cur->left);
        cout << cur->height << " ";
        heightPrint(cur->right);
    }
}//heightPrint
void BST::printSize(Tnode *cur){
    if(cur != NULL){
        printSize(cur->left);
        cout << cur->size << " ";
        printSize(cur->right);
    }
}//sizePrint

void BST::printBF(Tnode *cur){
    if(cur != NULL){
        printBF(cur->left);
        int bf = balanceFactor(cur);
        cout << bf << " ";
        printBF(cur->right);
    }
}//printBF

void BST::updateHeight(Tnode *cur){
    int heightLeft = getHeight(cur->left);
    int heightRight = getHeight(cur->right);
    int maxH = heightLeft;
    if(heightRight > heightLeft){
        maxH = heightRight;
    }
    cur->height = maxH + 1;
}//updateHeight
void BST::updateSize(Tnode *cur){
    if(cur == NULL){
        return;
    }
    else{
        int sizeLeft = getSize(cur->left);
        int sizeRight = getSize(cur->right);
        int maxS = sizeLeft + sizeRight + 1;
        cur->size = maxS;
    }
}//updateSize

Tnode* BST::rightRotation(Tnode *cur){ 
    Tnode *leftChild = cur->left; 
    cur->left = cur->left->right; 
    updateHeight(cur);
    updateSize(cur);
    leftChild->right = cur; 
    updateHeight(leftChild);
    updateSize(leftChild); 
    return leftChild;
}//rightRotation

Tnode* BST::leftRotation(Tnode *cur){
    Tnode *rightChild = cur->right;
    cur->right = cur->right->left;
    updateHeight(cur);
    updateSize(cur);
    rightChild->left = cur;
    updateHeight(rightChild);
    updateSize(rightChild);
    return rightChild;
}//leftRotation

Tnode* BST::restoreBalance(Tnode *cur){
    if(cur == NULL){
        return cur;
    }
    if(balanceFactor(cur) == 2){
        if(balanceFactor(cur->left) < 0){
            cur->left = leftRotation(cur->left);
        }
        cur = rightRotation(cur);
    }
    if(balanceFactor(cur) == -2){
        if(balanceFactor(cur->right) > 0){
            cur->right = rightRotation(cur->right);
        }
        cur = leftRotation(cur);
    }
    return cur;
}//restoreBalance()

Tnode* BST::findMin(Tnode *cur)
{
    if(cur == NULL){
        return NULL;
    }
    else if(cur->left == NULL){
        return cur;
    }
    else{
        return findMin(cur->left);
    }
}//findMin

void BST::findLCA(Tnode *cur, string akey1, string akey2){
    if(cur == NULL){
        return;
    }
    if(cur->key > akey1 && cur->key > akey2){
        findLCA(cur->left, akey1, akey2);
    }
    else if(cur->key < akey1 && cur->key < akey2){
        findLCA(cur->right, akey1, akey2);
    }
    else{
        cout << cur->key << endl;
    }
}//findLCA

void BST::printLongestPath(Tnode *cur){
    Tnode *temp = cur;
    while(temp != NULL){
        cout << temp->key << " ";
        int left = getHeight(temp->left);
        int right = getHeight(temp->right);
        if(left > right){
            temp = temp->left;
        }
        if(right > left){
            temp = temp->right;
        }
        if(left == right){
            temp = temp->left;
        }
    }
}

Tnode* BST::findKthSmallest(Tnode *cur, int& k){
    if(cur == NULL){
        return NULL;
    }
    Tnode *left = findKthSmallest(cur->left, k);
    if(left != NULL){
        return left;
    }
 
    k--;
    if(k == 0){
        cout << cur->key << endl;
        return cur;
    }
    
    return findKthSmallest(cur->right, k);
}
