#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
using namespace std;
using std::filesystem::directory_iterator;
void checkiffileisok(vector<string>& Files);
char filenamestart[] = "pacman_";
char filenamefinish[] = ".screen";
const int SizeToCheck = 6;

void main() {
    string path = "./";
    vector<string> GameFiles;
    for (const auto& file : directory_iterator(path))
    {
        GameFiles.push_back(file.path().filename().string()); // Add file's name to vector.
        checkiffileisok(GameFiles); //check if file format is ok
    }
    

    //sort vector.
    //make search function.
}

void checkiffileisok(vector<string>& Files)
{
    string last = Files[Files.size() - 1];
    int namesize = last.size(), i, j = SizeToCheck;
    for (i = 0; i < SizeToCheck; i++,namesize--, j--)
    {
        if ((last[i] != filenamestart[i]) || (last[namesize - 1] != filenamefinish[j]))
        {
            Files.pop_back();
            return;
        }
    }
    
}


//hamikra hou helek mehaluah!!!!!
//itamar - lo nitan lageshet lamikra - mimush = array of positions (3x20)
//godel hkovetz - amudot - lefi harishona -   shurot  - lefi EOF getline aharon.