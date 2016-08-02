#pragma once

template <class T>
struct tNode
{
    T value;
    tNode* l;
    tNode* r;
    tNode(): l(nullptr), r(nullptr) {}
};

template<class T, int S>
struct BinarySortedTree {
    tNode<T> nodes[S];
    tNode<T>* root;
    int size;
    int depth;
    BinarySortedTree(): root(nullptr), size(0), depth(0) {}
    tNode<T>* push(T val) {
        tNode<T>* node = &nodes[size++];
        node->value = val;
        if (root == nullptr) {
            root = node;
            depth = 1;
        }
        else {
            tNode<T>* parent = root;
            int nd = 2;
            for (;; nd++) {
                tNode<T>*& candidate = (val <= parent->value) ? parent->l : parent->r;
                if (candidate == nullptr) {
                    candidate = node;
                    break;
                }
                parent = candidate;
            }
            if (nd > depth) depth = nd;
        }
        return node;
    }
    tNode<T>* floor(T val) {
        tNode<T>* node = root;
        tNode<T>* last = nullptr;
        while (node) {
            if (val == node->value) return node;
            if (val >  node->value) {
                last = node;
                node = node->r;
            }
            else node = node->l;
        }
        return last;
    }
    tNode<T>* ceil(T val) {
        tNode<T>* node = root;
        tNode<T>* last = nullptr;
        while (node) {
            if (val <  node->value) {
                last = node;
                node = node->l;
            }   
            else if (val > node->value) node = node->r;
            else return node;
        }
        return last;
    }
    tNode<T>* find(T val) {
        tNode<T>* node = root;
        while (node) {
            if (val < node->value) node = node->l;
            else if (val > node->value) node = node->r;
            else return node;
        }
        return node;
    }
};

