#include "Animation.h"
#include "Entity.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

void Animation::loadAnimations(sf::Texture pText, const std::string& jsonFile, sf::Shape* pShape)
{
    texture = pText;
    animShape = pShape;
    animShape->setTexture(&texture);

    std::ifstream file(jsonFile);
    nlohmann::json data;
    file >> data;
    file.close();

    frameSize.x = (int)data["frame_size"]["width"];
    frameSize.y = (int)data["frame_size"]["height"];

    for (auto& [key, anim] : data["animations"].items()) 
    {
        animations[key] = {
            anim["frames"].get<int>(),
            anim["timeProgress"].get<float>(),
            anim["loop"].get<bool>(),
            anim["row"].get<int>()
        };
    }
}

void Animation::setAnimation(const std::string& animName) {
    
    if (animations.find(animName) != animations.end()) 
    {
        currentAnimation = animName;
        currentFrame = 0;
        elapsedTime = 0;
    }
}

void Animation::update(float deltaTime)
{
    if (currentAnimation.empty())
        return;

    AnimationData& anim = animations[currentAnimation];
    elapsedTime += deltaTime;

    if (elapsedTime >= anim.timeProgress) 
    {
        elapsedTime = 0;
        currentFrame = (currentFrame + 1) % anim.frames;
    }

    int frameX = currentFrame * frameSize.x;
    int frameY = animations[currentAnimation].row * frameSize.y;

    if (isFacingRight) 
    {
        animShape->setScale(1.f, 1.f);
        animShape->setOrigin(0, 0);
    }
    else 
    {
        animShape->setScale(-1.f, 1.f);
        animShape->setOrigin(frameSize.x * 2, 0);
    }
    animShape->setTextureRect(sf::IntRect(frameX, frameY, frameSize.x, frameSize.y));
}
