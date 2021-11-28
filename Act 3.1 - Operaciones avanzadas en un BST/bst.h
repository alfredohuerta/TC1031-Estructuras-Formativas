/**
 * @file bst.h
 * @author Erick Alfredo García Huerta - A01708119
 * @brief Archivo que contiene las funciones necesarias para el main.cpp
 */
#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T>
class BST;

template <class T>
class Node {
   private:
    T value;
    Node *left, *right;
   public:
    Node(T);
    Node(T, Node<T> *, Node<T> *);
    void add(T);
    bool find(T);
    void preorder(stringstream &) const;
    void inorder(stringstream &) const;
    void postorder(stringstream &) const;
    void printlevel(stringstream &, int) const;
    void levelorder(stringstream &) const;
    int height() const;
    bool ancestors(T, stringstream &);
    int whatLevelAmI(T);
    friend class BST<T>;
};

/**
 * @brief Construct a new Node< T>:: Node object
 * 
 * @param val 
 */
template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

/**
 * @brief Construct a new Node< T>:: Node object
 * 
 * @param val 
 * @param le 
 * @param ri 
 */
template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri) : value(val), left(le), right(ri) {}

/**
 * @brief Función que agrega un nuevo nodo al árbol y selecciona su posición en él en base a si es mayor o menor que el 
 * primer valor que se encuentra.
 * 
 * @param newValue valor a agregar
 */
template <class T>
void Node<T>::add(T newValue){
    if(newValue < value){
        if(left != 0){
            left->add(newValue);
        }else{
            left= new Node<T>(newValue);
        }
    }else{
        if(right != 0){
            right->add(newValue);
        }else{
            right= new Node<T>(newValue);
        }
    }
}

/**
 * @brief Función que busca un valor entre los nodos y manda a llamarse a sí misma en otras ramas en caso de no encontrar
 * el dato que busca.
 * 
 * @param value valor que se busca
 * @return true 
 * @return false 
 */
template <class T>
bool Node<T>::find(T valor){
    if(valor == value){
        return true;
    }

    if(valor < value){
        return (left != 0 && left->find(valor));
    }else{
        return (right != 0 && right->find(valor));
    }
}

/**
 * @brief función que imprime los datos en preorder
 * 
 * @param datos stringstream que contiene los datos del árbol.
 */
template <class T>
void Node<T>::preorder(stringstream &datos) const{
    datos << value;
    if(left != 0){
        datos << " ";
        left->preorder(datos);
    }
    if(right != 0){
        datos << " ";
        right->preorder(datos);
    }
}

/**
 * @brief Función que imprime los datos en orden.
 * 
 * @param datos stringstream que contiene los datos del árbol.
 */
template <class T>
void Node<T>::inorder(stringstream &datos) const{
    if(left != 0){
        left->inorder(datos);
    }
    if(datos.tellp() != 1){
        datos << " ";
    }
    datos << value;
    if(right != 0){
        right->inorder(datos);
    }
}

/**
 * @brief Función que imprime los datos en post order
 * 
 * @param datos stringstream que contiene los datos del árbol.
 */
template <class T>
void Node<T>::postorder(stringstream &datos) const{
    if(left != 0){
        left->postorder(datos);
    }
    if(right != 0){
        right->postorder(datos);
    }
    if(datos.tellp() != 1){
        datos << " ";
    }
    datos << value;
}

/**
 * @brief Imprime el nivel del nodo.
 * 
 * @param datos string stream donde se almacenan los datos
 * @param level nivel del nodo.
 */
template <class T>
void Node<T>::printlevel(stringstream &datos, int level) const{
    if(level == 0){
        if(datos.tellp() != 1){
            datos << " ";
        }
        datos << value;
    }
    if(left != 0){
        left->printlevel(datos, level-1);
    }
    if(right != 0){
        right->printlevel(datos, level -1);
    }
}

/**
 * @brief función que imprime todos los niveles del bst
 * 
 * @param datos string stream donde se almacenan los datos.
 */
template <class T>
void Node<T>::levelorder(stringstream &datos) const{
    int level = height();
    for(int i= 0; i < level; i++){
        printlevel(datos, i);
    }
}

/**
 * @brief Función que regresa la profundidad del BST
 * 
 * @return int nivel de profundidad.
 */
template <class T>
int Node<T>::height() const{
    int lvlright, lvlleft;
    lvlright= 0; 
    lvlleft= 0;

    if(left != 0){
        lvlleft= left->height()+1;
    }
    if(right != 0){
        lvlright= right->height()+1;
    }
    if (lvlleft == 0 && lvlright == 0){
        return 1;
    } 
    return (lvlright > lvlleft) ? lvlright : lvlleft;
}

/**
 * @brief función que busca si los nodos tienen ancestros
 * 
 * @param valor valor del nodo
 * @param datos ancestros del nodo.
 * @return true 
 * @return false 
 */
template <class T>
bool Node<T>::ancestors(T valor, stringstream &datos){
    if(valor == value){
        return true;
    }
    if(valor < value){
        if(datos.tellp() != 1){
            datos << " ";
        }
        datos << value;
        return (left != 0 && left->ancestors(valor, datos));
    }else{
        if(datos.tellp() != 1){
            datos << " ";
        }
        datos << value;
        return (right != 0 && right->ancestors(valor, datos));
    }
}

/**
 * @brief Función que devuelve en qué nodo está el nodo actual
 * 
 * @param valor valor del nodo
 * @return int nivel del nodo
 */
template <class T>
int Node<T>::whatLevelAmI(T valor){
    if(valor == value){
        return 1;
    }
    if(valor < value){
        if(left != 0){
            return left->whatLevelAmI(valor)+1;
        }
    }else{
        if(right != 0){
            return right->whatLevelAmI(valor)+1;
        }
    }

    return -1;
}

template <class T>
class BST {
   private:
    Node<T> *root;
   public:
    BST();
    bool empty() const;
    void add(T);
    bool find(T) const;
    string preorder() const;
    string inorder() const;
    string postorder() const;
    string levelorder() const;
    string visit();
    string ancestors(T);
    int height() const;
    int whatlevelamI(T) const;
};

/**
 * @brief Construct a new BST<T>::BST object
 */
template <class T>
BST<T>::BST() : root(0) {}

/**
 * @brief revisa si el árbol está vacío o no.
 * 
 * @return true 
 * @return false 
 */
template <class T>
bool BST<T>::empty() const{
    return (root == 0);
}

/**
 * @brief Función que agrega un nodo más al árbol
 * 
 * @param newValue valor a agregar.
 */
template <class T>
void BST<T>::add(T newValue){
    if (root != 0) {
        if (!root->find(newValue)) {
            root->add(newValue);
        }
    } else {
        root = new Node<T>(newValue);
    }
}

/**
 * @brief función que busca un valor dentro del árbol.
 * 
 * @param valor valor a buscar.
 * @return true se encontró el valor.
 * @return false no se encontró el valor.
 */
template <class T>
bool BST<T>::find(T valor) const{
    if(root != 0){
        return root->find(valor);
    }

    return false;
}

/**
 * @brief Función que imprime todos los datos del árbolen preorder.
 * 
 * @return string datos del árbol.
 */
template <class T>
string BST<T>::preorder() const{
    stringstream datos;

    datos << "[";
    if(!empty()){
        root->preorder(datos);
    }
    datos << "]";

    return datos.str();
}

/**
 * @brief Función que imprime todos los datos del árbol en orden.
 * 
 * @return string datos del árbol.
 */
template <class T>
string BST<T>::inorder() const{
    stringstream datos;

    datos << "[";
    if(!empty()){
        root->inorder(datos);
    }
    datos << "]";

    return datos.str();
}

/**
 * @brief Función que regresa todos los datos en post-order.
 * 
 * @return string datos del árbol.
 */
template <class T>
string BST<T>::postorder() const{
    stringstream datos;

    datos << "[";
    if(!empty()){
        root->postorder(datos);
    }
    datos << "]";

    return datos.str();
}

/**
 * @brief Función que imprime todos los datos del árbol por nivel.
 * 
 * @return string datos del árbol.
 */
template <class T>
string BST<T>::levelorder() const{
    stringstream datos;

    datos << "[";
    if(!empty()){
        root->levelorder(datos);
    }
    datos << "]";

    return datos.str();
}

/**
 * @brief Función que regresa todas las distintas formas de impresión de datos.
 * 
 * @return datos del árbol.
 */
template <class T>
string BST<T>::visit(){
    stringstream datos;

    datos << preorder() << endl;
    datos << inorder() << endl;
    datos << postorder() << endl;
    datos << levelorder() << endl;

    return datos.str();
}

/**
 * @brief Función que imprime los ancestros de un nodo.
 * 
 * @param valor valor del nodo que se planea investigar.
 * @return string ancestros del nodo
 */
template <class T>
string BST<T>::ancestors(T valor){
    stringstream datos;

    datos << "[";
    if(!empty()){
        if(!root->ancestors(valor, datos)){
            return "[]";
        }
    }
    datos << "]";

    return datos.str();
}

/**
 * @brief Función que obtiene la altura del árbol
 * 
 * @return int altura del árbol.
 */
template <class T>
int BST<T>::height() const{
    return root->height();
}

/**
 * @brief Función que regresa el nivel de un nodo.
 * 
 * @param valor nodo del que se quiere obtener el nivel.
 * @return int nivel del nodo.
 */
template <class T>
int BST<T>::whatlevelamI(T valor) const{
    if(root != 0){
        int nivel= root->whatLevelAmI(valor);
        if(nivel < 0){
            return -1;
        }
        return nivel;
    }

    return -1;
}

#endif
