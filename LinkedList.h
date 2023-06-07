//
// Created by Guhan on 2/16/2023.
//

#ifndef PROJECT1_LINKEDLIST_H
#define PROJECT1_LINKEDLIST_H

#endif //PROJECT1_LINKEDLIST_H
#pragma once
#include <string>
#include <iostream>
using namespace std;
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <sstream>


template <typename T>
class LinkedList {
public:
    // Nested class for each node
    struct Node{
        T data;
        Node* next;  //pointer to next node
        Node* prev;  //pointer to previous node
    };

// Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

//Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T&data);
    bool RemoveAt(unsigned int index);
    void Clear();
// Behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
// Accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value);
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
//Operators
T& operator[](unsigned int index);
const T& operator[](unsigned int index) const;
bool operator==(const LinkedList<T>& rhs) const;
// Copy assignment instructor
LinkedList<T>& operator=(const LinkedList<T>& rhs);
// Default Constructor
    LinkedList();
// Copy Constructor
    LinkedList(const LinkedList<T>& list);
//Destructor
    ~LinkedList();

private:
    unsigned int Node_Count = 0;
    Node* head;
    Node* tail;
    Node* n;

};

// Mutators
template <typename T>
void LinkedList<T>::AddHead(const T& data){
    // create a temp node
    n = new Node;
    n->data = data;
    n->prev = nullptr;
    n->next = nullptr;
    // if the list is not empty
    if (head == nullptr) {
        n->next = head;
        head = n;
        tail = head;
    }
        // if the list is empty
    else{
        head->prev = n;
        n->next = head;
        head = n;
    }
    Node_Count++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data){
    n = new Node;
    n->data = data;
    n->prev = nullptr;
    n->next = nullptr;
    // if list is not empty
    if (tail == nullptr){
        head = n;
        tail = n;
        tail->next = nullptr;
        tail->prev = nullptr;
    }
    // if the list is empty
    else{
        tail->next = n;
        n->prev = tail;
        tail = n;
        n = nullptr;
    }
    Node_Count++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count){        // takes in a list and adds all of those things to the front of the Linked List
    for(int i = (count - 1); i >= 0; --i){                                  // basically it creates a new head a bunch of times
        this->AddHead(data[i]);
    }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count){        // Same as above but adds all to the back of the linked list
    for(unsigned int i = 0; i < count; i++){
        this->AddTail(data[i]);

    }
}

template <typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data){
    Node* new_Node = new Node(); // creates new node
    new_Node->data = data;       // assigns passed in data to the new node
    new_Node->prev = node;  // sets new node's previous pointer to point to the passed in node
    new_Node->next = nullptr; // sets new node's forward pointer to be null

    if (node == tail){
        tail = new_Node;
        node->next = tail;
    }
    else {
        new_Node->next = node->next;
        node->next = new_Node;
    }

    Node_Count++;

}

template <typename T>
void LinkedList<T>::InsertBefore(Node *node, const T &data){
    // create new node
    Node* new_Node = new Node();
    new_Node->data = data;
    new_Node->next = node;
    new_Node->prev = nullptr;

    if (node == head){
        head = new_Node;
        node->prev = head;
    }
    else {
        node->prev->next = new_Node; // the next pointer for the node behind the passed in the node is the new node
        node->prev = new_Node;      // the pointer for the passed in node points back to the new node
    }
    Node_Count++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index){  // passes in data and the index of the node
    unsigned int temp_count = Node_Count - 1;
    if (index > temp_count){
        throw out_of_range("Out of range");
    }
    if (index == 0){                    // checks to see if index is 0 and inserts it at head if it is
        InsertBefore(head, data);
    }
    else if(index == temp_count){       // checks to see if index is at tail and inserts if it is
        InsertAfter(tail, data);
        Node_Count = Node_Count - 2;
    }
   else {
        // create a node to figure out what node comes before where we want to add our node
       Node* come_before = head->next;
       for (unsigned int i = 0; i < index - 2; ++i){
           come_before = come_before->next;
       }
        // create a new node with the data
        Node* new_Node = new Node();
        new_Node->data = data;

        // create a node to refer to the node that will come after the new node
        Node* come_after = come_before->next;

        new_Node->prev = come_before;     // sets new node to point to the nodes that come before and after it
        new_Node->next = come_after; 
        come_before->next = new_Node;     // sets before node to point to new node
        come_after->prev = new_Node;   // sets after node to point to new node
   }
    Node_Count++;
}

// Removal
template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (Node_Count == 0){       // return false if there is no head (in other words the List has a length of 0)
        return false;
    }

    else if (Node_Count == 1) { // checks to see if head is the only node left
        delete head;       // deletes the head
        head = nullptr;
        tail = nullptr;
        Node_Count--;
        return true;
    }
    else{
        Node * temp_node = head->next; // creates temp_node and points it to node past the head
        temp_node->prev = nullptr;
        delete head;                 // deletes the head node
        head = temp_node;           // creates new head
        Node_Count--;
        return true;
    }
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (Node_Count == 0){       // return false if there is no tail (in other words the list has a length of 0)
        return false;
    }

   else if (Node_Count == 1) { // checks if tail is only node left
        delete tail;
        head = nullptr;
        tail = nullptr;
        Node_Count--;
        return true;
    }

    else{
        Node* temp_node = tail->prev;  // sets temp node to be node behind tail
        temp_node->next = nullptr;
        delete tail;                // deletes tail
        tail = temp_node;       // creates new tail
        Node_Count--;

        return true;
    }
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    unsigned int remove_num = 0; // create counter for number of nodes removed
    vector<LinkedList<T>::Node*> remove_nodes;
    FindAll(remove_nodes, data);

    for (unsigned int i = 0; i < remove_nodes.size(); ++i) {   // iterates over the removed nodes vector and
        Node* prev_node = remove_nodes.at(i)->prev;     // sets the prev node to be the node before the node that will be removed
        Node* next_node = remove_nodes.at(i)->next;     // sets the next node to be the node after the node that will be removed

        prev_node->next = next_node;            // assigns previous node to next node
        next_node->prev = prev_node;            // assigns next node to previous node

        delete remove_nodes.at(i);              // deletes node at i

        Node_Count--;                       // both counters are changed
        remove_num++;
    }
    return remove_num;                  // returns the count of removed


    // This code also works and was my original idea however it only works on Clion
    // For some reason whenever I upload this code on Zybooks it doesn't do anything
    /**
    unsigned int remove_num = 0;            // this variable will track the number of
    Node* temp_node = head; // temp node is going to be used to iterate through the Linked List
    while (temp_node != nullptr){
        if (temp_node->data == data){
            Node* del_node = temp_node;   // node that is going to be deleted
            Node* x = temp_node->prev;  // node before the node that needs to be deleted
            Node* y = temp_node->next;  // node after the node that needs to be deleted

            x->next = y;        // assign previous node to next node
            y->prev = x;         // assign next node to previous node
            delete del_node;        // delete node with the matching data

            Node_Count--;
            remove_num++;
        }
        temp_node = temp_node->next; // move temp node down the list
    }
    return remove_num;
     **/
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index > Node_Count or Node_Count == 0) {
        return false;  // throw an error if out of range
    } else if (index == 0) {        // if index is 0 the head must be removed
        if (RemoveHead() == true) {
            return true;
        }
    } else if (index == Node_Count - 1) {   // if index is the final item of the list then the tail must be removed
        if (RemoveTail() == true) {
            return true;
        }
    } else {
        Node *temp_node = GetNode(index);           // create a temp node at the index of the node we want to remove

        Node *prev_node = temp_node->prev;         // set prev node to be the node that comes before the node we want to delete
        Node *next_node = temp_node->next;         // set next node to the node that comes after the node we want to delete
        if (prev_node != nullptr) {
            prev_node->next = next_node;        // assign prev node to next node
        }
        if (next_node != nullptr) {
            next_node->prev = prev_node;            // assign next node to prev node
        }
            delete temp_node;                   // delete temp node
            Node_Count--;
            return true;        // return true;
    }
    return false;
}




template <typename T>
void LinkedList<T>::Clear() {
    Node* temp_node = head;         // create a temp node
    while (temp_node != nullptr) {      // iterate through the entire Linked list and delete node after node
        Node* del_node = temp_node;        // assign delete node to be temp node
        temp_node = temp_node->next;
        delete del_node;            // delete delete node
    }
    head = nullptr;     // reset head, tail, and Node_Count
    tail = nullptr;
    Node_Count = 0;
}
// Print Functions
template <typename T>
void LinkedList<T>::PrintForward() const{
    Node* temp_Node = head;                 // Prints starting at the beginning or head of a linked list
    while (temp_Node != nullptr) {
        cout << temp_Node->data << endl;
        temp_Node = temp_Node->next;
    }

}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node *node) const {
        if (node == tail){
            cout << node->data << endl;         // if at the end of the list it just prints the tail
            node = nullptr;
        }
        else {
            cout << node->data << endl;        // if not at the end it prints data
            node = node->next;                  // shifts the node to the next node
            PrintForwardRecursive(node);        // Recursively calls itself again
        }
}

template <typename T>
void LinkedList<T>::PrintReverse() const{
    Node* temp_Node = tail;
    while (temp_Node != nullptr) {      // Prints starting at the end or the tail of a linked list
        cout << temp_Node->data << endl;
        temp_Node = temp_Node->prev;
    }
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node *node) const {
    if (node == head){
        cout << node->data << endl;     // if at the end of the list it prints the head
        node = nullptr;
    }
    else {
        cout << node->data << endl;     // if not at the end of the list it prints the value
        node = node->prev;              // shifts the node to the previous node
        PrintReverseRecursive(node);    // Recursively calls itself again
    }
}


//Operators
// Overload subscript operator (returns the data at a certain index)
template <typename T>
T& LinkedList<T>::operator[](unsigned int index){
    if (index > Node_Count - 1){
        throw out_of_range("Out of range");
    }
    else if(index == 0){
        return head->data;
    }
    else if(index == Node_Count - 1){
        return tail->data;
    }
    else{
        Node* temp_node = head;
        for (int i = 0; i < index + 1; i++){         // iterates until it is on the correct node
            temp_node = temp_node->next;
        }
        T return_data = temp_node->data;            // returns the data once it has reached the correct node
        return return_data;
    }
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const{
    if (index > Node_Count - 1){
        throw out_of_range("Out of range");
    }

    else if(index == 0){
        return head->data;
    }
    else if(index == Node_Count - 1){
        return tail->data;
    }
    else{
        Node* temp_node = head;
        for (int i = 0; i < index + 1; i++){         // iterates until it is on the correct node
            temp_node = temp_node->next;
        }
        T return_data = temp_node->data;            // returns the data once it has reached the correct node
        return return_data;
    }

}


//Copy Assignment Operator
template <typename T>           // This whole function essentially functions as a giant = because otherwise you cannot just create a new object by assigning an existing object to it
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs){
    if (&rhs != this){     // checks to see if passed in object is different to original object (Are they two separate objects?)

        Node_Count = rhs.Node_Count;      // assigns Node_Count to passed in Node_Count via assignment

        Node* temp_node = head;
        while (temp_node != nullptr){        //deletes all existing nodes to avoid have leakers
            Node* j = temp_node->next;
            delete temp_node;
            temp_node = j;
        }

        head = nullptr;
        tail = nullptr;

        Node* k = rhs.head;             // Adds each node to another Linked list
        while(k != nullptr){
            AddTail(k->data);
            k = k->next;
        }
    }

return *this;           // always needed at the end of a copy assignment constructor
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    unsigned int temp_count = Node_Count;
    // first check if the count is the same (they must have the same number of nodes)
    if (Node_Count == rhs.Node_Count) {
        for (unsigned int i = 0; i < temp_count; i++) {     // iterate throughout the Linked List and compare the values at each node to the rhs
            if (GetNode(i)->data != rhs.GetNode(i)->data)
                return false;                           // if any of them are different return false
        }
        return true;                            //otherwise it should return true
    }
        // return false if count is not the same
    else {
        return false;
    }
}


// Constructors and Destructor
//Default Constructor
template <typename T>
LinkedList<T>::LinkedList(){
    Node_Count = 0;
    head = nullptr;
    tail = nullptr;
}

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {

        Node_Count = list.Node_Count;
        head = nullptr;
        tail = nullptr;

        Node* temp_node = list.head;
        for(int i = 0; i < list.Node_Count; ++i){          // iterates through existing object and copies each one and creates a new list using the exact same data
            AddTail(temp_node->data);
            temp_node = temp_node->next;
        }


}

//Destructor
template <typename T>
LinkedList<T>::~LinkedList(){
    Node* delete_node = head;           // temporary node called delete node
    while (delete_node != nullptr) {      // while running through the list
        Node* x = delete_node;          // Node x points to delete node
        delete_node = delete_node->next;  // delete node iterates through list
        delete x;                       // deletes node x (gets rid of all temp nodes)
    }

}


// Accessors
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head(){
    return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail(){
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const{
    return tail;
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return Node_Count;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    unsigned int temp_count = Node_Count - 1;
    if (index > temp_count){
        throw out_of_range("Out of range");
    }

    else if(index == 0){
        return head;
    }
    else if(index == temp_count){
        return tail;
    }
    else{
        Node* temp_node = head;
        for (unsigned int i = 0; i < index; i++){         // iterates until it is on the correct node
            temp_node = temp_node->next;
        }

        return temp_node;           // returns the pointer of a specific node based on the index
    }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const{
    unsigned int temp_count = Node_Count - 1;
    if (index > temp_count){
        throw out_of_range("Out of range");
    }

    if(index == 0){
        return head;
    }
    //else if(index == temp_count){
        //return tail;
    //}

    Node* temp_node = head->next;
    for (unsigned int i = 0; i < index + 1; i++){         // iterates until it is on the correct node
        temp_node = temp_node->next;
    }

    return temp_node;

}


template <typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) {
    Node* temp_node = head;
    for (unsigned int i = 0; i < Node_Count; ++i){               // finds every instance of a value
        if(temp_node->data == value){
            outData.push_back(temp_node);               // everytime it is found that node is push_back onto the vector
        }
        temp_node = temp_node->next;                    // temp_node moves to the next node

    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) {
    Node* temp_node = head;
    for (unsigned int i = 0; i < Node_Count; ++i){
        if(temp_node->data == data){
            return temp_node;
        }
        else{
            temp_node = temp_node->next;
        }
    }
    return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
    Node* temp_node = head;             // creates a temp node to search through the whole linked list for a specific value
    for (int i = 0; i < Node_Count; ++i){
        if(temp_node->data == data){
            return temp_node;               // when it is found it is returned to the user
        }
        else{
            temp_node = temp_node->next;            // if it not found on that node it goes to the next one
        }
    }
    return nullptr;             // returns null if nothing is found
}