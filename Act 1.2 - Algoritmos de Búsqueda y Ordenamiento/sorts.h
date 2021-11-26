/*
* Alumno:  Erick Alfredo García Huerta.
* Matrícula: A01708119
*/

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

using namespace std;

template <class T>
class Sorts{
    private:
        void swap(vector<T>&, int, int);
        void copyArray(vector<T>&, vector<T>&, int, int);
        void mergeArray(vector<T>&, vector<T>&, int, int, int);
        void mergeSplit(vector<T>&, vector<T>&, int, int);
        int ayudaBinaria(vector<T>&, int, int, int);
    public:
        void ordenaSeleccion(vector<T>&);
        void ordenaBurbuja(vector<T>&);
        void ordenaMerge(vector<T>&);
        int busqBinaria(vector<T>&, int);
        int busqSecuencial(vector<T>&, int);  
};

template <class T>
void Sorts<T>::swap(vector<T> &array, int i, int j){
    
    T aux= array[i];
    array[i]= array[j];
    array[j]= aux;
}

template<class T>
void Sorts<T>::ordenaSeleccion(vector<T> &list){
    for(int i= 0; i < (list.size()-1); i++){
        int pos= i;
        for(int j= i+1; j < list.size(); j++){
            if(list[j] < list[pos]){
                pos= j;
            }
        }
        if(pos != i){
                swap(list, i, pos);
        }
    }
}

template<class T>
void Sorts<T>::ordenaBurbuja(vector<T> &list){
    for(int i= list.size()-1; i >= 0; i--){
        for(int j= 0; j < i; j++){
            if(list[j] > list[j+1]){
                swap(list, j, j+1);
            }
        }
    }
}

template<class T>
void Sorts<T>::ordenaMerge(vector<T> &list){
    vector<T> temp(list.size());
    mergeSplit(list, temp, 0, list.size()-1);
}

template<class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
    if(high - low < 1){
        return;
    }

    int mid= (high + low)/2; 

    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid+1, high);

    mergeArray(A, B, low, mid, high);

    copyArray(A, B, low, high);
}

template<class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high){
    int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid && j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template<class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high){
    for(int i= low; i <= high; i++){
        A[i]= B[i];
    }
}

template<class T>
int Sorts<T>::busqSecuencial(vector<T> &list, int val){
    for(int i= 0; i < list.size(); i++){
        if(list[i] == val){
            return i;
        }
    }
    return -1;
}

template<class T>
int Sorts<T>::ayudaBinaria(vector<T> &list, int low, int high, int value){
    if(low < high){
        int mid= (low + high)/2;
        if(list[mid] == value){
            return mid;
        }else if(value < list[mid]){
            return ayudaBinaria(list, low, mid-1, value);
        }else if(value > list[mid]){
            return ayudaBinaria(list, mid+1, high, value);
        }
    }
    return -1;
}

template<class T>
int Sorts<T>::busqBinaria(vector<T> &list, int val){
    return ayudaBinaria(list, 0, list.size()-1, val);
}

#endif
