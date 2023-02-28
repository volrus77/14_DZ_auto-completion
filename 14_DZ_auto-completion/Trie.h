#pragma once
#include <iostream>

const int ALPHABET_SIZE = 26;

// Структура узла дерева
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};

// Возвращет новый узел с пустыми детьми
// Возвращает новый узел с пустыми детьми
TrieNode* getNewNode();

bool search(struct TrieNode* root, std::string key);
void insert(TrieNode* root, std::string key);
bool isEmpty(TrieNode* root);
TrieNode* remove(TrieNode* root, std::string key, int depth = 0);
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res);
void findAllWords(TrieNode* root, char buf[], int ind, std::string& res);
void findMinPrefixesInner(std::string::iterator left, std::string::iterator center, std::string::iterator right,
    std::string& out);
std::string::iterator nextWord(std::string& str, std::string::iterator it);
TrieNode* findSubRoot(TrieNode* root, char buf[]);

void enterStartWord(char buf[]);
void outputRes(std::string& out);
void choiseAutoCompletion(std::string& out);
void toFillTrei(TrieNode* root);