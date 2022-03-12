#include <SFML/Graphics.hpp>

#include "../cfg/config.hpp"
#include "trand.hpp"

class Map : public sf::Drawable, public sf::Transformable{
public:    
    Map();
    Map(const sf::Color&);
    void update();
private:
    const int _mapWidth = CONFIG_WINDOW_WIDTH / CONFIG_CELL_SCALE_FACTOR;
    const int _mapHeight = (CONFIG_WINDOW_HEIGHT - CONFIG_WINDOW_LEGEND_HEIGHT) / CONFIG_CELL_SCALE_FACTOR;
    sf::Color mapColor = sf::Color::White;

    bool cellMap[CONFIG_WINDOW_HEIGHT][CONFIG_WINDOW_WIDTH][2];
    bool isEvenTurn;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};