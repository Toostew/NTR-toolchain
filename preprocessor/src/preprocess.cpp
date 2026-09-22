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

std::vector<std::string> MacroTable::getMacros() {
	std::vector<std::string> macros;

	for (std::pair<std::string,std::string> entry : hashmap) {
		macros.push_back(entry.first);
	}

	return macros;
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

	if (bufferFirst == "#include") {
		return directiveType::INCLUDE;
	}
	else if (bufferFirst == "#define") {
		return directiveType::DEFINE;
	}
	else if (bufferFirst == "#undefine") {
		return directiveType::UNDEFINE;
	} else {
		return directiveType::NON_DIRECTIVE;
	}

}

//search the stack for the file. If it exists, 1. Otherwise 0
//there should never be multiple of the same file to prevent cycles
bool PreProcessor::searchFileEntryStack(std::string fileName) {

	//const is like a declaration to say we will not modify anything related to fileEntry, and Auto& is reference to whatever variable this is (automatically detect)
	for (const auto& fileEntry : fileEntryStack) {
		if (fileEntry.fileName == fileName) {
			return true;
		}
	}
	return false;
}


void PreProcessor::includeHandler(std::string line) {
	std::string buffer;
	std::istringstream lineStream(line);

	lineStream >> buffer >> buffer; //skip the #include, we should get a file name.
	//at this point buffer should be populated with the name of the file,
	//RULE: no quotations allowed for now (check readme)

	//check for filename in stack
	if (!PreProcessor::searchFileEntryStack(buffer)) {
		//perfectly fine, continue on

		std::unique_ptr<std::ifstream> openFileStream = std::make_unique<std::ifstream>(buffer);

		//check to see if the file opens, hence actually exists/readable
		if (!openFileStream->is_open()) {
			//error, exit out
			std::cerr << "Could not open file " << buffer << std::endl;
			exit(20); //code 20 is special code for unable to open file
		}

		//file is actually openable, so we can add it to the stack
		fileEntry wrapperEntry = {buffer, std::move(openFileStream)};

		fileEntryStack.push_back(std::move(wrapperEntry));




	} else {
		//cycle detected, should error out
		std::cerr << "Cycle detected for: " << buffer << ", quitting"<< std::endl;
		exit(10); //code 10 is special code for cycles
	}
};

void PreProcessor::defineHandler(std::string line) {
	std::string key;
	std::string value;
	std::istringstream lineStream(line);

	lineStream >> key >> key; //skip the #define, we should get a file name.
	//read pointer now lies on the first whitespace beyond the key.
	//everything past this point is considered as the value, except trailing whitespace
	std::getline(lineStream, value);
	size_t start = value.find_first_not_of("\t"); //find the first non-whitespace character


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

		directiveType type = getLineDirective(buffer);

		switch(type) {
			case directiveType::INCLUDE:
				includeHandler(buffer);
				break;
			case directiveType::DEFINE:
				defineHandler(buffer);
				break;
			case directiveType::UNDEFINE:
				undefineHandler(buffer);
				break;
			case directiveType::NON_DIRECTIVE:
				//here we do macro expansion.


				break;

		}

	}

}

std::string PreProcessor::expandMacro(std::string line) {
	//this function expands the macro from its compact to full form
	//we have to check the ENTIRE macrotable and search the line for each entry




}

std::string PreProcessor::stripComment(std::string line) {
	//if it starts with a "//", like this comment, remove the remainder of the line
	//be careful because we only need to remove it wherever the // begins, till end of line

}






