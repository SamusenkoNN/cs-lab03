#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "histogram.h"
#include "svg.h"
#include <sstream>
#include <string>

using namespace std;



vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt)
{
    Input data;

    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "Enter bin count: ";
    in >> data.bin_count;
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

    size_t max_count = bins[0];
    for (size_t bin : bins)
    {
        if (max_count < bin)
        {
            max_count = bin;
        }
    }
    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << " ";
        }
        cout << bin << "|";
        size_t height;
        if (max_count > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
        }
        else
        {
            height = bin;
        }
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    size_t data_size = item_size * item_count;
    buffer->write(static_cast<const char*>(items), data_size);
    return data_size;
}


Input
download(const string& address)
{
    curl_global_init(CURL_GLOBAL_ALL);

    stringstream buffer;

    CURL* curl = curl_easy_init();
    if (curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            exit(1);
        }
        curl_easy_cleanup(curl);
    }

    return read_input(buffer, true);

}


int
main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    Input input;
    bool is_format_svg=true;
    if (argc > 1)
    {
        string url;
        for(int i=1; i<argc; i++)
        {
            if(strstr(argv[i], "-format"))
            {
                if(!(strstr(argv[i+1], "text")) && !(strstr(argv[i+1], "svg")))
                {
                    cerr<<"Restart program and choose format of histogram: text or svg"<<endl;
                    cerr<<"Example for svg: "<<"lab03.exe -format svg http://... > marks.svg"<<endl;
                    cerr<<"Example for text: "<<"lab03.exe -format text http://... > marks.txt"<<endl;
                    return 0;

                }
                if(strstr(argv[i+1], "text"))
                {
                    is_format_svg=false;

                }

            }
            if (strstr(argv[i], "http://"))
            {
                url = argv[i];
            }
        }
        input = download(url);
    }
    else
    {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    is_format_svg ? show_histogram_svg(bins) : show_histogram_text(bins);
//    show_histogram_svg(bins);

}
