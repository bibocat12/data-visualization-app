#include "Tree234.h"
#include <algorithm>

Tree234::Tree234() : root(new Node()) {}

Tree234::~Tree234() {
    deleteTree(root);
    for (auto snapshot : snapshots) {
        deleteTree(snapshot);
    }
}

void Tree234::create(std::vector<int>& nums)
{
    deleteTree(root);
    for (auto snapshot : snapshots) {
        deleteTree(snapshot);
    }
    root = new Node();
    for (auto i : nums) {
        insert(i);
    }
    resetState();
    takeSnapshot();
}

void Tree234::deleteTree(Node* node) {
    if (node) {
        for (auto child : node->children) {
            deleteTree(child);
        }
        delete node;
    }
}

void Tree234::insert(int key) {
    resetState();
    takeSnapshot();
    if (root->keys.size() == 3) {
        Node* newRoot = new Node();
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        operatedNodes.push_back(std::vector<Node*> {newRoot});
        root = newRoot;
        takeSnapshot();
        typeSnapshots.back() = "splitRoot";
    }
    insertNonFull(root, key);
    takeSnapshot();
    typeSnapshots.back() = "insert";
}

void Tree234::resetState()
{
    snapshots.clear();
    typeSnapshots.clear();
    operatedNodes.clear();
    operatedNodes.clear();
}

void Tree234::splitChild(Node* parent, int index) {
    Node* node = parent->children[index];
    Node* newNode = new Node();
    parent->keys.insert(parent->keys.begin() + index, node->keys[1]);
    parent->children.insert(parent->children.begin() + index + 1, newNode);

    newNode->keys.push_back(node->keys[2]);
    node->keys.resize(1);

    if (!node->isLeaf()) {
        newNode->children.push_back(node->children[2]);
        newNode->children.push_back(node->children[3]);
        node->children.resize(2);
    }
}

void Tree234::insertNonFull(Node* node, int key) {
    int i = node->keys.size() - 1;
    if (node->isLeaf()) {
        node->keys.push_back(key);
        std::sort(node->keys.begin(), node->keys.end());
    }
    else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 3) {
            operatedNodes.push_back(std::vector<Node*> {node->children[i]});
            if (!snapshots.empty()) preOperated(root, snapshots.back());
            splitChild(node, i);
            operatedNodes.back().push_back(node);
            if (key > node->keys[i]) {
                i++;
            }
            takeSnapshot();
            typeSnapshots.back() = "splitChild";
        }
        insertNonFull(node->children[i], key);
    }
}

void Tree234::remove(int key) {
    if (!root) return;
    remove(root, key);
    if (root->keys.empty()) {
        Node* oldRoot = root;
        if (root->isLeaf()) {
            root = nullptr;
        }
        else {
            root = root->children[0];
        }
        delete oldRoot;
        takeSnapshot();
    }
}

bool Tree234::remove(Node* node, int key) {
    int idx = 0;
    while (idx < node->keys.size() && node->keys[idx] < key) {
        idx++;
    }
    if (idx < node->keys.size() && node->keys[idx] == key) {
        if (node->isLeaf()) {
            node->keys.erase(node->keys.begin() + idx);
            takeSnapshot();
            return true; // Key found and removed
        }
        else {
            removeFromNonLeaf(node, idx);
            return true; // Key found and removed
        }
    }
    else {
        if (node->isLeaf()) return false; // Key not found
        bool flag = (idx == node->keys.size());
        if (node->children[idx]->keys.size() < 2) {
            fill(node, idx);
        }
        if (flag && idx > node->keys.size()) {
            return remove(node->children[idx - 1], key);
        }
        else {
            return remove(node->children[idx], key);
        }
    }
}

void Tree234::removeFromNonLeaf(Node* node, int idx) {
    int key = node->keys[idx];
    if (node->children[idx]->keys.size() >= 2) {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        takeSnapshot();
        remove(node->children[idx], pred);
    }
    else if (node->children[idx + 1]->keys.size() >= 2) {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        takeSnapshot();
        remove(node->children[idx + 1], succ);
    }
    else {
        merge(node, idx);
        remove(node->children[idx], key);
    }
}

void Tree234::removeFromLeaf(Node* node, int idx) {
    node->keys.erase(node->keys.begin() + idx);
}

int Tree234::getPredecessor(Node* node, int idx) {
    Node* cur = node->children[idx];
    while (!cur->isLeaf()) {
        cur = cur->children.back();
    }
    return cur->keys.back();
}

int Tree234::getSuccessor(Node* node, int idx) {
    Node* cur = node->children[idx + 1];
    while (!cur->isLeaf()) {
        cur = cur->children.front();
    }
    return cur->keys.front();
}

void Tree234::fill(Node* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->keys.size() >= 2) {
        borrowFromPrev(node, idx);
    }
    else if (idx != node->keys.size() && node->children[idx + 1]->keys.size() >= 2) {
        borrowFromNext(node, idx);
    }
    else {
        if (idx != node->keys.size()) {
            merge(node, idx);
        }
        else {
            merge(node, idx - 1);
        }
    }
}

void Tree234::borrowFromPrev(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx - 1];

    child->keys.insert(child->keys.begin(), node->keys[idx - 1]);
    operatedNodes.push_back(std::vector<Node*> {child});
    takeSnapshot();
    typeSnapshots.back() = "extraPrevKeys";
    if (!child->isLeaf()) {
        operatedNodes.push_back(std::vector<Node*> {child});
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
        takeSnapshot();
        typeSnapshots.back() = "movePrevEdges";
    }
    operatedNodes.push_back(std::vector<Node*> {node});
    operatedNodes.back().push_back(sibling);
    idxes.push_back(idx - 1);
    takeSnapshot();
    typeSnapshots.back() = "movePrevNodes";
    node->keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    takeSnapshot();
    typeSnapshots.back() = "skip";
}

void Tree234::borrowFromNext(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);
    operatedNodes.push_back(std::vector<Node*> {child});
    takeSnapshot();
    typeSnapshots.back() = "extraNextKeys";
    if (!child->isLeaf()) {
        operatedNodes.push_back(std::vector<Node*> {sibling});
        takeSnapshot();
        typeSnapshots.back() = "moveNextEdges";
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
        takeSnapshot();
        typeSnapshots.back() = "skip";
    }
    operatedNodes.push_back(std::vector<Node*> {node});
    operatedNodes.back().push_back(sibling);
    idxes.push_back(idx);
    takeSnapshot();
    typeSnapshots.back() = "moveNextNodes";
    node->keys[idx] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
    takeSnapshot();
    typeSnapshots.back() = "skip";
}

void Tree234::merge(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);
    takeSnapshot();
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
    takeSnapshot();
    if (!child->isLeaf()) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
        takeSnapshot();
    }
    node->keys.erase(node->keys.begin() + idx);
    takeSnapshot();
    node->children.erase(node->children.begin() + idx + 1);
    delete sibling;
    takeSnapshot();
}

bool Tree234::search(int key) {
    takeSnapshot();
    typeSnapshots.back() = "search";
    return search(root, key);
}

bool Tree234::search(Node* node, int key) const {
    if (!node) return false;
    int idx = 0;
    while (idx < node->keys.size() && node->keys[idx] < key) {
        idx++;
    }
    if (idx < node->keys.size() && node->keys[idx] == key) return true;
    if (node->isLeaf()) return false;
    return search(node->children[idx], key);
}

void Tree234::takeSnapshot() {
    snapshots.push_back(cloneTree(root));
    typeSnapshots.push_back("");
    if (operatedNodes.size() < snapshots.size()) {
        std::vector<Node*> oprNodes;
        operatedNodes.push_back(oprNodes);
    }
    if (idxes.size() < snapshots.size()) {
        idxes.push_back(-1);
    }
}

Tree234::Node* Tree234::cloneTree(Node* node) {
    if (!node) return nullptr;
    Node* newNode = new Node();
    newNode->keys = node->keys;
    if (operatedNodes.size() > snapshots.size()) {
        for (auto &oprNode : operatedNodes.back()) {
            if (oprNode == node) {
                oprNode = newNode;
            }
        }
    }
    for (auto child : node->children) {
        newNode->children.push_back(cloneTree(child));
    }
    return newNode;
}

void Tree234::preOperated(Node* node, Node* snapshotNode)
{
    if (!node) return;
    if (operatedNodes.size() > snapshots.size() && !operatedNodes.empty() && operatedNodes.back().front() == node) {
        operatedNodes.back().front() = snapshotNode;
    }
    for (int i = 0; i < node->children.size(); i++) {
        preOperated(node->children[i], snapshotNode->children[i]);
    }
}

Tree234::Node* Tree234::findParent(Node* child) const {
    if (root == nullptr || root == child) {
        return nullptr;
    }
    return findParent(root, child);
}

Tree234::Node* Tree234::findParent(Node* node, Node* child) const {
    if (node == nullptr || node->isLeaf()) {
        return nullptr;
    }
    for (Node* c : node->children) {
        if (c == child) {
            return node;
        }
        Node* parent = findParent(c, child);
        if (parent != nullptr) {
            return parent;
        }
    }
    return nullptr;
}
