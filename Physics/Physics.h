#ifndef POKUSAJ_PHYSICS_H
#define POKUSAJ_PHYSICS_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <limits>
#include <cmath>

namespace physics{
    // Function to check if a point intersects with a polygon
    bool intersects(const sf::Vector2f& point, const sf::VertexArray& polygon);

    // Function to check if two polygons intersect
    bool intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2);

    // Function to transform a polygon by a given transformation
    sf::VertexArray getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform);
}

#endif //POKUSAJ_PHYSICS_H