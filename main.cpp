#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
using namespace std;
#include <string.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>

int main(){
    string input; //declaring variables
    string username;
    string enterinput = "";

    std::vector<std::string> inputList;
        
        username = getenv("USER"); //taking username
        username.append(" >>> ");
        cout << username;
        getline(cin, input); //taking first input from the user
    	const char* ccinput = input.c_str();
    	
    	if (inputList.size() == 15){
                	inputList.erase(inputList.begin()); //if command history list size reaches 15 remove first one
                
                }
    	inputList.push_back(input); //append command to command history list

        while (1){
            if (input == "exit"){ //if user inputs exit command program terminates
                    exit(0);
                }

            pid_t  pid = fork(); //creating child process
            if (pid < 0){
                exit(0);
            }

            else if (pid == 0){ //starting child process

                if (input == ""){ //if user presses enter take another input
                    exit(0);                    
                }

                if (input == "listdir"){ //call ls command
                    execlp("ls", "ls", NULL);
                    exit(0);                    
                }

                if (input == "mycomputername"){ //call hostname command to print username
                    execlp("hostname", "hostname", NULL);
                    exit(0);
                }

                if (input == "whatsmyip"){ //call hostname -i command to print ip address
                    execlp("hostname", "hostname", "-i", (char *)0);
                    exit(0);
                }

                if ((input.rfind("printfile", 0) == 0) && (input.find(">") == string::npos)){
                    
                    std::string firstword = input.substr(0, input.find(" "));
                    std::string secondword = input.substr(input.find(" ")+1, -1); //second word is file name                   
                    
                    std::ifstream t(secondword);
                    std::string str((std::istreambuf_iterator<char>(t)),
                                    std::istreambuf_iterator<char>());

                    std::stringstream test(str);
                    std::string line;
                    std::vector<std::string> textlines;

                    int i = 0;

                    while(std::getline(test, line, '\n'))
                    {
                        textlines.push_back(line); //split file line by line and push to a list
                    }
                    
                    const char* ccenterinput = enterinput.c_str();
                    while (1){
                    pid_t  pidp = fork();
                    if (enterinput == ""){

                        if (pidp < 0){
                            exit(0);
                        }

                        else if (pidp == 0){
                            cout << textlines[i]; //print text file line by line
                            exit(0);
                        }

                        else{
                            wait(NULL);
                            i += 1;
                            if (i == textlines.size()){ //check if text file ends
                                cout << endl;
                                exit(0);
                            }                            
                           
		                    getline(cin, enterinput);
		                    const char* ccenterinput = enterinput.c_str();                           
                        }
                    }

                    else{
                        exit(0);
                    }

                    }                   
                }


                if ((input.rfind("printfile", 0) == 0) && (input.find(">") != string::npos)){
                    
                    std::stringstream test(input);
                    std::string line1;
                    std::vector<std::string> textlines1;
                
                    while(std::getline(test, line1, ' '))
                    {
                    	textlines1.push_back(line1);
                    }

                    const char* file1 = textlines1[1].c_str(); //take first file name
                    const char* file2 = textlines1[3].c_str(); //take second file name

                    execlp("cp", "cp", file1, file2, (char *)0);
                    exit(0);
                }

                if ((input.find("dididothat") != string::npos)){ //check if command is in history

                    std::string secondword = input.substr(input.find(" ")+1, -1);
                    secondword.erase(0, 1); //remove quote characters
		            secondword.erase(secondword.size() - 1);		    
                    
                    if ((input.find(" ") == string::npos)){
                        cout << "No" << endl;
                            exit(0);
                    }

                    else if(std::find(inputList.begin(), inputList.end(), secondword) != inputList.end()) { 
                        cout << "Yes" << endl; //if command is in input history print yes

                   	exit(0);
                    }

                    else{
                        cout << "No" << endl; //if command is not in input history print no
                        exit(0);
                    }                            
                }

                if (input == "hellotext"){ //opening gedit program
                    execlp("gedit", "gedit", NULL);
                }               
            }

            else{
                wait(NULL);
                cout << username;
                getline(cin, input);              
                        
                const char* ccinput = input.c_str();
                
                if (inputList.size() == 15){
                	inputList.erase(inputList.begin());          
                }
        
                inputList.push_back(input);
            }
        }
    
    return 0;
}
