#include "bits/stdc++.h"
#define MAX 10

using namespace std;

string code ;

class Node {
    public :
        int data;
        char chr;
        Node *lchild, *rchild, *parent;
        Node(){data = 0, lchild = NULL, rchild = NULL; parent = NULL;}
        Node(int d, char c){data = d, chr = c, lchild = NULL, rchild = NULL; parent = NULL;}
};

class Compare {
public:
    bool operator()(Node* a, Node* b){
       if (a->data > b->data) return true;
       return false;
    }
};

Node * make_parent(Node * a, Node * b){
    Node *c = new Node();
    c->data = a->data + b->data;
    a->parent = c;
    b->parent = c;
    c->lchild = a;
    c->rchild = b;
    return c;
}

void dfs(Node *node){
    if (node == NULL)
        return;
    cout << node->data << " " << node->chr << "\n";
    if (node->lchild != NULL)
        dfs(node->lchild);
    if (node->rchild != NULL)
        dfs(node->rchild);
}

bool code_for_char(char c, Node *node){
    if (node->chr == c)
        return true;
    if (node->lchild == NULL and node ->rchild == NULL)
        return false;
    bool flag = code_for_char(c, node->lchild);
    if (flag == 1)
        {code = '0'+ code;return true;}
    flag = code_for_char(c, node->rchild);
    if (flag == 1)
        {code = '1'+ code;;return true;}

    return false;
}

int main(){    
    
    string s;
    cout << "Enter a character sequence  : "; cin >> s;
    map <char, int> mp;
    for (int i = 0; i < s.size(); i++)
        mp[s[i]]++;
    cout << "Frequencies : \n";
    for (auto x : mp){
        cout << "   " << x.first << " " << x.second << "\n";
    }
    priority_queue <Node*, vector<Node*>, Compare> PQ;
    for (auto x : mp){
        Node *temp = new Node(x.second, x.first);
        PQ.push(temp);
    }

    Node *a, *b, *root = NULL, *c;
    while (!PQ.empty()){
        a = PQ.top();
        PQ.pop();
        if (PQ.empty())
            {root = a;break;}
        b = PQ.top();
        PQ.pop();
        c = make_parent(a,b);
        PQ.push(c);
    }

    // dfs(root);
    cout << "Codes : \n";
    map  <string, char> store;
    for (auto x : mp){
        cout << "   " << x.first << " : ";
        code = "";
        code_for_char(x.first , root);
        cout  << code << " \n";
        store[code] = x.first;
    }

    cout << "Directory completed SUCCESSFULLY!\n";
    string decode, final = "", ns = "";
    cout << "Enter string to decode : "; cin >> decode;
    cout << store["0000"] << " ";
    for (int i = 0; i < decode.size(); i++){
        ns += decode[i];
        if (store[ns] < 'a' || store[ns] > 'z')
            continue;

            char c = store[ns];
            final += c;
            ns = "";
    }
    cout << "The string is : " << final << "\n";

    return 0;
}
