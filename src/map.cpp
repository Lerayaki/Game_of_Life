#include "map.hpp"

Map::Map(){   
    isEvenTurn = false; 
    for (int y=0; y<CONFIG_WINDOW_HEIGHT; y++)
        for (int x=0; x<CONFIG_WINDOW_WIDTH; x++)
            cells[y][x][isEvenTurn] = trand::trandbool(STARTING_ALIVE_PROBABILITY);
}

void Map::update(){

    for (int y=0; y<CONFIG_WINDOW_HEIGHT; y++)
        for (int x=0; x<CONFIG_WINDOW_WIDTH; x++){
            int alive = 0;
            for (int i=std::max(y-1,0); i<=std::min(y+1,CONFIG_WINDOW_HEIGHT); i++)
                for (int j=std::max(x-1,0); j<=std::min(x+1,CONFIG_WINDOW_WIDTH); j++)
                    if ((i!=y || j!=x) && cells[i][j][isEvenTurn])
                        alive++;
                
            cells[y][x][!isEvenTurn] = (cells[y][x][isEvenTurn] ? (alive>1 && alive<4) : alive==3);
        }

    isEvenTurn = !isEvenTurn;
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = NULL;

        int pixelCount = 0;
        sf::VertexArray pixels(sf::Points,pixelCount);
        for (int y=0; y<CONFIG_WINDOW_HEIGHT; y++)
            for (int x=0; x<CONFIG_WINDOW_WIDTH; x++)
                if (cells[y][x][isEvenTurn]) {
                    sf::Vertex point(sf::Vector2f(x, y), sf::Color::White);
                    pixels.resize(pixelCount++);
                    pixels.append(point);
                }

        target.draw(pixels, states);
    }


    