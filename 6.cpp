#include "bits/stdc++.h"
#define MAX 10
using namespace std;

class Graph{
    int n, connected;
    int** adjMatrix;
    bool* visited;
    public :
        Graph (int size = 10){
            n = size;
            connected = 0;
            adjMatrix = new int *[n];
            visited = new bool[n];
            for (int i = 0; i < n; i++){
                adjMatrix[i] = new int[n];
                visited[i] = false;
                for (int j = 0; j < n; j++)
                    adjMatrix[i][j] = 0;
            }
        }
        ~Graph () {
            for (int i = 0; i < n; i++)
                delete[] adjMatrix[i];
            delete[] adjMatrix;
        }

        void addEdge(int u, int v);
        void removeEdge(int u, int v);
        void display();
        void dfs(int vertex);
        void dfs_with_stack(int vertex);
        void clear_visited();
        void bfs(int vertex);
        bool is_connected();
};


void Graph :: addEdge(int u, int v){
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}
void Graph :: removeEdge(int u, int v){
    adjMatrix[u][v] = 0;
    adjMatrix[v][u] = 0;
}
void Graph :: display(){
    cout << "----------------------------------------------------------\n";
    cout << "                    ADJACENCY MATRIX\n";
    cout << "    ";
    for (int i = 0; i < n; i++)
        cout << i << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << i << " : ";
        for (int j = 0; j < n; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
}

void Graph :: clear_visited(){
    for (int i = 0; i < n; i++)
        visited[i] = false;
    return;
}

void Graph :: dfs(int vertex){
    visited[vertex] = true;
    connected++;
    cout << vertex << " ";
    for (int i = 0; i < n; i++)
        if (adjMatrix[vertex][i] == 1 and visited[i] == false)
            dfs(i);
    return ;
}

void Graph :: dfs_with_stack(int vertex){
    clear_visited();
    stack <int> s;
    s.push(vertex);
    visited[vertex] = 1;

    while (!s.empty()){
        int v = s.top();
        s.pop();
        cout << v << " ";
        for (int i = 0; i < n; i++){
            if (adjMatrix[v][i] == 1 and visited[i] == false)  
                s.push(i), visited[i] = true;
        }
    }

}

void Graph :: bfs(int vertex){
    queue <int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()){
        int curr_vertex = q.front();
        q.pop();
        cout << curr_vertex << " ";
        for (int i = 0; i < n; i++)
            if (adjMatrix[curr_vertex][i] == 1 and visited[i] == false)
                visited[i] = true, q.push(i);
    }
    return;
}

bool Graph :: is_connected(){
    clear_visited();
    connected = 0;dfs(0);
    if (connected == n)
        return true;
    int count = 1;
    for (int i = 1; i < n; i++)
        if (visited[i] == false)
            dfs(i), count++;
    cout << "Total Connected components : " << count << "\n";
    return  false;
}
int main(){

    int n; cout << "Enter the number of nodes : "; cin >> n;
    Graph graph(n);

    while (true){
        int choice;
        cout << "----------------------------------------------------------\n";
        cout << "                       MAIN MENU\n";
        cout << "\n     1. Add Edge\n     2. Delete Edge\n" << 
                "     3. Display Graph\n     4. Add all edges for a particular node\n     5. DFS\n     6. BFS\n     7. Check if the Graph is Connected\n     8. DFS with Stack     \n     9. Exit\n";
        cout << "Enter your choice : "; cin >> choice;

        switch (choice){
            case 1 : {
                int u, v;
                cout << "     Enter first node : "; cin >> u;
                cout << "     Enter second node : "; cin >> v;
                graph.addEdge(u, v);
                break;
            }
            case 2 : {
                int u, v;
                cout << "     Enter first node : "; cin >> u;
                cout << "     Enter second node : "; cin >> v;
                graph.removeEdge(u, v);
                break;
            }
            case 3 : {
                graph.display();
                break;
            }
            case 4 : {
                int u;
                cout << "   Enter node : "; cin >> u;
                for (int i = 0; i < n; i++)
                    graph.addEdge(u, i);
                break;
            }
            case 5 : {
                int vertex; 
                cout << "Enter the root vertex : "; cin >> vertex;
                graph.clear_visited();
                graph.dfs(vertex);
                cout << "\n";
                break;
            }
            case 6 : {
                int vertex; 
                cout << "Enter the root vertex : "; cin >> vertex;
                graph.clear_visited();
                graph.bfs(vertex);
                cout << "\n";
                break;
            }
            case 7 : {
                if (graph.is_connected())
                    cout << "The graph is Connected!\n";
                else
                    cout << "The graph is NOT Connected!\n";
                break;
            }
            case 8 : {
                int vertex; 
                cout << "Enter the root vertex : "; cin >> vertex;
                graph.clear_visited();
                graph.dfs_with_stack(vertex);
                cout << "\n";
                break;
            }
            case 9 : {
                return 0;
            }
        }
    }
    
}
