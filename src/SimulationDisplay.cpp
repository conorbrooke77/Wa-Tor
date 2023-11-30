// Commentary: 
// 
// 
// 
// 
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// some helpful code here!
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// https://www.sfml-dev.org/tutorials/2.5/start-linux.php
// https://learnsfml.com/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Code:

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SeaCreature.hpp"

using namespace sf;

class SimulationDisplay {
private:
    int xdimension;
    int ydimension;
    int windowXSize;
    int windowYSize;
    std::vector<std::vector<RectangleShape>> simulationGrid;

    void initializeGrid() {
        int cellXSize = windowXSize / xdimension;
        int cellYSize = windowYSize / ydimension;
        simulationGrid.resize(xdimension, std::vector<RectangleShape>(ydimension));

        for (int i = 0; i < xdimension; ++i) {
            for (int k = 0; k < ydimension; ++k) {
                simulationGrid[i][k].setSize(Vector2f(cellXSize, cellYSize)); // Consider using cellXSize and cellYSize
                simulationGrid[i][k].setPosition(i * cellXSize, k * cellYSize);
            }
        }
    }

public:

    SimulationDisplay(int xdimension, int ydimension, int gridSize) {
        this->xdimension = xdimension;
        this->ydimension = ydimension; 

        windowXSize = gridSize;
        windowYSize = gridSize;
        initializeGrid();
    }
        
    void updateGrid(std::vector<SeaCreature*> seaCreatures) {

        // Clear the grid to set it to a default state
        for (int i = 0; i < xdimension; ++i) {
            for (int j = 0; j < ydimension; ++j) {
                simulationGrid[i][j].setFillColor(sf::Color::Blue); // Default color for empty cells
            }
        }

            // Update based on sea creatures
        for (SeaCreature* creature : seaCreatures) {
            int x = creature->getXPosition();
            int y = creature->getYPosition();

            cout << creature->getType() << endl;

            if (creature->getType() == "FISH")
                simulationGrid[x][y].setFillColor(sf::Color::Green);
            else
                simulationGrid[x][y].setFillColor(sf::Color::Red);
        }
    }

    void renderWindow() {
        RenderWindow window(VideoMode(windowXSize, windowYSize), "SFML Wa-Tor world");

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }

            for (const auto& row : simulationGrid) {
                for (const auto& cell : row) {
                    window.draw(cell);
                }
            }
            window.display();
        }
    }

    int getXDimension() const { 
        return xdimension; 
    }
    int getYDimension() const { 
        return ydimension; 
    }
    int getWindowWidth() const { 
        return windowXSize; 
    }
    int getWindowHeight() const { 
        return windowYSize; 
    }

};
