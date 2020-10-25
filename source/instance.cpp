#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <fstream>

using namespace std;

// <path> <file> <port>
int main(int argc, char const *argv[]){

    if(argc < 2){
        return 2;
    }
    string path = argv[1];
    if(chdir((char*)path.c_str())){
        return -2;
    }

    string js_file = "npm start";
    if(argc > 2){
        js_file = "node ";
        js_file += argv[2];
    }

    string PORT = "";
    if(argc > 3){
        PORT = "PORT=";
        PORT += argv[3];
    }
    string log_file = "";
    if(argc > 4){
        log_file =  " &>> ";
        log_file += argv[4];
    }

    string command = PORT+" "+js_file+log_file;
    while(system((char*)command.c_str())!=1);
    return 0;
}
