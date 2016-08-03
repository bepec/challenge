#pragma once

template<class T, int S>
struct AvlTree {
    struct Node {
        T value;
        int weight = 0;
        Node* kids[2] = { nullptr, nullptr };
    };
    Node nodes[S];
    Node* root = nullptr;
    int size = 0;
    
    Node* insert(T val) {
        Node* result = insert(val, root);
        if (!root) root = result;
        return result;
    }
    Node* insert(T val, Node* node) {
        if (node == nullptr) {
            node = &nodes[size++];
            node->value = val;
        }
        else {
            Node*& next = node->kids[val < node->value];
            if (next) node->weight -= next->weight;
            next = insert(val, next);
            node->weight += next->weight;
        }
        return node;
    }

    Node* find(T val, Node* node) {
        if (node == nullptr) return nullptr;
        if (node->value == val) return node;
        return find(val, node->kids[val < node->value]);
    }
};

