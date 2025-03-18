#include "Utils.h"

long long Utils::rand(long long l, long long r)
{
    long long res = 0;
    for (int i = 1; i <= 4; i++) {
        res = (res << 15) ^ (std::rand() & ((1 << 15) - 1));
    }
    return l + res % (r - l + 1);
}
