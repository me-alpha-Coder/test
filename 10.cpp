#include "bits/stdc++.h"
using namespace std;

class Node {
    public : 
        string key;
        string value;
        Node *left, *right, *parent;

        Node(){
            key = "xyz";
            value = "abc";
            left = NULL, right = NULL;
        }
        Node ( string data1, string data2, Node *node = NULL){
            this->key = data1;
            this->value = data2;
            this->left = NULL;
            this->right = NULL;
            this->parent = node;
        }
};



class Dictionary{
    
    public :
        Node *root, *temp;
        Dictionary(){root = NULL;}
        Dictionary(string d1, string d2){root = new Node(d1, d2);}

        void insert_node(string d1, string d2, Node *node, Node *parent);
        void display_ascending(Node *node);
        void display_descending(Node *node);
        void delete_node(string key, Node *node, Node *parent);
        void find_node(string d1, Node *node);
        void update_node(string d1, string d2, Node *node);
        int height(Node *N){
            if (N == NULL)
                return 0;
            return max(height(N->left), height(N->right))+1;
        }
        int getBalance(Node *N){
            if (N == NULL)
                return 0;
            return height(N->left) - height(N->right);
        }

        Node* rotateLeft(Node *z){

            temp = z->parent;
            Node *y = z->right;
            Node *t2 = y->left;

            if (temp != NULL and temp->left == z)
                temp->left = y;
            else if (temp != NULL and temp->right == z)
                temp->right = y;
            else if (temp == NULL)
                root = y;
            y->parent = temp;

            y->left = z;
            z->parent = y;

            z->right = t2;
            if (t2 != NULL) t2->parent = z;

            return y;
        }
        Node* rotateRight(Node *z){

            temp = z->parent;
            Node *y = z->left;
            Node *t3 = y->right;

            if (temp != NULL and temp->left == z)
                temp->left = y;
            else if (temp != NULL and temp->right == z)
                temp->right = y;
            else if (temp == NULL)
                root = y;
            y->parent = temp;

            y->right = z;
            z->parent = y;

            z->left = t3;
            if (t3 != NULL) t3->parent = z;

            return y;
        }
        Node* rotateRightLeft(Node *z){
            z->right = rotateRight(z->right);
            return z = rotateLeft(z);
        }
        Node* rotateLeftRight(Node *z){
            z->left = rotateLeft(z->left);
            return z = rotateRight(z);
        }
};

void Dictionary :: insert_node(string d1, string d2, Node *node, Node *parent){
    if (node == NULL){
        if (parent != NULL){
            if (parent->key > d1)
                parent->left = new Node( d1, d2, parent);
            else
                parent->right = new Node( d1, d2, parent);
        }
        else root = new Node( d1, d2, parent);
        return;
    }
    if (d1 < node->key)
        insert_node(d1, d2, node->left, node);
    else if (d1 > node->key)
        insert_node(d1, d2, node->right, node);

    int balance = getBalance(node);
    if (balance > 1 && d1 < node->left->key)
        {node = rotateRight(node);return;}
 
    if (balance < -1 && d1 > node->right->key)
        {node = rotateLeft(node);return;}
 

    if (balance > 1 && d1 > node->left->key)
        {node = rotateLeftRight(node);return;}
 
    if (balance < -1 && d1 < node->right->key)
        {node = rotateRightLeft(node);return;}
}

void Dictionary :: display_ascending(Node *node){
    if (node == NULL)
        return;

    display_ascending(node->left);
    cout << node->key << " ";
    display_ascending(node->right);
}

void Dictionary :: display_descending(Node *node){
    if (node == NULL)
        return;
    display_descending(node->right);
    cout << node->key << " ";
    display_descending(node->left);
}

void Dictionary :: delete_node(string key, Node *node, Node *parent){
    if (node == NULL)
        return;
    if (key == node->key){
        temp = node;
        if (parent != NULL and parent-> left == node)
            parent->left = NULL;
        else if (parent != NULL and parent-> right == node)
            parent->right = NULL;
        else if (parent == NULL)
            root = NULL;
        stack<Node *> s;
        s.push(node->left);
        s.push(node->right);
        while (!s.empty()){
            temp = s.top();
            s.pop();
            if (temp != NULL){
                insert_node(temp->key, temp->value, root, NULL);
                if (temp->left != NULL)s.push(temp->left);
                if (temp->right != NULL)s.push(temp->right);
            }
            delete temp;
        }
        delete node;
    }
    else if (key < node->key)
        delete_node(key, node->left, node);
    else if (key > node->key)
        delete_node(key, node->right, node);

    int balance = getBalance(node);
    if (balance > 1 and getBalance(node->left) >= 0)
        {node = rotateRight(node);return;}
 
    if (balance > 1 and getBalance(root->left) < 0)
        {node = rotateLeftRight(node);return;}
 
    if (balance < -1 and getBalance(root->right) <= 0)
        {node = rotateRight(node);return;}
 
    if (balance < -1 and getBalance(root->right) > 0)
        {node = rotateRightLeft(node);return;}
}

void Dictionary :: find_node(string key, Node *node){
    if (node == NULL)
        return;
    if (key == node->key)
        cout << "NODE FOUND !\n" << "   " << node->key << " : " << node->value << "\n";
    else if (key < node->key)
        find_node(key, node->left);
    else if (key > node->key)
        find_node(key, node->right);
}
void Dictionary :: update_node(string key, string update_value, Node *node){
    if (node == NULL)
        return;
    if (key == node->key){
        node->value = update_value;
        cout << "NODE UPDATED !\n" << "   " << node->key << " : " << node->value << "\n";
    }
    else if (key < node->key)
        update_node(key, update_value, node->left);
    else if (key > node->key)
        update_node(key, update_value, node->right);
}

int main(){
    int choice;
    Dictionary dictionary;
    do{
        cout<<"\n==========================================\n"
              "\n----------------DICTIONARY----------------\n"
        "\nEnter your choice:\n"
        "   1.Add new keyword.\n"
        "   2.Display the contents of the Dictionary.\n"
        "   3.Delete a keyword.\n"
        "   4.Find a keyword.\n"
        "   5.Update the meaning of a keyword.\n"
        "   6.Exit.\n"
        "==========================================\n";
        cin>>choice;
        switch(choice){
            case 1:{
                string key, value;
                cout << "Enter the key    : "; cin >> key;
                cout << "Enter the value  : "; cin >> value;
                dictionary.insert_node(key, value, dictionary.root, NULL);
            }
                break;
            case 2:{
                int c; cout << "1 . Ascending\n2 . Descending\nEnter your choice : ";
                cin >> c;
                if (c == 2)
                    dictionary.display_descending(dictionary.root);
                else
                    dictionary.display_ascending(dictionary.root);
            }
                break;
            case 3:{
                string key;
                cout << "Enter the key    : "; cin >> key;
                dictionary.delete_node(key, dictionary.root, NULL);
            }
                break;
            case 4:{
                string key;
                cout << "Enter the key    : "; cin >> key;
                dictionary.find_node(key, dictionary.root);
            }
                break;
            case 5:{
                string key, value;
                cout << "Enter the key    : "; cin >> key;
                cout << "Enter new value  : "; cin >> value;
                dictionary.update_node(key, value, dictionary.root);
            }
                break;
            case 6:
                break;
            default:cout<<"\nPlease enter a valid option!\n";
                break;
        }
    }while(choice!=6);

    return 0;
}