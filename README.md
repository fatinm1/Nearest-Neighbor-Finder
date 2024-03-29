KDTree Nearest Neighbor Finder

The KDTree Nearest Neighbor Finder is a C++ program designed to efficiently find the nearest geographical point of interest (POI) based on a given query location using a KD-Tree. This documentation covers the implementation details, setup instructions, and usage of the program.

Program Overview

The program is structured into several files to organize functionality logically and make the codebase easier to navigate. Here is an overview of the key components:

location.h: Defines the GeoPoint class representing a geographical point with latitude and longitude, the KDTree class for the KD-Tree implementation, and utility functions for distance calculations and brute-force nearest neighbor search.

location.cpp: Implements the KDTree class's methods, including insertion, nearest neighbor search, and utility functions defined in location.h.

driver.cpp: Contains the main function, which demonstrates how to use the KDTree to insert geographical points and find the nearest POI to a user-specified location.

mytest.cpp: Provides an example of how to conduct basic unit tests on the KDTree implementation, including insertion correctness and nearest neighbor search accuracy.

location.html and location.css: (Optional) A basic HTML and CSS setup for a potential web interface to interact with the KDTree Nearest Neighbor Finder. Implementation of the web interface's functionality would require additional backend integration not covered in this documentation.

Features
Efficient Nearest Neighbor Search: Leverages a KD-Tree for efficient spatial search, significantly improving performance over brute-force methods for large datasets.

Geographical Point Representation: Includes a GeoPoint class that simplifies the handling of geographical locations with latitude and longitude.

Accuracy: Includes functions to calculate the distance between geographical points accurately, considering the Earth's curvature.

Extendability: Designed with modularity in mind, allowing for easy integration into larger systems or expansion with additional features, such as bulk insertion or range queries.

Setup Instructions
Prerequisites: Ensure you have a C++ compiler installed on your system (e.g., GCC, Clang, MSVC) and that it supports C++11 or later, as the program uses features introduced in C++11.

Compilation: Navigate to the directory containing the source files and compile them. For example, using GCC, you could run:
g++ -std=c++11 -o KDTreeFinder driver.cpp location.cpp mytest.cpp

This command compiles the source files and links them into an executable named KDTreeFinder.

Running Tests: To run the provided tests, compile mytest.cpp along with location.cpp, substituting driver.cpp with mytest.cpp in the compilation command. It's recommended to run these tests to verify the correctness of the KD-Tree implementation.

Usage
After compiling the program, you can run it to perform nearest neighbor searches. The driver.cpp file is set up to accept user input for a query location (latitude and longitude) and then uses the KDTree to find and display the nearest POI.

Example Run
./KDTreeFinder

Follow the prompts to enter a latitude and longitude when the program runs. The program will output the nearest POI's latitude and longitude based on the provided locations.

Extending the Program
Web Interface: To create a web interface for the program, you would need to set up a server-side application (e.g., using Node.js, Flask, or Django) that interacts with the C++ KDTree implementation. The provided location.html and location.css files can serve as a starting point for the frontend.

Additional Features: Consider adding features like bulk insertions, deletion, and range queries to enhance the KDTree's functionality.

Contributions
Contributions to the KDTree Nearest Neighbor Finder are welcome. Whether it's bug fixes, improvements to the existing code, or new features, please feel free to fork the repository, make your changes, and submit a pull request.

MIT License

Copyright (c) [year] [full name]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
