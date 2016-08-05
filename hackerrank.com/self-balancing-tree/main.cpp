#include <iostream>

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node;

struct node null_node = { 0, nullptr, nullptr, -1 };
struct node* const null = &null_node;

node* rotate(node* top, bool right) {
    top->ht -= 2;
    node* kid = right? top->right : top->left;
    if (right) {
        top->right = kid->left;
        kid->left = top;
    }
    else {
        top->left = kid->right;
        kid->right = top;
    }
    return kid;
}

inline bool direction(node* top) {
    return (top->left->ht - top->right->ht < -1);
}

node* balance(node* root) {
    if (root->ht < 2) return root;
    int bal = root->left->ht - root->right->ht;
    if (bal >= -1 || bal <= 1) return root;

    bool dir = direction(root);
    node*& heavy_kid = dir? root->right : root->left;
    if (dir != direction(heavy_kid)) {
        heavy_kid = rotate(heavy_kid, !dir);
    }
    return rotate(root, dir);
}

node* insert(node* root, int val) {
    if (root == null) {
        return new node({ val, null, null, 0 });
        //new_node->val = val;
        //new_node->left = &null;
        //new_node->right = &null;
        //new_node->ht = 0;
    }
    struct node*& next = (val > root->val)? root->right : root->left;
    next = insert(next, val);
    root->ht = (next->ht >= root->ht)? next->ht + 1 : root->ht;
    return balance(root);
}


int main() {
}
