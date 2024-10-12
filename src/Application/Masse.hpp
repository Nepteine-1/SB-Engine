#ifndef MASSE_HPP
#define MASSE_HPP

#include <SFML/Graphics.hpp>

class Masse : public sf::Drawable {
    public:
        Masse(const sf::Vector2f& pos, int mass=10, bool isFixed=false);
        ~Masse();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        int m_mass;
        sf::RectangleShape m_shape;
        sf::Vector2f m_pos;
        bool m_isFixed;  // indicates if the mass is fixed
        sf::Vector2f m_vit;
        sf::Vector2f m_acc;

};

#endif