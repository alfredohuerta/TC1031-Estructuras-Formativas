/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*
*  Extiende este archivo para completar tu solución.
* 
* Alumno: Erick Alfredo García Huerta - A01708119
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;

public:
		Graph();
		Graph(int);
		void loadGraphMat(string, int, int);
		void loadGraphList(const string &, int, int);

		void addEdgeAdjMatrix(int, int);
		void addEdgeAdjList(int, int);

		string printAdjMat();
		string printAdjList();

		string DFS(int, int);
		string BFS(int, int);

		void dfsHelper(int, int, stack<int> &, list<int> &, vector<vector<int>> &, stringstream &);
    	void bfsHelper(int, int, queue<int> &, list<int> &, vector<vector<int>> &, stringstream &);

		static void printPath(vector<vector<int>> &, int, int, stringstream &);
    	static void printVisited(list<int>, stringstream &);

		bool contains(list<int>, int);
		void sortAdjList();
};

/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph() {
	edgesList = edgesMat = nodes = 0;
	adjList= {};
	adjMatrix= 0;
}

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param n valor del nodo.
 */
Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

/**
 * @brief función que carga el grafo desde un arhicvo de texto.
 * 
 * @param name nombre del archivo.
 * @param a 
 * @param b 
 */
void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++){
		adjMatrix[i] = 0;
	}	
	string line;
	ifstream lee (name);
	int u, v;
	if (lee.is_open()){
		while (getline(lee, line)){
			u = stoi(line.substr(1,1));
			v = stoi(line.substr(4,1));
			addEdgeAdjMatrix(u,v);
		}
		lee.close(); // Closes the file
	} else {
		cout << "Unable to open file";
	}
}

/**
 * @brief función que cargael grafo desde un archivo de texto
 * 
 * @param file_name nombre del archivo.
 * @param a 
 * @param b 
 */
void Graph::loadGraphList(const string &file_name, int a, int b){
	nodes = a;
    adjList = new vector<int>[nodes];

    string line;
    ifstream archivo(file_name);
    int u, v;
    if (archivo.is_open()) {
        while (getline(archivo, line)) {
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(4, 1));
            addEdgeAdjList(u, v);
        }
        archivo.close();
	} else{
		cout << "Unable to open file";
	}
}

/**
 * @brief Función que agrega una arista al grafo (matríz)
 * 
 * @param u 
 * @param v 
 */
void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

/**
 * @brief Función que agrega una arista al grafo (lista)
 * 
 * @param u 
 * @param v 
 */
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

/**
 * @brief Función que imprime los datos del grafo en una lista de adyacencia.
 * 
 * @return string datos de la lista
 */
string Graph::printAdjList(){
	  sortAdjList();
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
	return aux.str();

}

/**
 * @brief Función que imprime los datos del grafo en una matriz de adyacencia.
 * 
 * @return string datos de la matriz.
 */
string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

/**
 * @brief Función que aplica un depth first search
 * 
 * @param start nodo desde el que se inicia
 * @param goal nodo que se busca
 * @return string camino que se siguió
 */
string Graph::DFS(int start, int goal){
	stringstream aux;

	stack <int> st;
	list <int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1, -1));
	st.push(start);

	dfsHelper(start, goal, st, visited, paths, aux);
	printPath(paths, start, goal, aux);

	return aux.str();
}

/**
 * @brief Función que aplica un breath first search
 * 
 * @param start nodo desde el que se inicia
 * @param goal nodo que se busca
 * @return string camino recorrido.
 */
string Graph::BFS(int start, int goal){
	stringstream aux;

    queue<int> q;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(0));
    q.push(start);

    bfsHelper(start, goal, q, visited, paths, aux);
    printPath(paths, start, goal, aux);

    return aux.str();
}

/**
 * @brief Función que lleva a cabo el dfs y controla el recorrido.
 * 
 * @param current nodo donde se encuentra actualmente el recorrido e inicia.
 * @param goal nodo que se busca
 * @param st stack donde encuentran el nodo que se está recorriendo
 * @param visited nodos visitados
 * @param paths caminos recorridos
 * @param aux stringstream donde se almacenará paths
 */
void Graph::dfsHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths, stringstream &aux){
	if(current == goal){
		printVisited(visited, aux);
	} else if(st.empty()){
		cout << "No se encontró." << endl;
	} else{
		current= st.top();
		st.pop();
		visited.push_back(current);
		for(int i= 0; i < adjList[current].size(); i++){
			if(!contains(visited, adjList[current][i])){
				st.push(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
			}
		}
		dfsHelper(current, goal, st, visited, paths, aux);
	}
}

/**
 * @brief Función donde se lleva a cabo del bfs y controla el recorrido
 * 
 * @param current nodo donde se encuentra actualmente el recorrido e inicia.
 * @param goal nodo que se busca
 * @param q queue donde se encuentran los datos actuales.
 * @param visited lista donde se almacenan los nodos visitados
 * @param paths vector de caminos recorridos
 * @param aux  stringstream donde se imprimirá el recorrido.
 */
void Graph::bfsHelper(int current, int goal, queue<int> &q, list<int> &visited, vector<vector<int>> &paths, stringstream &aux){
	if(current == goal){
		printVisited(visited, aux);
	} else if(q.empty()){
		aux << " ";
	} else{
		current = q.front();
		q.pop();
		visited.push_back(current);
		for(int i= 0; i < adjList[current].size(); i++){
			if(!contains(visited, adjList[current][i])){
				q.push(adjList[current][i]);
				paths[adjList[current][i]].push_back(current);
			}
		}
		bfsHelper(current, goal, q, visited, paths, aux);
	}
}

/**
 * @brief Función que imprime el camino recorrido.
 * 
 * @param paths vector donde se almacenan los caminos.
 * @param start nodo donde se inicia el recorrido.
 * @param goal nodo donde termina el camino
 * @param aux stringstream donde se imprime el camino
 */
void Graph::printPath(vector<vector<int>> &paths, int start, int goal, stringstream &aux){
	aux << "path: ";
	int node= paths[goal][0];

	stack<int> alReves;
	alReves.push(goal);

	while(node != start){
		alReves.push(node);
		node= paths[node][0];
	}

	alReves.push(start);
	while(!alReves.empty()){
		aux << alReves.top();
		alReves.pop();
		if(!alReves.empty()){
			aux << " ";
		}
	}
}

/**
 * @brief Función que imprime los nodos visitados.
 * 
 * @param visited lista de nodos visitados.
 * @param aux stringstream donde se imprimen los nodos visitados.
 */
void Graph::printVisited(list<int> visited, stringstream &aux){
	aux << "visited: ";
	while(!visited.empty()){
		aux << visited.front() << " ";
		visited.pop_front();
	}
}

/**
 * @brief Función que dice si un nodo se encuentra en la lista de nodos visitados o no.
 * 
 * @param lista lista donde se encuentran los nodos visitados.
 * @param node nodo a buscar
 * @return true se ha visitado el nodo
 * @return false  no se ha visitado el nodo.
 */
bool Graph::contains(list<int> lista, int node){
	list<int>::iterator it;

	it= find(lista.begin(), lista.end(), node);

	if(it != lista.end()){
		return true;
	} else{
		return false;
	}
}

/**
 * @brief Función que ordena el grafo en una lista de adyacencia
 */
void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(),adjList[i].end());
	}
}

#endif /* Graph_H_ */
