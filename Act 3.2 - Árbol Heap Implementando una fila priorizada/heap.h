/*
* Alumno: Erick Alfredo García Huerta
* Matrícula: A01708119
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T>
class Heap{
    private: 
        T *data;
        int elements;
        unsigned int hsize;
        unsigned int count;
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);
    public:
        Heap(unsigned int);
        ~Heap();
        bool empty() const; //Regresa verdadero/falso si el heap está vacío.
        bool full() const; //Regresa verdadero/falso si está lleno el heap.
        int size() const; //Devuelve el tamaño del heap.
        void push(T); //Agrega un elemento en la fila.
        void pop(); //Elimina el elemento con mayor prioridad
        T top(); //Regresa el valor del elemento con mayor prioridad
        std::string toString() const; 
};


template <class T>
Heap<T>::Heap(unsigned int sze){
    hsize= sze;
    data= new T[hsize];
    count= 0;
    elements= 0;
}

template <class T>
Heap<T>::~Heap(){
    delete [] data; data= 0;
    hsize= 0;
    count= 0;
}

template <class T>
bool Heap<T>::empty() const{
    return (count == 0);
}

template <class T>
int Heap<T>::size() const{
    return elements;
}

template <class T>
bool Heap<T>::full() const{
    return (count == hsize);
}

template  <class T>
unsigned int Heap<T>::parent(unsigned int pos) const{
    return ((pos-1)/2);
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const{
    return ((pos*2)+1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const{
    return ((pos*2)+2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j){
    T aux= data[i];
    data[i]= data[j];
    data[j]= aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos){
    unsigned int lef= left(pos);
    unsigned int rig= right(pos);
    unsigned int min= pos;

    if(lef <= count && data[lef] < data[min]){
        min= lef;
    }
    if(rig <= count && data[rig] < data[min]){
        min= rig;
    }
    if(min != pos){
        swap(pos, min);
        heapify(min);
    }
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

template <class T>
void Heap<T>::push(T value){
    unsigned int pos;

    pos= count; 
    count++;

    while(pos > 0 && value < data[parent(pos)]){
        data[pos]= data[parent(pos)];
        pos= parent(pos);
    }

    data[pos]= value;
    elements++;
}

template <class T>
void Heap<T>::pop(){
    T aux= data[0];

    data[0]= data[--count];
    heapify(0);

    elements--;
}

template <class T>
T Heap<T>::top(){
    return data[0];
}

#endif
