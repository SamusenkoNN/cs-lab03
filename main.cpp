#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "histogram.h"
#include "svg.h"

using namespace std;



vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt) {
    Input data;

    if (prompt)
        cerr << "enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "enter bin count: ";
    cin >> data.bin_count;
    return data;
}

vector<size_t> make_histogram(Input input)
{
    double min, max;
    find_minmax(input.numbers, min, max);
    double bin_size = (max - min) / input.bin_count;
    vector<size_t> bins(input.bin_count, 0);
    for (size_t i = 0; i < input.numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < input.bin_count - 1 && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
    if (lo <= input.numbers[i] && input.numbers[i] < hi)
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[input.bin_count - 1]++;
        }
    }
    return bins;
}


void
show_histogram_text(const vector<size_t>& bins)
{

    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bins;
    max_bins = bins[0];

    for (size_t bin : bins)
    {
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }

    for (size_t bin : bins)
    {
        double height = bin;
        if (max_bins > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins);
        }


        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t zv = 0; zv < height; zv++)
        {
            cout << "*";
        }
        cout << endl;
    }
}


int main(int argc, char* argv[])
{
    if (argc > 1) {
        for(int i=0; i<argc; i++){
            cout<<"argv["<<i+1<<"]= "<<argv[i]<<endl;
        }
        return 0;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    const auto data = read_input(cin, true);

    const auto bins = make_histogram(data);

    show_histogram_svg(bins);


}
