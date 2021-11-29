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
		Graph();//
		Graph(int);//
		void loadGraphMat(string, int, int);//
		void loadGraphList(const string &, int, int);

		void addEdgeAdjMatrix(int, int);//
		void addEdgeAdjList(int, int);//

		string printAdjMat();//
		string printAdjMat_clean();//
		string printAdjList();//

		string DFS(int, int);
		string BFS(int, int);

		void dfsHelper(int, int, stack<int> &, list<int> &, vector<vector<int>> &, stringstream &);
    	void bfsHelper(int, int, queue<int> &, list<int> &, vector<vector<int>> &, stringstream &);

		static void printPath(vector<vector<int>> &, int, int, stringstream &);
    	static void printVisited(list<int>, stringstream &);

		bool contains(list<int>, int);
		void sortAdjList();
};

Graph::Graph() {
	edgesList = edgesMat = nodes = 0;
	adjList= {};
	adjMatrix= 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

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

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

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

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}


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

void Graph::printVisited(list<int> visited, stringstream &aux){
	aux << "visited: ";
	while(!visited.empty()){
		aux << visited.front() << " ";
		visited.pop_front();
	}
}

bool Graph::contains(list<int> lista, int node){
	list<int>::iterator it;

	it= find(lista.begin(), lista.end(), node);

	if(it != lista.end()){
		return true;
	} else{
		return false;
	}
}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(),adjList[i].end());
	}
}

#endif /* Graph_H_ */
