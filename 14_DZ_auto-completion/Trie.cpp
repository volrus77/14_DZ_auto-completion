#include "Trie.h"
#include <string>
using namespace std;
//bool exit_ = false;
//Возвращет новый узел с пустыми детьми
TrieNode* getNewNode()
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key)
{
    // ваш код
    TrieNode* current = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        if (!current->children[index])   // если нет потомка с таким индексом,
            current->children[index] = getNewNode(); // создаём его

        current = current->children[index];  // спускаемся в дочерний узел
    }

    // помечаем последний узлел как лист, т.е. конец слова
    current->isEndOfWord = true;
}

// Возвращает true если ключ есть в дереве, иначе false
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

// Возвращает true если root имеет лист, иначе false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое
    if (!root)
        return nullptr;
    // Если дошли до конца ключа
    if (depth == key.size()) {
        // Этот узел больше не конец слова
        // поэтому снимаем метку
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        // Если ключ не является префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Пока не дошли до конца ключа или определили, 
    // что его нет в дереве, рекурсивно вызываем для ребенка
    // соответствующего символа
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // возвращаем новый корень
    return root;
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    // Если дерево пустое
    if (!root)
        return;
    findAllWords(root, buf, ind, res);// нашёл все слова

    std::string res2;  // строка для самого короткого уникального префикса

    std::string::iterator l = res.begin();        //  левое
    std::string::iterator c = nextWord(res, l);   // текущее
    std::string::iterator r = nextWord(res, c);   // правое

    findMinPrefixesInner(c, l, c, res2); // случай для первого слова

    while (r != res.end()) // итерация по всем кроме, первого и последнего 
    {
        findMinPrefixesInner(l, c, r, res2);  // поиск для 'c'- current
        l = c;    // переназначаем по кругу
        c = r;
        r = nextWord(res, r);  // добавляем следующий правый элемент
    }

    findMinPrefixesInner(l, c, l, res2);  // случай для последнего слова

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

    int count = (cL > cR) ? cL : cR; // выбираем больший из двух

    for (int i = 0; i <= count; ++i)
    {
        if (*center != ' ')  // но не более длины самого слова
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
    // Если дерево пустое
    if (!root)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])  // если есть ребёнок под этим номером
        {
            TrieNode* current = root->children[i]; // переходим к ребёнку
            buf[ind] = 'a' + i;  // сохраняяем в буфере текущую букву

            // если дошли до конца слова
            if (current->isEndOfWord)
            {
                for (int i = 0; i <= ind; ++i) // запись слова
                    res = res + buf[i];

                res = res + " ";  //
            }
            findAllWords(current, buf, ind + 1, res);
        }
    }

}

TrieNode* findSubRoot(TrieNode* root, char buf[])
{
    if (strlen(buf) == 0)  // если нет ни одной буквы в buf[]
        return root;

    int ind = strlen(buf);
    TrieNode* current = root;
    for (int i = 0; i < ind; ++i)
    {
        // вычисляем индекс в алфавите через смещение отнсительно первой буквы
        int index = buf[i] - 'a';
        if (current->children[index])   // если есть ребёнок под этим номером
        {
            current = current->children[index];
        }
        else
            return nullptr; // если буква есть а слова нет
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