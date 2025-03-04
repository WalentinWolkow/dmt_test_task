#include <ctime>
#include <cstdlib>
#include <cmath>

int customRand(int xMax)
{
    return (int)lround(xMax / (double)RAND_MAX * rand());
}
