#ifndef LAB13_QUEUECIRCLE_H
#define LAB13_QUEUECIRCLE_H
#include <cassert>
#include <iostream>

class Queue {
private:
	int size;
	int front;
	int rear;
	int added_elements;
	int *array;

	int next(int pos) {
		return (pos + 1) % size;
	}

	int prev(int pos) {
		return (pos - 1 + size) % size;
	}

	void resize() {
		int new_size = size * 2;
		int *new_array = new int[new_size];

		for (int i = 0, cur = front; i < added_elements; ++i, cur = next(cur)) {
			new_array[i] = array[cur];
		}

		delete[] array;

		array = new_array;
		size = new_size;
		front = 0;
		rear = added_elements;
	}

public:
	Queue(int size) : size(size), front(0), rear(0), added_elements(0) {
		array = new int[size];
	}

	~Queue() {
		delete[] array;
	}

	void enqueue_rear(int value) {
		if (isFull()) resize();

		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	void enqueue_front(int value) {
		if (isFull()) resize();

		front = prev(front);
		array[front] = value;
		added_elements++;
	}

	int dequeue_front() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		--added_elements;
		return value;
	}

	int dequeue_rear() {
		assert(!isEmpty());
		rear = prev(rear);
		int value = array[rear];
		--added_elements;
		return value;
	}

	void display() {
		std::cout << "Front " << front << " - rear " << rear << "\t";
		if (isFull())
			std::cout << "full";
		else if (isEmpty()) {
			std::cout << "empty\n\n";
			return;
		}
		std::cout << "\n";

		for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
			std::cout << array[cur] << " ";

		std::cout << "\n\n";
	}

	int isEmpty() {
		return added_elements == 0;
	}

	bool isFull() {
		return added_elements == size;
	}
};
#endif