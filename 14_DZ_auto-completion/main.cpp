// 14_DZ_auto-completion.cpp : 

#include "Trie.h"

bool exit_ = false;
void menuExit();

int main()
{
	TrieNode* Root = getNewNode();  // создаём корень префисного дерева
	toFillTrei(Root);  // заполняем дерево
	
	while (!exit_)
	{
		char start[15]{};  // для начальных букв слова
		enterStartWord(start);

		// находим указатель на поддерево
		TrieNode* subRoot = findSubRoot(Root, start);
		char buf[15]{};
		strcpy_s(buf, start);
		std::string res;

		// ищем все слова поддерева
		findAllWords(subRoot, buf, strlen(buf), res);
		
		outputRes(res);
		choiseAutoCompletion(res);
		menuExit();
	}
	return 0;
}

void menuExit()
{
	char op;
	do
	{
		std::cout << "Choise the number : " << std::endl;
		std::cout << "0 - exit" << std::endl;
		std::cout << "1 - continue" << std::endl;
		std::cin >> op;
	} while (op != '0' && op != '1');
	if (op == '0')
		exit_ = true;
}
