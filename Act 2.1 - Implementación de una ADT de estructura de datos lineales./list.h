#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

template <class T> class List;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template<class T>
class List{
	private:
		Link<T> *head;
		int size;
	public:
		List();
		List(const List<T> &);
		~List();

		std::string toString() const;
		void insertion(T);
		int	search(int);
		void update(int, T);
		T deleteAt(int);
		T deleteFirst();

		void clear();
};

template<class T>
List<T> :: List() : head(0), size(0){}

template<class T>
List<T> :: ~List(){
	clear();
}

template<class T>
void List<T> :: clear(){
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template<class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template<class T>
void List<T> :: insertion(T val){
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	
	if (head == 0) {
		newLink->next = head;
		head = newLink;
		size++;
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}

	newLink->next = 0;
	p->next = newLink;
	size++;
}

template<class T>
int List<T> :: search(int val){
	Link<T> *p;
	int pos= 0;

	p= head;

	while (pos < size)
	{
		if(p->value == val){
			return pos;
		}

		p= p->next;
		pos++;
	}
	return -1;
}

template<class T>
void List<T> :: update(int index, T val){
	Link<T> *p;
	int pos= 0;

	p= head;

	while(pos != index){
		p= p->next;
		pos++;
	}

	p->value = val;
}

template<class T>
T List<T>::deleteFirst(){
	Link<T> *p;
	T value;

	p= head;
	head= p->next;
	value= p->value;

	delete p;
	size--;

	return value;
}

template<class T>
T List<T> :: deleteAt(int index){
	T value;
    Link<T> *p, *q;
    int pos;

	if(index == 0){
		return deleteFirst();
	}

	pos = 0;
    p = head;
    q = 0;

	while(pos != index){
		q= p;
		p= p->next;
		pos++;
	}

	value = p->value;
    q->next = p->next;
    delete p;
    size--;
    return value;
}

#endif
