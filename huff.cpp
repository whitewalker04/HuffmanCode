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
    int index;

    public:
    Node(string key){
        this->key = key;
        this->next = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->index = 0;
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
    int getIndex(){
        return this->index;
    }
    void setIndex(int index){
        this->index = index;
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
        this->size = 0;
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
        if(this->size == 0){
            this->head = node;
            this->tail = node;
        }
        else{
            tail->setNext(node);
            tail = node;
        }
        this->size++;
        node->setIndex(this->size);
        return this->head;
    }
    int existAt(string key){
        Node *cur = this->head;
        while (cur != nullptr){
            if (cur->getKey() == key){
                return cur->getIndex();
            }
            cur = cur->getNext();
        }
        return 0;
    }
    Node *at(int index){
        Node *cur = this->head;
        while (cur != nullptr){
            if (cur->getIndex() == index){
                return cur;
            }
            cur = cur->getNext();
        }
        return nullptr;
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
        int count = 0;
        leftList->setHead(this->head);
        rightList->setHead(this->head);
        leftList->setTail(this->tail);
        rightList->setTail(this->tail);
        while (cur != nullptr){
            count+=1;
            if (cur->getKey() == key){
                prev->setNext(nullptr);
                leftList->setTail(prev);
                rightList->setHead(cur->getNext());
                leftList->setSize(count - 1);
                rightList->setSize(this->size - count);
                cur->setNext(nullptr);
                return;
            }
            prev = cur;
            cur = cur->getNext();        
        }
    }

    Node *getNextParent(NodeList *seperatedInorder){
        Node *cur = this->head;
        while (cur != nullptr){
            if (seperatedInorder->existAt(cur->getKey())){
                return cur;
            }
            cur = cur->getNext();
        }
        return nullptr;
    }
    void adjustIndex(Node *node){
        Node *cur = node;
        while(cur != nullptr){
            cur->setIndex(cur->getIndex() - 1);
            cur = cur->getNext();
        }
    }
    void removeLast(Node *prev){
        prev->setNext(nullptr);
        this->tail = prev;
        this->size--;
    }
    void removeFirst(Node *cur){
        this->head = cur->getNext();
        cur->setNext(nullptr);
        adjustIndex(this->head);
        this->size--;
    }
    void removeBetween(Node *prev, Node *cur){
        prev->setNext(cur->getNext());
        cur->setNext(nullptr);
        adjustIndex(prev->getNext());
        this->size--;
    }

    void remove(string key){
        Node *cur = this->head;
        Node *prev = this->head;
        while (cur != nullptr){
            if (cur->getKey() == key){
                if ( cur->getIndex() == 1 ){
                    removeFirst(cur);
                   // delete[] cur;
                    return;
                }
                else if( cur->getIndex() == this->size ){
                    removeLast(prev);
                    return;
                }
                else{
                    removeBetween(prev, cur);
                    return;
                }

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
    void buildTree(NodeList* inorderhead, NodeList* levelorderhead){
        Node *node = levelorderhead->getHead();
        this->root = node;
        buildTree(inorderhead, levelorderhead, true);
        //return this->root;
    }
    void buildTree(NodeList* inorderhead, NodeList* levelorderhead, bool isRoot){
        Node *parent = levelorderhead->getNextParent(inorderhead);
        //cout << "Parent: " << parent->getKey() << endl;
        NodeList *leftList = new NodeList();
        NodeList *rightList = new NodeList();

        // separate  inorder list based on root or parent we found from levelorder list
        inorderhead->seperateList(leftList, rightList, parent->getKey());

        // cout << "Left Seperated:" << endl;
        // leftList->print();
        // cout << "Right Seperated:" << endl;
        // rightList->print();
        // cout << leftList->getSize() << endl;
        // cout << rightList->getSize() << endl;
        if( leftList->getSize() == 1 ) {
            parent->setLeft( leftList->getHead());
            //levelorderhead->remove(leftList->getHead()->getKey());
        } else {
            parent->setLeft( levelorderhead->getNextParent(leftList));
            buildTree(leftList, levelorderhead, false);
        }

        if( rightList->getSize() == 1 ) {
            parent->setRight( rightList ->getHead() );
            //levelorderhead->remove(rightList->getHead()->getKey());
        } else {
            parent->setRight( levelorderhead->getNextParent(rightList) );
            buildTree(rightList, levelorderhead, false);
        }
    }
    void decode(Node *node, string encode, int startAt, string *decoded){
        string result = "";
        if (startAt > encode.length()){
            return;
        }
        if(node->getLeft() == nullptr && node->getRight() == nullptr){
            int key = stoi(node->getKey());
            char val = (char)key;
            result += val;
            *decoded += result;
            node = this->root;
            decode(node, encode, startAt, decoded);
        }
        else if(encode[startAt] == '0'){
            startAt++;
            decode(node->getLeft(), encode, startAt, decoded);
        }
        else if(encode[startAt] == '1'){
            startAt++;
            decode(node->getRight(), encode, startAt, decoded);
        }
        return;
    }
    string decode(string encode){
        string decoded = "";
        Node *cur = this->root;
        if (cur->getLeft() == nullptr && cur->getRight() == nullptr){
            return decoded;
        }
        if (encode != ""){
            decode(cur, encode, 0, &decoded);
        }
        return decoded;
    }
    void print( const std::string& prefix, Node *node, bool isLeft ) {
        if( node != nullptr ) {
            cout << prefix;
    
            cout << (isLeft ? "├──" : "└──" );
    
            // print the value of the node
            cout << "[" << node->getKey() << endl;
    
            // enter the next tree level - left and right branch
            print( prefix + ( isLeft ? "│   " : "    "), node->getLeft(), true );
            print( prefix + ( isLeft ? "│   " : "    "), node->getRight(), false );
        }
    }

    void print() {
        print( "", this->root, false );    
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
string parseFile(ifstream &fp){
    string value = "";
    string line;
    while (getline(fp, line)){
        value += line;    
    }
    return value;
    
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
    string encoded = "";

    
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
    encoded = parseFile(encode);
    //cout << encoded << endl;
    //inordered->print();
    //levelordered->print();
    //cout << "Size = " << levelordered->getSize() << endl;

    Tree huffTree;
    //cout << inordered->existAt("121") << endl;
    //cout << inordered->existAt("89") << endl;
    huffTree.buildTree(inordered, levelordered);
    //huffTree.print();
    cout << huffTree.decode(encoded);
    


    return 0;
}