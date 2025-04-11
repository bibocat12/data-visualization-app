#pragma once

#include <vector>
#include <string>
#include <map> 
#include <algorithm>



class Trie {
public:
    Trie();
    ~Trie();

    
    void insert(const std::string& word);
    bool search(const std::string& word);
    bool startsWith(const std::string& prefix);
    void remove(const std::string& word);
    void create(const std::vector<std::string>& words);
    void clear();
	
    std::vector<std::string> getAllWords();

    
    struct TrieNodeInfo {
        int order = -1;     
		int orderDisplay = -1;
        int parentOrder = -1; 
        int depth = -1;       
        char character = '\0';
        bool isEndOfWord = false;
    };

  
    std::vector<TrieNodeInfo> getNodesInfo();

   
    struct TrieSnapshot {
        std::string operation;    
        int currentNodeOrder = -1; 
        char currentChar = '\0';   
        std::vector<TrieNodeInfo> nodesInfo; 
      
    };

    TrieSnapshot getSnapshot();

    std::vector<TrieSnapshot> insertSnapshots(const std::string& word);
    std::vector<TrieSnapshot> searchSnapshots(const std::string& word);
    std::vector<TrieSnapshot> removeSnapshots(const std::string& word); // Complex

private:
    struct TrieNode {
        
        std::map<char, TrieNode*> children;
     
        bool isEndOfWord;
        int order; 
        int orderDisplay;
        int depth; 
        char character; 

        TrieNode(char ch = '\0', int d = 0) : isEndOfWord(false), order(-1), orderDisplay(-1), depth(d), character(ch) {
        }

        ~TrieNode() {
        }
    };

    TrieNode* root;
    int nextOrder; 
	int nextOrderDisplay;


    void clearRecursive(TrieNode* node);


    void getAllWordsRecursive(TrieNode* node, std::string currentPrefix, std::vector<std::string>& words);


    void assignOrderAndDepth(
        TrieNode*& node, 
        TrieNode* parent, 
        int& currentOrder,
        int& currentOrderDisplay);


    void collectNodesInfoRecursive(TrieNode* node, int parentOrder, std::vector<TrieNodeInfo>& infoList);


    TrieNode* removeRecursive(TrieNode* node, const std::string& word, int depth, bool& removedAny);

    TrieNode* removeSnapshot(TrieNode* node, const std::string& word, int index, std::vector<TrieSnapshot>& snapshots, bool& deletedNode);


    // Helper to check if a node has any children
    bool hasChildren(TrieNode* node);

    // Snapshot recording helper
    void recordSnapshot(std::vector<TrieSnapshot>& snapshots,
        const std::string& operation,
        TrieNode*& currentNode,
        char currentChar = '\0');


  
    void insertSnapshot(TrieNode*& node, const std::string& word, int index, std::vector<TrieSnapshot>& snapshots);
    bool searchSnapshot(TrieNode* node, const std::string& word, int index, std::vector<TrieSnapshot>& snapshots);


};