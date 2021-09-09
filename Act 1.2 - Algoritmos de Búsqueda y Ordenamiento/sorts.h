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
    public:
        vector <T> ordenaSeleccion(const vector<T>&);
        vector <T> ordenaBurbuja(const vector<T>&);
        vector <T> ordenaMerge(const vector<T>&);
        vector <T> busqSecuencial(const vector<T>&, int);
        vector <T> busqBinaria(const vector<T>&, int);      
};

template <class T>
void Sorts<T> :: swap(vector<T> &prueba, int i, int j){
    vector<T> v(prueba);
    T aux= v[i];
    v[i]= v[j];
    v[j]= aux;
}

template <class T>
void Sorts<T> :: copyArray(vector<T> &A, vector<T> &B, int low, int high){
    for(int i= low, i <= high; i++){
        A[i]= B[i];
    }
}

template <class T>
void Sorts<T> :: mergeArray(vector<T> &A, vector<T> &B, int low, int high, int mid){
    int i, j, k;

    i= low;
    j= mid+1;
    k= high;

    while (i <= mid && <= high)
    {
        if(A[i]<A[j]){
            B[k]= A[i];
            i++;
        }else{
            B[k]= A[j];
            j++;
        }
        k++;
    }

    if(i>mid){
        for(; j <=high; j++){
            B[k+1]= A[j];
        }
    }else{
        for(; i <=mid ; i++){
            B[k+1]= A[i];
        }
    }
    
}

template <class T>
void Sorts<T> :: mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
    int mid;

    if(high-low < 1){
        return;
    }

    mid= (high+low)/2;

    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid+1, high);

    mergeArray(A, B, low, mid, high);

    copyArray(A, B, low, high);
}

template <class T>
vector <T> Sorts<T> :: ordenaSeleccion(const vector<T> &prueba){
    vector <T> v(prueba);

    for (int i= v.size() - 1; i > 0; i--){
        int num= 0; 

        for (int j= 0; j<=i; j++){

            if (v[j] > v[num]){
                num= j;
            }
        }
    
        if (num != i){
            swap(v, i, num);
        }
    }

    return v;
}

template <class T>
vector <T> Sorts<T> :: ordenaBurbuja(const vector<T> &prueba){
    vector <T> v(prueba);

    for(int i= v.size() - 1; i > 0; i--){

        for(int j= 0; j<i; j++){

            if(v[j] < v[j+1]){
                swap(v, j, j+1);
            }
        }
    }

    return v;
}

template <class T>
vector <T> Sorts<T> :: ordenaMerge(const vector<T> &prueba){
    vector <T> v(prueba);
    vector <T> temp(v.size());

    mergeSplit(v, tmp, 0, v.size()-1);

    retunr v;
}

template <class T>
vector <T> Sorts<T> :: busqSecuencial(const vector<T> &prueba, int num){
    vector <T> v(prueba);
    vector <T> ans(num);

    int n;
    
    for(int i= 0; i<v.size(); i++){
        if (v[i]== ans){
            n= i;
        }else{
            n= -1;
        }
    }

    return n;
}

template <class T>
vector <T> Sorts<T> :: busqBinaria(const vector<T> &prueba, int num){
    vector <T> v(prueba);
    vector <T> ans(num);

}

#endif