#include <iostream>
#include "location.h"
#include <vector>

using namespace std;

bool isValidLatitude(double lat) {
    return lat >= -90.0 && lat <= 90.0;
}

bool isValidLongitude(double lon) {
    return lon >= -180.0 && lon <= 180.0;
}

int main() {
    KDTree tree;
    // Populate the tree with predefined POIs
    tree.insert(GeoPoint(89.9999, -135.0)),  // Slightly off the North Pole
    tree.insert(GeoPoint(-89.9999, 45.0)),   // Slightly off the South Pole
    tree.insert(GeoPoint(0.1, 179.9)),       // Near the International Date Line (east)
    tree.insert(GeoPoint(0.2, -179.9)),      // Near the International Date Line (west)
    tree.insert(GeoPoint(90.0000, 0.0000)),   // North Pole
    tree.insert(GeoPoint(89.9999, 0.0000)),  // South Pole
    tree.insert(GeoPoint(-89.9999, 0.0000)),
    tree.insert(GeoPoint(40.7128, -74.0060)); // New York
    tree.insert(GeoPoint(51.5074, -0.1278));  // London
    tree.insert(GeoPoint(35.6895, 139.6917)); // Tokyo
    tree.insert(GeoPoint(-33.8688, 151.2093)); // Sydney, Australia
    tree.insert(GeoPoint(48.8566, 2.3522));   // Paris, France
    tree.insert(GeoPoint(-23.5505, -46.6333)); // São Paulo, Brazil
    tree.insert(GeoPoint(55.7558, 37.6173));  // Moscow, Russia
    tree.insert(GeoPoint(28.6139, 77.2090));  // New Delhi, India
    tree.insert(GeoPoint(39.9042, 116.4074)); // Beijing, China
    tree.insert(GeoPoint(-34.6037, -58.3816)); // Buenos Aires, Argentina
    tree.insert(GeoPoint(30.0444, 31.2357));  // Cairo, Egypt
    tree.insert(GeoPoint(1.3521, 103.8198));  // Singapore
    tree.insert(GeoPoint(59.3293, 18.0686));  // Stockholm, Sweden
    tree.insert(GeoPoint(37.7749, -122.4194)); // San Francisco, USA

   double queryLat, queryLon;
   cout << "Enter latitude of your location (-90 to 90): ";
    while (!(cin >> queryLat) || !isValidLatitude(queryLat)) {
        cout << "Invalid latitude. Please enter a value between -90 and 90: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
    }

    cout << "Enter longitude of your location (-180 to 180): ";
    while (!(cin >> queryLon) || !isValidLongitude(queryLon)) {
        cout << "Invalid longitude. Please enter a value between -180 and 180: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
    }

    // Find and output the nearest POI
    GeoPoint queryPoint(queryLat, queryLon);
    GeoPoint nearestPOI = tree.nearestNeighbor(queryPoint);

    cout << "The nearest POI is at latitude: " << nearestPOI.latitude 
         << ", longitude: " << nearestPOI.longitude << endl;

    return 0;
}