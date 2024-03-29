# KDTree Nearest Neighbor Finder

The KDTree Nearest Neighbor Finder is a C++ program designed to efficiently find the nearest geographical point of interest (POI) based on a given query location using a KD-Tree. This repository contains the source code and documentation for the program.

## Table of Contents
- Program Overview
- Features
- Setup Instructions
- Usage
- Extending the Program
- Contributions
- License

## Program Overview
The program is organized into several components to logically separate functionality and simplify navigation of the codebase:

- `location.h`: Defines the `GeoPoint` class for representing geographical points with latitude and longitude, the KDTree class for the KD-Tree implementation, and utility functions for distance calculations and brute-force nearest neighbor search.

- `location.cpp`: Implements the methods of the KDTree class, including insertion, nearest neighbor search, and utility functions declared in `location.h`.

- `driver.cpp`: Contains the main function demonstrating how to use the KDTree to insert geographical points and find the nearest POI for a user-specified location.

- `mytest.cpp`: Provides examples of how to perform basic unit tests on the KDTree implementation, including tests for insertion correctness and nearest neighbor search accuracy.
