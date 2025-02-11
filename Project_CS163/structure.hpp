#ifndef structure_hpp
#define structure_hpp

#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;

template<typename T>
class TreeNode {
public:
    bool color;
    string* pWord;
    T* pDef;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode<T>() : color(0), pWord(nullptr), pDef(nullptr), left(nullptr), right(nullptr), parent(nullptr) {};
    TreeNode<T>(bool color_x, string key, T def) : color(color_x), pWord(new string(key)), pDef(new T(def)), left(nullptr), right(nullptr), parent(nullptr) {};
    TreeNode<T>(bool color_x, string key, T def, TreeNode* par) : color(color_x), pWord(new string(key)), pDef(new T(def)), left(nullptr), right(nullptr), parent(par) {};
};

template<typename T>
class myDictionary {
private:
    int size_of_rbt;
    TreeNode<T>* root;
    
    void rotateLine(TreeNode<T>*& child, TreeNode<T>*& parent, TreeNode<T>*& grandparent) {
        if (child == parent->left) {
            parent->parent = grandparent->parent;
            if (parent->right) parent->right->parent = grandparent;
            grandparent->left = parent->right;
            parent->right = grandparent;
            if (grandparent == root) root = parent;
            else if (parent->parent->left == grandparent) parent->parent->left = parent;
            else parent->parent->right = parent;
            grandparent->parent = parent;
            grandparent->color = 1;
            parent->color = 0;
        }
        else {
            parent->parent = grandparent->parent;
            if (parent->left) parent->left->parent = grandparent;
            grandparent->right = parent->left;
            parent->left = grandparent;
            if (grandparent == root) root = parent;
            else if (parent->parent->left == grandparent) parent->parent->left = parent;
            else parent->parent->right = parent;
            grandparent->parent = parent;
            grandparent->color = 1;
            parent->color = 0;
        }
    }
    
    void rotateTriangle(TreeNode<T>*& child, TreeNode<T>*& parent, TreeNode<T>*& grandparent) {
        if (child == parent->left) {
            child->parent = grandparent;
            grandparent->right = child;
            if (child->right) child->right->parent = parent;
            parent->left = child->right;
            parent->parent = child;
            child->right = parent;
        }
        else {
            child->parent = grandparent;
            grandparent->left = child;
            if (child->left) child->left->parent = parent;
            parent->right = child->left;
            parent->parent = child;
            child->left = parent;
        }
    }
    
    void balance(TreeNode<T>* child) {
        TreeNode<T>* parent = child->parent;
        TreeNode<T>* grandparent = parent->parent;
        TreeNode<T>* uncle = ((parent == grandparent->left) ? grandparent->right : grandparent->left);
        if (uncle && uncle->color == 1) {
            parent->color = 0;
            uncle->color = 0;
            grandparent->color = 1;
            if (grandparent == root) grandparent->color = 0;
            else {
                if (grandparent->parent->color == 1) balance(grandparent);
            }
            return;
        }
        else if (!uncle || uncle->color == 0) {
            bool isOnLine = ((child == parent->left && parent == grandparent->left) || (child == parent->right && parent == grandparent->right));
            if (!isOnLine) {
                rotateTriangle(child, parent, grandparent);
                rotateLine(parent, child, grandparent);
            }
            else rotateLine(child, parent, grandparent);
        }
    }
    
public:
    myDictionary() {
        size_of_rbt = 0;
        root = nullptr;
    }
    
    void insert(string key, T def) {
        if (!root) {
            root = new TreeNode<T>(0, key, def);
            return;
        }
        TreeNode<T>* newNode = new TreeNode<T>(1, key, def);
        TreeNode<T>* cur = root;
        while (true) {
            if (key.compare(*(cur->pWord)) >= 0) {
                if (cur->right) {
                    cur = cur->right;
                    continue;
                }
                else {
                    cur->right = newNode;
                    newNode->parent = cur;
                    break;
                }
            }
            else {
                if (cur->left) {
                    cur = cur->left;
                    continue;
                }
                else {
                    cur->left = newNode;
                    newNode->parent = cur;
                    break;
                }
            }
        }
        if (newNode->parent->color == 1) balance(newNode);
    }
    
    void drawTree() {
        queue<TreeNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode<T>* t = q.front(); q.pop();
            cout << *(t->pWord) << " | color : " << t->color << " | left : " << ((t->left) ? (*(t->left->pWord)) : "-1") << " | right : " << ((t->right) ? (*(t->right->pWord)) : "-1") << "\n";
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }

    TreeNode<T>* search( TreeNode<T>* pRoot = root, string keyword )
    {
        if (!pRoot) return pRoot;
        if ( keyword == (* (pRoot->pWord)) ) return pRoot;
        if ( keyword < (*(pRoot->pWord)) ) return search(pRoot->left, keyword);
        if ( keyword > (*(pRoot->pWord)) ) return search(pRoot->right, keyword);
    }
    
    ~myDictionary() {
        queue<TreeNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode<T>*& t = q.front(); q.pop();
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
            delete t->pWord;
            delete t->pDef;
            delete t;
        }
    }
};

#endif /* structure_hpp */
