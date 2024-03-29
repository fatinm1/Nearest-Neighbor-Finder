#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <chrono>
#include "location.h"

using namespace std;
using namespace chrono;

void printTestResult(bool result, const string& testName) {
    cout << testName << ": " << (result ? "Passed" : "Failed") << endl;
}

GeoPoint generateRandomPoint() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> latDist(-90.0, 90.0);
    uniform_real_distribution<> lonDist(-180.0, 180.0);
    return GeoPoint(latDist(gen), lonDist(gen));
}

int main() {
    //Basic Testing
    KDTree tree;
    vector<GeoPoint> points = {
       // Edge case test points
        GeoPoint(0.0, 0.0),          //Equator and Prime Meridian intersection
        GeoPoint(0.0, 180.0), 
        GeoPoint(89.9999, -135.0),   // Slightly off the North Pole
        GeoPoint(-89.9999, 45.0),    // Slightly off the South Pole
        GeoPoint(0.1, 179.9),        // Near the International Date Line (east)
        GeoPoint(0.2, -179.9),       // Near the International Date Line (west)
        GeoPoint(90.0000, 0.0000),   // North Pole
        GeoPoint(89.9999, 0.0000),   // South Pole
        GeoPoint(-89.9999, 0.0000),
        GeoPoint(0.0, -50.0),         // Equator in the Atlantic Ocean
        GeoPoint(45.0, 0.0),           // Mid-latitude at Prime Meridian
        //Normal points
        GeoPoint(40.7128, -74.0060),  // New York
        GeoPoint(51.5074, -0.1278),   // London
        GeoPoint(35.6895, 139.6917),  // Tokyo
        GeoPoint(-33.8688, 151.2093), // Sydney, Australia
        GeoPoint(48.8566, 2.3522),    // Paris, France
        GeoPoint(-23.5505, -46.6333), // São Paulo, Brazil
        GeoPoint(55.7558, 37.6173),   // Moscow, Russia
        GeoPoint(28.6139, 77.2090),   // New Delhi, India
        GeoPoint(39.9042, 116.4074),  // Beijing, China
        GeoPoint(-34.6037, -58.3816), // Buenos Aires, Argentina
        GeoPoint(30.0444, 31.2357),   // Cairo, Egypt
        GeoPoint(1.3521, 103.8198),   // Singapore
        GeoPoint(59.3293, 18.0686),   // Stockholm, Sweden
        GeoPoint(37.7749, -122.4194), // San Francisco, USA
    };

    // Test insertion
    for (const auto& point : points) {
        tree.insert(point);
    }

    bool insertTestResult = (tree.getSize() == (int)points.size());
    printTestResult(insertTestResult, "Insert Test");

    // Test nearest neighbor search
    bool searchTestResult = true;
    for (const auto& testPoint : points) {
        GeoPoint nearestFromKDTree = tree.nearestNeighbor(testPoint);
        GeoPoint nearestFromBruteForce = findNearestPOIBruteForce(testPoint, points);

        if (!nearestFromKDTree.isApproximatelyEqual(nearestFromBruteForce)) {
            searchTestResult = false;
            cout << "Search Test Failed for Point: Latitude " << testPoint.latitude 
                 << ", Longitude " << testPoint.longitude << endl;
            break;
        }

        // Additional validation for geographic range
        if (!(nearestFromKDTree.latitude >= -90 && nearestFromKDTree.latitude <= 90) ||
            !(nearestFromKDTree.longitude >= -180 && nearestFromKDTree.longitude <= 180)) {
            searchTestResult = false;
            cout << "Invalid geographic range for Point: Latitude " << testPoint.latitude 
                 << ", Longitude " << testPoint.longitude << endl;
            break;
        }
    }
    printTestResult(searchTestResult, "Search Test");

    // Overall test result
    printTestResult(insertTestResult && searchTestResult, "Overall KDTree Functionality");

    //Test with random data
    KDTree tree2;
    const int testPointsCount = 2000;  // Number of random points for testing
    vector<GeoPoint> points2;

    // Generate random test points
    for (int i = 0; i < testPointsCount; ++i) {
        points2.push_back(generateRandomPoint());
    }

    // Test insertion time
    auto start = high_resolution_clock::now();
    for (const auto& point2 : points2) {
        tree2.insert(point2);
    }
    auto stop = high_resolution_clock::now();
    auto insertionDuration = duration_cast<microseconds>(stop - start);
    cout << "Insertion time for " << testPointsCount << " points: " 
         << insertionDuration.count() << " microseconds" << endl;

    // Test nearest neighbor search time
    start = high_resolution_clock::now();
    for (const auto& testPoint2 : points2) {
        tree.nearestNeighbor(testPoint2);
    }
    stop = high_resolution_clock::now();
    auto searchDuration = duration_cast<microseconds>(stop - start);
    cout << "Search time for " << testPointsCount << " points: " 
         << searchDuration.count() << " microseconds" << endl;

    return 0;
}
