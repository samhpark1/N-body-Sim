#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <random>

const int WIDTH = 2000;
const int HEIGHT = 1500;

class GravitySource{
public:
    sf::CircleShape s;
    sf::Vector2f pos;
    float strength;

    GravitySource(float x_pos, float y_pos,  float strength){
        pos.x = x_pos;
        pos.y = y_pos;

        this->strength = strength;

        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(6);
    }


    void render(sf::RenderWindow& wind){
        wind.draw(s);
    }

    sf::Vector2f getPos() const{
        return pos;
    }

    float getStrength() const{
        return strength;
    }
};

class Particle{
public:
    sf::CircleShape s;
    sf::Vector2f pos;
    sf::Vector2f vel;
    float t;

    Particle(float x_pos, float y_pos, float x_vel, float y_vel, float time){
        pos.x = x_pos;
        pos.y = y_pos;

        vel.x = x_vel;
        vel.y = y_vel;

        t = time;

        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(1);
    }

    void render(sf::RenderWindow& wind){
        s.setPosition(pos);
        wind.draw(s);
    }

    sf::Vector2f getPos(){
        return pos;
    }

    float getVel(){
        return sqrt(pow(vel.x, 2) + pow(vel.y, 2));
    }

    void updatePhysics(std::vector<GravitySource*>& src){
        float closest_dist = MAXFLOAT;
        float final_vel = 0;
        for (int i = 0; i < src.size(); i++){
            float x_dist = src[i]->getPos().x - pos.x;
            float y_dist = src[i]->getPos().y - pos.y;

            float dist = sqrt(pow(x_dist, 2) + pow(y_dist, 2));
            closest_dist = fmin(closest_dist, dist);
            float inverse_dist = 1.f/dist;

            float x_norm = inverse_dist * x_dist;
            float y_norm = inverse_dist * y_dist;

            float inv_sqr = pow(inverse_dist, 2);

            float x_accel = t * x_norm * src[i]->getStrength() * inv_sqr;
            float y_accel = t * y_norm * src[i]->getStrength() * inv_sqr;

            vel.x += x_accel;
            vel.y += y_accel;


            final_vel = sqrt(pow(vel.x, 2) + pow(vel.y, 2));

            pos.x += vel.x;
            pos.y += vel.y;
        }

        if (pow(final_vel, 2) > 155){
            final_vel = sqrt(155);
        }

        s.setFillColor(sf::Color(255, 100 + pow(final_vel, 2), 100 + pow(final_vel, 2)));

    }
};


float gaussian_random(float mean, float stddev) {
    static std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}




int main(int argc, char* argv[])
{
    int time_scale = atof(argv[2]);
    int n_particles = atoi(argv[1]);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My Program");
    window.setFramerateLimit(30);

    GravitySource* source = new GravitySource(WIDTH/2, HEIGHT/2, 10000);



    std::vector<GravitySource*> g_sources = {source};
    std::vector<Particle> particles;

    srand(time(NULL));
    for (int i = 0; i < n_particles; i++){
        float x = gaussian_random(WIDTH/2, WIDTH/6);
        float y = gaussian_random(HEIGHT/2, HEIGHT/6);
        Particle particle(x, y, rand()%5, rand()%5, time_scale);
        particles.push_back(particle);
    }


    bool space_pressed = false;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) space_pressed = true;
        
        if (space_pressed){
            window.clear();

            for (int i = 0; i < particles.size(); i++){
                particles[i].updatePhysics(g_sources);
                particles[i].render(window);
            }

            window.display();
        }
    }

    return 0;
}
