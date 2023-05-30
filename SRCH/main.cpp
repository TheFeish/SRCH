#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <set>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::multimap;
using std::stringstream;
using std::smatch;
using std::regex;
using std::regex_search;
using std::pair;
using std::regex_constants::icase;
using std::set;
using std::numeric_limits;
using std::streamsize;

int question0_1(string message) {
    int temp = -1;
    cout << message << endl;
    while (temp != 0 && temp != 1) {
        cin >> temp;
        if (temp != 0 && temp != 1 || cin.fail()) {
            cout << "Ivedete neteisinga reiksme" << endl;
            temp = -1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return temp;
}

bool illegalChar(char c) {
    c = tolower(c);
    return !(c >= 'a' && c <= 'z');
}

void readFile(multimap<string, int>& words, set<string>& urls) {
    string file, temp, str, line;
    int failasParuostas = 0, lineNr = 0;
    ifstream input;
    while (failasParuostas == 0) {
        try {
            cout << "Pasirinkite duomenu faila: ";
            cin >> file;
            input.open(file);
            if (input.fail()) {
                throw "Pasirinktas failas neegzistuoja.";
            }
            failasParuostas = 1;
        }
        catch (const char* e) {
            cout << e << endl;
            if (question0_1("Ar norite bandyti skaityti faila is naujo? 0 - Ne, 1 - taip") == 0) {
                break;
            }
        }
    }
    if (failasParuostas == 1) {
        stringstream ss;
        while (getline(input, line)) {
            ss.clear();
            ss.str(line);
            while (ss >> str) {
                smatch matches;
                regex_search(str, matches, regex("(http://|https://)?www(.{1}[a-z0-9]+){2,}", icase));
                if (matches.length() > 0) { urls.insert(matches.str()); }
                for (auto c : str) {
                    if (illegalChar(c)) {
                        if (temp.length() > 0) {
                            words.insert(pair<string, int>(temp, lineNr));
                            temp.clear();
                        }
                    }
                    else {
                        temp.push_back(tolower(c));
                    }
                }
                if (temp.length() > 0) {
                    words.insert(pair<string, int>(temp, lineNr));
                    temp.clear();
                }
            }
            lineNr++;
        }
    }
    input.close();
}

int main()
{
    multimap<string, int> words;
    string stringOld = "", stringNew;
    set<string> urls;
    readFile(words, urls);
    ofstream output("output.txt");
    for (auto i : words) {
        stringNew = i.first;
        if (stringNew != stringOld) {
            output << endl << stringNew << " Count: " << words.count(stringNew) << " Lines: " << i.second;
        }
        else {
            output << " " << i.second;
        }
        stringOld = stringNew;
    }
    output << endl << endl << "Urls:" << endl;
    for (auto i : urls) {
        output << i << endl;
    }
    cout << endl << "Iveskite bet koki simboli norint isjungti programa" << endl;
    cin >> stringOld;
    cin.ignore();
    return 0;
}

