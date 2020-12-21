#include <iostream>

class List {    //stack implementation (list)
    class Node {    //item of the list
    public:
        int n;  //value of item
        Node* next; //next item
        Node* prev; //previous item
        Node() {
            n = NULL;
            next = nullptr;
            prev = nullptr;
        }
        Node(int n) {
            this->n = n;
            next = nullptr;
            prev = nullptr;
        }
    };
    Node* begin;    //pointer to the beginning of the list
    Node* end;  //pointer to the end of the list
public:
    int size;   //number of items
    List() {
        begin = new Node();
        end = new Node();
        size = 0;
    }
    Node* getEnd(){ //return the end
        if (size == 0) {    //list is empty
            return nullptr;
        }
        else if (size == 1) {   //return the begin
            return begin;
        }
        return end;
    }
    void pushBack(int n) {  //add item in the end
        if (size == 0) {    //item is the begin of list
            begin->n = n;
        }
        else if (size == 1) {
            end->n = n;
            end->prev = begin;
            begin->next = end;
        }
        else {
            auto node = new Node(n);
            auto end = this->end;
            end->next = node;
            node->prev = end;
            this->end = node;
        }
        size++;
    }
    void popBack() {    //remove end item
        if (size == 1) {    //remove begin
            begin->n = NULL;
            size--;
        }
        else if (size == 2) {
            begin->next = nullptr;
            end->prev = nullptr;
            end->n = NULL;
            size--;
        }
        else if (size > 2) {
            end->prev->next = nullptr;
            end = end->prev;
            size--;
        }
    }
};

class Heap {   //heap implementation
private:
    const int LENGTH = 10000;   //size of array of items
    int* arr;   //array of items
    int size;   //real number of items
    class Iterator {    //iterator of heap implementation 
        int* arr;   //pointer to array of items
        int* size;  //pointer to real number of items
        List* stack;    //stack of passed items
        int pos;    //current position in array
        char type;  //type of iterator: 'd' - DFS, 'b' - BFS
    public:
        Iterator(int* arr, int* size, List* stack, char type, int pos = 0) {
            this->arr = arr;
            this->size = size;
            this->stack = stack;
            this->type = type;
            this->pos = pos;
            if (stack->size == 0)   //root of heap
                stack->pushBack(0);
        };
        ~Iterator() = default;
        Iterator operator++() { //get next iterator
            int newPos = pos; 
            if (type == 'd') {  //DFS
                if (newPos * 2 + 1 < *size) {   //left child of item 
                    newPos = newPos * 2 + 1;
                    stack->pushBack(newPos);
                }
                else {
                    while (((newPos - 1) / 2) * 2 + 2  != newPos + 1 || newPos + 1 >= *size) {  //parent with child
                        newPos = (newPos - 1) / 2;  //going up
                        if (newPos == 0) {  //have reached the root, end
                            return *this;
                        }
                    }
                    ++newPos;   //right chilp of item
                    stack->pushBack(newPos);
                }
            }
            else {  //BFS
                if (newPos + 1 >= *size)    //end
                    return *this;
                newPos++;   //next item of array is next step of BFS
                stack->pushBack(newPos);
            }
            pos = newPos;
            return *this;
        }
        Iterator operator--() { //get prev iterator
            if (pos == 0)   //have reached the root, end
                return *this;
            pos = stack->getEnd()->prev->n; //get penultimate item of stack
            stack->popBack();
            return *this;
        }
        Iterator operator+(const int& c) {  //get iterator after c count of steps forward
            auto iter = *(new Iterator(arr, size, stack, type, pos));
            for (int i = 0; i < c; i++) {
                ++iter;
            }
            return iter;
        }
        Iterator operator-(const int& c) {  //get iterator after c count of steps backward
            auto iter = *(new Iterator(arr, size, stack, type, pos));
            for (int i = 0; i < c; i++) {
                --iter;
                if (iter.pos == 0)
                    return iter;
            }
            return iter;
        }
        Iterator operator+() const{
            return *this;
        }
        Iterator operator-() const{
            return *this;
        }
        int val() { //value of current item
            return arr[pos];
        }
    };
    void heapify(int i) {   //restoring heap after removing item
        int left = 2 * i + 1;   //left child
        int right = 2 * i + 2;  //right child
        int el;
        if (left < size) {
            if (arr[i] < arr[left]) {   //rearrange
                el = arr[i];
                arr[i] = arr[left];
                arr[left] = el;
                heapify(left);
            }
        }
        if (right < size) {
            if (arr[i] < arr[right]) {  //reaarange
                el = arr[i];
                arr[i] = arr[right];
                arr[right] = el;
                heapify(right);
            }
        }
    }
    int getPos(int n) { //get position of item with n value
        if (n > arr[0])
            return -1;
        for (int i = 0; i < size; i++) {
            if (n == arr[i])
                return i;
        }
        return -1;
    }
public:
    Heap() {
        arr = new int[LENGTH];
        size = 0;
    }
    bool contains(int n) {  //checked availability of item with n value
        if (n > arr[0])
            return false;
        for (int i = 0; i < size; i++) {
            if (n == arr[i])
                return true;
        }
        return false;
    }
    void insert(int n) { 
        int i = size;
        arr[i] = n; //at the end of array
        int parent = (i - 1) / 2;   //parent of item
        while (parent >= 0 && arr[parent] < arr[i] && i > 0) {  //if item more than parent, swap it
            int el = arr[i];
            arr[i] = arr[parent];
            arr[parent] = el;
            i = parent;
            parent = (i - 1) / 2;
        }
        size++;
    }
    void remove(int n) {
        int pos = getPos(n);
        if (pos != -1) {
            int el = arr[pos];
            arr[pos] = arr[size - 1];
            size--;
            heapify(pos);
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
    }
    Iterator create_dft_iterator() {
        return *(new Iterator(arr, &size, new List(), 'd'));
    }
    Iterator create_bft_iterator() {
        return *(new Iterator(arr, &size, new List(), 'b'));
    }
};

int main(){
    auto heap = new Heap();
    heap->insert(3);
    heap->insert(2);
    heap->insert(0);
    heap->insert(4);
    heap->insert(1);
    heap->insert(6);
    heap->insert(5);
    heap->print();
    std::cout << std::endl;
    heap->remove(5);
    heap->print();
    std::cout << std::endl;
    for (auto iterDFT = heap->create_dft_iterator(); iterDFT.val() != 0; ++iterDFT) {
        std::cout << iterDFT.val() << " ";
    }
    std::cout << std::endl;
    for (auto iterBFT = heap->create_bft_iterator(); iterBFT.val() != 0; ++iterBFT) {
        std::cout << iterBFT.val() << " ";
    }
    return 0;
}