/**
 * @file quadratic.h
 * @author Erick Alfredo García Huerta - A01708119
 * @brief programa con la solución al main
 */
#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic{
    private:
        unsigned int (*func) (const Key);
        unsigned int size;
        unsigned int count;

        Key *keys;
        Key initialValue;
        Value *values;

        long indexOf(const Key) const;
    public:
        Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
        ~Quadratic();
        bool full() const;
        void clear();
        std::string toString() const;

        void put(Key, Value);
        Value get(const Key);
};

/**
 * Constructor de objeto quadratic
 * 
 * @tparam unsigned int tamaño -> tamaño del arreglo.
 * @tparam Key init -> valor por defecto de las llaves que carcan espacios vacíos.
 * @tparam unsigned int (*f) -> función que calcula el valor de la llave
 */
template <class Key, class Value>
Quadratic <Key, Value>::Quadratic(unsigned int tam, Key init, unsigned int (*f) (const Key)){
	size = tam;
	keys = new Key[size];
	
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];
	
	for (int j = 0; j  < tam; j++){
		values[j] = 0;
    }

	func = f;
	count = 0;
}

/**
 * @brief Destructor de Quadratic
 */
template <class Key, class Value>
Quadratic <Key, Value>::~Quadratic(){
    delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;
}

/**
 * @brief 
 * 
 * @param Key k -> llave que usará para calcular el valor del índice
 * @return long -> valor del índice
 * 
 * hacer un for con un j*j para la prueba cuadrática
 */
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const{
	unsigned int i, start;

	start = i = func(k) % size;
	for(int j= 0; j < size; j++){
		if (keys[i] == k) {
			return i;
		}
		i = (start + j*j) % size;
	}
	return -1;
}

/**
 * @brief función que devuelve un valor booleano de si la clase está llena o no.
 *  
 * @return true 
 * @return false 
 */
template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

/**
 * @brief función que restaura el valor de todas las llaves a su valor inicial
 */
template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}

/**
 * @brief función que convierte a string los valores de la hash table.
 * 
 * @return std::string cadena de strings con los valores de la tabla.
 */
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v){
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return;
	}

	start = i = func(k) % size;

	for(int j= 0; j < size; j++){
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
            return;
		}
		i = (start + j*j) % size;
	}
	return;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k){
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
	return 0;
}

#endif
