#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <fstream>
#include <list>

using namespace std;

void run_node(
  string _command // <path> <file> <port>
){
    string command = "./instance " + _command;
    system( (char*) command.c_str() );
}

int main(int argc, char const *argv[]){
    
    //open file 'instance.lines'
    ifstream f("./instance.lines", ios::in | ios::binary);

    if(!f.is_open()) return -1;

    //get size of the file
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    f.seekg(0);

    char buffer[size];
    
    //read file buffer
    f.read(buffer, size);
    f.close();

    list<string> lines;
    list<string>::iterator l;
    lines.emplace_back("");
    l = lines.end(); l--;

    for (size_t i = 0; i < size; i++)
    {
        if(buffer[i] == '\n'){
            lines.emplace_back("");
            l = lines.end(); l--; continue;
        }
        char str[2]; str[0] = buffer[i];
        *l += str;
    }
    
    thread threads[lines.size()];
    size_t t=0;

    for (l=lines.begin(); l!=lines.end(); l++)
    {
        //cout << (*l) << endl;
        threads[t++] = thread(run_node, *l);
    }

    t = 0;

    for (l=lines.begin(); l!=lines.end(); l++)
    {
        threads[t++].join();
    }
    

    //run_node("../node_app main1.js 8080");
    return 0;
}
