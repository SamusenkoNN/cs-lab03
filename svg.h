#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <vector>
#include <iostream>
using namespace std;

void
bin_brightness(size_t bin_1, size_t bin_max, string& color);

void
svg_end();

void
svg_rect(double x, double y, double width, double height, string stroke, string fill);

void
svg_text(double left, double baseline, string text);

void
show_histogram_svg(const vector<size_t>& bins);


#endif // SVG_H_INCLUDED
