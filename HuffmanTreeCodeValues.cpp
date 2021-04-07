#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define NUMBER_OF_COLS 2
#define FILE_DELIMETER ' '

using namespace std;

class Node {
    Node *next;
    string *values;
    Node *left, *right,*parent;
    //Tree *root;
    public:
    Node() {
        this->next = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->values = new string[3];
        for( int i =0; i< 3; i++ )
            this->values[i] = " ";
    }
    
    Node( string ch, string frequency, string code = " " ) {
        values = new string[3];
        this->values[0] = ch;
        this->values[1] = frequency;
        this->values[2] = code;
        this->next = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
    Node *getNext() {
        return this->next;
    }
    void setNext( Node *next ) {
        this->next = next;
    }
    string getCh() {
        return this->values[0];
    }
    void setCh( string ch ) {
        this->values[0] = ch;
    }
    string getFrequency() {
        return this->values[1];
    }
    void setFrequency( string frequency ) {
        this->values[1] = frequency;
    }
    string getCode() {
        return this->values[2];
    }
    void setCode( string code ) {
        this->values[2] = code;
    }
    Node *getLeft() {
        return this->left;
    }
    void setLeft( Node *left ) {
        this->left = left;
    }
    Node *getRight() {
        return this->right;
    }
    void setRight( Node *right ) {
        this->right = right;
    }
    Node*getParent() {
        return this->parent;
    }
    Node setParent( Node *parent ) {
        this->parent = parent;
    }
};

class NodeList {
    Node *head;
    Node *tail;
    int size;
    public:
    NodeList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = -1;
    }
    
    void insertFront( Node *newNode ) {
        newNode->setNext( this->head );
        this->head = newNode;
    }
    
    void insertEnd( Node *newNode ) {
        this->tail->setNext( newNode );
        this->tail = newNode;
    }
      
    void insertBetween( Node *newNode ) {
        Node *cur, *prev;
        cur = this->head;
        
        while( cur != nullptr ) {
            if( stoi( cur->getFrequency() ) > stoi( newNode->getFrequency() ) )
                break;
            prev = cur;
            cur = cur->getNext();
        }
        
        prev->setNext( newNode );
        newNode->setNext( cur );
    }
    
    void insert( Node *newNode ) {
        if( this ->head == nullptr ) {
            this->head = newNode;
            this->tail = this->head;
        }
        else if( stoi( newNode->getFrequency() ) <= stoi( this->head->getFrequency() ) ) {
            insertFront( newNode );
        }
        else if( stoi( newNode->getFrequency() ) >= stoi( this->tail->getFrequency() ) ) {
            insertEnd( newNode );
        }
        else {
            insertBetween( newNode );
        }
        this->size++;
    }
    
    void print() {
        Node *cur = head;
        while( cur != nullptr ) {
            cout<< "[ " << cur->getCh() << " " << cur->getFrequency() << " ] -> ";
            cur = cur->getNext();
        }
        cout<<endl;
    }

    Node *getHead() {
        return this->head;
    }

    void setHead( Node *head ) {
        this->head = head;
    }

    Node *getTail() {
        return this->tail;
    }

    void setTail( Node *tail ) {
        this->tail = tail;
    }
    void decreaseSize( int n ) {
        int size = this->size;
        setSize( size - n );
    }
    int getSize() {
        return this->size +1;
    }
    
    void setSize( int size ) {
        this->size = size;
    }
    
};

class HashMap {
    Node *root;
    public:
    HashMap() {
        this->root = root;
    }
    Node *getRoot() {
        return this->root;
    }
    void setRoot( Node *root) {
        this->root = root;
    }
    void updateCode( Node *node, bool isLeft, string code = " " ) {
        if( node != nullptr ) {
            
            code = isLeft ? "0" : "1" ;
            code =  node == this->root ? "" : node->getParent()->getCode() + code;
            
            node->setCode( code );
            
            //node->setCode( node->getParent()->getCode() + code );
            updateCode( node->getLeft(), true, node->getCode() );
            updateCode( node->getRight(), false, node->getCode() );
        }
    }
    
    Node *maxHeapify( Node *n1, Node *n2, int num ) {
        Node *node = new Node();
        node->setCh( "N" + to_string( num ) );
        if( n1 != nullptr || n2 != nullptr )
           node->setFrequency( to_string( stoi( n1->getFrequency() ) + stoi( n2->getFrequency() ) ) );
        node->setLeft( n1 );
        node->setRight( n2 );
        //updateCode( n1, true );
        //updateCode( n2, false );
        n1->setNext( nullptr );
        n2->setNext( nullptr );
        n1->setParent( node );
        n2->setParent( node );
        return node;
    }
    void print( const std::string& prefix, Node *node, bool isLeft ) {
        if( node != nullptr ) {
            cout << prefix;
    
            cout << (isLeft ? "├──" : "└──" );
    
            // print the value of the node
            cout << "[" << node->getCh() << " | " << node->getFrequency() << " | " << node->getCode() << "]" <<endl;
    
            // enter the next tree level - left and right branch
            print( prefix + ( isLeft ? "│   " : "    "), node->getLeft(), true );
            print( prefix + ( isLeft ? "│   " : "    "), node->getRight(), false );
        }
    }

    void print( Node *node ) {
        print( "", node, false );    
    }
};

// This class is designed to wrap the input together but not required anymore
class ParseCharacterAndFrequency {
    string ch;
    string frequency;
    public:
    ParseCharacterAndFrequency() {
        this->ch = "";
        this->frequency = "";
    }
    string getCh() {
        return this->ch;
    }
    void setCh( string ch ) {
        this->ch = ch;
    }
    string getFrequency() {
        return this->frequency;
    }
    void setFrequency( string frequency ) {
        this->frequency = frequency;
    }
};

void parseLine( string line, string *ch, string *frequency/*ParseCharacterAndFrequency &lineInput*/ ) {
    char word[10];
    int index = 0;
    int wordCount = 0;
    
    for( int i= 0; i< line.length(); i++ ) {
        if( line[i] != ' ' && line[i] !='\r' ) {
            word[index] = line[i];
            index++;
        }
        if( line[i] ==' ' || line[i] =='\r' || i == line.length()-1 ) {
            word[index] = '\0';
            
            //wordCount == 0 ? lineInput.setCh( word ) : lineInput.setFrequency( word );
            wordCount == 0 ? *ch = word : *frequency = word;
           
            index = 0;
            wordCount++;
            
        }
    }
}

int main( int argc, char **argv ) {
    if( argc !=2 ) {
        cout<< "Usage: ./a.out filename.txt" << endl;
        return 1;
    }
    
    string filename = argv[1];
    string ch, frequency, line;
    ifstream file(filename);
    NodeList *list;
    Node *node;
    if ( !file ) {
        cout << "Unable to open " <<filename <<endl;
        return 2;
    }
    
    list = new NodeList();
    
    //ParseCharacterAndFrequency *lineInput = new ParseCharacterAndFrequency();
    
    //read every line from file and create linked list  
    while( getline( file, line ) ) {
        
        //parseLine( line, *lineInput );
        parseLine( line, &ch, &frequency );
        
        //cout<< ch << " " << frequency << endl;
        
        node = new Node( ch, frequency );
        list->insert( node );
        
        //cout << lineInput->getCh() <<" " << lineInput->getFrequency() <<  endl;
    }
    
    list->print();
    
    cout << endl;
    
    int i = 0;

    Node *firstNode, *secondNode, *newHead, *hashNode, *cur;
    HashMap hashMapTree;
    
    cur = list->getHead();
    while( list->getSize() > 1 ) {
        firstNode = list->getHead();
        secondNode = firstNode->getNext();
        newHead = secondNode->getNext();
        
        hashNode = hashMapTree.maxHeapify( firstNode, secondNode, i );
        
        newHead != nullptr ? list->setHead( newHead ) : list->setHead( hashNode ) ;
        
        //newHead != nullptr ?  list->setHead( newHead ) : list->setHead( hashNode );
        
        hashMapTree.setRoot( list->getHead() );
        
        if( newHead != nullptr) {
            list->insert( hashNode );
            list->decreaseSize( 2 );
        }
        else {
             list->decreaseSize( 1 );
        }
        
        list->print();
        
        cout<< endl;
        
        i++;

        
        //cout<< "size" << list->getSize() << endl;
    }
    
    
    cout<< endl << endl;
    
    hashMapTree.updateCode( hashMapTree.getRoot(), false, hashMapTree.getRoot()->getCode() );
    //hashMapTree.updateCode( hashMapTree.getRoot()->getLeft(), true, "0" );
    //hashMapTree.updateCode( hashMapTree.getRoot()->getRight(), false, "1" );
        
    hashMapTree.print( hashMapTree.getRoot() );

   
    return 0;
}
