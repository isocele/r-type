
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <sstream>
#include <vector>

int main () {

	std::ifstream is ("stage1.txt", std::ifstream::binary);
	if (is) {
		// get length of file:
		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		char * buffer = new char [length];

		is.read (buffer,length);

		if (is){
			std::stringstream test;
			test.str (buffer);
			std::string segment;
			std::vector<std::string> seglist;
			
			while(std::getline(test, segment, '\n'))
			{
				std::cout<<segment<<"\n";
				seglist.push_back(segment);
			}
		} else
			std::cout << "error: only " << is.gcount() << " could be read";
		is.close();

		delete[] buffer;
	}
	return 0;
}
