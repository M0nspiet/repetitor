#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Word {
    string name;
    string description;
};

ostream& operator<<(ostream& ost, const Word& word);

template <class A>
class AvlTree {
    template <class AA>
    struct Node {
        AA obj;
        int height;
        Node* left;
        Node* right;
    };

    Node(const AA& _obj)
        : obj(_obj), height(1), left(nullptr), right(nullptr) {
    }

protected:
    Node<AA>* root;

    function<int(const A&, const A&)> compare;

    int getHeight(Node<A>* node) {
        return node ? node->height : 0;
    }
    void updateHeight(Node<A>* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    int getBalanceFactor(Node<A>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node<A>* rotateLeft(Node<A>* node) {
        AVLNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }
    Node<A>* rotateRight(Node<A>* node) {
        AVLNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    Node<A>* balance(Node<A>* node) {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    Node<A>* insert(Node<A>* node, const A& obj) {
        if (!node) return new AVLNode<T>(obj);

        if (compare(obj, node->obj) < 0)
            node->left = insert(node->left, obj);
        else if (compare(obj, node->obj) > 0)
            node->right = insert(node->right, obj);
        else
            return node;

        return balance(node);
    }
    Node<A>* find(Node<A>* node, const A& obj) {
        if (!node) return nullptr;

        if (compare(obj, node->obj) == 0) return node;
        if (compare(obj, node->obj) < 0) return find(node->left, obj);
        return find(node->right, obj);
    }

    void inOrderTraversal(Node<A>* node, ostream& os) const {
        if (node) {
            inOrderTraversal(node->left, os);
            os << node->obj << endl;
            inOrderTraversal(node->right, os);
        }
    }

public:
    AVLTree(function<int(const T&, const T&)> cmp)
        : root(nullptr), compare(cmp) {
    }

    bool add(const A& obj) {
        root = insert(root, obj);
    }

    bool search(A& obj) {
        AVLNode<T>* result = find(root, obj);
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

void load_dictionary_from_csv(const string& filename, AvlTree<Word>& Avl_tree);