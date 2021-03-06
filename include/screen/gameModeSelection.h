/**
 * File: gameModeSelection.h
 * Author: Logan
 * Description: Front-end class that defines the behaviour of the Game Mode selection screen
 */

#ifndef BATTLESHIP_GAMEMODESELECTION_H
#define BATTLESHIP_GAMEMODESELECTION_H

#include "../entity/button.h"
#include "screenTemplate.h"

#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class GameModeSelection : public ScreenTemplate {
    private:
        /**
         * Background texture
         */
        sf::Texture gameModeBackgroundTexture;

        /**
         * Idle 1 player button texture
         */
        sf::Texture idleOnePlayerButtonTexture;

        /**
         * Active 1 player button texture
         */
        sf::Texture activeOnePlayerButtonTexture;

        /**
         * Idle 2 player button texture
         */
        sf::Texture idleTwoPlayerButtonTexture;

        /**
         * Active 2 player button texture
         */
        sf::Texture activeTwoPlayerButtonTexture;

        /**
         * Idle back button texture
         */
        sf::Texture idleBackButtonTexture;

        /**
         * Active back button texture
         */
        sf::Texture activeBackButtonTexture;

        /**
         * Idle instructions button texture
         */
        sf::Texture idleInstructionsButtonTexture;

        /**
         * Active instructions button texture
         */
        sf::Texture activeInstructionsButtonTexture;

        /**
         * Background sprite
         */
        sf::Sprite backgroundSprite;

        /**
         * 1 Player button
         */
        Button *onePlayerButton;

        /**
         * 2 Player button
         */
        Button *twoPlayerButton;

        /**
         * Back button
         */
        Button *backButton;

        /**
         * Instructions button
         */
        Button *instructionsButton;

        /**
         * Mouse position vector
         */
        sf::Vector2f mousePosition;

        /**
         * System event
         */
        sf::Event event{};

        /**
         * Calls State::updateMousePosition() and entity::Button::updateButtonState()
         */
        void update(sf::RenderWindow &gui, sf::Vector2f mousePosition);

        /**
         * Polls for system events
         */
        void poll(sf::RenderWindow &gui);

        /**
         * Renders all sprites
         */
        void render(sf::RenderWindow &gui);

    public:
        /**
         * Constructor
         */
        GameModeSelection();

        /**
         * Copy constructor
         */
        GameModeSelection(const GameModeSelection &source);

        /**
         * Destructor
         */
        ~GameModeSelection();

        /**
         * Overloaded assignment operator
         */
        GameModeSelection &operator=(const GameModeSelection &source);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_GAMEMODESELECTION_H