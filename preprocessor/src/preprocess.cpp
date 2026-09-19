//this is the preprocessor

#include "preprocess.h"



//MacroTable
MacroTable::MacroTable(){
	
}

std::string MacroTable::search(std::string key){
	
}

void MacroTable::define(std::string key, std::string value){

}

void undefine(std::string key){

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




