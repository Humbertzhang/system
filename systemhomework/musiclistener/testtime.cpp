#include <iostream>
#include <sys/time.h>

using namespace std;

int main()
{
	timeval tv;
	gettimeofday(&tv,NULL);
	cout << tv.tv_usec << endl;

	return 0;
}
