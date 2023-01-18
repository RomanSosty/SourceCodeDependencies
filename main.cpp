#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void printDependencies(vector<string> &dependencies, string input)
{
    sort(dependencies.begin(), dependencies.end());
    auto temp = unique(dependencies.begin(), dependencies.end());
    dependencies.erase(temp, dependencies.end());

    cout << "Je potřeba zkompilovat tyto soubory: " << input << ",";
    for (string i : dependencies)
    {
        cout << i << ",";
    }
}

void searchDependencies(multimap<string, string> &m, string input, vector<string> &dependencies)
{
    multimap<string, string>::iterator i;
    for (i = m.begin(); i != m.end(); ++i)
    {
        if (input == i->second)
        {
            dependencies.push_back(i->first);
            searchDependencies(m, i->first, dependencies);
        }
    }
}

void readFile(string str, multimap<string, string> &m)
{
    ifstream myfile("SmallProject.txt");
    vector<string> numbers;

    if (myfile.is_open())
    {
        while (myfile)
        {
            myfile >> str;
            if (str != "->")
            {
                numbers.push_back(str);
            }
        }
        myfile.close();
    }
    else
        cout << "Nelze otevřít soubor";

    // naplnění multimap, hodnotami z vektoru
    for (int i = 0; i < numbers.size() - 1; i++)
    {
        string key = numbers[i];
        i++;
        string value = numbers[i];
        m.insert(pair<string, string>(key, value));
    }
}

int main()
{
    //překlep dependencies
    string str;
    vector<string> dependecies;
    multimap<string, string> m;
    string input;

    cout << "Zadejte číslo změného souboru: ";
    cin >> input;

    readFile(str, m);
    searchDependencies(m, input, dependecies);
    printDependencies(dependecies, input);

    return 0;
}