#ifndef PARTICULEGENERATOR_HPP_INCLUDED
#define PARTICULEGENERATOR_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Features/Random/Random.hpp>
#include "Ball.hpp"

class Particule;

class ParticuleGenerator : public sf::Drawable
{
    public:
        ParticuleGenerator(const float X, const float Y);
        ~ParticuleGenerator();

        void add(const float X, const float Y); // Creates a single particle at the given postion
        void add(); // Creates a single particle at the position of the generator

        void emit(sf::Time deltaTime); // Generates a particle at each time interval "particulePerSecond"
        void update(sf::Time deltaTime);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        size_t size(void) const { return lParticules.size(); }

        void setPosition(const float X, const float Y) { pos.x = X; pos.y = Y; }
        void setPosition(sf::Vector2f& newPos) { pos = newPos; }
        sf::Vector2f getPosition(void) { return pos; }
        void start(void);
        void stop(void);
        void enableDuration(const bool boolean) { EnableDuration = boolean; lifeTime =0; timeLastParticuleAdded=0; };
        bool isWorking(void) const { return working; };
        void setDuration(const float time) { duration = time; } // Changes generator duration
        void setParticulePerSecond(const int cadence) { particulePerSecond = cadence; }
        float getParticulePerSecond(void) { return particulePerSecond; }
        void setLifeTimeParticule(const float value) { lifeTimeParticule = value; }
        float getLifeTimeParticule(void) { return lifeTimeParticule; }
        void setTypeParticule(const short value) { typeParticule = value;}
        short getTypeParticule(void) { return typeParticule; }

    private:
        std::vector<Particule*> lParticules;
        sf::Vector2f pos;
        short typeParticule;
        bool working, EnableDuration; // Indicates that the generator is in use/ Indicates that the generator has a running time
        float duration, lifeTime; // generator lifetime
        float particulePerSecond; // no limitations
        /*  Only useful for emit() // The maximum number of particles a generator can deliver per second depends on the system performance
            0 => Generator start delayed by 'particulePerSecond'
            Always initialize to 1 for direct boot
        */
        float timeLastParticuleAdded; 
        float lifeTimeParticule; // particles lifetime
        sf::Vector2f particlesOffset;
        sf::Vector2i prevGenPos;
};

#endif
