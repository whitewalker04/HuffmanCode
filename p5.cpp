#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Node{
    string key;
    Node *next;

    public:
    Node(string key){
        this->key = key;
        this->next = nullptr;
    }
    string getKey(){
        return this->key;
    }
    Node *getNext(){
        return this->next;
    }
    void setKey(string key){
        this->key = key;
    }
    void setNext(Node *next){
        this->next = next;
    }
};

class NodeList{
    Node *head;
    Node *tail;
    int size;

    public:
    NodeList(){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = -1;
    }
    Node *getHead(){
        return this->head;
    }
    void setHead(Node *head){
        this->head = head;
    }
    Node *getTail(){
        return this->tail;
    }
    void setTail(Node *tail){
        this->tail = tail;
    }
    int getSize(){
        return this->size;
    }
    void setSize(int size){
        this->size = size;
    }
    Node* insertAfter(Node *node){
        if(this->size == -1){
            this->head = node;
            this->tail = node;
        }
        else{
            tail->setNext(node);
            tail = node;
        }
        this->size++;
        return this->head;
    }
    void print(){
        Node *cur = head;
        while(cur != nullptr){
            cout << cur->getKey() << " -> ";
            cur = cur->getNext();
        }
        cout << endl;
    }

};

void parseFile(ifstream &fp, NodeList *head){
    string line;
    Node *node;
    int index = 0;
    while(!fp.eof()){
        getline( fp, line);
        char word[100];
    
        for(int i= 0; i< line.length(); i++){
            if( line[i] != ' ' && line[i] !='\r'){
                word[index] = line[i];
                index++;
            }
            if( line[i] ==' ' || line[i] =='\r' || i == line.length()-1 ){
                word[index] = '\0';
                node = new Node(word);
                head->insertAfter(node);
                index=0;
            }
        }
    }
    
}
int countNumofWhitespace( string input ) {
    int count = 0;
    for ( int i = 0; i < input.length(); i++ ){
        if ( input[i] == ' ' ){
            count++;
        }
    }
    return count;
}

int numOfCols( ifstream &fp ){
    int cols = 0;
    string inputFirstLine;
    getline( fp, inputFirstLine );
    int whitespace = countNumofWhitespace( inputFirstLine );
    cols = whitespace + 1;
    return cols;
}


int main(int argc, char **argv){
    if (argc != 4){
        cout << "Invalid number of arguments" << endl;
        return 0;
    }
    string fileInorder = argv[1];
    string fileLevelorder = argv[2];
    string fileEncoded = argv[3];
    NodeList *inordered = new NodeList();
    NodeList *levelordered = new NodeList();
    NodeList *encoded;

    
    ifstream inorder(fileInorder);
    ifstream levelorder(fileLevelorder);
    ifstream encode(fileEncoded);
    if (!inorder) {
        cout << "Unable to open " << fileInorder << endl;
        return 2;
    }
    if (!levelorder) {
        cout << "Unable to open " << fileLevelorder << endl;
        return 2;
    }
    if (!encode) {
        cout << "Unable to open " << fileEncoded << endl;
        return 2;
    }
    parseFile(inorder,inordered);
    parseFile(levelorder, levelordered);
    //parseFile(encode, encoded);
    inordered->print();
    levelordered->print();


    
    return 0;
}