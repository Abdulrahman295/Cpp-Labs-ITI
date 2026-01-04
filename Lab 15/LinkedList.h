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

	Node *getMiddle(Node *start, Node *last) {
		if (start == nullptr) return nullptr;

		if (start == last) return start;

		Node *slow = start;
		Node *fast = start->next;

		while (fast != last) {
			fast = fast->next;
			slow = slow->next;
			if (fast != last && fast != nullptr) {
				fast = fast->next;
			}
		}

		return slow;
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

	bool linearSearch(int target) {
		return findNode(target) != nullptr;
	}

	bool binarySearch(int target) {
		Node *left = head;
		Node *right = nullptr;

		while (left != right) {
			Node *mid = getMiddle(left, right);

			if (mid == nullptr) return false;

			if (mid->data == target)
				return true;
			else if (mid->data < target)
				left = mid->next;
			else
				right = mid;
		}

		return false;
	}

	void insertionSort() {
		if (length < 2) return;

		for (Node *cur = head->next; cur != nullptr; cur = cur->next) {
			int key = cur->data;
			Node *temp = cur;
			Node *prev = cur->prev;

			while (prev != nullptr && prev->data > key) {
				temp->data = prev->data;
				temp = prev;
				prev = prev->prev;
			}

			temp->data = key;
		}
	}

	void bubbleSort() {
		if (length < 2) return;

		for (int i = 0; i < length - 1; i++) {
			Node *inner = head;
			bool swapped = false;

			for (int j = 0; j < length - 1 - i; j++) {
				if (inner == nullptr || inner->next == nullptr) break;

				if (inner->data > inner->next->data) {
					std::swap(inner->data, inner->next->data);
					swapped = true;
				}
				inner = inner->next;
			}

			if (!swapped) break;
		}
	}

	void selectionSort() {
		if (length < 2) return;

		for (Node *start = head; start != nullptr; start = start->next) {
			Node *min_node = start;

			for (Node *cur = start->next; cur != nullptr; cur = cur->next) {
				if (cur->data < min_node->data) {
					min_node = cur;
				}
			}

			if (min_node != start) {
				std::swap(start->data, min_node->data);
			}
		}
	}
};

#endif