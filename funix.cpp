// Author: Xiaoyun Wang

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "funix.h"

using namespace std;

void cd(Funix *funix, int argCount, const char *arguments[])
  // calls cd() with currentDirectory as one of its parameters
{
    funix->currentDirectory = funix->currentDirectory->cd(argCount, arguments); 
}

int eXit(Funix *funix, int argCount, const char *arguments[])
  // checks "exit" command, returns 0 on proper exit
{
    if (argCount != 0)
    {
	cout<<"usage: exit"<<endl;
        return 1;
    } else return 0;
}

void getCommand(Funix *funix, char *command)
  // writes prompt and reads command
{
    writePrompt(funix);
    fgets(command, COMMAND_LENGTH, stdin);
}

void init(Funix *funix)
  // creates currentDirectory, and sets umask and time
{
    funix->currentDirectory = new Directory;
    funix->time  = 0;
    funix->umask = 0;
    funix->currentDirectory->createDirectory("/",NULL,funix->umask,funix->time);
}

void ls(Funix *funix, int argCount, const char *arguments[])
  // calls ls() with currentDirectory as one of its parameters
{
    funix->currentDirectory->ls(argCount, arguments);
}

void mkdir(Funix *funix, int argCount, const char *arguments[])
  // calls mkdir() with currentDirectory as one of its parameters
{
    funix->currentDirectory->mkdir(argCount, arguments, 7-funix->umask, funix->time);
/*if(funix->currentDirctory->numSubDir>=3) 
  {
  	cout<<finix->currentDirectory->name <<"already contains the maximum number of directories"<<endl;
  	return;
  }
  
  else {
    
    	for(i=0; i<funix->currentDirectory -> numSubDir;i++)
    	  {
    	  	if(funix->currentDirectory ->subDirectory[i] -> name ==arguments[0])
			  {
			  cout<<"cannot create directory"<<funix->currentDirectory -> subDirectory[i]-> name<<": File exists"<<endl; 
			  return;
		      }
		  }
    	Directory temp_pointer = new Directory * [funix->currentDirectory->numSubDir+1];
    	if(funix->currentDirectory ->numSubDir!=0)
    	  {memcpy(temp_pointer,funix->currentDirectory->subDirectory,sizeof(Directory *) * funix->currentDirectory->numSubDir)
    	  delete[] funix->currentDirectory->subDirectory; 
    	  }
    	  funix->currentDirectory->subDirectory=temp_pointer;
    	  temp_pointer[funix->currentDirectory->numSubDir]=new Directory;
    	  funix->currentDirectory->numSubDir ++;
	}*/
}

int processCommand(Funix *funix, char *command)
  // returns 0 on proper exit
{
    //cout<<"Input command: "<<command;
    const char **arguments=new const char*[MAX_ARGUMENTS+1];
    char *temp_str = new char[COMMAND_LENGTH+1];
    int argC = 0;
    //bool in_str = false;
    int current = 0;
    for (unsigned int i=0;i<strlen(command);i++)
    {
        if (command[i]==' ' || command[i]=='\n')
        {
            //in_str=false;//if (command[i]!='\n') current=0;
            if (current!=0)
            {
                arguments[argC]=new char[current+1];
                temp_str[current]='\0';
                memcpy((void*)arguments[argC],temp_str,sizeof(char)*current+1);
                //arguments[argC][current]='\0';
                argC++;
                current=0;
            }
        } else {
            temp_str[current]=command[i];
            current++;
            //in_str=true;
        }
    }
    /*if (current!=0)
    {
        arguments[argC]=new char[current+1];
        temp_str[current]='\0';
        memcpy((void*)arguments[argC],temp_str,sizeof(char)*current+1);
        //arguments[argC][current]='\0';
        argC++;
    }*/
    //cout<<argC<<" tokens: ";
    //for (int i=0;i<argC;i++) cout<<arguments[i]<<"|";
    //cout<<endl;

    funix->time++;
    int return_value = 1;
    if (strcmp(arguments[0],"exit")==0)
        return_value = eXit(funix, argC-1, &arguments[1]);
    else if (strcmp(arguments[0],"cd")==0)
        cd(funix,argC-1, &arguments[1]);
    else if (strcmp(arguments[0],"ls")==0)
        ls(funix,argC-1, &arguments[1]);
    else if (strcmp(arguments[0],"mkdir")==0)
        mkdir(funix,argC-1, &arguments[1]);
    else if (strcmp(arguments[0],"umask")==0)
        umask(funix,argC-1, &arguments[1]);
    else cout<<arguments[0]<<": Command not found."<<endl;
 
    for (int i=0;i<argC;i++)
    {
        delete[] arguments[i];arguments[i]=NULL;
    }   
    delete[] temp_str;temp_str=NULL;
    delete[] arguments;arguments=NULL;
    return return_value;
}

void run(Funix *funix)
  // reads and processes commands in a loop until proper exit
{
    bool to_continue = true;
    char* command = new char[COMMAND_LENGTH+1];
    init(funix);
    while (to_continue)
    {
      getCommand( funix,command );
      if (processCommand( funix, command )==0) to_continue=false;
    } 
}

void umask(Funix *funix, int argCount, const char *arguments[])
  // checks "umask" command and executes it if it is proper
{
    //printf(">umask< running...\n");
    if (argCount!=1) {cout<<"usage: umask octal"<<endl;return;}
    int temp=atoi(arguments[0]);
    if (temp<0 || temp>7) {cout<<"umask: octal must be between 0 and 7"<<endl;return;}
    funix->umask = temp;
}

void writePrompt(Funix *funix)
  // shows path and '#'
{
    funix->currentDirectory->showPath();
    printf(" # ");
}

