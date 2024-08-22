#ifndef INLINE_H_INCLUDED
#define INLINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#define PI 3.14159

/**
 *  @brief Renvoie un float pseudo-aléatoirement.
 *
 *  @param Min: Borne inférieur de la sélection
 *  @param Max: Borne supérieur de la sélection
 **/
inline float randF(float Min, float Max) // Renvoie un nombre float dans l'intervalle [Min;Max]
{
    float offset=0;
    if(abs(Min) > 0) { offset = Min; }
    float res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1)) ;
    return res + offset;
}

/**
 *  @brief Renvoie un entier pseudo-aléatoirement.
 *
 *  @param Min: Borne inférieur de la sélection
 *  @param Max: Borne supérieur de la sélection
 **/float m_ax, m_ay;
inline int randI(int Min, int Max) // Renvoie un nombre entier dans l'intervalle [Min;Max]
{
    int offset=0;
    if(abs(Min) > 0) { offset = Min; }
    int res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1));
    return res + offset;
}

/**
 *  @brief Renvoie l'angle entre l'axe formé avec les deux points et l'axe horizontal.
 *
 *  @param origine: Point d'origine du vecteur de l'axe
 *  @param point: Point directeur du vecteur de l'axe
 *
 *  @return Angle en RADIANS
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
 *  @brief Effectue la rotation d'un point autour d'un centre dans le sens trigonométrique.
 *
 *  @param angleSupp: Angle de rotation souhaité (en Radian)
 *  @param origine: Point d'origine
 *  @param point: Point subissant la rotation
 **/
inline void rotationPts(const float angleSupp, const sf::Vector2f origine, sf::Vector2f& point) // rotation dans le sens horaire d'un point
{
    float angle = findAngle(origine, point); // En radian
    float normeVect = sqrtf((point.x - origine.x)*(point.x - origine.x) + (point.y - origine.y)*(point.y - origine.y));

    angle += angleSupp;

    //changement de la position du point
    point.x = normeVect * cos(angle) + origine.x;
    point.y = /* y est inversé dans le repère global */ -normeVect * sin(angle) + origine.y;
}

// Détermine si deux solides (Convexes et définis par un ensemble de points) se chevauchent
// Renvoie true si c'est le cas , false sinon
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
 *  @brief Indique si les segments [p11 p12] et [p21 p22] se croisent.
 *
 *  @return True s'il y a collision, False sinon.
 **/
inline bool crossingLines(sf::Vector2f& p11, sf::Vector2f& p12, sf::Vector2f& p21, sf::Vector2f& p22)
{
    float cd1, cd2; // Coef directeur des droites (p11 p12) et (p21 p22)

    /* Cas ou un des segments est vertical */
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

    float co1, co2; // Coord à l'origine des droites (p11 p12) et (p21 p22)
    co1= p11.y - cd1*p11.x;
    co2= p21.y - cd2*p21.x;

    /* Cas segments parallèles */
    if(cd1 == cd2) {
        if( co1 == co2) {
            if(std::max(p11.x, p12.x) >= std::min(p21.x, p22.x) && std::max(p21.x, p22.x)>= std::min(p11.x, p12.x) && std::max(p11.y, p12.y) >= std::min(p21.y, p22.y) && std::max(p21.y, p22.y)>= std::min(p11.y, p12.y)) {
                return true;
            }
        }
        return false;
    }

    sf::Vector2f pointIntersection;
    pointIntersection.x = (co2 - co1)/(cd1 - cd2); // On trouve l'absisse d'intersection => Risque de division par zéro
    pointIntersection.y = cd1 * pointIntersection.x + co1; // Il ne reste plus qu'a retrouver y avec une des deux équations de droite

    // On vérifie si ce point appartient aux deux segments [p11 p12] et [p21 p22] => Si vrai alors il y a croisement sinon c'est faux
    if(pointIntersection.x >= std::min(p11.x, p12.x) && pointIntersection.x <= std::max(p11.x, p12.x) && pointIntersection.y >= std::min(p11.y, p12.y) && pointIntersection.y <= std::max(p11.y, p12.y)) {
        if(pointIntersection.x >= std::min(p21.x, p22.x) && pointIntersection.x <= std::max(p21.x, p22.x) && pointIntersection.y >= std::min(p21.y, p22.y) && pointIntersection.y <= std::max(p21.y, p22.y)) {
            return true;
        }
    }
    return false;
}

/**
 *  @brief Indique si il y a une collision entre deux polygones à leurs frontières.
 *
 *  @param j1: Polygone 1
 *  @param j2: Polygone 2
 *
 *  @return True si il y a collision, False sinon.
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

#endif // INLINE_H_INCLUDED
