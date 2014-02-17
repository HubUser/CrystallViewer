#include <fstream>
#include <utils.h>

namespace Utils {
	using namespace std;
	string readFile(string aFileName) {
		ifstream is(aFileName.c_str(), ifstream::in);
		if (!is) {
			return string();
		}
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char *buffer = new char[length];
        is.read(buffer, length);

        is.close();  // unsafe

        return string(buffer);
	}
}