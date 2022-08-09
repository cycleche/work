#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	cout << "argument num = " << argc << endl;
	for(int i = 0; i < argc; ++i)
	{
		cout << "the " << i << " argument is " << argv[i] << endl;
	}
	return 0;
}
