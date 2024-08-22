#ifndef RESOLVER_HPP
#define RESOLVER_HPP

#include <SFML/Graphics.hpp>
#include <Application/Masse.hpp>
#include <Application/Spring.hpp>
#include <glm/glm.hpp>

class Resolver {
    public:
        static void resolve(Masse&, Masse&, const Spring&);
        static void dynamic_resolution(Masse&, Masse&, const Spring&, const sf::Time&) {}
};

#endif