#include <Application/App.hpp>
#include <glm/glm.hpp>

#define G 9.8f*130.f

App::App() : holding(false), showShape(true) { 
    EventHandler::getEventHandler()->addMouseObserver(this); 
    // Create srping
    Spring ressort  = {7000.0f, 30.f};
    m_typeRessort = ressort;

    // create each mass
    createSoftBody(sf::Vector2f(200,20), sf::Vector2f(5,12), 1.0f, 30.f);
    m_selectedMass=nullptr;

    m_listSupport.push_back(Masse(sf::Vector2f(100, 400),10, true));
    m_listSupport.push_back(Masse(sf::Vector2f(400, 600),10, true));
    m_listSupport.push_back(Masse(sf::Vector2f(100, 800),10, true));

    m_listSupport[0].m_shape.setSize(sf::Vector2f(200.f,100.f));
    m_listSupport[1].m_shape.setSize(sf::Vector2f(200.f,100.f));
    m_listSupport[2].m_shape.setSize(sf::Vector2f(200.f,100.f));
}

App::~App() {}

void App::addMass(Masse&& m) {
    m_listMasse.push_back(m);
}

void App::createSoftBody(sf::Vector2f pos, sf::Vector2f size, float mass_of_points, float space_between_points) {
    float offset = m_listMasse.size();
    std::cout  << std::endl;
    
    for(int h=0; h<size.x;h++) {
        for(int l=0; l<size.y;l++) {
            if(h== size.x-1) addMass(Masse(sf::Vector2f(pos.x+space_between_points*l, pos.y+space_between_points*h),mass_of_points));
            else addMass(Masse(sf::Vector2f(pos.x+space_between_points*l, pos.y+space_between_points*h),mass_of_points));
        }    
    }

    for(int h=0; h<size.x;h++) {
        for(int l=0; l<size.y;l++) {
            if(h>0) {
                link(m_listMasse[(h)*size.y+l+offset],m_listMasse[(h-1)*size.y+l+offset]);
            }
            if(l>0) {
                link(m_listMasse[(h)*size.y+l+offset],m_listMasse[(h)*size.y+l-1+offset]);
            }
            if(l>0 && h>0) {
                link(m_listMasse[(h)*size.y+l+offset],m_listMasse[(h-1)*size.y+l-1+offset]);
            }
            if(l<size.y-1 && h>0) {
                link(m_listMasse[(h)*size.y+l+offset],m_listMasse[(h-1)*size.y+l+1+offset]);
                
            }
        }    
    }
}

void App::link(Masse& m1, Masse& m2) {
    std::vector<Masse*> temp;
    temp.push_back(&m1);
    temp.push_back(&m2);
    m_lienMasse.push_back(temp);
}

void App::update(sf::Time deltaTime) {

    // input handling
    if(m_selectedMass!=nullptr) {
        m_selectedMass->m_pos = holdingPoint - m_selectedMass->m_shape.getSize()*(0.5f);
        m_selectedMass->m_vit = sf::Vector2f(0,0);
        m_selectedMass->m_acc = sf::Vector2f(0,0);
        m_selectedMass->m_shape.setPosition(m_listMasse[0].m_pos);
    }

    // reset acceleration
    for(int i=0; i<m_listMasse.size(); i++) {
        if(m_listMasse[i].m_isFixed) m_listMasse[i].m_acc = sf::Vector2f(0,0);
        else m_listMasse[i].m_acc = sf::Vector2f(0,G);
    }

    for(int i=0; i<m_lienMasse.size(); i++) Resolver::resolve(*m_lienMasse[i][0], *m_lienMasse[i][1], m_typeRessort);

    for(int i=0; i<m_listMasse.size(); i++) {
        m_listMasse[i].m_vit +=  m_listMasse[i].m_acc * deltaTime.asSeconds();

        // static resolution
        sf::Vector2f nextPos = m_listMasse[i].m_pos + m_listMasse[i].m_vit * deltaTime.asSeconds();
        nextPos += sf::Vector2f(m_listMasse[i].m_shape.getSize().x/2, m_listMasse[i].m_shape.getSize().y/2);

        for(int e=0; e<m_listSupport.size(); e++) {
            sf::Vector2f nearest_point;
            nearest_point.x = std::max(m_listSupport[e].m_shape.getPosition().x, std::min(nextPos.x, m_listSupport[e].m_shape.getPosition().x + m_listSupport[e].m_shape.getSize().x));
            nearest_point.y = std::max(m_listSupport[e].m_shape.getPosition().y, std::min(nextPos.y, m_listSupport[e].m_shape.getPosition().y + m_listSupport[e].m_shape.getSize().y));
                
            sf::Vector2f rayToNearest = nearest_point - nextPos;
            float overlap = /*m_listMasse[i].m_shape.getSize().x*/ 5 - std::sqrt(rayToNearest.x * rayToNearest.x + rayToNearest.y * rayToNearest.y);

            if (std::isnan(overlap)) overlap=0;

            if(overlap > 0) {
                sf::Vector2f temp = rayToNearest*(1/std::sqrt(rayToNearest.x * rayToNearest.x + rayToNearest.y * rayToNearest.y)) * overlap;
                if (std::isnan(temp.x) || std::isnan(temp.y)) { nextPos = nearest_point; }
                else {

                nextPos = nextPos - rayToNearest*(1/std::sqrt(rayToNearest.x * rayToNearest.x + rayToNearest.y * rayToNearest.y)) * overlap;
                
                m_listMasse[i].m_vit = sf::Vector2f(0,0) ;
                }
            }
        }

        nextPos -= sf::Vector2f(m_listMasse[i].m_shape.getSize().x/2, m_listMasse[i].m_shape.getSize().y/2);
        m_listMasse[i].m_pos = nextPos ;
        m_listMasse[i].m_shape.setPosition(m_listMasse[i].m_pos);
    }
}

void App::notify(sf::Mouse::Button mouse, sf::Vector2i& pos, bool clicked) {
    holdingPoint = sf::Vector2f(pos.x, pos.y);

    /*if(mouse == sf::Mouse::Button::Left && clicked) holding = true;
    if(mouse == sf::Mouse::Button::Left && !clicked) holding = false;*/
    if(mouse == sf::Mouse::Button::Left && clicked) {
        bool MassSelectedfound=false;
        int i = 0;
        while(!MassSelectedfound && i<m_listMasse.size()) {
            if(pos.x <= m_listMasse[i].m_pos.x + m_listMasse[i].m_shape.getSize().x && pos.x >= m_listMasse[i].m_pos.x &&
            pos.y <= m_listMasse[i].m_pos.y + m_listMasse[i].m_shape.getSize().y && pos.y >= m_listMasse[i].m_pos.y) {
                m_selectedMass = &m_listMasse[i];
                MassSelectedfound=true;
            }
            i++;
        }
    }
    if(mouse == sf::Mouse::Button::Left && !clicked) {
        m_selectedMass = nullptr;
    }
    if(mouse == sf::Mouse::Button::Middle && clicked) {
        showShape = !showShape;
    }
}

void App::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // draw lines
    sf::VertexArray va(sf::Lines, m_lienMasse.size()*2);
    for(int i=0; i<m_lienMasse.size(); i++) {
        va[i*2].position = sf::Vector2f(m_lienMasse[i][0]->m_pos.x + m_lienMasse[i][0]->m_shape.getSize().x/2,m_lienMasse[i][0]->m_pos.y + m_lienMasse[i][0]->m_shape.getSize().y/2); 
        va[i*2+1].position = sf::Vector2f(m_lienMasse[i][1]->m_pos.x + m_lienMasse[i][1]->m_shape.getSize().x/2,m_lienMasse[i][1]->m_pos.y + m_lienMasse[i][1]->m_shape.getSize().y/2); 

        va[i*2].color = sf::Color::Black;
        va[i*2+1].color = sf::Color::Black;
    }
    target.draw(va);

    // draw shapes
    if (showShape) for(int i=0; i<m_listMasse.size(); i++) target.draw(m_listMasse[i].m_shape);
    for(int i=0; i<m_listSupport.size(); i++) target.draw(m_listSupport[i].m_shape);
}
