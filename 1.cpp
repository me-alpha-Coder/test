#include <bits/stdc++.h>
#define MAX 10
using namespace std;

class Node {
    public :
        string name;
        long int telephone_no;
        int next;

        Node(){
            name = "xyz";
            telephone_no = 123456789;
            next = -1;
        }
        Node (string data1, long int data2){
            this->name = data1;
            this->telephone_no = data2;
            this->next = -1;
        }
};

class HashingLinearProbing{
    Node **hash_table;

    public :
        HashingLinearProbing(){
            hash_table = new Node*[MAX];
            for (int i = 0; i < MAX; i++)
                hash_table[i] = NULL;
        }
        ~HashingLinearProbing(){
            for (int i = 0; i < MAX; i++)
                delete hash_table[i];
            delete[] hash_table;
        }

        void insert_entry(string data1, long int data2);
        void display();
        void delete_entry(string data1, long int data2);
        void search_entry(long int number);
};

void HashingLinearProbing :: insert_entry(string data1, long int data2){
    int index = data2 % MAX;
    Node *temp = new Node(data1, data2);
    int offset = 1;
    while (hash_table[index] != NULL and offset <= MAX){
        index ++;
        index %= MAX;
        offset++;
    }
    if (hash_table[index] == NULL)
        hash_table[index] = temp;

    return;
}
void HashingLinearProbing :: display(){
    cout << "----------------------------------------------------------\n";
    cout << "                    DIRECTORY\n";
    cout << "Linear Probing\n";
    for (int i = 0; i < MAX; i++){
        cout << i << "-> " ;
        if (hash_table[i] != NULL)
            cout << hash_table[i]->name << ":" << hash_table[i]->telephone_no ;
        cout << "\n";
    }
    return;
}
void HashingLinearProbing :: delete_entry(string data1, long int data2){
    int index = data2 % MAX;
    int offset = 1;
    while ((hash_table[index] == NULL or !(hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2)) and offset <= MAX){
        index ++;
        index %= MAX;
        offset++;
    }
    if (hash_table[index] != NULL and hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2){
        Node *temp = hash_table[index];
        hash_table[index] = NULL;
        delete temp;
        cout << "Data deleted!\n";
    }
    else
        cout << "Data not Found!\n";
}
void HashingLinearProbing :: search_entry(long int number){
    int index = number % MAX;
    int offset = 1, count = 0;
    while ((hash_table[index] == NULL or hash_table[index]->telephone_no != number) and offset <= MAX){
        index ++;
        index %= MAX;
        offset++;
        count ++;
    }
    if (hash_table[index] != NULL and hash_table[index]->telephone_no == number){
        cout << "Data Found!\n";
        cout << "   Name : " << hash_table[index]->name << "\n";
        cout << "   Telephone Number : " << hash_table[index]->telephone_no << "\n";
        cout << "   Comparisons : " << count << "\n";
    }
    else
        cout << "Data not Found!\n";
}

class HashingLinearProbingChainingWithoutReplacement : public HashingLinearProbing{
    Node **hash_table, *prev;

    public :
        HashingLinearProbingChainingWithoutReplacement(){
            hash_table = new Node*[MAX];
            for (int i = 0; i < MAX; i++)
                hash_table[i] = NULL;
        }
        ~HashingLinearProbingChainingWithoutReplacement(){
            for (int i = 0; i < MAX; i++)
                delete hash_table[i];
            delete[] hash_table;
        }
        void insert_entry(string data1, long int data2);
        void display();
        void delete_entry(string data1, long int data2);
        void search_entry(long int number);
};

void HashingLinearProbingChainingWithoutReplacement :: insert_entry(string data1, long int data2){
    int index = data2 % MAX;
    Node *temp = new Node(data1, data2);
    int p = -1;
    int offset = 1;
    while (hash_table[index] != NULL and offset <= MAX){
        p = index;
        index ++;
        index %= MAX;
        offset++;
    }
    if (hash_table[index] == NULL)
        hash_table[index] = temp;
    if (p != -1)
        hash_table[p]->next = index;
    return;
}
void HashingLinearProbingChainingWithoutReplacement :: display(){
    cout << "----------------------------------------------------------\n";
    cout << "                    DIRECTORY\n";
    cout << "Linear Probing With Chaining Wihout Replacement(Drawbacks)\n";
    for (int i = 0; i < MAX; i++){
        cout << i << "-> " ;
        if (hash_table[i] != NULL)
            cout << hash_table[i]->name << ":" << hash_table[i]->telephone_no << " " << hash_table[i]->next ;
        cout << "\n";
    }
    return;
}
void HashingLinearProbingChainingWithoutReplacement :: delete_entry(string data1, long int data2){
    int index = data2 % MAX;
    int offset = 1;
    while ((hash_table[index] == NULL or !(hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2)) and offset <= MAX){
        index ++;
        index %= MAX;
        offset++;
    }
    if (hash_table[index] != NULL and hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2){
        Node *temp = hash_table[index];
        hash_table[index] = NULL;
        delete temp;
        cout << "Data deleted!\n";
    }
    else
        cout << "Data not Found!\n";
}
void HashingLinearProbingChainingWithoutReplacement :: search_entry(long int number){
    int index = number % MAX;
    int offset = 1, count = 0;
    while ((hash_table[index] == NULL or hash_table[index]->telephone_no != number) and offset <= MAX){
        index ++;
        index %= MAX;
        offset++;
        count ++;
    }
    if (hash_table[index] != NULL and hash_table[index]->telephone_no == number){
        cout << "Data Found!\n";
        cout << "   Name : " << hash_table[index]->name << "\n";
        cout << "   Telephone Number : " << hash_table[index]->telephone_no << "\n";
        cout << "   Comparisons : " << count << "\n";
    }
    else
        cout << "Data not Found!\n";
}

class HashingLinearProbingChainingWithReplacement : public HashingLinearProbing{
    Node **hash_table, *prev;

    public :
        HashingLinearProbingChainingWithReplacement(){
            hash_table = new Node*[MAX];
            for (int i = 0; i < MAX; i++)
                hash_table[i] = NULL;
        }
        ~HashingLinearProbingChainingWithReplacement(){
            for (int i = 0; i < MAX; i++)
                delete hash_table[i];
            delete[] hash_table;
        }
        void insert_entry(string data1, long int data2);
        void display();
        void delete_entry(string data1, long int data2);
        void search_entry(long int number);
};
void HashingLinearProbingChainingWithReplacement :: insert_entry(string data1, long int data2){
    int index = data2 % MAX;
    Node *temp = new Node(data1, data2);
    prev = NULL;
    int p = -1;
    int offset = 1;

    if (hash_table[index] == NULL)
        {hash_table[index] = temp;return;}

    if (hash_table[index] != NULL and hash_table[index]->telephone_no % MAX != index){
        string d1 = hash_table[index]->name;
        long int d2 = hash_table[index]->telephone_no;
        int d3 = hash_table[index]->next;

        hash_table[index] = temp;

        int new_index = d2 % MAX;
        while (hash_table[hash_table[new_index]->next]->telephone_no % MAX == d2 % MAX)
            new_index = hash_table[new_index]->next;
        hash_table[new_index]->next = d3;
        insert_entry(d1, d2);
        return;
    }


    while (index != -1){
        p = index;
        index = hash_table[index]->next;
    }
    index = p;
    while (hash_table[index] != NULL and offset < MAX){
        index++;
        index %= MAX;
        offset++;
    }
    if (hash_table[index] == NULL)
        hash_table[index] = temp;
    if (p != -1)
        hash_table[p]->next = index;
    return;
}
void HashingLinearProbingChainingWithReplacement :: display(){
    cout << "----------------------------------------------------------\n";
    cout << "                    DIRECTORY\n";
    cout << "Linear Probing With Chaining Wih Replacement\n";
    for (int i = 0; i < MAX; i++){
        cout << i << "-> " ;
        if (hash_table[i] != NULL)
            cout << hash_table[i]->name << ":" << hash_table[i]->telephone_no << " " << hash_table[i]->next ;
        cout << "\n";
    }
    return;
}
void HashingLinearProbingChainingWithReplacement :: delete_entry(string data1, long int data2){
    int index = data2 % MAX;
    int offset = 1;

    if (hash_table[index] != NULL and hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2){
        int temp = index;
        int p = -1;
        while (hash_table[temp]->next != -1)
            p = temp, temp = hash_table[temp]->next;
        if (temp == index){
            Node *t = hash_table[index];
            hash_table[index] = NULL;
            delete t;
            cout << "Data deleted!\n";
            return;
        }
        else{
            int n = hash_table[index]->next;
            Node *t = hash_table[index];
            hash_table[index] = hash_table[temp];
            hash_table[index]->next = n;
            hash_table[p]->next = -1;
            hash_table[temp] = NULL;
            delete t;
            cout << "Data deleted!\n";
            return;
        }


    }

    prev = NULL;
    while ((hash_table[index] != NULL and !(hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2)) and offset <= MAX){
        prev = hash_table[index];
        index = hash_table[index]->next;
        offset++;
    }
    if (hash_table[index] != NULL and hash_table[index]->name == data1 and hash_table[index]->telephone_no == data2){
        Node *temp = hash_table[index];
        if (prev != NULL)
            prev->next = hash_table[index]->next;
        hash_table[index] = NULL;
        delete temp;
        cout << "Data deleted!\n";
    }
    else
        cout << "Data not Found!\n";
}
void HashingLinearProbingChainingWithReplacement :: search_entry(long int number){
    int index = number % MAX;
    int offset = 1, count = 0;
    while ((hash_table[index] != NULL and hash_table[index]->telephone_no != number) and offset <= MAX){
        index = hash_table[index]->next;
        offset++;
        count++;
    }
    if (hash_table[index] != NULL and hash_table[index]->telephone_no == number){
        cout << "Data Found!\n";
        cout << "   Name : " << hash_table[index]->name << "\n";
        cout << "   Telephone Number : " << hash_table[index]->telephone_no << "\n";
        cout << "   Comparisons : " << count << "\n";
    }
    else
        cout << "Data not Found!\n";
}

int main(){

    HashingLinearProbing record1;
    HashingLinearProbingChainingWithoutReplacement record2;
    HashingLinearProbingChainingWithReplacement record3;

    while (true){
        int choice;
        cout << "----------------------------------------------------------\n";
        cout << "----------------------------------------------------------\n";
        cout << "                          MENU \n";
        cout << "\n     1. Add record\n     2. Delete record\n" <<
                "     3. Display record\n     4. Search record\n     5. Exit\n";
        cout << "Enter your choice : "; cin >> choice;
        cout << "Order of ouput : \n    1. Linear Probing\n    2. Linear Probing With Chaining Wihout Replacement\n    3. Linear Probing With Chaining With Replacement\n";
        switch(choice){
            case 1 : {
                string name; long int telephone_no;
                cout << "     Enter name : "; cin >> name;
                cout << "     Enter telephone number : "; cin >> telephone_no;
                record1.insert_entry(name, telephone_no);
                record2.insert_entry(name, telephone_no);
                record3.insert_entry(name, telephone_no);
                break;
            }
            case 2 : {
                string name; long int telephone_no;
                cout << "     Enter name : "; cin >> name;
                cout << "     Enter telephone number : "; cin >> telephone_no;
                record1.delete_entry(name, telephone_no);
                record2.delete_entry(name, telephone_no);
                record3.delete_entry(name, telephone_no);
                break;
            }
            case 3 : {
                record1.display();
                record2.display();
                record3.display();
                break;
            }
            case 4 : {
                long int telephone_no;
                cout << "     Enter telephone number : "; cin >> telephone_no;
                record1.search_entry(telephone_no);
                record2.search_entry(telephone_no);
                record3.search_entry(telephone_no);
                break;
            }
            case 5 : {
                return 0;
            }
        }

    }
}
