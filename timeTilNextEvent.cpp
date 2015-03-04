#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main ()
{
    srand (time (0));

    while (1)
    {
	cout << (1 + rand () % 6) << endl;
    }

    return 0;
}
