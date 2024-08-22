#include <Application/Masse.hpp>
#include <iostream>

Masse::Masse(const sf::Vector2f& pos, int mass, bool isFixed) : m_mass(mass), m_pos(pos), m_vit(0,0),
m_acc(0,0), m_isFixed(isFixed) {
    m_shape.setFillColor(sf::Color::Black);
    m_shape.setPosition(m_pos);
    m_shape.setSize(sf::Vector2f(20,20));
}

Masse::~Masse() {}

void Masse::update(sf::Time deltaTime) {
    m_vit +=  m_acc * deltaTime.asSeconds() ;
    m_pos +=  m_vit * deltaTime.asSeconds() ;

    m_shape.setPosition(m_pos);
}

void Masse::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape);
}