KDTree Nearest Neighbor Finder

The KDTree Nearest Neighbor Finder is a C++ program designed to efficiently find the nearest geographical point of interest (POI) based on a given query location using a KD-Tree. This repository contains the source code and documentation for the program.

Table of Contents

Program Overview
Features
Setup Instructions
Usage
Extending the Program
Contributions
License
Program Overview
The program is organized into several components to logically separate functionality and simplify navigation of the codebase:

location.h: Defines the GeoPoint class for representing geographical points with latitude and longitude, the KDTree class for the KD-Tree implementation, and utility functions for distance calculations and brute-force nearest neighbor search.

location.cpp: Implements the methods of the KDTree class, including insertion, nearest neighbor search, and utility functions declared in location.h.

driver.cpp: Contains the main function demonstrating how to use the KDTree to insert geographical points and find the nearest POI for a user-specified location.

mytest.cpp: Provides examples of how to perform basic unit tests on the KDTree implementation, including tests for insertion correctness and nearest neighbor search accuracy.

location.html and location.css: Offers a basic HTML and CSS setup for a potential web interface to interact with the KDTree Nearest Neighbor Finder. Note: Implementation of this web interface's functionality requires additional backend integration not covered in this documentation.

Features
Efficient Nearest Neighbor Search: Uses a KD-Tree for spatial search, significantly improving performance over brute-force methods for large datasets.
Geographical Point Representation: Includes a GeoPoint class that simplifies handling geographical locations.
Accuracy: Features functions for accurate distance calculations between geographical points, considering the Earth's curvature.
Extendability: Designed with modularity in mind, allowing easy integration into larger systems or addition of features like bulk insertion or range queries.
Setup Instructions
Prerequisites
Ensure you have a C++ compiler installed on your system (e.g., GCC, Clang, MSVC) that supports C++11 or later.

Compilation
Navigate to the directory containing the source files and compile them. For example, using GCC:

sh
Copy code
g++ -std=c++11 -o KDTreeFinder driver.cpp location.cpp mytest.cpp
This compiles the source files and links them into an executable named KDTreeFinder.

Running Tests
To run the provided tests, compile mytest.cpp along with location.cpp, substituting driver.cpp with mytest.cpp in the compilation command. Running these tests is recommended to verify the KD-Tree implementation's correctness.

Usage
After compiling the program, run it to perform nearest neighbor searches. driver.cpp is set up to accept user input for a query location and use the KDTree to find and display the nearest POI.

Example Run
