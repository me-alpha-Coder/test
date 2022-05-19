#include<bits/stdc++.h>
using namespace std;
queue <int> que;
int vertex;

int main()
{
    cout<<"\nEnter the number of vertex : ";
    cin>>vertex;

    int adj[vertex][vertex];
    int topol[vertex] = {0};

    for(int i = 0;i <vertex; i++){
        for(int j = 0;j < vertex; j++){
            adj[i][j] = 0;
        }
    }

    int e= 0;
    cout<<"\nEnter the number of edges : ";
    cin>>e;

    for (int i = 0; i < e; i++){
        int x, y;
        cin>>x>>y;
        adj[x][y] = 1;
        topol[y] += 1;
    }
  
    for (int i=0;i<vertex;i++)
    {
        if(topol[i]==0)
        {
            que.push(i);
            topol[i] = -1;
        }
    }

    if(que.empty())
    {
        cout<<"\nNot an Acyclic Directed Graph!";
    }

    cout<<"Topological Sort: ";
    while(!que.empty()){
        int x = que.front();
        for(int i = 0; i < vertex; i++)
        {
            if(adj[x][i]==1)
            {
                topol[i] -= 1;

                if(topol[i]==0)
                {
                    topol[i] = -1;
                    que.push(i);
                }

            }
        }
        cout<<" "<<x;
        que.pop();
        
    }cout << endl;
}
