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

//scans the line for a directive.
//anything that doesn't immediately start with # is branded as NON_DIRECTIVE
directiveType PreProcessor::getLineDirective(std::string line) {
	std::string bufferFirst;
	std::string bufferRemainder;

	std::istringstream lineStream(line);

	lineStream >> bufferFirst; //load the first non-whitespaced full word

	if (bufferFirst.compare("#include")) {
		return directiveType::INCLUDE;
	}
	else if (bufferFirst.compare("#define")) {
		return directiveType::DEFINE;
	}
	else if (bufferFirst.compare("#undefine")) {
		return directiveType::UNDEFINE;
	} else {
		return directiveType::NON_DIRECTIVE;
	}

}

void PreProcessor::includeHandler(std::string line) {
	std::string buffer;
	std::istringstream lineStream(line);

	lineStream >> buffer >> buffer; //skip the #include, we should get a file name.
	//at this point buffer should be populated with the name of the file
};

void PreProcessor::defineHandler(std::string line) {
	std::string key;
	std::string value;
	std::istringstream lineStream(line);

	lineStream >> key >> key; //skip the #define, we should get a file name.
	//read pointer now lies on the first whitespace beyond the key.
	//everything past this point is considered as the value, except trailing whitespace
	std::getline(lineStream, value);
	size_t start = value.find_first_of("\t"); //find the first non-whitespace character
	if (start != std::string::npos) {
		value = value.substr(start);
	} else {
		value.clear(); // The value was just whitespace
	}

	PreProcessor::macroTable.define(key, value);


};

//remove the value associated with the stated key
void PreProcessor::undefineHandler(std::string line) {
	std::string key;
	std::istringstream lineStream(line);

	lineStream >> key >> key;

	PreProcessor::macroTable.undefine(key);
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




