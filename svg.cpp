#include "svg.h"


void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}


void
svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y <<"' width='"<< width <<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}


void
svg_text(double left, double baseline, string text) {
   cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";

}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    const auto MAX_ASTERISK = (IMAGE_WIDTH - TEXT_WIDTH)/10;

    size_t max_bin = bins[0];
    for (size_t bin : bins) {
        if (max_bin < bin) {
            max_bin = bin;
        }
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        double height = bin;
        if (max_bin > MAX_ASTERISK) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "aqua");
        top += BIN_HEIGHT;
    }

    svg_end();
}
