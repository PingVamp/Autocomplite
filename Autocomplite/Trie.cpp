#include <iostream>
#include "Trie.h"

using namespace std;

// ��������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
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
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false 
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
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
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

bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

//����������� ������� ������ ���� ������ �� �������� ����. pref ��� �������� ���������� ��� ������
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

//������� ������ �������������� ����. ��������� ���� �� �������� ������� � ����� � ������� suggestionsRec 
//������� ������ �� ���������� ������� ������� �������� ����� 
void printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root; //���� ��� ������� �� ��������� ��������
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = (int)query[level] - 97;

        if (!pCrawl->children[index])
        {
            std::cout << "��� ������ ��������" << std::endl;
            return;
        }

        pCrawl = pCrawl->children[index];
    }

    bool isWord = (pCrawl->isEndOfWord == true);
    bool isLast = isLastNode(pCrawl);

    if (isWord && isLast) //���� ������� �������� ������ � �� ��� �� ������� ������ ��������, �� ������� ��� �������
    {
        cout << query << endl;
        return;
    }
    if (!isLast)        //���� ������ ������� ����, �� ���������� suggestionsRec ��� ������ ����
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return;
    }
}