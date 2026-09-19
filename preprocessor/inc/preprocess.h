//this is the preprocess

#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>


struct fileEntry{
	std::string fileName;
	std::unique_ptr<std::ifstream> fileStream;
};

enum class directiveType {
	INCLUDE,
	DEFINE,
	UNDEFINE,
	NON_DIRECTIVE
};


class MacroTable {
	public:
		MacroTable();
		std::string search(std::string key); //search the map linearly for a key, return its value
		void define(std::string key, std::string value); //populate with entry
		void undefine(std::string key); //remove entry



	private:
		std::unordered_map<std::string,std::string> hashmap;

		
		
};


class PreProcessor {
	public:
		PreProcessor();
		void processFile(std::string inputFile, std::string outputFile); //this is the function that actually does shit


	
	private:
		MacroTable macroTable; //macrotable instance
		std::vector<fileEntry> fileEntryStack; //psuedostack using a vector instead

		directiveType getLineDirective(std::string line); //figures out what type of directive the line is


		void includeHandler(std::string line); //function to handle include directives
		void defineHandler(std::string line);  //handles defines
		void undefineHandler(std::string line); //handles undefines

		std::string expandMacro(std::string line);
		std::string stripComment(std::string line);
};





#endif