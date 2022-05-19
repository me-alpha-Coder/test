#include "bits/stdc++.h"
using namespace std;

int p[] = {10, 3, 9, 2, 0, 10}, q[] = {5, 6, 4, 4, 3, 8, 0};
int weight[7][7], cost[7][7], root[7][7];

class Node {
    public :
        int data;
        Node *lchild, *rchild;

        Node(){data = 0, lchild = NULL, rchild = NULL;}
        Node(int d){data = d, lchild = NULL, rchild = NULL;}
};

Node * find_tree(int i, int j){
    Node *temp = new Node(root[i][j]);
    if (i != root[i][j]-1)
        (i+1 == root[i][j]-1) ? temp->lchild = new Node(root[i][root[i][j]-1]) : temp->lchild = find_tree(i, root[i][j]-1);

    if (j != root[i][j])
        (j-1 == root[i][j]) ? temp->rchild = new Node(root[root[i][j]][j]) : temp->rchild = find_tree(root[i][j], j);
    return temp;
}

void dfs(Node *node){
    cout << node->data << " ";
    if (node->lchild != NULL)
        dfs(node->lchild);

    if (node->rchild != NULL)
        dfs(node->rchild);

}


int main(){
    for (int i = 0; i < 7; i++)
        weight[i][i] = q[i], cost[i][i] = 0, root[i][i] = 0;

    for (int k = 1; k < 7; k++){
        cout << "Step" << k << " : \n\n";
        for (int i = 0; i < 7-k; i++){
            weight[i][i+k] = p[i+k-1] + q[i+k] + weight[i][i+k-1];
            int temp = INT_MAX, tempI = -1;
            for (int j = i+1; j < i+k+1; j++)
                if (temp > cost[i][j-1]+ cost[j][i+k] + weight[i][i+k])
                    temp = cost[i][j-1]+ cost[j][i+k] + weight[i][i+k], tempI = j;
            cost[i][i+k] = temp;
            root[i][i+k] = tempI;

            cout << "   " << i << i+k << ":: " << weight[i][i+k] << " " << cost[i][i+k] << " " << root[i][i+k] << " \n";
        }
        cout << "---------------------------------\n";




    }
    Node *r = find_tree(0, 6);
    cout << "PREORDER : ";
    dfs(r);


    return 0;
}
