#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <functional>

using namespace std;

template <class A>
class AvlTree {
    struct Node {
        A obj;
        int height;
        Node* left;
        Node* right;

        Node(const A& _obj)
            : obj(_obj), height(1), left(nullptr), right(nullptr) {
        }
    };
protected:
    Node* root;

    function<int(const A&, const A&)> compare;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor == 2) { // левое поддерево выше (правый поворот)
            if (getBalanceFactor(node->left) == -1) {
                rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor == -2) { // правое поддерево выше (левый поворот)
            if (getBalanceFactor(node->right) == 1) {
                rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, const A& obj) {
        if (!node)
            return new Node(obj);

        if (compare(obj, node->obj) < 0)
            node->left = insert(node->left, obj);
        else
            node->right = insert(node->right, obj);

        return balance(node);
    }
    Node* find(Node* node, const A& obj) {
        if (!node) return nullptr;

        if (compare(obj, node->obj) == 0)
            return node;
        if (compare(obj, node->obj) < 0)
            return find(node->left, obj);
        return find(node->right, obj);
    }

    void inOrderTraversal(Node* node, ostream& os) const {
        if (node) {
            inOrderTraversal(node->left, os);
            os << node->obj << " ";
            inOrderTraversal(node->right, os);
        }
    }

public:
    AvlTree(function<int(const A&, const A&)> cmp)
        : root(nullptr), compare(cmp) {
    }

    bool add(const A& obj) {
        root = insert(root, obj);
        return true; //TODO: ?????
    }

    bool search(A& obj) {
        Node* result = find(root, obj);
        if (result) {
            obj = result->obj;
            return true;
        }
        return false;
    }
    void printInOrder(ostream& os) const {
        inOrderTraversal(root, os);
    }
};

#endif // AVL_H
