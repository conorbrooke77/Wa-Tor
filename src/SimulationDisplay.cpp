// Commentary: 
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
    const int WINDOW_X_SIZE = 900;
    const int WINDOW_Y_SIZE = 1000;

    std::vector<std::vector<RectangleShape>> simulationGrid;
    std::vector<std::pair<int, int>> cellsToReset;
    RenderWindow window;
    Font font;

    void initializeGrid() {
        int cellXSize = WINDOW_X_SIZE / xdimension;
        int cellYSize = (WINDOW_Y_SIZE-100) / ydimension;
        simulationGrid.resize(xdimension, std::vector<RectangleShape>(ydimension));
        font.loadFromFile("src/Roboto-Regular.ttf");

        for (int i = 0; i < xdimension; ++i) {
            for (int k = 0; k < ydimension; ++k) {
                simulationGrid[i][k].setSize(Vector2f(cellXSize, cellYSize));
                simulationGrid[i][k].setPosition(i * cellXSize, k * cellYSize);
            }
        }
    }

public:

    SimulationDisplay(int gridSize) {
        xdimension = gridSize;
        ydimension = gridSize; 

        window.create(VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "SFML Wa-Tor world");
        initializeGrid();
    }
        
    void updateGrid(const vector<vector<SeaCreature*>>& grid) {
        
        #pragma omp parallel
        {
            std::vector<std::pair<int, int>> localCellsToReset;

            #pragma omp for nowait
            for (int i = 0; i < grid.size(); ++i) {
                for (int j = 0; j < grid[i].size(); ++j) {
                    SeaCreature* creature = grid[i][j];
                    if (creature != nullptr && creature->updateState()) {
                        // Update cell color based on the creature type
                        if (creature->getType() == "FISH")
                            if (creature->isEaten())
                                simulationGrid[i][j].setFillColor(sf::Color::Blue);
                            else
                                simulationGrid[i][j].setFillColor(sf::Color::Green);
                        else if (creature->getType() == "SHARK") {
                            if (creature->isStarved())
                                simulationGrid[i][j].setFillColor(sf::Color::Blue);
                            else
                                simulationGrid[i][j].setFillColor(sf::Color::Red);
                        }

                        if (creature->oldXPosition != -1)
                            localCellsToReset.push_back({creature->oldXPosition, creature->oldYPosition});
                    }
                }
            }
            #pragma omp critical
            cellsToReset.insert(cellsToReset.end(), localCellsToReset.begin(), localCellsToReset.end());
        }
    }

    void initializeRenderWindow() {
        for (int i = 0; i < simulationGrid.size(); i++) {
            for (int j = 0; j < simulationGrid[i].size(); j++) {
                simulationGrid[i][j].setFillColor(sf::Color::Blue); // Set each cell to blue
                window.draw(simulationGrid[i][j]);
            }
        }
    }

    void renderWindow(const vector<vector<SeaCreature*>>& grid, int fishPopulation, int sharkPopulation) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                std::cout << "Closing window" << std::endl;
                window.close();
            }
        }

        for (int i = 0; i < simulationGrid.size(); i++) {
            for (int j = 0; j < simulationGrid[i].size(); j++) {
                SeaCreature* creature = grid[i][j];
                if (creature != nullptr && creature->updateState()) {
                    window.draw(simulationGrid[i][j]);  // Draw only changed cells
                    creature->setMoved(false); // Reset the changed flag
                }
            }
        }

            // Reset the cells to blue
        for (auto& position : cellsToReset) {
            simulationGrid[position.first][position.second].setFillColor(sf::Color::Blue);
            window.draw(simulationGrid[position.first][position.second]); // Optionally draw them immediately
            cellsToReset.clear();
        }
        sf::RectangleShape clearArea(sf::Vector2f(window.getSize().x, 100));
        clearArea.setPosition(0, window.getSize().y - 100);
        clearArea.setFillColor(sf::Color::Black);  // Set the color to the background color of your window

        // Draw the clearArea rectangle over the bottom 100 pixels
        window.draw(clearArea);

        // Draw population scores
        sf::Text fishText;
        fishText.setFont(font);
        fishText.setString("Fish Population: " + std::to_string(fishPopulation));
        fishText.setCharacterSize(24);
        fishText.setFillColor(sf::Color::White);
        fishText.setPosition(30, window.getSize().y - 100);

        sf::Text sharkText;
        sharkText.setFont(font);
        sharkText.setString("Shark Population: " + std::to_string(sharkPopulation));
        sharkText.setCharacterSize(24); 
        sharkText.setFillColor(sf::Color::White);
        sharkText.setPosition(30, window.getSize().y - 70);

        window.draw(fishText);
        window.draw(sharkText);

        window.display();
    }

    bool isWindowOpen() {
        return window.isOpen();
    }

};
