#include "Physics.h"

// Function to check if a point intersects with a polygon
bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon) {
    // Check if the point is inside the polygon using the ray casting algorithm
    size_t n = polygon.getVertexCount() - 1;
    size_t intersectionCount = 0;
    sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

    // Compute the bounding box of the polygon
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::min();
    for (size_t i = 0; i < n; ++i) {
        minX = std::min(minX, polygon[i].position.x);
        maxX = std::max(maxX, polygon[i].position.x);
        minY = std::min(minY, polygon[i].position.y);
        maxY = std::max(maxY, polygon[i].position.y);
    }

    // Early exit if the point is outside the bounding box
    if (point.x < minX || point.x > maxX || point.y < minY || point.y > maxY) {
        return false;
    }

    // Check for intersections
    for (size_t i = 0; i < n; ++i) {
        sf::Vector2f p1 = polygon[i].position;
        sf::Vector2f p2 = polygon[(i + 1) % n].position;

        // Check if the ray intersects with the edge
        if ((p1.y < point.y && p2.y >= point.y) ||
            (p2.y < point.y && p1.y >= point.y)) {
            float t = (point.y - p1.y) / (p2.y - p1.y);
            float intersectX = p1.x + t * (p2.x - p1.x);

            // Check if the intersection is to the right of the point
            if (intersectX <= point.x && intersectX <= rayEnd.x) {
                ++intersectionCount;
            }
        }
    }

    // Return true if the number of intersections is odd
    return intersectionCount % 2 == 1;
}

// Function to check if two polygons intersect
bool physics::intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2) {
    // Check for separating axis using the SAT algorithm
    std::vector<sf::Vector2f> edges;
    size_t n1 = poly1.getVertexCount() - 1;
    size_t n2 = poly2.getVertexCount() - 1;

    // Get edges from both polygons
    for (size_t i = 0; i < n1; i++) {
        edges.push_back(poly1[i].position - poly1[(i + 1) % n1].position);
    }
    for (size_t i = 0; i < n2; i++) {
        edges.push_back(poly2[i].position - poly2[(i + 1) % n2].position);
    }

    // Check for separating axis using each edge
    for (const auto& edge : edges) {
        sf::Vector2f normal = sf::Vector2f(-edge.y, edge.x);

        // Normalize the normal
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();

        // Project the polygons onto the normal
        for (size_t j = 0; j < n1; j++) {
            float projection = poly1[j].position.x * normal.x + poly1[j].position.y * normal.y;
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        for (size_t j = 0; j < n2; j++) {
            float projection = poly2[j].position.x * normal.x + poly2[j].position.y * normal.y;
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        // Check if the projections overlap
        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    return true;
}

// Function to transform a polygon by a given transformation
sf::VertexArray physics::getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform) {
    sf::VertexArray transformed = polygon;

    // Transform each vertex
    for (size_t i = 0; i < transformed.getVertexCount(); ++i) {
        transformed[i].position = transform.transformPoint(transformed[i].position);
    }

    return transformed;
}