#ifndef LAB13_LINKEDLIST_H
#define LAB13_LINKEDLIST_H
#include <iostream>

struct Node {
	int data { };
	Node* next { };
	Node* prev { };

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}
};

class LinkedList {
private:
	Node *head;
	Node *tail;
	int length;

	void link(Node* first, Node*second) {
		if(first) first->next = second;

		if(second) second->prev = first;
	}

	void delete_and_link(Node* node) {
		if (node == head)
			head = node->next;
		if (node == tail)
			tail = node->prev;

		link(node->prev, node->next);

		delete node;
		length--;
	}

	Node* findNode(int value) {
		for (Node* cur = head; cur; cur = cur->next) {
			if (cur->data == value)
				return cur;
		}
		return nullptr;
	}

public:

	LinkedList() : head(nullptr), tail(nullptr), length(0) { }

	~LinkedList() {
		while (head) {
			delete_front();
		}
	}

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			std::cout << cur->data << " ";
		std::cout << "\n";
	}

	void insert_front(int value) {
		Node* item = new Node(value);

		if (!head)
			head = tail = item;
		else {
			link(item, head);
			head = item;
		}

		length++;
	}

	void insert_before(int value, int target) {
		Node* target_node = findNode(target);
		if (target_node == nullptr) return;

		Node* new_node = new Node(value);
		link(target_node->prev, new_node);
		link(new_node, target_node);

		if (target_node == head)
			head = new_node;

		length++;
	}

	void insert_after(int value, int target) {
		Node* target_node = findNode(target);
		if (target_node == nullptr) return;

		Node* new_node = new Node(value);
		Node* node_after = target_node->next;

		link(target_node, new_node);
		link(new_node, node_after);

		if (target_node == tail)
			tail = new_node;

		length++;
	}

	void insert_end(int value) {
		Node* item = new Node(value);

		if (!head)
			head = tail = item;
		else {
			link(tail, item);
			tail = item;
		}

		length++;
	}

	void delete_front() {
		if(!head) return;
		delete_and_link(head);
	}

	void delete_end() {
		if(!tail) return;
		delete_and_link(tail);
	}

	void delete_nodes_with_value(int value) {
		if (!length) return;

		Node* cur = head;
		while (cur != nullptr) {
			Node* next_node = cur->next;

			if (cur->data == value) delete_and_link(cur);

			cur = next_node;
		}

	}

	int getLength() const {
		return length;
	}

	int getValueAt(int index) const {
		if(index < 0 || index >= length)
			throw std::out_of_range("Index out of range");

		Node* cur = head;
		for(int i = 0; i < index; i++)
			cur = cur->next;

		return cur->data;
	}
};

#endif