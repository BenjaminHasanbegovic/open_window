#include "../includes/sceneHandler.h"
#include "../includes/eventListener.h"
#include <utility>
#include <ranges>

// static members
std::vector<SceneHandler*> SceneHandler::instances{};
std::string SceneHandler::currentScene{};
std::pmr::unordered_map<sf::Event::EventType,std::pmr::unordered_map<std::string, EventListener*>> eventListeners{};


SceneHandler::SceneHandler(
    sf::RenderWindow &window,
    std::function<void()> mainLoop,
    const std::string &backgroundTrackPath,
    const bool autoPlayBackgroundTrack
)
    : autoPlayBackgroundTrack(autoPlayBackgroundTrack),
      window(&window),
      mainLoop(std::move(mainLoop))
{
    // Ensure ID is initialized
    if (id.empty()) {
        id = "Scene"; // default base name
    }

    // Ensure unique IDs
    uint numOfRenamedIds{1};
    while (true) {

        auto instanceIt = std::ranges::find_if(instances,
            [this](const SceneHandler* e) { return e->getId() == this->id; }
        );

        if (instanceIt == instances.end())
            break;

        this->id = "Scene_" + std::to_string(numOfRenamedIds);
        numOfRenamedIds++;
    }

    instances.push_back(this);

    // Audio setup
    if (!backgroundTrackPath.empty()) {
        loadBackgroundMusic(backgroundTrackPath);
        if (autoPlayBackgroundTrack && backgroundTrack) {
            backgroundTrack->play();
        }
    }
}

void SceneHandler::open() const {
    currentScene = getId();

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                continue;
            }
            if (!this->eventListeners.empty()) {
                auto iteration = this->eventListeners.find(event.type);
                if (iteration != this->eventListeners.end()) {
                    for (const auto &listener: iteration->second | std::views::values) {
                        if (listener && listener->getIsListeningStatus()) {
                            listener->getCallback()(event);
                        }
                    }
                }
            }
            if (!EventListener::globalInstances.empty()) {
                auto iteration = EventListener::globalInstances.find(event.type);

                if (iteration != EventListener::globalInstances.end()) {
                    for (const auto &listener: iteration->second | std::views::values) {
                        if (listener && listener->getIsListeningStatus()) {
                            listener->getCallback()(event);
                        }
                    }
                }
            }
        }

        window->clear(sf::Color::Black);

        // Run main loop logic
        if (mainLoop) {
            mainLoop();
        }

        window->display();
    }
}
