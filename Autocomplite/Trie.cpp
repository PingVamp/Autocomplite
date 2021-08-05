#include <iostream>
#include "Trie.h"

using namespace std;

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
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
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// Вохвращает true если root имеет лист, иначе false 
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

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
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

bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

//Рекурсивная функция вывода слов идущих из заданной ноды. pref для хранения информации для вывода
void suggestionsRec(struct TrieNode* root, string pref)
{
    if (root->isEndOfWord)
    {
        cout << pref;
        cout << endl;
    }

    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            pref += 97 + i;
            suggestionsRec(root->children[i], pref);
            pref.pop_back();
        }
    }
}

//Функция вывода автозаполнения слов. Проверяет есть ли заданный префикс и далее с помощью suggestionsRec 
//выводит идущие из последнего символа данного префикса слова 
void printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root; //Нода для прохода по заданному префиксу
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = (int)query[level] - 97;

        if (!pCrawl->children[index])
        {
            std::cout << "Нет такого префикса" << std::endl;
            return;
        }

        pCrawl = pCrawl->children[index];
    }

    bool isWord = (pCrawl->isEndOfWord == true);
    bool isLast = isLastNode(pCrawl);

    if (isWord && isLast) //Если префикс является словом и за ним не следует других символов, то выводим сам префикс
    {
        cout << query << endl;
        return;
    }
    if (!isLast)        //Если другие символы есть, то используем suggestionsRec для вывода слов
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return;
    }
}