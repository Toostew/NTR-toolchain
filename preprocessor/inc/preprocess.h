//this is the preprocess

#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

class PreProcessor {
	public:
		PreProcessor();
		void processFile(string inputFile, string outputFile);
	
	private:
		MacroTable macroTable;
};


class MacroTable {
	public:
		MacroTable();
		string linearSearch(string key); //search the map linearly for a key, return its value
		
	private:
		unordered_map<string, string> hashMap;
		
		
};


#endif