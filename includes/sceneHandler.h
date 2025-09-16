#pragma once
#include "UIelements/UIelement.h"
#include <memory>
#include <SFML/Audio.hpp>
#include <functional>

class EventListener;

class SceneHandler {
    public:
    SceneHandler(sf::RenderWindow &window, std::function<void()> mainLoop, const std::string &backgroundTrackPath,
                  bool autoPlayBackgroundTrack);

    std::pmr::unordered_map<sf::Event::EventType,std::pmr::unordered_map<std::string, EventListener*>> eventListeners;


    //Window handling
    void open() const;

    //Audio
    bool autoPlayBackgroundTrack{false};
    //Setters
    //Audio
    void loadBackgroundMusic(const std::string& trackPath) {
        backgroundTrack = std::make_unique<sf::Music>();
        if (!backgroundTrack->openFromFile(trackPath)) {
            backgroundTrack = nullptr; // Failed to load
        }
    }
    void playBackgroundTrack()const {if (backgroundTrack) backgroundTrack->play();}
    void stopBackgroundTrack()const {if (backgroundTrack) backgroundTrack->stop();}
    void pauseBackgroundTrack()const {if (backgroundTrack) backgroundTrack->pause();}
    //Identification
    void setId(const std::string& newId){id = newId;};
    //Getters
    //Window logic


    //Audio
    [[nodiscard]] uint64_t getBackgroundTrackTimestamp()const {
        if (backgroundTrack) {
            return backgroundTrack->getPlayingOffset().asMicroseconds();
        }else {
            return 0;
        }
    };
    [[nodiscard]] uint64_t getBackgroundTrackLength()const {
       if (backgroundTrack) {
           return backgroundTrack->getDuration().asMicroseconds();
       }else {
           return 0;
       }
   };
    [[nodiscard]] float getBackgroundTrackVolume()const {
        if (backgroundTrack) {
            return backgroundTrack->getVolume();
        }else {
            return 0.f;
        }
    };
    [[nodiscard]] float getBackgroundTrackPitch()const {
        if (backgroundTrack) {
            return backgroundTrack->getPitch();
        }else {
            return 0.f;
        }
    };
    [[nodiscard]] float getBackgroundTrackAttenuation()const {
        if (backgroundTrack) {
            return backgroundTrack->getAttenuation();
        }else {
            return 0.f;
        }
    };
    [[nodiscard]] bool backgroundMusicLoops()const {
        if (backgroundTrack) {
            return backgroundTrack->getLoop();
        }else {
            //False because if there is no music there is no looping
            return false;
        }
    };
    [[nodiscard]] sf::SoundSource::Status getBackgroundSongStatus()const {
        if (backgroundTrack) {
            return backgroundTrack->getStatus();
        }else {
            return sf::SoundSource::Stopped;
        }
    };
    //Identification
    [[nodiscard]] const std::string& getId() const { return id; }
protected:
    //Identification
    std::string id;


    //Window logic
    sf::RenderWindow *window = nullptr;
    std::function<void()> mainLoop;

    //Scene logic
    std::vector<std::unique_ptr<UIelement>> elements;

    //Audio
    std::unique_ptr<sf::Music> backgroundTrack;
private:
    static std::vector<SceneHandler*> instances;
    static std::string currentScene;
};