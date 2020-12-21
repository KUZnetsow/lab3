#include <iostream>

class List {
    class Node {
    public:
        int n;
        Node* next;
        Node* prev;
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
    Node* begin;
    Node* end;
public:
    int size;
    List() {
        begin = new Node();
        end = new Node();
        size = 0;
    }
    Node* getEnd(){
        if (size == 0) {
            return nullptr;
        }
        else if (size == 1) {
            return begin;
        }
        return end;
    }
    void pushBack(int n) {
        if (size == 0) {
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
    void popBack() {
        if (size == 1) {
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

class Heap {
private:
    const int LENGTH = 10000;
    int* arr;
    int size;
    class Iterator {
        int* arr;
        int* size;
        List* stack;
        int pos;
        char type;
    public:
        Iterator(int* arr, int* size, List* stack, char type, int pos = 0) {
            this->arr = arr;
            this->size = size;
            this->stack = stack;
            this->type = type;
            this->pos = pos;
            if (stack->size == 0)
                stack->pushBack(0);
        };
        ~Iterator() = default;
        Iterator operator++() {
            int newPos = pos; 
            if (type == 'd') {
                if (newPos * 2 + 1 < *size) {
                    newPos = newPos * 2 + 1;
                    stack->pushBack(newPos);
                }
                else {
                    while (((newPos - 1) / 2) * 2 + 2  != newPos + 1 || newPos + 1 >= *size) {
                        newPos = (newPos - 1) / 2;
                        if (newPos == 0) {
                            return *this;
                        }
                    }
                    ++newPos;
                    stack->pushBack(newPos);
                }
            }
            else {
                if (newPos + 1 >= *size)
                    return *this;
                newPos++;
                stack->pushBack(newPos);
            }
            pos = newPos;
            return *this;
        }
        Iterator operator--() {
            if (pos == 0)
                return *this;
            pos = stack->getEnd()->prev->n;
            stack->popBack();
            return *this;
        }
        Iterator operator+(const int& c) {
            auto iter = *(new Iterator(arr, size, stack, type, pos));
            for (int i = 0; i < c; i++) {
                ++iter;
            }
            return iter;
        }
        Iterator operator-(const int& c) {
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
        int val() {
            return arr[pos];
        }
    };
    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int el;
        if (left < size) {
            if (arr[i] < arr[left]) {
                el = arr[i];
                arr[i] = arr[left];
                arr[left] = el;
                heapify(left);
            }
        }
        if (right < size) {
            if (arr[i] < arr[right]) {
                el = arr[i];
                arr[i] = arr[right];
                arr[right] = el;
                heapify(right);
            }
        }
    }
    int getPos(int n) {
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
    bool contains(int n) {
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
        arr[i] = n;
        int parent = (i - 1) / 2;
        while (parent >= 0 && arr[parent] < arr[i] && i > 0) {
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