#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(T data) {
        this->data = data;
        left = right = nullptr;
    }
};

template <typename T>
class BST {
public:
    Node<T>* root;
    BST() {
        root = nullptr;
    }
    void insert(T data) {
        Node<T>* node = new Node<T>(data);
        if (root == nullptr) {
            root = node;
            return;
        }
        Node<T>* current = root;
        Node<T>* parent = nullptr;
        while (true) {
            parent = current;
            if (data < current->data) {
                current = current->left;
                if (current == nullptr) {
                    parent->left = node;
                    break;
                }
            }
            else {
                current = current->right;
                if (current == nullptr) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
    bool isEmpty() {
        return root == nullptr;
    }
    bool isFull() {
        return false;
    }
    int size() {
        return size(root);
    }
    int size(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            return size(node->left) + 1 + size(node->right);
        }
    }
    Node<T>* remove(Node<T>* node, T data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->data) {
            node->left = remove(node->left, data);
        }
        else if (data > node->data) {
            node->right = remove(node->right, data);
        }
        else {
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }
            Node<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    void printInOrder() {
        printInOrder(root);
    }
    void printInOrder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
    Node<T>* getNext(Node<T>* node, T data) {
        Node<T>* current = search(node, data);
        if (current == nullptr) {
            return nullptr;
        }
        if (current->right != nullptr) {
            return minValueNode(current->right);
        }
        else {
            Node<T>* successor = nullptr;
            Node<T>* ancestor = root;
            while (ancestor != current) {
                if (current->data < ancestor->data) {
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else {
                    ancestor = ancestor->right;
                }
            }
            return successor;
        }
    }
    Node<T>* search(Node<T>* node, T data) {
        if (node == nullptr || node->data == data) {
            return node;
        }
        if (node->data < data) {
            return search(node->right, data);
        }
        return search(node->left, data);
    }
    // Returns true if given tree is a BST. 
    bool isBST(Node<T>* node)
    {
        // Base case 
        if (node == NULL)
            return true;

        //checks the value of the node to the left to make sure it is less than the current node
        if (node->left != NULL && node->left->data > node->data)
            return false;

        //checks the value of the node to the right to make sure it is more than the current node
        if (node->right != NULL && node->right->data < node->data)
            return false;

        return isBST(node->left) && isBST(node->right);
        
    }

    int kthSmallest(Node<T>* root, int k)
    {

            if (root == NULL || k < 0)
                return -1;

        // Count the total number of nodes in the tree
        int count = 0;
        int kSmallestValue = -1;

        // Inorder traversal to find the kth smallest value
        Node<T>* current = root;
        while (current != NULL)
        {
            // If left child is NULL, print the current node data and
            // move to its right child
            if (current->left == NULL)
            {
                count++;

                // If count is equal to k, set the kth smallest value
                if (count == k)
                    kSmallestValue = current->data;

                current = current->right;
            }
            // If left child is not NULL, find the inorder predecessor
            else
            {
                // Find inorder predecessor
                Node<T>* predecessor = current->left;
                while (predecessor->right != NULL && predecessor->right != current)
                    predecessor = predecessor->right;

                // If the right child of predecessor is NULL, set right child as current
                if (predecessor->right == NULL)
                {
                    predecessor->right = current;
                    current = current->left;
                }

                // If right child of predecessor is current, set right child as NULL and print current
                else
                {
                    predecessor->right = NULL;
                    count++;

                    // If count is equal to k, set the kth smallest value
                    if (count == k)
                        kSmallestValue = current->data;

                    current = current->right;
                }
            }
        }

        return kSmallestValue;
    }
};

int main() {

    BST<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(9);
    bst.insert(13);
    bst.insert(94);
    bst.insert(93);
    bst.insert(79);
    bst.insert(29);
    bst.printInOrder();


    if (bst.isBST(bst.root))
        cout << "It is a BST" << endl;
    else
        cout << "It is not a BST" << endl;

    int k = 2;
    cout << "K'th smallest element is " << bst.kthSmallest(bst.root, k);

    return 0;
}