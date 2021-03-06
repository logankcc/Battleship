/**
 * File: difficultySelection.cpp
 * Author: Logan
 * Description: Front-end class that defines the behaviour of the Difficulty selection screen
 */

#include "../../include/screen/difficultySelection.h"

using screen::DifficultySelection;

DifficultySelection::DifficultySelection() : ScreenTemplate() {
    State::loadTexture(this->difficultyBackgroundTexture, "difficultySelection/DifficultyBackground.png");
    State::loadTexture(this->idleEasyButtonTexture, "difficultySelection/IdleEasyButton.png");
    State::loadTexture(this->activeEasyButtonTexture, "difficultySelection/ActiveEasyButton.png");
    State::loadTexture(this->idleHardButtonTexture, "difficultySelection/IdleHardButton.png");
    State::loadTexture(this->activeHardButtonTexture, "difficultySelection/ActiveHardButton.png");
    State::loadTexture(this->idleBackButtonTexture, "difficultySelection/IdleBackButton.png");
    State::loadTexture(this->activeBackButtonTexture, "difficultySelection/ActiveBackButton.png");
    State::loadTexture(this->idleInstructionsButton, "difficultySelection/IdleInstructionsButton.png");
    State::loadTexture(this->activeInstructionsButton, "difficultySelection/ActiveInstructionsButton.png");

    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->difficultyBackgroundTexture, this->backgroundSprite);

    this->easyButton = new Button(sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), this->idleEasyButtonTexture, this->activeEasyButtonTexture);
    this->hardButton = new Button(sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), this->idleHardButtonTexture, this->activeHardButtonTexture);
    this->backButton = new Button(sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleBackButtonTexture, this->activeBackButtonTexture);
    this->instructionsButton = new Button(sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleInstructionsButton, this->activeInstructionsButton);
}

DifficultySelection::DifficultySelection(const DifficultySelection &source) {
    this->difficultyBackgroundTexture = source.difficultyBackgroundTexture;
    this->idleEasyButtonTexture = source.idleEasyButtonTexture;
    this->activeEasyButtonTexture = source.activeEasyButtonTexture;
    this->idleHardButtonTexture = source.idleHardButtonTexture;
    this->activeHardButtonTexture = source.activeHardButtonTexture;
    this->idleBackButtonTexture = source.idleBackButtonTexture;
    this->activeBackButtonTexture = source.activeBackButtonTexture;
    this->idleInstructionsButton = source.idleInstructionsButton;
    this->activeInstructionsButton = source.activeInstructionsButton;
    this->backgroundSprite = source.backgroundSprite;
    this->mousePosition = source.mousePosition;
    this->event = source.event;
    this->easyButton = new Button(*(source.easyButton));
    this->hardButton = new Button(*(source.hardButton));
    this->backButton = new Button(*(source.backButton));
    this->instructionsButton = new Button(*(source.instructionsButton));
}

DifficultySelection::~DifficultySelection() {
    delete this->easyButton;
    this->easyButton = nullptr;

    delete this->hardButton;
    this->hardButton = nullptr;

    delete this->backButton;
    this->backButton = nullptr;

    delete this->instructionsButton;
    this->instructionsButton = nullptr;
}

screen::DifficultySelection &DifficultySelection::operator=(const DifficultySelection &source) {
    if (this == &source) {
        return *this;
    } else {
        this->difficultyBackgroundTexture = source.difficultyBackgroundTexture;
        this->idleEasyButtonTexture = source.idleEasyButtonTexture;
        this->activeEasyButtonTexture = source.activeEasyButtonTexture;
        this->idleHardButtonTexture = source.idleHardButtonTexture;
        this->activeHardButtonTexture = source.activeHardButtonTexture;
        this->idleBackButtonTexture = source.idleBackButtonTexture;
        this->activeBackButtonTexture = source.activeBackButtonTexture;
        this->idleInstructionsButton = source.idleInstructionsButton;
        this->activeInstructionsButton = source.activeInstructionsButton;
        this->backgroundSprite = source.backgroundSprite;
        this->mousePosition = source.mousePosition;
        this->event = source.event;
        this->easyButton = source.easyButton;
        this->hardButton = source.hardButton;
        this->backButton = source.backButton;
        this->instructionsButton = source.instructionsButton;
        return *this;
    }
}

void DifficultySelection::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    State::updateMousePosition(gui, mousePosition);
    this->easyButton->updateButtonState(mousePosition);
    this->hardButton->updateButtonState(mousePosition);
    this->backButton->updateButtonState(mousePosition);
    this->instructionsButton->updateButtonState(mousePosition);
}

void DifficultySelection::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->easyButton->getButtonState())) {
                    State::difficulty = State::Difficulty::EASY;
                    State::changeScreen(Screens::FLEET_PLACEMENT);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->hardButton->getButtonState())) {
                    State::difficulty = State::Difficulty::HARD;
                    State::changeScreen(Screens::FLEET_PLACEMENT);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->backButton->getButtonState())) {
                    State::changeScreen(Screens::GAME_MODE_SELECTION);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->instructionsButton->getButtonState())) {
                    State::changeScreen(Screens::INSTRUCTIONS);
                    break;
                } else {
                    break;
                }

            default:
                break;
        }
    }
}

void DifficultySelection::render(sf::RenderWindow &gui) {
    gui.clear();

    gui.draw(this->backgroundSprite);
    easyButton->render(gui);
    hardButton->render(gui);
    backButton->render(gui);
    instructionsButton->render(gui);

    if (State::getCurrentScreen() == Screens::DIFFICULTY_SELECTION) {
        gui.display();
    }
}

void DifficultySelection::run(sf::RenderWindow &gui) {
    this->update(gui, this->mousePosition);
    this->poll(gui);
    this->render(gui);
}