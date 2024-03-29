#include "location.h"
KDTree::KDTree(const KDTree& other){
    copyNodes(other.root); //uses the copy constructor
}

KDTree::Node* KDTree::copyNodes(const Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(node->point);
    newNode->left = copyNodes(node->left);
    newNode->right = copyNodes(node->right);
    return newNode;
}

KDTree::~KDTree() {
    clearTree(root);
}

void KDTree::clearTree(Node* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

int KDTree::getSize() const {
    return size;
}

void KDTree::insert(GeoPoint point) {
    root = insertRec(root, point, 0);
    size++;
}

KDTree::Node* KDTree::insertRec(Node* node, GeoPoint point, unsigned depth) {
    if (node == nullptr) {
        return new Node(point);
    }
    // Calculate current dimension (0 for latitude, 1 for longitude)
    unsigned cd = depth % 2;

    if (cd == 0) {
        // Compare latitude
        if (point.latitude < node->point.latitude)
            node->left = insertRec(node->left, point, depth + 1);
        else
            node->right = insertRec(node->right, point, depth + 1);
    } else {
        // Compare longitude
        if (point.longitude < node->point.longitude)
            node->left = insertRec(node->left, point, depth + 1);
        else
            node->right = insertRec(node->right, point, depth + 1);
    }

    return node;
}

// Method to find the nearest neighbor to a given query point.
GeoPoint KDTree::nearestNeighbor(GeoPoint queryPoint) {
    // Initiates the recursive nearest neighbor search starting from the root node.
    return nearestNeighborRec(root, queryPoint, 0).point;
}

KDTree::Node KDTree::nearestNeighborRec(Node* node, GeoPoint queryPoint, unsigned depth) {
    if (node == nullptr) {
        // If the node is null, return an invalid GeoPoint as a sentinel
        return Node(GeoPoint(-1000, -1000));
    }

    // Determine current dimension (0 for latitude, 1 for longitude)
    unsigned cd = depth % 2;

    Node *nextBranch, *otherBranch;
    if (cd == 0) { // Latitude comparison
        if (queryPoint.latitude < node->point.latitude) {
            nextBranch = node->left;
            otherBranch = node->right;
        } else {
            nextBranch = node->right;
            otherBranch = node->left;
        }
    } else { // Longitude comparison
        if (queryPoint.longitude < node->point.longitude) {
            nextBranch = node->left;
            otherBranch = node->right;
        } else {
            nextBranch = node->right;
            otherBranch = node->left;
        }
    }

    // Search down the tree
    Node best = nextBranch ? nearestNeighborRec(nextBranch, queryPoint, depth + 1) : Node(GeoPoint(-1000, -1000));
    double bestDist = (best.point.latitude != -1000) ? distanceCalc(queryPoint, best.point) : numeric_limits<double>::max();

    // Check if we need to search the other branch
    double nodeDist = distanceCalc(queryPoint, node->point);
    if (nodeDist < bestDist) {
        best = *node;
        bestDist = nodeDist;
    }

    // Calculate the distance to the splitting plane
    double planeDist = cd == 0 ? abs(queryPoint.latitude - node->point.latitude)
                               : abs(queryPoint.longitude - node->point.longitude);
    if (planeDist < bestDist && otherBranch) {
        Node otherBest = nearestNeighborRec(otherBranch, queryPoint, depth + 1);
        double otherBestDist = (otherBest.point.latitude != -1000) ? distanceCalc(queryPoint, otherBest.point) : numeric_limits<double>::max();
        if (otherBestDist < bestDist) {
            best = otherBest;
        }
    }
    return best;
}

GeoPoint findNearestPOIBruteForce(const GeoPoint& queryPoint, const vector<GeoPoint>& points) {
    GeoPoint nearestPoint(0, 0); // Initialized with some default values
    double minDistance = numeric_limits<double>::max();

    for (const auto& point : points) {
        double distance = distanceCalc(queryPoint, point);
        if (distance < minDistance) {
            minDistance = distance;
            nearestPoint = point;
        }
    }

    return nearestPoint;
}

double distanceCalc(GeoPoint a, GeoPoint b) {
    const double R = 6371.0; // Earth's radius in kilometers

    // Handling for points near the poles
    if (abs(a.latitude) > 89.9999 || abs(b.latitude) > 89.9999) {
        double lat1 = degreesToRadians(a.latitude);
        double lat2 = degreesToRadians(b.latitude);
        double dLat = lat2 - lat1;
        double c = 2 * atan2(sqrt(sin(dLat / 2) * sin(dLat / 2)), sqrt(1 - sin(dLat / 2) * sin(dLat / 2)));
        return R * c;
    }
    // Convert latitudes and longitudes from degrees to radians
    double lat1 = degreesToRadians(a.latitude);
    double lat2 = degreesToRadians(b.latitude);
    double lon1 = degreesToRadians(a.longitude);
    double lon2 = degreesToRadians(b.longitude);
    
    // Calculate the differences in latitude and longitude
    double dLat = lat2 - lat1;
    double dLon = abs(lon2 - lon1);
    if (dLon > M_PI) dLon = 2 * M_PI - dLon; // Adjust for crossing 180 degrees
    
    // Apply the Haversine formula to calculate great-circle distance
    double a2 = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a2), sqrt(1 - a2));

    return R * c; // Distance in kilometers
}

double degreesToRadians(double degrees) {
    // Converts angle from degrees to radians
    return degrees * M_PI / 180.0;
}