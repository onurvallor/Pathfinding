#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>


class GridElement{
private:

    sf::RectangleShape box;
    sf::RenderWindow& p_window;

    float boxDimensions = 20;


public:
    bool isWall = false;

    float x = 0;
    float y = 0;

    GridElement(sf::RenderWindow& window) : p_window(window){
        box.setSize(sf::Vector2f(boxDimensions, boxDimensions));
        box.setFillColor(sf::Color(255, 255, 255));
        //box.setPosition(x,y);
        //std::cout << "Grid Element Created" << std::endl;
    }

    void draw(){
        p_window.draw(box);
    }

    void setPosition(float x, float y) {
        this->y = y;
        this->x = x;

        box.setPosition(this->x, this->y);
    }

    void setColor() {

    }

    void clicked(sf::Event &event) {
        if (event.type == sf::Event::MouseButtonPressed &&
            box.getPosition().x < sf::Mouse::getPosition(p_window).x && 
            box.getPosition().x + boxDimensions > sf::Mouse::getPosition(p_window).x && 
            box.getPosition().y < sf::Mouse::getPosition(p_window).y && 
            box.getPosition().y + boxDimensions > sf::Mouse::getPosition(p_window).y) {
            // std::cout << box.getPosition().x << std::endl;
            
            if (isWall == true) {
                isWall = false;
                std::cout << isWall << std::endl;
                box.setFillColor(sf::Color(255, 255, 255));
                return;
            }
            if (isWall == false) {
                isWall = true;
                std::cout << isWall << std::endl;
                box.setFillColor(sf::Color(255, 0, 255));
                return;
            }

            std::cout << "click!" << std::endl;
        }
    }

};


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    //GridElement element(window);

    std::vector<GridElement> boardItems;
    int boardSize = 10;

    for (int col = 0; col < boardSize; col++) {
        for (int row = 0; row < boardSize; row++) {
            GridElement box(window);
            box.setPosition(25 * col, 25 * row);
            boardItems.push_back(box);
        }
    }
    
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            for (GridElement &box : boardItems) {
                box.clicked(event);
            }

        }
        // Clear screen
        window.clear();

        for (GridElement &box : boardItems) {
            box.draw();
        }


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}