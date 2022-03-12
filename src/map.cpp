#include "map.hpp"

Map::Map(){   
    isEvenTurn = false; 
    for (int y=0; y<_mapHeight; y++)
        for (int x=0; x<_mapWidth; x++)
            cellMap[y][x][isEvenTurn] = trand::trandbool(CONFIG_CELL_INIT_TRUE_PROBABILITY);
}

void Map::update(){

    for (int y=0; y<_mapHeight; y++)
        for (int x=0; x<_mapWidth; x++){
            int alive = 0;
            for (int i=std::max(y-1,0); i<=std::min(y+1,_mapHeight); i++)
                for (int j=std::max(x-1,0); j<=std::min(x+1,_mapWidth); j++)
                    if ((i!=y || j!=x) && cellMap[i][j][isEvenTurn])
                        alive++;
                
            cellMap[y][x][!isEvenTurn] = (cellMap[y][x][isEvenTurn] ? (alive>1 && alive<4) : alive==3);
        }

    isEvenTurn = !isEvenTurn;
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = NULL;

        if(CONFIG_CELL_SCALE_FACTOR == 1){
                int pixelCount = 0;
                sf::VertexArray pixels(sf::Points,pixelCount);
                for (int y=0; y<_mapHeight; y++)
                    for (int x=0; x<_mapWidth; x++)
                        if (cellMap[y][x][isEvenTurn]) {
                            sf::Vertex point(sf::Vector2f(x, y), sf::Color::White);
                            pixels.resize(pixelCount++);
                            pixels.append(point);
                        }

                target.draw(pixels, states);
        } else {
                sf::VertexArray cells(sf::Quads);
                for (int y=0; y<_mapHeight; y++)
                    for (int x=0; x<_mapWidth; x++)
                        if (cellMap[y][x][isEvenTurn]) {
                            int cellOriginX = x*CONFIG_CELL_SCALE_FACTOR;
                            int cellOriginY = y*CONFIG_CELL_SCALE_FACTOR;

                            cells.append(sf::Vertex(sf::Vector2f(cellOriginX, cellOriginY), sf::Color::White));
                            cells.append(sf::Vertex(sf::Vector2f(cellOriginX, cellOriginY + CONFIG_CELL_SCALE_FACTOR-1), sf::Color::White));
                            cells.append(sf::Vertex(sf::Vector2f(cellOriginX + CONFIG_CELL_SCALE_FACTOR-1, cellOriginY + CONFIG_CELL_SCALE_FACTOR-1), sf::Color::White));
                            cells.append(sf::Vertex(sf::Vector2f(cellOriginX + CONFIG_CELL_SCALE_FACTOR-1, cellOriginY), sf::Color::White));
                        }

                target.draw(cells, states);
        }
        
    }


    