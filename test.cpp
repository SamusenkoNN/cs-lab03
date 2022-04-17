#include "histogram.h"
#include <cassert>
#include <string.h>
#include "svg.h"
using namespace std;
void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test1()
{
    double min=0;
    double max=0;
    find_minmax({-1,-2,-3},min,max);
    assert(max == -1);
    assert(min == -3);
}

void
test2()
{
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void
test3()
{
    double min = 0;
    double max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void
test4()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void
brightness_test_1()
{
    size_t bin_1=2;
    size_t bin_max=2;
    size_t color = 10 - ((bin_1 * 9) / bin_max);

    assert(color == 1);                            //самый тёмный цвет

}

void
brightness_test_2()
{
    size_t bin_1=1;
    size_t bin_max=9;
    size_t color = 10 - ((bin_1 * 9) / bin_max);

    assert(color== 9);                            //самый светлый цвет

}


main()
{
    test_positive();
    test1();
    test2();
    test3();
    test4();
    brightness_test_1();
    brightness_test_2();
}
