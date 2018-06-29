/*************************
Author:Alperen Kantarci  *
Number: 150140140        *
**************************/

/* In order to compile the program write g++ main.cpp classes.h */


#include <iostream>

using namespace std;

class Node{
protected:
    int data;
    Node* next;
    Node* prev;
public:
    Node(int=0);
    void setNextNode(Node*);        //Setting next Node
    void setPrevNode(Node*);        //Setting prev Node
    void setData(int);              //Setting the data of Node
    Node& getNextNode() const;
    const int getNodeData()const;
    Node& getPrevNode() const;
};

Node::Node(int input){
    data=input;
    next=NULL;
    prev=NULL;
}

void Node::setNextNode(Node* input){
    next = input;
}

void Node::setPrevNode( Node* input){
    prev= input;
}

void Node::setData(int input){
    data = input;
}

Node& Node::getNextNode()const{
    return *next;
}

const int Node::getNodeData()const{
    return data;
}

Node& Node::getPrevNode()const{
    return *prev;
}

class ARTraverser {
    friend class AdderRemover;
    friend class FAFR;
    friend class FALR;
    friend class LAFR;
    friend class LALR;
protected:
    Node* current;
public:
    virtual bool hasNode() = 0;
    virtual Node* next() = 0;
};

/*********************************************************************************************************
    It traverse through a container from the beginning
    element to the end element. FAFR and FALR classes are going to use this strategy as its traverser.
*********************************************************************************************************/
class ARTF : public ARTraverser {
public:
    bool hasNode();
    Node* next();
};

bool ARTF::hasNode(){
   return (current!=NULL) ?  true :  false;
}

Node* ARTF::next(){                 //ARTF will traverse with next node
    Node* tmp=current;
    current = &current->getNextNode();
    return tmp;
}

/*********************************************************************************************************
    It traverse through a container from the end element to
    the beginning element. LAFR and LALR classes are going to use this strategy as its traverser.
*********************************************************************************************************/

class ARTL : public ARTraverser {
public:
    bool hasNode();
    Node* next();
};


bool ARTL::hasNode(){
    return (current!=NULL) ?  true :  false;
}

Node* ARTL::next(){     //ARTL will traverse with prev node because it's from end to beginning
    Node* tmp=current;
    current = &current->getPrevNode();
    return tmp;
}

class AdderRemover {
protected:
    Node*   head;
    Node*   tail;
    string  name;
    int     nodeCount;
    ARTraverser* traverser;
public:
    virtual void  add(const int) = 0;
    virtual void remove() = 0;
    virtual void setTraverser() = 0;
    void display() const;
    void removeAll();
    void traverse()const;
};

void AdderRemover::display()const{
    if(nodeCount==0){   //If there are no nodes in list
        cout << name << " | NodeCount:" << nodeCount << endl << "------"  << endl;
        cout << "There is no element to print" << endl << endl ;
        return;
    }
    Node* tmp=head;
    cout << name << " | NodeCount:" << nodeCount << endl << "------"  << endl;
    for(int i=0 ; i < nodeCount ; i++){
        cout << tmp->getNodeData() << endl;
        tmp = &tmp->getNextNode();
    }
    cout << endl;
}

void AdderRemover::removeAll(){
    if(head==NULL){
        cout << "THERE IS NO NODE FOR REMOVE!"<<endl;
        return;
    }
    else{
        Node* removingTmp=head;
        Node* tmp;
        for(int i=0 ; i < nodeCount ; i++){
             tmp=&removingTmp->getNextNode();
             delete removingTmp;
             removingTmp=tmp;
        }
        head=NULL;
        tail=NULL;
        nodeCount=0;
    }
}

void AdderRemover::traverse()const{
    if(nodeCount==0){
        cout << name << " | NodeCount:" << nodeCount << endl << "------"  << endl;
        cout << "There is no element to print" << endl;
        return;
    }
    cout << name << " | NodeCount:" << nodeCount << endl << "------"  << endl;
    while(traverser->hasNode()){
        cout <<  traverser->current->getNodeData() << endl;
        traverser->next();
    }
    cout << endl ;
}


class FAFR : public AdderRemover {
public:
    FAFR();
    void add(const int);
    void remove();
    void setTraverser();
};

FAFR::FAFR(){
    head=NULL;
    tail=NULL;
    traverser=NULL;
    nodeCount=0;
    name="FAFR";
}

void FAFR::add(const int input){
    Node* tmp = new Node(input);
    if(head==NULL){
        head=tmp;
        tail=tmp;
        nodeCount++;
    }else{
        tmp->setNextNode(head);
        head->setPrevNode(tmp);
        head=tmp;
        nodeCount++;
    }
}

void FAFR::remove(){
    if(head==NULL){
        cout << "THERE IS NO NODE FOR REMOVE!"<<endl;
        return;
    }
    else{
        Node* tmp;
        Node* removingTmp;
        tmp=&head->getNextNode();
        tmp->setPrevNode(NULL);
        removingTmp=head;
        head = tmp;
        delete removingTmp;
        nodeCount--;
    }
}

void FAFR::setTraverser(){
    traverser = new ARTF();
    traverser->current=head;
}

class FALR : public AdderRemover {

public:
    FALR();
    void add(const int);
    void remove();
    void setTraverser();
};

FALR::FALR(){
    head=NULL;
    tail=NULL;
    traverser=NULL;
    nodeCount=0;
    name="FALR";
}

void FALR::add(const int input){
    Node* tmp = new Node(input);
    if(head==NULL){
        head=tmp;
        tail=tmp;
        nodeCount++;
    }else{
        tmp->setNextNode(head);
        head->setPrevNode(tmp);
        head=tmp;
        nodeCount++;
    }
}

void FALR::remove(){
    if(head==NULL){
        cout << "THERE IS NO NODE FOR REMOVE!"<<endl;
        return;
    }
    else{
        Node* tmp;
        Node* removingTmp;
        tmp=&tail->getPrevNode();
        tmp->setNextNode(NULL);
        removingTmp=tail;
        tail->setPrevNode(NULL);
        tail=tmp;
        delete removingTmp;
        nodeCount--;
    }
}

void FALR::setTraverser(){
    traverser = new ARTF();
    traverser->current=head;
}

class LAFR : public AdderRemover {
public:
    LAFR();
    void add(const int);
    void remove();
    void setTraverser();
};

LAFR::LAFR(){
    head=NULL;
    tail=NULL;
    traverser=NULL;
    nodeCount=0;
    name="LAFR";
}

void LAFR::add(const int input){
    Node* tmp = new Node(input);
    if(head==NULL){
        head=tmp;
        tail=tmp;
        nodeCount++;
    }else{
        tmp->setPrevNode(tail);
        tail->setNextNode(tmp);
        tail=tmp;
        nodeCount++;
    }
}

void LAFR::remove(){
   if(head==NULL){
        cout << "THERE IS NO NODE FOR REMOVE!"<<endl;
        return;
    }
    else{
        Node* tmp;
        Node* removingTmp;
        tmp=&head->getNextNode();
        tmp->setPrevNode(NULL);
        removingTmp=head;
        head = tmp;
        delete removingTmp;
        nodeCount--;
    }
}

void LAFR::setTraverser(){
    traverser = new ARTL();
    traverser->current=tail;
}

class LALR : public AdderRemover {

public:
    LALR();
    void add(const int);
    void remove();
    void setTraverser();
};

LALR::LALR(){
    head=NULL;
    tail=NULL;
    traverser=NULL;
    nodeCount=0;
    name="LALR";
}

void LALR::add(const int input){
     Node* tmp = new Node(input);
    if(head==NULL){
        head=tmp;
        tail=tmp;
        nodeCount++;
    }else{
        tmp->setPrevNode(tail);
        tail->setNextNode(tmp);
        tail=tmp;
        nodeCount++;
    }
}

void LALR::remove(){
    if(head==NULL){
        cout << "THERE IS NO NODE FOR REMOVE!"<<endl;
        return;
    }
    else{
        Node* tmp;
        Node* removingTmp;
        tmp=&tail->getPrevNode();
        tmp->setNextNode(NULL);
        removingTmp=tail;
        tail->setPrevNode(NULL);
        tail=tmp;
        delete removingTmp;
        nodeCount--;
    }
}

void LALR::setTraverser(){
    traverser = new ARTL();
    traverser->current=tail;
}
