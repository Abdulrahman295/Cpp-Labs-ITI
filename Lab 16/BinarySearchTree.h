#ifndef LAB13_BINARYSEARCHTREE_H
#define LAB13_BINARYSEARCHTREE_H
#include <algorithm>

struct Node {
	int data;
	Node* left;
	Node* right;

	explicit Node(const int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
	Node *root;

	Node* min_node(Node *cur) const{
		while (cur && cur->left) cur = cur->left;
		return cur;
	}

	Node* max_node(Node *cur) const{
		while (cur && cur->right) cur = cur->right;
		return cur;
	}

	Node* insert_node(int value, Node* node) {
		if (!node) return new Node(value);

		if (value < node->data)
			node->left = insert_node(value, node->left);
		else if (value > node->data)
			node->right = insert_node(value, node->right);

		return node;
	}

	Node* delete_node(int target, Node* node) {
		if (!node) return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else {
			if (!node->left && !node->right) {
				delete node;
				return  nullptr;
			}

			if (!node->right) {
				Node* temp = node->left;
				delete node;
				return temp;
			}

			if (!node->left) {
				Node* temp = node->right;
				delete node;
				return temp;
			}

			Node* mn = min_node(node->right);
			node->data = mn->data;	// copy & go delete
			node->right = delete_node(node->data, node->right);

		}

		return node;
	}

	void make_empty(Node* node) {
		if (!node) return;

		make_empty(node->left);
		make_empty(node->right);
		delete node;
	}

	int depth(Node* node) const{
		if (!node) return 0;
		return 1 + std::max(depth(node->left), depth(node->right));
	}

public:

	BinarySearchTree() : root(nullptr) {
	}

	~BinarySearchTree() {
		make_empty(root);
		root = nullptr;
	}

	void insert(int value) {
		root = insert_node(value, root);
	}

	void remove(int target) {
		root = delete_node(target, root);
	}

	bool search(int target) const {
		Node* cur = root;
		while (cur != nullptr) {
			if (target == cur->data)
				return true;

			if (target < cur->data)
				cur = cur->left;
			else
				cur = cur->right;
		}

		return false;
	}

	int getDepth() const{
		return depth(root);
	}

	int getMin() const{
		Node* mn = min_node(root);
		return mn ? mn->data : -1;
	}

	int getMax() const {
		Node* mx = max_node(root);
		return mx ? mx->data : -1;
	}
};

#endif