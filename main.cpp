#include <SFML/Graphics.hpp>
#include "./includes/openWindow.h"
#include "./includes/eventListener.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Testing window");

    // Shapes
    sf::CircleShape greenCircle(50.f);
    greenCircle.setFillColor(sf::Color::Green);
    greenCircle.setOrigin(greenCircle.getRadius(), greenCircle.getRadius());
    greenCircle.setPosition(200.f + greenCircle.getRadius(), 200.f + greenCircle.getRadius());

    sf::CircleShape yellowCircle(50.f);
    yellowCircle.setFillColor(sf::Color::Yellow);
    yellowCircle.setOrigin(yellowCircle.getRadius(), yellowCircle.getRadius());

    bool drawGreen = false;
    bool drawYellow = false;

    // Scene setup
    SceneHandler scene(
        window,
        [&]() {
            if (drawGreen) window.draw(greenCircle);
            if (drawYellow) window.draw(yellowCircle);
        },
        "../ANBR-Continent.ogg",
        false
    );

    // Global EventListener for left mouse click
    EventListener clickListener(
        "toggleYellow",
        &scene,
        sf::Event::MouseButtonPressed,
        [&](const sf::Event& event) {
            if (scene.getBackgroundSongStatus() == 0 || scene.getBackgroundSongStatus() == 1 ) {
                scene.playBackgroundTrack();
            }else {
                scene.pauseBackgroundTrack();
            }
           std::cout << scene.getBackgroundSongStatus();

        },
        true,
        false,
        nullptr
    );

    EventListener clickListener1(
        "toggleYellow",
        &scene,
        sf::Event::MouseButtonPressed,
        [&](const sf::Event& event) {
            if (scene.getBackgroundSongStatus() == 0 || scene.getBackgroundSongStatus() == 1 ) {
                scene.playBackgroundTrack();
            }else {
                scene.pauseBackgroundTrack();
            }
           std::cout << scene.getBackgroundSongStatus();

        },
        true,
        false,
        nullptr
    );


    scene.open();
}
