/*ADVANCED PROGRAMMING IN C++
  ASSIGNMENT 7 BY ABUBAKAR MUGHAL (1725225)

  The original code can be found in the github repository 

  The following program will:
  1. Reads a JSON file (input.json) into a json object.
  2. Modifies the JSON data: changes the value of the "name" field and adds/updates
     a "timestamp" field with the current time.
  3. Writes the modified JSON data back to a new file (output.json) which is automatically created by the program.

  To run the program:
   1. Create a sample input.json file with the following code to test the program:
       {
          "name": "Original Name",
          "age": 25
       }
   2. Place the json.hpp file in the project directory
   3. Compile and run
*/

#include <iostream>
#include <fstream>
#include <iomanip> // for setting the precision of the output.
#include <chrono>  //  for time measurement.
#include "json.hpp"

using json = nlohmann::json;
using namespace std::chrono;

// Mark the function parameters that should not be modified as const references
void readAndModifyJson(const std::string &inputFile, const std::string &outputFile)
{
    std::ifstream inFile(inputFile, std::ios::in);
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

    std::ofstream outFile(outputFile, std::ios::out);
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
    const std::string inputFile = "input.json";
    const std::string outputFile = "output.json";
    constexpr int iterations = 1000; // Marked as constexpr since it is a compile-time constant

    // Use auto for start and end to let the compiler deduce the correct type
    const auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        readAndModifyJson(inputFile, outputFile);
    }

    const auto end = high_resolution_clock::now(); // to get the current time before and after the function execution.
    const duration<double> duration = end - start;

    std::cout << "JSON modification completed in "
              << std::fixed << std::setprecision(5) // to format the output to 5 decimal places.
              << (duration.count() / iterations) << " seconds per iteration." << std::endl;

    return 0;
}

/* 
   The average CPU time of the original code is 0.00079 seconds
   The average CPU time of the optimized code is 0.00072 seconds
   Hence, performance gains have been achieved*/
