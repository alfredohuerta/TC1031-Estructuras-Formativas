/**
 * @file dlist.h
 * @author Erick Alfredo García Huerta - A01708119
 * @brief Archivo sobre double linked list.
 * @date 2021-11-27
 * 
 */

#ifndef _DLIST_H_
#define _DLIST_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList{
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int 	 size;
    public:
        DList();
	    DList(const DList<T>&);
	    ~DList();

        void clear();
        bool empty();
        string toStringBackward() const;
        string toStringForward() const;

        void insertion(T);
        int search(T);
        void update(int, T);
        T deleteFirst();
        T deleteAt(int);
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList(){
    clear();
}

/**
 * @brief Método que limpia todos los datos de la lista
 */
template <class T>
void DList<T>::clear(){
    DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

/**
 * @brief Método que devuelve un valor booleano en caso de que la lista esté vacía
 * 
 * @return true 
 * @return false 
 */
template <class T>
bool DList<T>::empty(){
    return (head == 0 && tail == 0);
}

/**
 * @brief Método que imprime los valores de la lista comenzando desde la cabeza
 * 
 * @return string 
 */
template <class T>
string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

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

/**
 * @brief Método que imprime los valores de la lista empezando desde la cola.
 * 
 * @return string 
 */
template <class T>
string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

/**
 * @brief Método que inserta un valor en la lista, difereciando si es el primer elemento de esta o no.
 * 
 * @param val 
 */
template <class T>
void DList<T>::insertion(T val){
    DLink<T> *newLink;

    newLink= new DLink<T>(val);

    if(empty()){
        head= newLink;
        tail= newLink;
    }else{
        tail->next = newLink;
        newLink->previous= tail;
        tail= newLink;
    }

    size++;
}

/**
 * @brief Método que recorre todo la la lista en búsqueda de un valor cuyo índice regresa en caso de encontrar, si no 
 * regresa un valor inválido.
 * 
 * @param value 
 * @return int indice del valor buscado.
 */
template <class T>
int DList<T>::search(T value){
    int pos;
    DLink<T> *p;

    pos = 0;
    p= head;
    
    while(pos != size){
        if(p->value == value){
            return p->value;
        }
        pos++;
        p= p->next;
    }

    return -1;
}

/**
 * @brief Método que reemplaza el valor de uno de los elementos de la lista, recorriendo toda la lista usando como 
 * referencia su índice.
 * 
 * @param index indice del valor a cambiar
 * @param value valor que tomará el lugar del antiguo
 */
template <class T>
void DList<T>::update(int index, T value){
    int pos;
    DLink<T> *p;

    pos= 0; 
    p= head;

    while(pos != index){
        pos++;
        p= p->next;
    }

    p->value = value;
}

/**
 * @brief Método que elimina y reacomoda la lista una vez borra el primer elemento de la misma.
 * 
 * @return T valor que ha sido borrado.
*/
template <class T>
T DList<T>::deleteFirst(){
    T gValue;
    DLink<T> *p;

    p= head;
    gValue= p->value;

    if(head == tail){
        head= 0;
        tail= 0;
    }else{
        head= p->next;
        p->next->previous = 0;
    }

    delete p;
    size--;

    return gValue;
}

/**
 * @brief Método que borra un valor de la lista dado su posición en ella.
 * 
 * @param index posición del valor en la lista
 * @return T valor borrado
 */
template <class T>
T DList<T>::deleteAt(int index){
    DLink<T> *p;
    int pos;
    T gValue;
    
    if(index == 0){
        return deleteFirst();
    }

    p= head;
    pos= 0;

    while(pos != index){
        p= p->next;
        pos++;
    }

    gValue= p->value;
    p->previous->next = p->next;

	if (p->next != 0) {
		p->next->previous = p->previous;
	}

    size--;
    delete p;

    return gValue;
}

#endif
