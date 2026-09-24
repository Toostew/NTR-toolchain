#include "main.h"

#include "preprocess.h"

int main (){
	std::cout << "this is a test 2" << std::endl;
	PreProcessor sample;
	sample.processFile("test.txt", "output.txt");

	return 0;
}
