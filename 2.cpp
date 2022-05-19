#include <bits/stdc++.h>
#define MAX 10
using namespace std;

class Node {
    public : 
        string key;
        string value;
        Node *next;

        Node(){
            key = "xyz";
            value = "abc";
            next = NULL;
        }
        Node (string data1, string data2){
            this->key = data1;
            this->value = data2;
            this->next = NULL;
        }
};

class Dictionary{

    Node **hash_table, *start, *prev;
    public :
        Dictionary(){
            hash_table = new Node*[MAX];
            for (int i = 0; i < MAX; i++)
                hash_table[i] = NULL;
        }
        ~Dictionary(){
            for (int i = 0; i < MAX; i++){
                Node *temp = hash_table[i];
                while (temp != NULL){
                    Node *to_be_deleted = temp;
                    temp = temp->next;
                    delete to_be_deleted;
                }
                delete temp;
            }
            delete[] hash_table;
        }
        int find_hash(string key);
        void Insert(string data1, string data2);
        void Display();
        void Delete(string data1);
        void Find(string data1);
};

int Dictionary :: find_hash(string key){
    long int hash = 0;
    hash = (key[0]-'A'+1)*(key[1]-'A'+1)*(key[2]-'A'+1);
    return hash%MAX;
}

void Dictionary :: Insert(string data1, string data2){
    int index = find_hash(data1);
    Node *temp = new Node(data1, data2);
    if (hash_table[index] == NULL)
        hash_table[index] = new Node(data1, data2);
    else {
        start = hash_table[index];
        while (start->next != NULL)
            start = start->next;
        start->next = temp;
    }
    return;
}

void Dictionary :: Display(){
    cout << "----------------------------------------------------------\n";
    cout << "                    DIRECTORY\n";
    for (int i = 0; i < MAX; i++){
        start = hash_table[i];
        cout << i << ": \n";
        while (start != NULL){
            cout << "   " << start->key << ": " << start->value << " \n";
            start = start->next;
        }
    }
    return;
}

void Dictionary :: Delete(string data1){
    int index = find_hash(data1);
    if (hash_table[index] == NULL)
        cout << "Data not Found!\n";
    else {
        cout << "Data deleted!\n";
        while (hash_table[index]->key == data1){
            Node *temp = hash_table[index];
            hash_table[index] = hash_table[index]->next;
            delete temp;
            
            if (hash_table[index] == NULL)
                return;
        }
        prev = hash_table[index];
        start = hash_table[index]->next;
        while (start != NULL){
            if (start->key == data1){
                Node *temp = start;
                start = start->next;
                prev->next = start;
                delete temp;
                continue;
            }
            prev = start;
            start = start->next;
        }
       
    }
    return;
}

void Dictionary :: Find(string data1){
    int index = find_hash(data1);
    start = hash_table[index];
    if (start == NULL)
        cout << "Data not Found!\n";
    else {
        cout << "Data Found!\n";
        while (start != NULL){
            if (start->key == data1)
                cout << "   value : " << start->value << "\n";
            start = start->next;
        }
    }
    return;
}

int main(){

    Dictionary record;

    while (true){
        int choice;
        cout << "----------------------------------------------------------\n";
        cout << "----------------------------------------------------------\n";
        cout << "                          MENU \n";
        cout << "\n     1. Add record\n     2. Delete record\n" << 
                "     3. Display record\n     4. Search record\n     5. Exit\n";
        cout << "Enter your choice : "; cin >> choice;

        switch(choice){
            case 1 : {
                string key; string value;
                cout << "     Enter key : "; cin >> key;
                cout << "     Enter value : "; cin >> value;
                record.Insert(key, value);
                break;
            }
            case 2 : {
                string key;
                cout << "     Enter key : "; cin >> key;
                record.Delete(key);
                break;
            }
            case 3 : {
                record.Display();
                break;
            }
            case 4 : {
                string key;
                cout << "     Enter key : "; cin >> key;
                record.Find(key);
                break;
            }
            case 5 : {
                return 0;
            }
        }

    }

}
