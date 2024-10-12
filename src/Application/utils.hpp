#ifndef INLINE_H_INCLUDED
#define INLINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#define PI 3.14159

/**
 *  @brief Returns a pseudo-random float.
 **/
inline float randF(float Min, float Max) 
{
    float offset=0;
    if(abs(Min) > 0) { offset = Min; }
    float res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1)) ;
    return res + offset;
}

/**
 *  @brief Returns a pseudo-random int.
 **/
inline int randI(int Min, int Max) 
{
    int offset=0;
    if(abs(Min) > 0) { offset = Min; }
    int res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1));
    return res + offset;
}

/**
 *  @brief Returns the angle between the segment formed with two points and the horizontal axis.
 *
 *  @param origine: Origin point of axis vector
 *  @param point: Vector point of the horizontal axis
 *
 *  @return Angle in RADIANS
 **/
inline float findAngle_OldVersion(const sf::Vector2f& origine, const sf::Vector2f& point)
{
    sf::Vector2f tempVector = sf::Vector2f(point.x - origine.x, point.y - origine.y);
    float angle =0;

    if(tempVector.x > 0 ) {
        angle = atan(-tempVector.y / tempVector.x);
        if(angle < 0) { angle = 2*PI + angle; }
    }
    else if(tempVector.x < 0 ) { angle = atan(-tempVector.y / tempVector.x) + PI; }
    else { angle = atan(tempVector.y / tempVector.x); }

    return angle;
}

inline float findAngle(const sf::Vector2f& origine, const sf::Vector2f& point)
{
    sf::Vector2f tempVector = sf::Vector2f(point.x - origine.x, point.y - origine.y);
    float dot = tempVector.x*1 + tempVector.y*0;     
    float det = tempVector.x*0 - tempVector.y*1;
    float angle = atan2(det, dot);

    return angle;
}

/**
 *  @brief Rotates a point around a center in the trigonometric direction.
 *
 *  @param angleSupp: Desired rotation angle (in radians)
 *  @param origine: Point of origin
 *  @param point: Point undergoing rotation
 **/
inline void rotationPts(const float angleSupp, const sf::Vector2f origine, sf::Vector2f& point) // rotation dans le sens horaire d'un point
{
    float angle = findAngle(origine, point); // En radian
    float normeVect = sqrtf((point.x - origine.x)*(point.x - origine.x) + (point.y - origine.y)*(point.y - origine.y));

    angle += angleSupp;

    //change the position of the point
    point.x = normeVect * cos(angle) + origine.x;
    point.y = /* y is inverted in the global landmark */ -normeVect * sin(angle) + origine.y;
}

// Determines whether two solids (convex and defined by a set of points) overlap
// Returns true if true , false otherwise
inline bool overlappingSAT(sf::VertexArray &j1, sf::VertexArray &j2)
{

    for(size_t i=0; i < j1.getVertexCount(); i++) {
        int j = (i+1)%j1.getVertexCount();
        sf::Vector2f axeProjection = sf::Vector2f(-(j1[j].position.y - j1[i].position.y) ,j1[j].position.x - j1[i].position.x);

        float minf1 = 1000000, maxf1 = -1000000;
        for(size_t e=0; e < j1.getVertexCount(); e++) {
            float proj = j1[e].position.x * axeProjection.x + j1[e].position.y * axeProjection.y;
            minf1 = std::min(minf1, proj);
            maxf1 = std::max(maxf1, proj);
        }

        float minf2 = 1000000, maxf2 = -1000000;
        for(size_t e=0; e < j2.getVertexCount(); e++) {
            float proj = j2[e].position.x * axeProjection.x + j2[e].position.y * axeProjection.y;
            minf2 = std::min(minf2, proj);
            maxf2 = std::max(maxf2, proj);
        }

        if(!(maxf2 > minf1 && maxf1> minf2)) { return false; }
    }
    return true;
}

/**
 *  @brief Indicates whether the [p11 p12] and [p21 p22] segments intersect.
 *
 *  @return True if there is a collision, False otherwise
 **/
inline bool crossingLines(sf::Vector2f& p11, sf::Vector2f& p12, sf::Vector2f& p21, sf::Vector2f& p22)
{
    float cd1, cd2; // Coef director of the straight line (p11 p12) and (p21 p22)

    /*  Case where one of the segments is vertical  */
    if(p11.y == p12.y)
    {
        if(p11.y >= std::min(p21.y, p22.y) && p11.y <= std::max(p21.y, p22.y) && std::max(p11.x,p12.x) >= std::min(p21.x, p22.x) && std::max(p21.x,p22.x) >= std::min(p11.x, p12.x)) {
            return true;
        }
        return false;
    }
    else if(p21.y == p22.y)
    {
        if(p21.y >= std::min(p11.y, p12.y) && p21.y <= std::max(p11.y, p12.y) && std::max(p21.x,p22.x) >= std::min(p11.x, p12.x) && std::max(p11.x,p12.x) >= std::min(p21.x, p22.x)) {
            return true;
        }
        return false;
    }

    cd1 = p11.x >= p12.x ? (p11.y - p12.y)/(p11.x - p12.x) : (p12.y - p11.y)/(p12.x - p11.x);
    cd2 = p21.x >= p22.x ? (p21.y - p22.y)/(p21.x - p22.x) : (p22.y - p21.y)/(p22.x - p21.x);

    float co1, co2; // Coord at the origin of the lines (p11 p12) and (p21 p22)
    co1= p11.y - cd1*p11.x;
    co2= p21.y - cd2*p21.x;

    /* Parallel segment cases */
    if(cd1 == cd2) {
        if( co1 == co2) {
            if(std::max(p11.x, p12.x) >= std::min(p21.x, p22.x) && std::max(p21.x, p22.x)>= std::min(p11.x, p12.x) && std::max(p11.y, p12.y) >= std::min(p21.y, p22.y) && std::max(p21.y, p22.y)>= std::min(p11.y, p12.y)) {
                return true;
            }
        }
        return false;
    }

    sf::Vector2f pointIntersection;
    pointIntersection.x = (co2 - co1)/(cd1 - cd2); // We find the intersection axis => Risk of division by zero
    pointIntersection.y = cd1 * pointIntersection.x + co1; //It remains only to find 'y' with one of the two equations of right

    // We check if this point belongs to the two segments [p11 p12] and [p21 p22] => If true then there is crossing otherwise it’s false
    if(pointIntersection.x >= std::min(p11.x, p12.x) && pointIntersection.x <= std::max(p11.x, p12.x) && pointIntersection.y >= std::min(p11.y, p12.y) && pointIntersection.y <= std::max(p11.y, p12.y)) {
        if(pointIntersection.x >= std::min(p21.x, p22.x) && pointIntersection.x <= std::max(p21.x, p22.x) && pointIntersection.y >= std::min(p21.y, p22.y) && pointIntersection.y <= std::max(p21.y, p22.y)) {
            return true;
        }
    }
    return false;
}

/**
 *  @brief Indicates if there is a collision between two polygons at their boundaries.
 *
 *  @param j1: Polygon 1
 *  @param j2: Polygon 2
 *
 *  @return True if there is a collision, false otherwise.
 **/
inline bool overlappingCSL(sf::VertexArray &j1, sf::VertexArray &j2)
{
    for(size_t i=0; i < j1.getVertexCount(); i++)
    {
        int a= (i+1)%j1.getVertexCount();
        for(size_t j=0; j < j2.getVertexCount(); j++)
        {
            int b= (j+1)%j2.getVertexCount();
            if(crossingLines(j1[i].position, j1[a].position, j2[j].position, j2[b].position))
            {
                return true;
            }
        }
    }
    return false;
}

#endif
