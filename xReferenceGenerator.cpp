#include "stdafx.h"
#include "linkedlist.h"

#include "hashtable.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

//These languages are supported.
enum typeStr{C, CPP, JAVA, PYTHON, CSHARP, JS, RUBY, LUA, NONE};

//Numbers the lines of a file
void numberLines(string input){
	ofstream outputFile;
	ifstream inputFile;

	inputFile.open(input);
	outputFile.open("output.txt");
	
	//Make sure the file exists first, or the program will break
	if(inputFile.is_open()){
		string line;
		int lineCount = 1;

		//getline grabs the entire line from inputFile, and moves pointers for you.  
		while(getline(inputFile, line)){
			outputFile << lineCount << " " << line << endl;
			lineCount++;
		}
	}
	else{
		cout << "File not found" << endl;
		return;
	}

	cout << "File written" << endl;

	inputFile.close();
	outputFile.close();

}

//Hashing function
unsigned int myHash (string key, int sizeOfStorage) {
     unsigned int hashval = 0;
	 for(size_t i = 0; i < key.length(); i++){
              hashval += key[i];
	 }
    return hashval % sizeOfStorage;
 }

//This converts the string from the extension to a enum value
typeStr strConversion(string extension){
		if (extension == "c" || extension == "h"){
			return C;
		}
		else if (extension == "cpp"){
			return CPP;
		}
		else if (extension == "java" || extension == "class"){
			return JAVA;
		}
		else if (extension == "py"){
			return PYTHON;
		}
		else if (extension == "cs"){
			return CSHARP;
		}
		else if (extension == "js"){
			return JS;
		}
		else if (extension == "rb"){
			return RUBY;
		}
		else if (extension == "lua"){
			return LUA;
		}
		else{
			return NONE;
		}
}


int main(int argc, char* argv[])
{
	
	string* reserved;		//We hold the language in this pointer
	string extension = "";	//This holds the filetype
	//Call from the command line
	if (argc > 1){

		//These arrays hold reserved words for each language.
		//C
		string cReserved[84] = {"auto", "if", "break", "int", "case", "long", "char", "register", "continue", "return", "default", "short", "do", "sizeof", "double", 
				"static", "else", "struct", "entry", "switch", "extern", "typedef", "float", "union", "for", "unsigned", "goto", "while", "enum", 
				"void", "const", "signed", "volatile"};
		//C++
		string cppReserved[84] = {"alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", 
				"case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "constexpr", "const_cast", "continue",
				"decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", 
				"float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
				"nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", 
				"sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef", 
				"typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"};
		//Java
		string jReserved[84] = {"abstract", "continue", "for", "new", "switch", "assert", "default", "goto", "package", 
				"synchronized", "boolean", "do", "if", "private", "this", "break", "double", "implements", "protected", "throw", 
				"byte", "else", "import", "public", "throws", "case", "enum", "instanceof", "return", "transient", "catch", "extends", 
				"int", "short", "try", "char", "final","inter", "face static", "void", "class", "finally", "long stric", "tfp", "volatile", 
				"const", "float", "native", "super", "while"};
		//Python
		string pyReserved[84] = {"and", "del", "from", "not", "while", "as", "elif", "global", "or", "with", "assert", "else", "if",
				"pass", "yield", "break", "except", "import", "print", "class", "exec", "in", "raise", "continue", "finally", "is", "return",
				"def", "for", "lambda", "try", };
		//C#
		string csResevered[84] = {"abstract", "as", "base", "bool", "break", "byte", "case", "catch", "char", "checked", "class", "const", 
				"continue", "decimal", "default", "delegate", "do", "double", "else", "enum", "event", "explicit", "extern", "false", "finally",
				"fixed", "float", "for", "foreach", "goto", "if", "implicit", "in", "int", "interface", "internal", "is", "lock", "long", "namespace",
				"new", "null", "object", "operator", "out", "override", "params", "private", "protected", "public", "readonly", "ref", "return", "sbyte",
				"sealed", "short", "sizeof", "stackalloc", "static", "string", "struct", "switch", "this", "throw", "true", "try", "typeof", "uint", "ulong",
				"unchecked", "unsafe", "ushort", "using", "virtual", "void", "volatile", "while"};
		//Javascript
		string jsReserved[84] = {"break", "case", "catch", "continue", "debugger", "default", "delete", "do", "else", "finally", "for", "function", "if",
				"in", "instanceof", "new", "return", "switch", "this", "throw", "try", "typeof", "var", "void", "while", "with"};
		//Ruby
		string rbReserved[84] = {"alias", "and", "BEGIN", "begin", "break", "case", "class", "def", "defined", "do", "else", "elsif", "END", "end", "ensure",
				"false", "for", "if", "in", "module", "next", "nil", "not", "or", "redo", "rescue", "retry", "return", "self", "super", "then", "true", "undef", 
				"unless", "until", "when", "while", "yield"};
		//Lua
		string luaReserved[84] = {"and", "break", "do", "else", "elseif", "end", "false", "for", "function", "if", "in", "local", "nil", "not", "or", "repeat", 
				"return", "then", "true", "until", "while"};

		
		//Number the input file
		numberLines(argv[1]);
		//Extract extension from file.
		extension = argv[1];
		int index = extension.find_last_of(".") + 1;
		extension = extension.substr(index, extension.length());

		//Loads the proper language array.
		switch(strConversion(extension)){
			case C:
				reserved = cReserved;
				break;
			case CPP:
				reserved = cppReserved;
				break;
			case JAVA:
				reserved = jReserved;
				break;
			case PYTHON:
				reserved = pyReserved;
				break;
			case CSHARP:
				reserved = csResevered;
				break;
			case JS:
				reserved = jsReserved;
				break;
			case RUBY:
				reserved = rbReserved;
				break;
			case LUA:
				reserved = luaReserved;
				break;
			default:
				//If there isn't a recognized language, the reserved bank is empty
				cout << "Language not recognized." << endl;
				cout << "I'll try my best anyway." << endl;
				string defReserved[84];
				for (int i = 0; i < 84; i++){
					defReserved[i] = "";
				}
				reserved = defReserved;
				break;
			}
		}

	else{
		//Load a default file
		numberLines("input.txt");
		string defReserved[84];
		for (size_t i = 0; i < 84; i++){
			defReserved[i] = "";
		}
		reserved = defReserved;
	}

	//The table of reserved words
	hashtable<string> resTable(89);

	//Hashing the reserved words
	for (size_t i = 0; i < 84; i++){
		resTable.insert(reserved[i]);
	}
	//Read in our output file
	ifstream programIn;
	programIn.open("output.txt");

	if (programIn.is_open()){
		
		//Our hash table for the reference file
		//Reference index[257];
		hashtable<Reference> index;
		
		//This cleans up the tokens from each line.
		regex re("[^\\w\\]\\[#.<>]+");

		//Read through the file
		string currentLine;	
		while(getline(programIn, currentLine)){

			//Breaks the current line into a vector of tokens
			vector<string> tokens;
			istringstream iss(currentLine);								   
			copy(istream_iterator<string>(iss),istream_iterator<string>(), back_inserter<vector<string>>(tokens));
		
			//We run this for every token in the line
			for(size_t i = 1; i < tokens.size(); i++){	
				string token = regex_replace(tokens.at(i), re, "");
				if(!resTable.contains(token)){
					//int key = myHash(token, 257);
					//If the reference is there already, we need to add just the line number and sort the vector.
					if (index.contains(token)){
						//Make sure that it wasn't already marked on this line
						if(find(index[token].locations.begin(), index[token].locations.end(), stoi(tokens.at(0))) == index[token].locations.end()){
							index[token].locations.push_back(stoi(tokens.at(0)));
							}
						}
					//We don't have the reference already
					else{
						//Create a new Reference
						Reference newEntry = Reference(token);
						newEntry.locations.push_back(stoi(tokens.at(0)));
						index.insert(newEntry);
					}
				}
			}	

		}
		//Our finished file
		ofstream programOut;
		programOut.open("index.txt");

		index.print();

		//We move the hash table into a vector for sorting
		vector<Reference> alphabetize;

		for(size_t i = 0; i < 257; i++){
			if (index[i].name != "NULL" && index[i].name != ""){
				alphabetize.push_back(index[i]);
			}
		}
		//Because of the < operator of the reference class, this produces an alpha ordered vector
		sort(alphabetize.begin(), alphabetize.end());

		//Output our vector to console and file.
		for(size_t i = 0; i < alphabetize.size(); i++){
			//cout << alphabetize.at(i).name << " :: ";
			programOut << alphabetize.at(i).name << " :: ";
			for (size_t j = 0; j < alphabetize.at(i).locations.size(); j++){
			//	cout << alphabetize.at(i).locations.at(j) << " ";
				programOut << alphabetize.at(i).locations.at(j) << " ";
			}
			//cout << endl;
			programOut << endl;
		}
		cout << "Index file written" << endl;
		programIn.close();
		programOut.close();
	}
	else{
		cout << "File missing!" << endl;
	}

	system("PAUSE");
	return 0;
	
}