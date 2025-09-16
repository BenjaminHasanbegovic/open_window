#pragma once
#include "./UIelements/UIelement.h"
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>

class SceneHandler;

class EventListener {
public:
    explicit EventListener(
        std::string id,
        sf::Event::EventType eventType,
         std::function<void(const sf::Event&)> callback,
        bool listenAutomatically,
        bool restrictedToElement,
        UIelement* parentElement);

    explicit EventListener(
        std::string id,
        SceneHandler* scene,
        sf::Event::EventType eventType,
                  std::function<void(const sf::Event &)> callback,
                  bool listenAutomatically,
                  bool restrictedToElement,
                  UIelement *parentElement);

    static std::pmr::unordered_map<sf::Event::EventType,std::pmr::unordered_map<std::string, EventListener*>> globalInstances;
    // Setters
    // Event logic
    void setListeningStatus(const bool isListening) { listening = isListening; }
    void setEventType(const sf::Event::EventType newEventType) { eventType = newEventType; }
    void setCallback(const  std::function<void(const sf::Event&)>& newCallback) { callback = newCallback; }

    // Identification
    void setId(const std::string& newId) { id = newId; }


    // Hierarchy
    void setParentElement(UIelement& elementToAttachTo) { parentElement = &elementToAttachTo; hasParentElement = true; }
    void setRestrictedToElement(const bool isRestricted) { restrictedToElement = isRestricted; }

    //Scope
    void setIsGlobal(const bool global) { isGlobal = global; }

    // Getters
    // Event logic
    [[nodiscard]] bool getIsListeningStatus() const { return listening; }
    [[nodiscard]] sf::Event::EventType getEventType() const { return eventType; }
    [[nodiscard]]  std::function<void(const sf::Event&)> getCallback() const { return callback; }

    // Identification
    [[nodiscard]] std::string getId() const { return id; }
    [[nodiscard]] const std::string* getIdPointer() const { return &id; }

    // Hierarchy
    [[nodiscard]] UIelement* getParentElement() const { return parentElement; }
    [[nodiscard]] bool getIfIsRestrictedToElement() const { return restrictedToElement; }
    [[nodiscard]] bool getHasParentElement() const { return hasParentElement; }

    //Scope
    [[nodiscard]] bool getIsGlobal() const { return isGlobal; }

protected:
    // Event logic
    bool listening{true};
    sf::Event::EventType eventType;
    std::function<void(const sf::Event&)> callback;

    // Scope
    bool isGlobal{false};

    // Identification
    std::string id;

    // Hierarchy
    bool hasParentElement{false};
    UIelement* parentElement{nullptr};
    bool restrictedToElement{false};
};
