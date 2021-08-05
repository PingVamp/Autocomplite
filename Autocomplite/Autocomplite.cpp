// Autocomplite.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "Trie.h"
#include <string>

int main()
{
    std::cout << "Hello World!\n";
    setlocale(LC_ALL, "Russian");

    struct TrieNode* root = getNewNode();
    insert(root, "hello");
    insert(root, "dog");
    insert(root, "hell");
    insert(root, "cat");
    insert(root, "a");
    insert(root, "hal");
    insert(root, "fun");
    insert(root, "fungus");
    insert(root, "fear");
    insert(root, "feature");
    insert(root, "feat");

    bool exit = false;
    string pref;
    string buff;
    while (!exit)
    {
        std::cout << "Начните вводить слова. Нажмите enter для вывода списка вариантов конца слова." << std::endl;
        std::cout << "Введите clear для начала ввода нового слова." << std::endl;
        std::cout << "Введите new для начала добавления нового слова в словарь." << std::endl;
        std::cout << "Введите exit для выхода" << std::endl;
        cout << pref;
        cin >> buff;
        pref += buff;
        if (buff == "exit")
        {
            exit = true; 
            continue;
        }
        if (buff == "clear")
        {
            pref.clear();
            continue;
        }
        if (buff == "new")
        {
            std::cout << "Введите новое слово." << std::endl;
            cin >> buff;
            insert(root, buff);
            pref.clear();
            continue;
        }
        printAutoSuggestions(root, pref);
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
