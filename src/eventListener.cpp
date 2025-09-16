#include "../includes/sceneHandler.h"
#include "../includes/eventListener.h"
#include <utility>

//Static members
std::pmr::unordered_map<
    sf::Event::EventType,
    std::pmr::unordered_map<std::string, EventListener*>
> EventListener::globalInstances{};

void searchForDuplicatesIds(auto &mapToSearch, std::string &baseId) {
    uint suffix = 1;
    const std::string originalId = baseId;

    while (true) {
        const bool foundDuplicateId = std::ranges::any_of(
            mapToSearch,
            [&](const auto& pair) {
                return pair.second.contains(baseId);
            }
        );
        if (!foundDuplicateId) break;
        baseId = originalId + std::to_string(suffix++);
    }
}
EventListener::EventListener(
    std::string id,
    const sf::Event::EventType eventType,
    std::function<void(const sf::Event&)> callback,
    const bool listenAutomatically,
    const bool restrictedToElement,
    UIelement* parentElement)
    : listening(listenAutomatically),
      eventType(eventType),
      callback(std::move(callback)),
      isGlobal(true),
      id(std::move(id)),
      parentElement(parentElement),
      restrictedToElement(restrictedToElement)
{
    searchForDuplicatesIds(globalInstances, this->id);
    globalInstances[eventType].emplace(this->id, this);
}

EventListener::EventListener(
    std::string id,
    SceneHandler* scene,
    const sf::Event::EventType eventType,
    std::function<void(const sf::Event&)> callback,
    const bool listenAutomatically,
    const bool restrictedToElement,
    UIelement* parentElement)
    : listening(listenAutomatically),
      eventType(eventType),
      callback(std::move(callback)),
      id(std::move(id)),
      parentElement(parentElement),
      restrictedToElement(restrictedToElement)
{
    searchForDuplicatesIds(scene->eventListeners, this->id);
    scene->eventListeners[eventType].emplace(this->id, this);

}