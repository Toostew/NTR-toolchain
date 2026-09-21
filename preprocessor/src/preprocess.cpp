//this is the preprocessor

#include "preprocess.h"



//MacroTable
MacroTable::MacroTable(){
	
}

std::string MacroTable::search(std::string key){
	auto iterator = hashmap.find(key);

	if(iterator != hashmap.end()){
		return iterator->second; //returns the value associated with iterator->first
	} else {
		return ""; //there's probably a more reliable return than just straight blank
	}

}

void MacroTable::define(std::string key, std::string value){
	hashmap[key] = value; //define the value to macro table
}

void MacroTable::undefine(std::string key){
	hashmap.erase(key); //remove the std::pair of this key, which removes both key and value associated
}




//preprocessor
PreProcessor::PreProcessor(){
	
}

directiveType PreProcessor::getLineDirective(std::string line) {

}

void includeHandler(std::string line) {

};

void defineHandler(std::string line) {

};

void undefineHandler(std::string line) {

};

void PreProcessor::processFile(std::string inputFile, std::string outputFile){
	std::string buffer;

	//open inputStream and outputStream
	std::ofstream writeFile(outputFile);

	fileEntry wrappedEntry = {inputFile, std::make_unique<std::ifstream>(inputFile)};

	fileEntryStack.push_back(std::move(wrappedEntry)); //add entry to end of stack

	while(!fileEntryStack.empty()){
		fileEntry* currentEntry = &fileEntryStack.back();

		if(!std::getline(*currentEntry->fileStream, buffer)){
			//if getline returns nothing, we can move on
			fileEntryStack.pop_back();
			continue;
		}



	}




}




