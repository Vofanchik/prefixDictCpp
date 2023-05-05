#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#define ALPHABET_SIZE 26

struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode* getNewNode(void);
TrieNode* remove(TrieNode*, std::string, int depth = 0);

bool search(TrieNode* root, std::string key);
bool isEmpty(TrieNode*);

void insert(TrieNode* root, std::string key);
void substitution(TrieNode* root, std::vector<std::string>& result, std::string currentWord);
void residue(TrieNode* root, char buf[], int indexChar, std::vector<std::string>& result, int& counterWords, bool endWord);
void output_all_strings(TrieNode* current);
TrieNode* search_str(TrieNode* root, std::string key);



