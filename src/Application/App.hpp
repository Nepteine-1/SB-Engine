#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>

#include <Engine/EventHandler.hpp>

#include <Application/Masse.hpp>
#include <Application/Resolver.hpp>
#include <Application/Spring.hpp>

#include <vector>
#include <iostream>

class Engine;

class App : public sf::Drawable, public MouseObserver{
    public:
        App();
        virtual ~App();
        void update(sf::Time deltaTime);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void notify(sf::Mouse::Button, sf::Vector2i&, bool clicked);
        void link(Masse&, Masse&);
        void addMass(Masse&&);
        void createSoftBody(sf::Vector2f, sf::Vector2f, float, float);

    private:
        Spring m_typeRessort;

        std::vector<Masse> m_listMasse;
        std::vector<std::vector<Masse*>> m_lienMasse;

        std::vector<Masse> m_listSupport;

        bool holding;
        sf::Vector2f holdingPoint;
        Masse* m_selectedMass;

        bool showShape;
};

#endif