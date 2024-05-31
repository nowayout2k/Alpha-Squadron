//
// Created by Johnnie Otis on 5/30/24.
//

#include "../Header/GameManager.h"
#include "../Header/Input.h"

GameManager::GameManager()
{
    SetUpInput();
    std::unique_ptr<sf::Drawable> entity;
    entity = std::make_unique<Player>();
}

void GameManager::SetUpInput()
{
    //Setup Input
    Input::SubscribeKey(sf::Keyboard::Key::W,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(0, -10);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Up)
                                {
                                    offset = sf::Vector2f(0, 0);
                                    break;
                                }
                                if(key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right ||
                                    key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D)
                                {
                                    offset = sf::Vector2f(0, -5);
                                }

                            }

                            player.MovePosition(offset);
                        });
    Input::SubscribeKey(sf::Keyboard::Key::S,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(0, 10);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Down)
                                {
                                    offset = sf::Vector2f(0, 0);
                                    break;
                                }
                                if(key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right ||
                                        key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D)
                                {
                                    offset = sf::Vector2f(0, 5);
                                }

                            }

                            player.MovePosition(offset);
                        });
    Input::SubscribeKey(sf::Keyboard::Key::A,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(-10, 0);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Left)
                                {
                                    offset = sf::Vector2f(0, 0);
                                    break;
                                }
                                if(key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down ||
                                   key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S)
                                {
                                    offset = sf::Vector2f(-5, 0);
                                }

                            }

                            player.MovePosition(offset);
                        });
    Input::SubscribeKey(sf::Keyboard::Key::D,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(10, 0);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Right)
                                {
                                    offset = sf::Vector2f(0, 0);
                                    break;
                                }
                                if(key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down ||
                                   key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S)
                                {
                                    offset = sf::Vector2f(5, 0);
                                }

                            }

                            player.MovePosition(offset);
                        });

    Input::SubscribeKey(sf::Keyboard::Key::Up,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(0, -10);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right ||
                                   key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D)
                                {
                                    offset = sf::Vector2f(0, -5);
                                }

                            }

                            player.MovePosition(offset);
                        });
    Input::SubscribeKey(sf::Keyboard::Key::Down,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(0, 10);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right ||
                                   key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D)
                                {
                                    offset = sf::Vector2f(0, 5);
                                }

                            }

                            player.MovePosition(offset);
                        });
    Input::SubscribeKey(sf::Keyboard::Key::Left,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(-10, 0);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down ||
                                   key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S)
                                {
                                    offset = sf::Vector2f(-5, 0);
                                }

                            }

                            player.MovePosition(offset);
                        });
    Input::SubscribeKey(sf::Keyboard::Key::Right,
                        [this](std::vector<sf::Keyboard::Key> otherKeys)
                        {
                            sf::Vector2f offset(10, 0);
                            for (sf::Keyboard::Key key : otherKeys)
                            {
                                if(key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down ||
                                   key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S)
                                {
                                    offset = sf::Vector2f(5, 0);
                                }
                            }

                            player.MovePosition(offset);
                        });
}
