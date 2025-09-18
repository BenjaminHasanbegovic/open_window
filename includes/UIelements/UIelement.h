#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class UIelement {
public:
    virtual ~UIelement() = default;
    //Getters
    //Identification
    std::string getId()const {return id;};
    std::string getClassName()const{return className;};

    //Hierarchy
    std::string getParentId()const{return  parent->getId();};
    std::vector<UIelement*> getChildren()const;

    //Styling attributes
    sf::Vector2f getPosition()const{return position;};
    sf::Vector2f getSize()const{return size;};
    double getRotation()const{return rotation;};
    int getZIndex()const{return zIndex;};
    bool isVisible()const{return visible;};
    sf::Color getBackgroundColor()const{return backgroundColor;};
    sf::Color getBorderColor()const{return borderColor;};
    uint32_t getBorderThickness()const{return borderThickness;};
    //Text attributes
    sf::Font getFont()const{return font;};
    sf::Color getFontColor()const{return fontColor;};
protected:
    //Identification
    std::string id;
    std::string className;

    //Hierarchy
    UIelement* parent = nullptr;
    std::vector<UIelement*> children;

    //Styling attributes
    sf::Vector2f position;
    sf::Vector2f size;
    double rotation = 0;
    int zIndex = 0;
    bool visible{true};
    sf::Color backgroundColor = sf::Color::Transparent;
    sf::Color borderColor = sf::Color::Transparent;
    uint32_t borderThickness{1};

    //Text attributes
    const std::string defaultFontPath = "resources/fonts/Roboto-Regular.ttf";
    sf::Font font = [](const std::string& fontPath) {
        sf::Font font;
        if (!font.loadFromFile(fontPath)) {
            std::cout << "Failed to load font: " << fontPath <<".\nInstead the default font path will be used :" <<std::endl;
        };
        return font;
    }(defaultFontPath);
    sf::Color fontColor = sf::Color::White;

    //Rendering
    virtual void render() = 0;
    std::string content;
    std::string placeholder = "PLACEHOLDER";

    //Event logic
    std::string allowedEventTypes[41]={
        "keyPressed",
        "keyDown",
        "keyReleased",
        "mouseClick",
        "mouseDoubleClick",
        "mouseDown",
        "mouseUp",
        "scrollWheelMove",
        "mouseMove",
        "mouseEnter",
        "mouseLeave",
        "onFocus",
        "onLostFocus",
        "onSelect",
        "onDeselect",
        "onEnable",
        "onDisable",
        "onLoad",
        "onRender",
        "onRemove",
        "onNewStyleChange",
        "onNewPosition",
        "onNewSize",
        "onNewRotation",
        "onNewZindex",
        "onNewBackgroundColor",
        "onNewBorderColor",
        "onNewBorderThickness",
        "onNewFontColor",
        "onNewFont",
        "onFontLoad",
        "onContentChange",
        "onInput",
        "onPlaceholderChange",
        "onVisibilityChange",
        "onHierarchyChange",
        "onNewParent",
        "onNewChild",
        "onRemoveChild",
        "onNewId",
        "onNewClassName",
    };
};