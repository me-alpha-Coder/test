#include "bits/stdc++.h"
#define MAX 10
using namespace std;

class Node {
    public :
        int data;
        Node *lchild, *rchild;

        Node(){data = 0, lchild = NULL, rchild = NULL;}
        Node(int d){data = d, lchild = NULL, rchild = NULL;}
};

class Tree {
    public :
        Node *root;
        Tree(int d = 0){root = new Node(d);}

        void insert_node(int node, int parent, Node *temp);

        void recursive_inorder(Node *node);
        void recursive_preorder(Node *node);
        void recursive_postorder(Node *node);

        void iterative_inorder();
        void iterative_preorder();
        void iterative_postorder();

        int height(Node *node);
        void delete_node(int n, Node *node);
        void delete_all_nodes(Node *node);
        void cloning(Node *self, Node *clone);
        bool compare(Node *node1, Node *node2);
};

void Tree :: insert_node(int node, int parent, Node *temp){
    if (temp == NULL)
        return;
    if (temp->data == parent){
        if (temp->lchild == NULL)
            {temp->lchild = new Node(node); return;}
        if (temp->rchild == NULL)
            {temp->rchild = new Node(node); return;}
        return;
    }

    insert_node(node, parent, temp->lchild);
    insert_node(node, parent, temp->rchild);

    return;
}

void Tree :: recursive_inorder(Node *node){
    if (node == NULL)
        return;
    recursive_inorder(node->lchild);
    cout << node->data << " ";
    recursive_inorder(node->rchild);
}
void Tree :: recursive_preorder(Node *node){
    if (node == NULL)
        return;
    cout << node->data << " ";
    recursive_preorder(node->lchild);
    recursive_preorder(node->rchild);
}
void Tree :: recursive_postorder(Node *node){
    if (node == NULL)
        return;
    recursive_postorder(node->lchild);
    recursive_postorder(node->rchild);
    cout << node->data << " ";
}

void Tree :: iterative_inorder(){
    stack <Node *> s;
    Node *current = root;
    while (current != NULL or !s.empty()) {
        s.push(current);
        while (current != NULL)
            {s.push(current->lchild); current = s.top();}
        s.pop();
        current = s.top();
        cout << current->data << " ";
        s.pop();
        current = current->rchild;
    }
    return;
}
void Tree :: iterative_preorder(){
    stack <Node *> s;
    s.push(root);
    Node *current;
    while (!s.empty()){
        current = s.top();
        cout << current->data << " ";
        s.pop();
        if (current->rchild != NULL) s.push(current->rchild);
        if (current->lchild != NULL) s.push(current->lchild);
    }
}
void Tree :: iterative_postorder(){
    stack <Node *> s;
    s.push(root);
    Node *current = root;
    vector <int> v(16);
    while (!s.empty()){
        while (current != NULL and current->lchild != NULL and v[current->data] != 1){s.push(current->lchild); current = s.top();}
        current = s.top();
        s.pop();
        cout << current->data << " ";
        if (s.empty())
            break;
        current = s.top();
        if (current != NULL and v[current->data] == 0){
            if (current->rchild != NULL) s.push(current->rchild);
            v[current->data] = 1;
            current = s.top();
        }
    }
}

int Tree :: height(Node *node){
    if (node == NULL)
        return 0;
    return 1 + max(height(node->lchild), height(node->rchild));
}
void Tree :: delete_all_nodes(Node *node){
    if (node == NULL) return;
    node->data = 0;
    delete_all_nodes(node->lchild);
    node->lchild = NULL;
    delete_all_nodes(node->rchild);
    node->rchild = NULL;
    // node->data = NULL;
    node = NULL;
    delete node;
}
void Tree :: delete_node(int n, Node *node){
    if (node == NULL)
        return;
    if (root->data == n)
        {delete_all_nodes(root);return;}
    if (node->lchild != NULL and node->lchild->data == n)
        {delete_all_nodes(node->lchild); node->lchild = NULL;return;}
    if (node->rchild != NULL and node->rchild->data == n)
        {delete_all_nodes(node->rchild); node->rchild = NULL;return;}
    delete_node(n, node->lchild);
    delete_node(n, node->rchild);
}
void Tree :: cloning(Node *self, Node *clone){
    if (self == NULL)
        return;
    if (self->lchild != NULL){
        clone->lchild = new Node(self->lchild->data);
        cloning(self->lchild, clone->lchild);
    }
    if (self->rchild != NULL){
        clone->rchild = new Node(self->rchild->data);
        cloning(self->rchild, clone->rchild);
    }

}
bool Tree :: compare(Node *node1, Node *node2){
    if (node1 == NULL and node2 == NULL)
        return true;
    if (node1 == NULL or node2 == NULL or node1->data != node2->data)
        return false ;

    return (compare(node1->lchild, node2->lchild) and
            compare(node1->rchild, node2->rchild)
           );

}

void make_tree(vector<int> &inorder,  vector<int> &preorder, int s, int e, Tree &t,int parent){
    if (s > e)
        return;
    if (s == e)
        {t.insert_node(inorder[s], parent, t.root);return;}
    int found = 0;
    for (int i = 0; i < preorder.size(); i++){
        int f = false;
        for (int j = s; j < e+1; j++){
            if (preorder[i] == inorder[j])
                {found = j;f = true;break;}
        }
        if (f) break;
    }
    t.insert_node(inorder[found], parent, t.root);
    make_tree(inorder, preorder, s, found-1, t, inorder[found]);
    make_tree(inorder, preorder, found+1, e, t, inorder[found]);

}


int main(){
    Tree tree;
    int n; cout << "Enter number of nodes : "; cin >> n;
    cout << "NODE :: PARENT\n";
    for  (int i = 1; i < n; i++){
        int node, parent; cin >> node >> parent;
        tree.insert_node(node, parent, tree.root);
    }
    while (true){
        int choice;
        cout << "----------------------------------------------------------\n";
        cout << "----------------------------------------------------------\n";
        cout << "                          MENU \n";
        cout << "\n     1. Insert a Node\n     2. Inorder\n     3. Preorder\n     4. Postorder\n     5. Height\n     6. Cloning and deletion\n     7. Creating binary tree from inorder and preoder\n     8. Delete node\n     9. Equality of Trees\n    10. Exit\n";
        cout << "Enter your choice : "; cin >> choice;

        switch (choice){
            case 1 : {
                int node, parent;
                cout << "Enter Node number : "; cin >> node;
                cout << "Enter Parent Node : "; cin >> parent;
                tree.insert_node(node, parent, tree.root);
                break;
            }
            case 2 : {
                cout << "RECUSRIVE : "; tree.recursive_inorder(tree.root);cout << "\n";
                cout << "ITERATIVE : "; tree.iterative_inorder();cout << "\n";
                break;
            }
            case 3 : {
                cout << "RECUSRIVE : ";tree.recursive_preorder(tree.root);cout << "\n";
                cout << "ITERATIVE : ";tree.iterative_preorder();cout << "\n";
                break;
            }
            case 4 : {
                cout << "RECUSRIVE : ";tree.recursive_postorder(tree.root);cout << "\n";
                cout << "ITERATIVE : ";tree.iterative_postorder();cout << "\n";
                break;
            }
            case 5 : {
                cout << "Height of the tree  : " << tree.height(tree.root) << "\n";
                break;
            }
            case 6 : {
                Tree new_tree;
                tree.cloning(tree.root, new_tree.root);
                tree.delete_all_nodes(tree.root);

                cout << "RECUSRIVE : ";cout << "Deleted Tree : ";tree.recursive_inorder(tree.root);cout << "\n";
                cout << "RECUSRIVE : ";cout << "New Cloned Tree : ";new_tree.recursive_inorder(new_tree.root) ; cout << "\n";
                tree = new_tree;
                cout << "RECUSRIVE : ";cout << "Tree after requating : ";tree.recursive_inorder(tree.root);cout << "\n";
                break;
            }
            case 7 : {
                int n; cout << "Enter the number of Nodes : "; cin >> n;
                vector <int> inorder(n), preorder(n);

                cout << "Enter the Inorder : ";
                for (int i = 0; i < n; i++)
                    cin >> inorder[i];
                cout << "Enter the Preorder : ";
                for (int i = 0; i < n; i++)
                    cin >> preorder[i];

                Tree t(preorder[0]);
                for (int i = 0; i < n-1; i++)
                    if (preorder[0] == inorder[i]){
                        make_tree(inorder, preorder, 0, i-1,t, 0);
                        make_tree(inorder, preorder, i+1, n-1,t, 0);
                        break;
                    }
                cout << "RECUSRIVE : ";t.recursive_inorder(t.root); cout << "\n";
                cout << "RECUSRIVE : ";t.recursive_preorder(t.root); cout << "\n";
                break;
            }
            case 8 : {
                int n; cout << "Enter the Node : "; cin >> n;
                tree.delete_node(n, tree.root);
                break;
            }
            case 9 : {
                Tree tree2;
                int n; cout << "Enter the number of Nodes (BT): "; cin >> n;
                cout << "NODE :: PARENT\n";
                for (int i = 1; i < n; i++){
                    int node, parent; cin >> node >> parent;
                    tree2.insert_node(node, parent, tree2.root);
                }
                if (tree.compare(tree2.root, tree.root))
                    cout  << "The trees are equal !\n";
                else
                    cout << "They are not equal ! \n";
                break;
            }
            case 10 : return 0;
        }
    }

}
