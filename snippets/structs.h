#include <iostream>

const bool DEBUG = true;

#define COUT if (DEBUG) std::cout
#define ARRAY_SIZE(A) sizeof(A)/sizeof(A[0])

struct Exc {};

//struct Object {};
typedef int Object;

//static const int MAX_SIZE = 10000;
static const int MAX_SIZE = 10;

void printArray(Object* array, int size) {
    COUT << size << ":[";
    for (int i = 0; i < size; i++) {
        COUT <<  (i > 0 ? ", " : "") << array[i];
    }
    COUT << "]";
}

void swap(Object& a, Object& b) {
    Object temp = a;
    a = b;
    b = temp;
}

void quickSort(Object* array, int size) {
    if (size < 2) return;
    Object& p = array[size/2];
    int i, j;
    for (i = 0, j = size - 1;; i++, j--) {
        while (array[i] < p) i++;
        while (p < array[j]) j--;
        if (i >= j) break;
        swap(array[i], array[j]);
    }
    quickSort(array, i);
    quickSort(array + i, size - i);
}

// stack based on static array
struct Stack {
    Object data[MAX_SIZE];
    int size;
    Stack(): size(0) {}
    void push(Object value) {
        if (size == MAX_SIZE) throw Exc();
        data[size] = value;
        size++;
    }
    Object pop() {
        if (size == 0) throw Exc();
        size--;
        return data[size];
    }
    int find(Object value) {
        for (int i = 0; i < size; i++)
            if (value == data[i]) return i;
        return -1;
    }
    void print() {
        COUT << size << ":[";
        for (int i = 0; i < size; i++) {
            COUT <<  (i > 0 ? ", " : "") << data[i];
        }
        COUT << "]";
    }
};

// circular queue based on static array
// random access using method get
// iterate using method get or manually calculate overlapping
struct Queue {
    Object data[MAX_SIZE];
    int size;
    int first; // index of first element in data
    Queue(): size(0), first(0) {}
    Object& get(int n) {
        if (n < 0 || n >= size) throw Exc();
        return data[(first+n) % MAX_SIZE];
    }
    void push(Object value) {
        if (size == MAX_SIZE) throw Exc();
        data[(first+size) % MAX_SIZE] = value;
        size++;
    }
    Object pop() {
        if (size == 0) throw Exc();
        Object result = data[first];
        first = ((first+1) % MAX_SIZE);
        size--;
        return result;
    }
    int find(Object value) {
        for (int i = 0; i < size; i++)
            if (data[(first+i) % MAX_SIZE] == value) return i;
        return -1;
    }
    void print() {
        COUT << size << ":[";
        for (int i = 0; i < size; i++) {
            COUT <<  (i > 0 ? ", " : "") << data[(first+i) % MAX_SIZE];
        }
        COUT << "]";
    }
};

// single (forward) linked list
// doesn't manage object lifetime - beware!
struct List {
    struct Node {
        Object value;
        Node* next;
        Node(const Object& v): value(v), next(NULL) {}
    };
    int size;
    Node* first;
    Node* preFirst;
    List(): size(0), first(NULL), preFirst(new Node(0)) {}
    Node* insert(const Object& obj, Node* after) {
        Node* node = new Node(obj);
        if (after == NULL) {
            node->next = first;
            first = node;
        }
        else {
            node->next = after->next;
            after->next = node;
        }
        size++;
        return node;
    }
    bool remove(Node* node) {
        if (node == NULL) throw Exc();
        Node** ptr = NULL;
        if (node == first) ptr = &first;
        else {
            for (Node* i = first; i != NULL; i = i->next) {
                if (i->next == node) ptr = &i->next;
            }
        }
        if (ptr != NULL) {
            *ptr = node->next;
            size--;
            delete node;
            return true;
        }
        else return false;
    }
    Node* find(const Object& value) {
        for (Node* i = first; i != NULL; i = i->next)
            if (i->value == value) return i;
        return NULL;
    }
    void print() {
        COUT << size << ":[";
        for (Node* i = first; i != NULL; i = i->next) {
            COUT << (i != first ? ", " : "") << i->value;
        }
        COUT << "]";
    }
};


struct Graph {




};

