//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Audio.h"
#include <SFML/Audio.hpp>
#include <iostream>

void Audio::Test()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("audio/example.wav")) {
        std::cerr << "Failed to load sound file" << std::endl;
        return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Wait for the sound to finish
    sf::sleep(sf::seconds(buffer.getDuration().asSeconds()));
}