#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

void LoginFailureAddToSet (string line, std::set<string> &IpBlockStrings)
{
    stringstream ss(line);
    string token;
    vector<string> tokens;
    char delimiter = ' ';

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    if( tokens[3] == "login" && tokens[4] == "failure" )
    {
        IpBlockStrings.insert("/ip firewall address-list add address="+ tokens[9] +" list=IPBlock");
    }

}

int main(int argc, char *argv[])
{
   // system("chcp 1251");
   // system("chcp 866");
    system("cls");
// testh
    std::set<string> IpBlockStrings;

    if (argc >= 2)
    {
        std::string path(argv[1]);
        std::ifstream fout(path);

        if (fout.is_open())
        {
            std::string line;
            while (std::getline(fout, line))
            {
                LoginFailureAddToSet(line, IpBlockStrings);
            }
        }

        for (auto TekStr : IpBlockStrings)
            std::cout << TekStr << endl;
        fout.close();
    }

    system("pause");
    return 0;
}
