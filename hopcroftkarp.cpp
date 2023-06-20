
#include <iostream>
#include <list>
#include <queue>

#define INF 999999

using namespace std;

class GrafoBipartido{
    
	int particaoA, particaoB;
	list<int> *adj;
	int *emparelhamentoA, *emparelhamentoB, *dist;

public:
	GrafoBipartido(int m, int n); 
	void adicionarAresta(int u, int v); 
	bool buscaEmLargura();
	bool buscaEmProfundidade(int u);
	int hopcroftKarp();
	void verificarEmparelhamento();
};

int GrafoBipartido::hopcroftKarp(){
	emparelhamentoA = new int[particaoA+1];
	emparelhamentoB = new int[particaoB+1];
	dist = new int[particaoA+1];

	for (int u=0; u<=particaoA; u++)
		emparelhamentoA[u] = 0;
	for (int v=0; v<=particaoB; v++)
		emparelhamentoB[v] = 0;

	int result = 0; 
	while (buscaEmLargura()){
		for (int u=1; u<=particaoA; u++){
            if (emparelhamentoA[u]==0 && buscaEmProfundidade(u)){
                result++;
            }	
        }
	}
	return result;
}

bool GrafoBipartido::buscaEmLargura(){
	queue<int> Q;
	for (int u=1; u<=particaoA; u++){
		if (emparelhamentoA[u]==0){
			dist[u] = 0;
			Q.push(u);
		} else {
            dist[u] = INF;
        }
	}
	dist[0] = INF;

	while (!Q.empty()){
		int u = Q.front();
		Q.pop();
		if (dist[u] < dist[0]){
			list<int>::iterator i;
			for (i=adj[u].begin(); i!=adj[u].end(); ++i){
                int v = *i;
				if (dist[emparelhamentoB[v]] == INF){
					dist[emparelhamentoB[v]] = dist[u] + 1;
					Q.push(emparelhamentoB[v]);
				}
			}
		}
	}
	return (dist[0] != INF);
}

bool GrafoBipartido::buscaEmProfundidade(int u){
	if (u != 0){
		list<int>::iterator i;
		for (i=adj[u].begin(); i!=adj[u].end(); ++i){
			int v = *i;
			if (dist[emparelhamentoB[v]] == dist[u]+1){
				if (buscaEmProfundidade(emparelhamentoB[v]) == true){
					emparelhamentoB[v] = u;
					emparelhamentoA[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

GrafoBipartido::GrafoBipartido(int particaoA, int particaoB){
	this->particaoA = particaoA;
	this->particaoB = particaoB;
	adj = new list<int>[particaoA+1];
}

void GrafoBipartido::adicionarAresta(int u, int v){
	adj[u].push_back(v);
}

void GrafoBipartido::verificarEmparelhamento(){
	for(int i = 1; i < particaoA+1; i++){
		if(emparelhamentoA[i] != 0){
			cout << i << " Emparelhado com " << emparelhamentoA[i] << endl;
		}
	}
}

int main(){

    int A = 300;
    int B = 300;
    int qtdeArestas = 5;

	GrafoBipartido g(A, B);

    srand(10);
    for(int i = 1; i < A+1; i++){
        for(int j = 0; j < 1 + rand() % qtdeArestas; j++){
            g.adicionarAresta(i, 1 + rand () % B);
        }
    }

	// GrafoBipartido g(4, 5);

	// g.adicionarAresta(1, 1);
	// g.adicionarAresta(1, 3);
    // g.adicionarAresta(2, 1);
	// g.adicionarAresta(2, 2);
	// g.adicionarAresta(2, 5);
	// g.adicionarAresta(3, 3);
	// g.adicionarAresta(3, 2);
    // g.adicionarAresta(4, 3);
    
    cout << g.hopcroftKarp() << " Emparelhamentos no total" << endl;
	// g.verificarEmparelhamento();

	return 0;
}
