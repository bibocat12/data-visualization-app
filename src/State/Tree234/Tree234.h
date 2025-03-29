#pragma once

#include <vector>
#include <string>
#include <iostream>

class Tree234 {
public:
    struct Node {
        std::vector<int> keys;
        std::vector<int> nodes;
        std::vector<Node*> children;
        int edge;
        bool isLeaf() const { return children.empty(); }
    };

    Tree234();
    ~Tree234();
    void create(std::vector<int>& nums);
    void insert(int key);
    void remove(int key);
    bool search(int key);
    Node* findParent(Node* child) const;
    void takeSnapshot();
    std::vector<Node*> snapshots;
    std::vector<std::string> typeSnapshots;
    std::vector<std::vector<Node*>> operatedNodes;
    std::vector<int> idxes;

private:
    Node* root;

    void resetState();
    void splitChild(Node* parent, int index);
    void insertNonFull(Node* node, int key);
    void merge(Node* node, int index);
    bool remove(Node* node, int key);
    void removeFromNonLeaf(Node* node, int index);
    void removeFromLeaf(Node* node, int index);
    int getPredecessor(Node* node, int index);
    int getSuccessor(Node* node, int index);
    void fill(Node* node, int index);
    void borrowFromPrev(Node* node, int index);
    void borrowFromNext(Node* node, int index);
    bool search(Node* node, int key) const;
    void deleteTree(Node* node);
    Node* findParent(Node* node, Node* child) const;
    Node* cloneTree(Node* node);
    void preOperated(Node* node, Node* snapshotNode);
};

