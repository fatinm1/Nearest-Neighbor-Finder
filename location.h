#ifndef LOCATION_H
#define LOCATION_H

#include <stdexcept>
#include <iostream>
#include <vector>  
#include <string>
#include <math.h>
using namespace std;

class GeoPoint {
public:
    double latitude;
    double longitude;

   GeoPoint(double lat, double lon) : latitude(lat), longitude(lon) {}
   bool isApproximatelyEqual(const GeoPoint& other, double tolerance = 0.00001) const {
        // Check for approximate equality in latitude
        bool latClose = abs(latitude - other.latitude) < tolerance;

        // Calculate the difference in longitude and adjust for wraparound at 180 degrees
        double longDiff = abs(longitude - other.longitude);
        if (longDiff > 180) {
            longDiff = 360 - longDiff; // Adjust for crossing 180 degrees
        }

        // Check for approximate equality in longitude
        bool longClose = longDiff < tolerance;

        // Both latitude and longitude must be within the tolerance for the points to be considered approximately equal
        return latClose && longClose;
    }

};

double distanceCalc(GeoPoint a, GeoPoint b);
double degreesToRadians(double degrees);
GeoPoint findNearestPOIBruteForce(const GeoPoint& queryPoint, const vector<GeoPoint>& points);

class KDTree {
private:
    struct Node {
        GeoPoint point;
        Node *left, *right;

        Node(GeoPoint p) : point(p), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size = 0;  // Size of the tree

    // Helper functions for insertion and search
    Node* insertRec(Node* node, GeoPoint point, unsigned depth);
    Node nearestNeighborRec(Node* node, GeoPoint queryPoint, unsigned depth);

public:
    KDTree() : root(nullptr) {}
    KDTree(const KDTree&);
    ~KDTree();
    KDTree& operator=(const KDTree&);
    void clearTree(Node* node); 
    void insert(GeoPoint point);
    GeoPoint nearestNeighbor(GeoPoint queryPoint);
    Node* copyNodes(const Node* node);
    int getSize() const;  // Declaration of getSize
};

#endif // LOCATION_H
