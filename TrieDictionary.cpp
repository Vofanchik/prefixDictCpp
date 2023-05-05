#include "TrieDictionary.h"
#include <vector>
#include <string.h>

TrieNode* getNewNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

void insert(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';

        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    node->isEndOfWord = true;
}

bool search(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

TrieNode* search_str(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return nullptr;

        node = node->children[index];
    }

    return node;
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;

    return true;
}

TrieNode* remove(TrieNode* root, std::string key, int depth)
{
    if (!root)
        return nullptr;

    if (depth == key.size()) {

        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    return root;
}

std::string output = "";
void output_all_strings(TrieNode* current)
{
    
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (current->children[i] != nullptr)
        {
            output.push_back('a' + i);
            if (current->children[i]->isEndOfWord)
            {
                output.push_back(' ');
                std::cout << output << "\n";
                continue;
            }
            output_all_strings(current->children[i]);

        }
    }
}

void substitution(TrieNode* root, std::vector<std::string>& result, std::string currentWord) 
{
    if (!root) 
        return;

        
    char buf[100]; 
    int indexChar = 0; 
    int counterWords = 0; 
    
    while (indexChar < currentWord.length()) 
    {

        for (int i = 0; i < ALPHABET_SIZE; ++i) 
        {
            if (root->children[i]) 
            {
                if (currentWord[indexChar] == i + 'a') 
                {
                    buf[indexChar] = i + 'a';  
                    indexChar++;               
                    root = root->children[i]; 


                    i = ALPHABET_SIZE;
                    if (root->isEndOfWord && indexChar == currentWord.length()) 
                    {
                        buf[indexChar] = '\0'; 
                        result.push_back(buf); 
                        counterWords++;                  

                    }
                    else if (indexChar == currentWord.length()) 
                    {
                        buf[indexChar] = '\0';            
                        result.push_back(buf); 

                    }

                }
            }
        }
    }
    if (counterWords == 0)  
        result.clear();      
    residue(root, buf, indexChar, result, counterWords, false);

}
void residue(TrieNode* root, char buf[], int indexChar, std::vector<std::string>& result, int& counterWords, bool endWord)
{
    if (endWord) 
    {
        buf[indexChar] = '\0'; 
        result.push_back(buf);
        counterWords++;                
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        //if (counterWords >= 5) 
        //    return;
        if (root->children[i]) 
        {
            buf[indexChar] = i + 'a';
            endWord = root->children[i]->isEndOfWord;
            residue(root->children[i], buf, indexChar + 1, result, counterWords, endWord);
        }
    }
}