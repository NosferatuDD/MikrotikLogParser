#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
   // system("chcp 1251");
   // system("chcp 866");
    system("cls");

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

                if (line.find("login failure") != std::string::npos)
                {

                   // std::cout << line.find("login failure") << std::endl;
                    int a = 0, b = 0;
                    for(unsigned int i = line.find("login failure"), sc=0; i < line.length(); i++)

                    {
                        if (line[i] == ' ')sc++;
                        if (sc == 6 && a == 0) a = i;
                        if (sc == 7)
                        {
                            b = i;
                            break;
                        }
                    }

                    IpBlockStrings.insert("/ip firewall address-list add address="+ line.substr((a+1),(b - a)) +"list=IPBlock");
                }
            }
        }

        for (auto TekStr : IpBlockStrings)
            std::cout << TekStr << endl;
        fout.close();
    }

    system("pause");
    return 0;
}
