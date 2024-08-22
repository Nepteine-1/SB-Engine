#include <Application/Resolver.hpp>
#include <Application/utils.hpp>
#include <chrono>
#include <thread>

// Ici seul la masse subit l'action du support et voit ses caractéristiques modifiées
// Cette fonction s'utilise avec les liens entre les masses
void Resolver::resolve(Masse& m, Masse& s, const Spring& ressort){ // Suppose qu'il y a un ressort entre la masse et le support
    glm::vec2 m_center = glm::vec2(m.m_pos.x + m.m_shape.getSize().x/2,m.m_pos.y + m.m_shape.getSize().y/2);
    glm::vec2 s_center = glm::vec2(s.m_pos.x + s.m_shape.getSize().x/2,s.m_pos.y + s.m_shape.getSize().y/2);
    
    float angle = findAngle(sf::Vector2f(s_center.x, s_center.y),sf::Vector2f(m_center.x, m_center.y)) + M_PI/2;
    float long_spring = glm::length(glm::vec2(-m_center+s_center)); // Longueur entre masse et support (en pxl, pas en m !)
    
    float x=long_spring-ressort.m_lo;
    float f=0.95f; // coeff d'amortissement
    float damping_coef = 0.75f;

    if(!m.m_isFixed) {
        m.m_acc.x += -((ressort.m_k*x*glm::sin(angle))/m.m_mass)*damping_coef - m.m_vit.x*f;
        m.m_acc.y += -((ressort.m_k*x*glm::cos(angle))/m.m_mass)*damping_coef - m.m_vit.y*f;
    } 
    if(!s.m_isFixed) {  //A MODIFIER
        s.m_acc.x += +((ressort.m_k*x*glm::sin(angle))/s.m_mass)*damping_coef - s.m_vit.x*f;
        s.m_acc.y += +((ressort.m_k*x*glm::cos(angle))/s.m_mass)*damping_coef - s.m_vit.y*f;
    }
}



