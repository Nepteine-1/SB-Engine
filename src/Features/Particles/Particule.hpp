#ifndef PARTICULE_HPP_INCLUDED
#define PARTICULE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <Features/Random/Random.hpp>
#include "ParticuleGenerator.hpp"

    //////////////////////////////////////////////////////////////
    ////////////// Base particle template //////////////////////// 
    //////////////////////////////////////////////////////////////

class Particule : public sf::Drawable
{
    public:
        Particule();
        Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex);
        Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex, float dureeVie);
        virtual ~Particule();

        virtual void update(const sf::Time& deltaTime) = 0;
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y) = 0; // update speed and position of particles
        virtual void processPhysics(void) = 0;
        virtual void processCollision(void) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool isDead(void) const {return m_isDead; }
        sf::Vector2f& getPosition(void) { return m_pos; }
        sf::Vector2f& getVitesse(void) { return m_vit; }
        float getLifeTimeMaxParticule(void) { return m_lifeTimeMax; }
        void setLifeTimeMaxParticule(const float value) { m_lifeTimeMax = value; }

    protected:
        bool m_isDead;
        sf::Vector2f m_pos, m_vit;
        float m_lifeTime, m_lifeTimeMax;
        sf::VertexArray m_forme;
};

    //////////////////////////////////////////////////////////////
    ////////////// Ball particle /////////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Ball : public Particule
{
    public:
        Particule_Ball();
        Particule_Ball(const float X,const float Y);
        Particule_Ball(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Ball();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void processPhysics(void);
        virtual void processCollision(void);

    protected:
        sf::Vector2f m_posInit, m_vitInit;
        float m_timeElapsedJump;
        float m_radius, m_radiusInit, m_masse;
        sf::Color m_color;
};

    //////////////////////////////////////////////////////////////
    ////////////// Snow particle /////////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Snow : public Particule
{
    public:
        Particule_Snow();
        Particule_Snow(const float X,const float Y);
        Particule_Snow(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Snow();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void processPhysics(void);
        virtual void processCollision(void) {}

    protected:
        float m_radius, m_radiusInit;
        sf::Color m_color;
};

    //////////////////////////////////////////////////////////////
    ////////////// Dot particle //////////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Dot : public Particule
{
    public:
        Particule_Dot();
        Particule_Dot(const float X,const float Y);
        Particule_Dot(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Dot();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void processPhysics(void);
        virtual void processCollision(void) {}

    protected:
        float m_taille;
        sf::Color m_color;
};

    //////////////////////////////////////////////////////////////
    ////////////// Fire particle /////////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Fire : public Particule
{
    public:
        Particule_Fire();
        Particule_Fire(const float X,const float Y);
        Particule_Fire(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Fire();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void processPhysics(void);
        virtual void processCollision(void) {}

    protected:
        float m_taille;
        float phase;
        float amplitude;
        sf::Color m_color;
};

    //////////////////////////////////////////////////////////////
    ////////////// Trail particle ////////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Trail : public Particule
{
    public:
        Particule_Trail();
        Particule_Trail(const float X,const float Y);
        Particule_Trail(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Trail();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void processPhysics(void) {} 
        virtual void processCollision(void) {} 

    protected:
        float m_taille;
        sf::Color m_color;
};


    //////////////////////////////////////////////////////////////
    ////////////// Dot Falling particle ////////////////////////// 
    //////////////////////////////////////////////////////////////

class Particule_Dot_Fall : public Particule
{
    public:
        Particule_Dot_Fall();
        Particule_Dot_Fall(const float X,const float Y);
        Particule_Dot_Fall(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Dot_Fall();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void processPhysics(void);
        virtual void processCollision(void) {} 

    protected:
        sf::Vector2f m_posInit, m_vitInit;
        float m_timeElapsedJump;
        float m_taille, m_masse;
        sf::Color m_color;
};

#endif