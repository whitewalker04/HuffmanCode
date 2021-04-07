#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Node{
    string key;
    Node *next;
    Node *left;
    Node *right;

    public:
    Node(string key){
        this->key = key;
        this->next = nullptr;
        this->left = nullptr;
        this->right = nullptr;
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
    Node *getRight(){
        return this->right;
    }
    void setRight(Node *right){
        this->right = right;
    }
    Node *getLeft(){
        return this->left;
    }
    void setLeft(Node *left){
        this->left  = left;
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
    void seperateList(NodeList *leftList, NodeList *rightList, string key){
        Node *cur = this->head;
        Node *prev = this->head;
        leftList->setHead(this->head);
        rightList->setHead(this->head);
        while (cur != nullptr){
            if (cur->getKey() == key){
                prev->setNext(nullptr);
                rightList->setHead(cur->getNext());
                cur->setNext(nullptr);
                return;
            }
            prev = cur;
            cur = cur->getNext();        
        }
    }

};
class Tree{
    Node *root;
    public: 
    Tree(){
        this->root = nullptr;
    }
    Node *getRoot(){
        return this->root;
    }
    void setRoot(Node *root){
        this->root = root;
    }
    Node *buildTree(NodeList* inorderhead, NodeList* levelorderhead){
        Node *lonode = levelorderhead->getHead();//level order node
        Node *ionode;//in order node
        Node *node = new Node(lonode->getKey());
        this->root = node;
        
        return nullptr;
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

    NodeList *leftlist = new NodeList();
    NodeList *rightList = new NodeList();

    inordered->seperateList(leftlist, rightList, "130");
    cout << "Left Seperated:" << endl;
    leftlist->print();
    cout << "Right Seperated:" << endl;
    rightList->print();


    
    return 0;
}