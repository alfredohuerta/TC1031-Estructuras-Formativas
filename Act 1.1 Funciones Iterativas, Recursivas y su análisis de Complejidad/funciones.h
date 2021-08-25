/*
* funciones.h
* 
* Author: Erick Alfredo García Huerta
* Matrícula: A01708119
*
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
using namespace std;

class Funciones
{
    public:
        int sumaIterativa(int);
        int sumaRecursiva(int);
        int sumaDirecta(int);
};

int Funciones :: sumaIterativa (int n){ // O(n)
    int acum= 0;
    for (int i= 0; i <= n ; i++){
        acum += i;
    }
    return acum;
}

int Funciones :: sumaRecursiva (int n){ //  O(n)
    if (n <= 0){
        return 0; // O(n)
    } else{
        return n + sumaRecursiva(n-1); // O(1)
    }
}

int Funciones :: sumaDirecta (int n){ // O(1)
    return (n*(n+1)/2);
}

#endif