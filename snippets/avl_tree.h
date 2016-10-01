#pragma once

#include "snippets/common.h"

template<class T, int S>
struct AvlTree {
    struct Node {
        static Node* getnull() {
            static Node null;
            return &null;
        }
        inline bool isnull() { return this == getnull(); }
        T value;
        int height = -1;
        Node* kids[2] = { nullptr, nullptr };
        Node(const T& v): value(v), height(0) {
            kids[0] = getnull();
            kids[1] = getnull();
        }
        Node() {}
        Node(const Node&) = default;
        Node& operator= (const Node&) = default;
    };

    Node nodes[S];
    Node* root = Node::getnull();
    int size = 0;

    Node* insert(T val) {
        return insert(val, root);
    }

    Node* insert(T val, Node*& node) {
        if (node->isnull()) {
            node = &nodes[size++];
            *node = Node(val);
            return node;
        }
        Node*& kid = node->kids[val > node->value];
        Node* inserted = insert(val, kid);
        node->height = MAX(node->height, kid->height + 1);
        node = balance(node);
        return inserted;
    }

    Node* rotate(Node* node, int dir) {
        node->height -= 2;
        Node* kid = node->kids[dir];
        node->kids[dir] = kid->kids[!dir];
        kid->kids[!dir] = node;
        return kid;
    }

    // true if right kid is heavier, false otherwise
    bool bias(Node* node) {
        return (node->kids[0]->height - node->kids[1]->height < 0);
    }

    Node* balance(Node* node) {
        if (node->height < 2) return node;
        // right goes negative
        int bal = node->kids[0]->height - node->kids[1]->height;
        if (bal >= -1 && bal <=1 ) return node;
        bool dir = bias(node);
        Node* heavy_kid = node->kids[dir];
        if (bias(heavy_kid) != dir) {
            node->kids[dir] = rotate(heavy_kid, !dir);
        }
        return rotate(node, dir);
    }

    Node* find(T val, Node* node) {
        if (isnull(node)) return nullptr;
        if (node->value == val) return node;
        return find(val, node->kids[val > node->value]);
    }

    template<class F> void iterate(F& func) { iterate(func, root); }
    template<class F> bool iterate(F& func, Node* node) {
        if (node->isnull()) return true;
        if (iterate(func, node->kids[0]) == false) return false;
        if (func(node) == false) return false;
        return iterate(func, node->kids[1]);
    }
};

