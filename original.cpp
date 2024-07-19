#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "json.hpp"

using json = nlohmann::json;
using namespace std::chrono;

void readAndModifyJson(std::string &inputFile, std::string &outputFile)
{
    std::ifstream inFile(inputFile);
    if (!inFile.is_open())
    {
        std::cerr << "Could not open input file." << std::endl;
        return;
    }

    json j;
    inFile >> j;
    inFile.close();

    // Modify JSON data
    if (j.contains("name"))
    {
        j["name"] = "Modified Name";
    }
    else
    {
        j["name"] = "New Name";
    }

    j["timestamp"] = std::time(nullptr);

    std::ofstream outFile(outputFile);
    if (!outFile.is_open())
    {
        std::cerr << "Could not open output file." << std::endl;
        return;
    }

    outFile << std::setw(4) << j << std::endl;
    outFile.close();
}

int main()
{
    std::string inputFile = "input.json";
    std::string outputFile = "output.json";

    int iterations = 1000; // Increase iterations to make timing more significant
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        readAndModifyJson(inputFile, outputFile);
    }

    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;

    std::cout << "JSON modification completed in "
              << std::fixed << std::setprecision(5)
              << (duration.count() / iterations) << " seconds per iteration." << std::endl;

    return 0;
}
