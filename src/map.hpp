#include <SFML/Graphics.hpp>

#include "../cfg/config.hpp"
#include "trand.hpp"

class Map : public sf::Drawable, public sf::Transformable{
public:    
    Map();
    void update();
private:
    bool cells[CONFIG_WINDOW_HEIGHT][CONFIG_WINDOW_WIDTH][2];
    bool isEvenTurn;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};