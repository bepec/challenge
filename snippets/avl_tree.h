#pragma once

template<class T, int S>
struct AvlTree {
    struct Node {
        static Node* getnull() {
            static Node null;
            return &null;
        }
        inline bool isnull() { return this == getnull(); }
        T value;
        int weight = 0;
        int height = -1;
        Node* kids[2] = { nullptr, nullptr };
        Node(const T& v): value(v), weight(1), height(0) {
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
        node->weight -= kid->weight;
        Node* inserted = insert(val, kid);
        node->height = std::max(node->height, kid->height + 1);
        node->weight += kid->weight;
        node = balance(node);
        return inserted;
    }

    Node* balance(Node* node) {
        if (node->height < 2) return node;
        // right goes negative
        int bal = node->kids[0]->height - node->kids[1]->height;
        if (bal >= -1 && bal <=1 ) return node;
        bool dir = (bal < 1);
        Node* heavy_kid = node->kids[dir];
        if (heavy_kid->kids[dir]->height > heavy_kid->kids[!dir]->height) {
            node->height -= 2;
            // TODO: check if heavy_kid height remains the same (testcase)
            node->kids[dir] = heavy_kid->kids[!dir];
            heavy_kid->kids[!dir] = node;
            return heavy_kid; // becomes node
        }
        // TODO: rotate twice
        return node;
    }
    Node* find(T val, Node* node) {
        if (isnull(node)) return nullptr;
        if (node->value == val) return node;
        return find(val, node->kids[val > node->value]);
    }
};

