#include "Trie.h"
#include <iostream> 

Trie::Trie() : root(new TrieNode('\0', 0)), nextOrder(0) {} // Root node at depth 0

Trie::~Trie() {
    clear();
    delete root;
    root = nullptr;
}

void Trie::clear() {
    clearRecursive(root);

    root->children.clear();
    root->isEndOfWord = false; 
    nextOrder = 0;
}

void Trie::clearRecursive(TrieNode* node) {
    if (!node) return;

    for (auto const& [key, val] : node->children) {
        clearRecursive(val); 
        delete val;          
    }

    node->children.clear();


}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {


        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode(c, current->depth + 1);
        }
        current = current->children[c];
    }
    current->isEndOfWord = true; 
}

bool Trie::search(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {


        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return current != nullptr && current->isEndOfWord; 
}

bool Trie::startsWith(const std::string& prefix) {
    TrieNode* current = root;
    for (char c : prefix) {


        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return current != nullptr;
}

void Trie::create(const std::vector<std::string>& words) {
    clear(); 
    root = new TrieNode('\0', 0); 
    for (const std::string& word : words) {
        insert(word);
    }
    // Assign order/depth after creation for visualization
    assignOrderAndDepth(root, nullptr, nextOrder = 0, nextOrderDisplay = 0);
}

std::vector<std::string> Trie::getAllWords() {
    std::vector<std::string> words;
    getAllWordsRecursive(root, "", words);
    return words;
}

void Trie::getAllWordsRecursive(TrieNode* node, std::string currentPrefix, std::vector<std::string>& words) {
    if (!node) return;

    if (node->isEndOfWord) {
        words.push_back(currentPrefix);
    }

    for (auto const& [key, val] : node->children) {
        getAllWordsRecursive(val, currentPrefix + key, words);
    }

}


void Trie::assignOrderAndDepth(TrieNode* node, TrieNode* parent, int& currentOrder, int& currentOrderDisplay) {
    if (!node) return;

    node->order = currentOrder++;
    node->orderDisplay = currentOrderDisplay;
    node->depth = (parent) ? parent->depth + 1 : 0; 
	

   
    std::vector<char> sortedKeys;
    for (auto const& [key, val] : node->children) {
        sortedKeys.push_back(key);
    }
    std::sort(sortedKeys.begin(), sortedKeys.end());
    int cnt = 0;
    for (char key : sortedKeys) {
        if (cnt >= 1)
            currentOrderDisplay++;
        assignOrderAndDepth(node->children[key], node, currentOrder, currentOrderDisplay);
        cnt++;

    }


}


void Trie::collectNodesInfoRecursive(TrieNode* node, int parentOrder, std::vector<TrieNodeInfo>& infoList) {
    if (!node) return;

    TrieNodeInfo info;
    info.order = node->order;
	info.orderDisplay = node->orderDisplay;
    info.parentOrder = parentOrder;
    info.depth = node->depth;
    info.character = node->character;
    info.isEndOfWord = node->isEndOfWord;
    infoList.push_back(info);


    std::vector<char> sortedKeys;
    for (auto const& [key, val] : node->children) {
        sortedKeys.push_back(key);
    }
    std::sort(sortedKeys.begin(), sortedKeys.end());

    for (char key : sortedKeys) {
        collectNodesInfoRecursive(node->children[key], node->order, infoList);
    }

}

std::vector<Trie::TrieNodeInfo> Trie::getNodesInfo() {
    std::vector<TrieNodeInfo> infoList;
    // Ensure order/depth are assigned first if needed (might be done after modifications)
    assignOrderAndDepth(root, nullptr, nextOrder = 0, nextOrderDisplay = 0);
    collectNodesInfoRecursive(root, -1, infoList); // Root has no parent (-1)
    // Sort by order to match AVL tree's inorder-like output for visualization state
    std::sort(infoList.begin(), infoList.end(), [](const TrieNodeInfo& a, const TrieNodeInfo& b) {
        return a.order < b.order;
        });
    return infoList;
}


void Trie::recordSnapshot(std::vector<TrieSnapshot>& snapshots,
    const std::string& operation,
    TrieNode* currentNode,
    char currentChar)
{
    // Re-assign orders and depths before capturing state if modifications happened
    assignOrderAndDepth(root, nullptr, nextOrder = 0, nextOrder = 0);
	for (int i = 0; i < snapshots.size(); i++) {
		TrieSnapshot snapshot = snapshots[i];


	}
    TrieSnapshot snapshot;
    snapshot.operation = operation;
    snapshot.currentNodeOrder = (currentNode) ? currentNode->order : -1;
    snapshot.currentChar = currentChar;
    snapshot.nodesInfo = getNodesInfo(); // Capture the current state of all nodes

    snapshots.push_back(snapshot);
}

// --- Snapshot Function Implementations ---

void Trie::insertSnapshotHelper(TrieNode*& node, const std::string& word, int index, std::vector<TrieSnapshot>& snapshots) {
    if (index == word.length()) {
        if (!node->isEndOfWord) {
            node->isEndOfWord = true;
            recordSnapshot(snapshots, "mark_end", node, '\0');
        }
        else {
            // Optional: record snapshot indicating word already exists
            recordSnapshot(snapshots, "already_exists", node, '\0');
        }
        return;
    }

    char c = word[index];
    recordSnapshot(snapshots, "traverse", node, c);

    // If using fixed array: int childIndex = getCharIndex(c); TrieNode*& nextNode = node->children[childIndex];
    TrieNode*& nextNode = node->children[c]; // Use reference for potential creation

    if (nextNode == nullptr) {
        nextNode = new TrieNode(c, node->depth + 1);
        // Record snapshot *after* creation and re-ordering
        recordSnapshot(snapshots, "create_node", nextNode, c);
    }

    insertSnapshotHelper(nextNode, word, index + 1, snapshots);
}


Trie::TrieSnapshot Trie::getSnapshot()
{
	TrieSnapshot snapshot;
	snapshot.operation = "initial";
	snapshot.currentNodeOrder = -1;
	snapshot.currentChar = '\0';
	snapshot.nodesInfo = getNodesInfo();
	return snapshot;
    
}

std::vector<Trie::TrieSnapshot> Trie::insertSnapshots(const std::string& word) {
    std::vector<TrieSnapshot> snapshots;
    if (word.empty()) return snapshots;

    // Start snapshotting from root
    TrieNode* current = root; // Use a non-reference variable for the initial call
    insertSnapshotHelper(current, word, 0, snapshots);

    // Final snapshot showing the completed state
    recordSnapshot(snapshots, "end_insert", nullptr, '\0');
    return snapshots;
}

bool Trie::searchSnapshotHelper(TrieNode* node, const std::string& word, int index, std::vector<TrieSnapshot>& snapshots) {
    if (!node) return false; // Should not happen if starting from root

    recordSnapshot(snapshots, "traverse", node, (index < word.length()) ? word[index] : '\0');

    if (index == word.length()) {
        if (node->isEndOfWord) {
            recordSnapshot(snapshots, "found_word", node, '\0');
            return true;
        }
        else {
            recordSnapshot(snapshots, "found_prefix_not_word", node, '\0');
            return false;
        }
    }

    char c = word[index];
    // If using fixed array: int childIndex = getCharIndex(c); TrieNode* nextNode = node->children[childIndex];
    auto it = node->children.find(c);
    if (it == node->children.end()) {
        recordSnapshot(snapshots, "not_found", node, c);
        return false;
    }

    return searchSnapshotHelper(it->second, word, index + 1, snapshots);
}


std::vector<Trie::TrieSnapshot> Trie::searchSnapshots(const std::string& word) {
    std::vector<TrieSnapshot> snapshots;
    if (word.empty()) return snapshots;
    searchSnapshotHelper(root, word, 0, snapshots);
    // Final snapshot
    recordSnapshot(snapshots, "end_search", nullptr, '\0');
    return snapshots;
}


// --- Remove Implementation (Basic - No Snapshots Yet) ---
// Snapshotting remove is complex because node deletion changes structure significantly.

bool Trie::hasChildren(TrieNode* node) {
    // If using map:
    return !node->children.empty();
    // If using fixed array:
    // for(int i=0; i<ALPHABET_SIZE; ++i) {
    //     if (node->children[i]) return true;
    // }
    // return false;
}

Trie::TrieNode* Trie::removeRecursive(TrieNode* node, const std::string& word, int depth, bool& removedAny) {
    if (!node) return nullptr;

    // If last character of the word is being processed
    if (depth == word.length()) {
        if (node->isEndOfWord) {
            node->isEndOfWord = false; // Unmark the word
            removedAny = true;
            // If node has no children, it can be deleted.
            if (!hasChildren(node)) {
                delete node;
                node = nullptr;
            }
        }
        return node;
    }

    // Recurse for the next character
    char c = word[depth];
    // If using fixed array: int index = getCharIndex(c); node->children[index] = removeRecursive(...);
    auto it = node->children.find(c);
    if (it != node->children.end()) {
        it->second = removeRecursive(it->second, word, depth + 1, removedAny);
        // If the recursive call deleted the child node
        if (it->second == nullptr) {
            node->children.erase(it); // Remove entry from map
        }
    }


    // After recursion, check if the current node can be deleted:
    // It should not be the end of another word and should have no children.
    if (node != root && !node->isEndOfWord && !hasChildren(node) && removedAny) {
        delete node;
        node = nullptr;
    }

    return node;
}


void Trie::remove(const std::string& word) {
    if (word.empty()) return;
    bool removedAny = false; 
    root = removeRecursive(root, word, 0, removedAny);

    if (root == nullptr) {
        root = new TrieNode('\0', 0);
    }

    assignOrderAndDepth(root, nullptr, nextOrder = 0, nextOrderDisplay = 0);
}


Trie::TrieNode* Trie::removeRecursiveSnapshot(TrieNode* node, const std::string& word, int index, std::vector<TrieSnapshot>& snapshots, bool& deletedNode) {
    if (!node) {
        
        deletedNode = false;
        return nullptr;
    }

    recordSnapshot(snapshots, "remove_traverse", node, (index < word.length() ? word[index] : '\0'));

  
    if (index == word.length()) {
        if (node->isEndOfWord) {
            node->isEndOfWord = false;
            recordSnapshot(snapshots, "remove_unmark_end", node, '\0');
    
            if (!hasChildren(node)) {
                recordSnapshot(snapshots, "remove_delete_leaf", node, '\0');
                delete node;
                deletedNode = true; 
                return nullptr; 
            }
            else {
                deletedNode = false; 
                return node; 
            }
        }
        else {
 
            recordSnapshot(snapshots, "remove_word_not_found_at_end", node, '\0');
            deletedNode = false; 
            return node;
        }
    }


    char c = word[index];
    auto it = node->children.find(c);
    if (it == node->children.end()) {

        recordSnapshot(snapshots, "remove_path_not_exist", node, c);
        deletedNode = false;
        return node;
    }

    TrieNode* childNode = it->second;
    bool childDeleted = false;
    TrieNode* resultNode = removeRecursiveSnapshot(childNode, word, index + 1, snapshots, childDeleted);


    if (childDeleted) {
        node->children.erase(it); 
        recordSnapshot(snapshots, "remove_update_parent_link", node, c);
    }

    if (node != root && !node->isEndOfWord && !hasChildren(node) && childDeleted) { 
        recordSnapshot(snapshots, "remove_delete_intermediate", node, '\0');
        delete node;
        deletedNode = true;
        return nullptr;
    }
    else {
        deletedNode = false; 
        return node;
    }
}


std::vector<Trie::TrieSnapshot> Trie::removeSnapshots(const std::string& word) {
    std::vector<TrieSnapshot> snapshots;
    if (word.empty() || !root) return snapshots;

    bool deleted = false; 

    removeRecursiveSnapshot(root, word, 0, snapshots, deleted);
    recordSnapshot(snapshots, "end_remove", nullptr, '\0');
    return snapshots;
}