#include <chrono>
#include <iostream>

// Test to see if its faster to reuse linked list nodes or to expand a contiguious array
// Premise: In a system where head is continuously being popped, it is impossible to use a standard continuous array
// The constant shifting of elements would be O(n) on every arr[0].delete()

// In a system where only the head mattered and we did not wish to iterate over container, is it faster to use a queue
// or to make a linked list? queue resizing calls malloc & takes O(n) to copy items, 
// linked list takes O(1) insertion w/ no copying BUT calls malloc on each new element entry

// Reference: Keyboard Warrior (https://github.com/FamousHero/KeyboardWarrior) - needed to pop 1st element after a certain time interval
// but also required iterable container to update elements position on screen every frame

namespace LinkedList {
	struct Node {
		char element;
		Node* next;

		Node(char char_t)
			:element{char_t}, next{nullptr}
		{

		}
	};
	// If popNode called in succession, tail only points to last freed node ie. 3 sequential calls will have 2 unreachable nodes behind tail
	class LinkedList {
		int m_size;
		Node* m_head;
		Node* m_tail;
		Node* m_freed_node_start;
	public:
		LinkedList()
			:m_head{ nullptr }, m_freed_node_start{ nullptr },m_size{ 0 }, m_tail{nullptr}
		{

		}

		~LinkedList() {
			while (m_head) {
				Node* temp = m_head;
				m_head = m_head->next;
				delete temp;
			}
		}

		void addNode(char char_t) {
			
			if (m_freed_node_start) { //If we have a freed node use it. tail can't be in use if this != nullptr
				m_freed_node_start->element = char_t;
				m_freed_node_start = m_freed_node_start->next; // Eventually we reach past tail and become nullptr
				return;
			}
			Node* newNode = new Node(char_t);
			if (m_head == nullptr) //if we just created a new LL (head == null && tail == null)
			{
				m_head = newNode;
				m_tail = m_head;
			}
			else if(m_tail){
				m_tail->next = newNode;
				m_tail = m_tail->next;
			}
				++m_size;

		}

		void popNode() {
			if (m_size == 0)
				return;
			if (m_head) {
				Node* temp = m_head;
				m_head = m_head->next;
				temp->next = nullptr;

				//Reuse the node & remove cyclical graph (head->...->tail->head) => (head->....->tail->nullptr)
				m_tail->next = temp;
				m_tail = m_tail->next;
				m_tail->next = nullptr;
				
				if(m_freed_node_start == nullptr){ //If there are no freed nodes set this to the first one
					m_freed_node_start = temp;
				}
			}
			--m_size;
			return;
		}
	};
}