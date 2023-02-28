#include "Trie.h"
#include <string>
using namespace std;
//bool exit_ = false;
//��������� ����� ���� � ������� ������
TrieNode* getNewNode()
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
    // ��� ���
    TrieNode* current = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        if (!current->children[index])   // ���� ��� ������� � ����� ��������,
            current->children[index] = getNewNode(); // ������ ���

        current = current->children[index];  // ���������� � �������� ����
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    current->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false
bool search(struct TrieNode* root, std::string key)
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

// ���������� true ���� root ����� ����, ����� false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������
    if (!root)
        return nullptr;
    // ���� ����� �� ����� �����
    if (depth == key.size()) {
        // ���� ���� ������ �� ����� �����
        // ������� ������� �����
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� ����� ��� ����������, 
    // ��� ��� ��� � ������, ���������� �������� ��� �������
    // ���������������� �������
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // ���� � ����� ��� ��������� �����
    // (������ ������ ���� ��� �������� �������),
    // � �� �� ������������� ������ ������.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // ���������� ����� ������
    return root;
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    // ���� ������ ������
    if (!root)
        return;
    findAllWords(root, buf, ind, res);// ����� ��� �����

    std::string res2;  // ������ ��� ������ ��������� ����������� ��������

    std::string::iterator l = res.begin();        //  �����
    std::string::iterator c = nextWord(res, l);   // �������
    std::string::iterator r = nextWord(res, c);   // ������

    findMinPrefixesInner(c, l, c, res2); // ������ ��� ������� �����

    while (r != res.end()) // �������� �� ���� �����, ������� � ���������� 
    {
        findMinPrefixesInner(l, c, r, res2);  // ����� ��� 'c'- current
        l = c;    // ������������� �� �����
        c = r;
        r = nextWord(res, r);  // ��������� ��������� ������ �������
    }

    findMinPrefixesInner(l, c, l, res2);  // ������ ��� ���������� �����

    res = res2;
}

std::string::iterator nextWord(std::string& str, std::string::iterator it)
{
    if (str.empty())
        ;
    //return;

    while (*it != ' ' && it != str.end())
    {
        it++;
    }
    it++;
    return it;
}

void findMinPrefixesInner(std::string::iterator left, 
    std::string::iterator center,
    std::string::iterator right, std::string& out)
{
    std::string::iterator copyCenter1 = center;
    std::string::iterator copyCenter2 = center;

    int cL = 0;
    while (*left == *copyCenter1)
    {
        left++;
        copyCenter1++;
        cL++;
    }

    int cR = 0;
    while (*right == *copyCenter2)
    {
        right++;
        copyCenter2++;
        cR++;
    }

    int count = (cL > cR) ? cL : cR; // �������� ������� �� ����

    for (int i = 0; i <= count; ++i)
    {
        if (*center != ' ')  // �� �� ����� ����� ������ �����
        {
            out = out + *center;
            center++;
        }
        else
            break;
    }
    out = out + ' ';
}

void findAllWords(TrieNode* root, char buf[], int ind, string& res)
{
    // ���� ������ ������
    if (!root)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])  // ���� ���� ������ ��� ���� �������
        {
            TrieNode* current = root->children[i]; // ��������� � ������
            buf[ind] = 'a' + i;  // ���������� � ������ ������� �����

            // ���� ����� �� ����� �����
            if (current->isEndOfWord)
            {
                for (int i = 0; i <= ind; ++i) // ������ �����
                    res = res + buf[i];

                res = res + " ";  //
            }
            findAllWords(current, buf, ind + 1, res);
        }
    }

}

TrieNode* findSubRoot(TrieNode* root, char buf[])
{
    if (strlen(buf) == 0)  // ���� ��� �� ����� ����� � buf[]
        return root;

    int ind = strlen(buf);
    TrieNode* current = root;
    for (int i = 0; i < ind; ++i)
    {
        // ��������� ������ � �������� ����� �������� ����������� ������ �����
        int index = buf[i] - 'a';
        if (current->children[index])   // ���� ���� ������ ��� ���� �������
        {
            current = current->children[index];
        }
        else
            return nullptr; // ���� ����� ���� � ����� ���
    }
    return current;
}

void enterStartWord(char buf[])
{
    char st[15]{};
    std::cout << "Enter the begining of the word : ";
    std::cin >> st;

    for (int i = 0; i < strlen(st); ++i)
        buf[strlen(buf)] = st[i];
}

void outputRes(std::string& out)
{
    if (out.length() == 0)
    {
        std::cout << "There are no words" << std::endl;
        return;
    }
    int count = 0;
    for (int i = 0; i < out.length();)
    {
        std::cout << ++count << " ";
        while (out[i] != ' ')
        {
            std::cout << out[i++];
        }
        std::cout << std::endl;
        i++;
    }
}

void choiseAutoCompletion(std::string& out)
{
    char op[5]{};
    std::cout << "Choise the number of the word : ";
    std::cin >> op;
    int count = 1;
    for (int i = 0; i < out.length();)
    {
        while (out[i] != ' ')
        {
            if (atoi(op) == count)
                std::cout << out[i];
            i++;
        }
        i++;
        count++;
    }
    std::cout << std::endl;
}

void toFillTrei(TrieNode* root)
{

    insert(root, "call");
    insert(root, "cat");
    insert(root, "cult");
    insert(root, "run");
    insert(root, "rut");

    insert(root, "dog");
    insert(root, "dot");
    insert(root, "dove");
    insert(root, "duck");
    insert(root, "zebra");

    insert(root, "a");
    insert(root, "answer");
    insert(root, "another");
    insert(root, "anotation");
    insert(root, "algo");
    insert(root, "hero");
    insert(root, "heroplane");
    insert(root, "the");

}