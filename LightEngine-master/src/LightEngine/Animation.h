#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class Texture;
class Entity;

class Animation
{
    struct AnimationData {
        int frames;
        float timeProgress;
        bool loop;
        int row;
    };

    sf::Texture texture;
    sf::Shape* animShape;
    sf::Vector2i frameSize;
    std::map<std::string, AnimationData> animations;
    std::string currentAnimation;
    int currentFrame = 0;
    float elapsedTime = 0;
    bool isFacingRight = true;

public:
    void SetIsFacingRight(bool pIsFacingRight) { isFacingRight = pIsFacingRight; }
    void loadAnimations(sf::Texture pText, const std::string& jsonFile, sf::Shape* pShape);
    void setAnimation(const std::string& animName);
    void update(float deltaTime);
};

