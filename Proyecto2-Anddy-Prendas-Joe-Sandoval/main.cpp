#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class PointNode {
private:
    std::string name;
    int x;
    int y;
    std::string color;
    PointNode* next;
    PointNode* prev;
public:
    PointNode() {

    }
    PointNode(std::string name, int x, int y) {
        this->name = name;
        this->x = x;
        this->y = y;
        this->next = nullptr;
        this->prev = nullptr;
    }
    void setColor(std::string nColor) {
        color = nColor;
    }
    std::string getColor() {
        return this->color;
    }
    std::string getName() {
        return this->name;
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    PointNode* getNext() {
        return this->next;
    }
    PointNode* getPrev() {
        return this->prev;
    }
    void setName(std::string name) {
        this->name = name;
    }
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }
    void setNext(PointNode* next) {
        this->next = next;
    }
    void setPrev(PointNode* prev) {
        this->prev = prev;
    }
};
class PointList {
private:
    PointNode* head;
public:
    PointList() {
        this->head = nullptr;
    }
    void insertPoint(std::string name, int x, int y) {
        PointNode* newNode = new PointNode(name, x, y);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            PointNode* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNode);
            newNode->setPrev(current);
        }
    }
    void paintPoints(std::string sName, std::string newColor) {
        PointNode* current = head;
        while (current != nullptr and current->getName() != sName) {
            current = current->getNext();
        }
        if (current->getName() == sName) {
            current->setColor(newColor);
        }
        else {
            std::cout << "No se encontro este punto";
        }
    }
    bool isUniqueName(std::string name) { //Cambiar nombre
        PointNode* current = head;
        while (current != nullptr) {
            if (current->getName() == name) {
                return false;
            }
            current = current->getNext();
        }
        return true;
    }
    void displayPoints() {
        PointNode* current = head;
        while (current != nullptr) {
            std::cout << current->getName() << ", ";
            current = current->getNext();
        }
    }
    void drawPoints(sf::RenderWindow& window) {
        PointNode* current = head;
        while (current != nullptr) {
            sf::CircleShape pointCircle(5);
            pointCircle.setPosition(current->getX(), current->getY());

            if (current->getColor() == "Negro") {
                pointCircle.setFillColor(sf::Color::Black);
            }
            else if (current->getColor() == "Rojo") {
                pointCircle.setFillColor(sf::Color::Red);
            }
            else if (current->getColor() == "Azul") {
                pointCircle.setFillColor(sf::Color::Blue);
            }
            else if (current->getColor() == "Blanco") {
                pointCircle.setFillColor(sf::Color::White);
            }
            window.draw(pointCircle);
            // Dibujahacia el siguiente punto
            if (current->getNext() != nullptr) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(current->getX() + 5, current->getY() + 5), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(current->getNext()->getX() + 5, current->getNext()->getY() + 5), sf::Color::Blue)
                };
                window.draw(line, 2, sf::Lines);
            }
            current = current->getNext();
        }
    }
};
class RouteNode {
private:
    std::string name;
    PointList pointList;
    RouteNode* next;
    RouteNode* prev;
public:
    RouteNode() {
    }
    RouteNode(std::string name) {
        this->name = name;
    }
    std::string getName() {
        return this->name;
    }
    PointList& getPointList() {
        return this->pointList;
    }
    RouteNode* getNext() {
        return this->next;
    }
    RouteNode* getPrev() {
        return this->prev;
    }
    void setName(std::string name) {
        this->name = name;
    }
    void setPointList(PointList pointList) {
        this->pointList = pointList;
    }
    void setNext(RouteNode* next) {
        this->next = next;
    }
    void setPrev(RouteNode* prev) {
        this->prev = prev;
    }
    void drawList(sf::RenderWindow& window) {
        this->pointList.drawPoints(window);
    }
};
class RouteList {
private:
    RouteNode* head;
public:
    RouteList() {
        this->head = nullptr;
    }
    void insertRoute(std::string name) {
        RouteNode* newNode = new RouteNode(name);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            RouteNode* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNode);
            newNode->setPrev(current);
        }
    }
    RouteNode* searchRoute(std::string name) {
        RouteNode* current = head;
        while (current != nullptr) {
            if (current->getName() == name) {
                return current;
            }
            current = current->getNext();
        }
        return nullptr;
    }
    bool isUniqueName(std::string name) {
        RouteNode* current = head;
        while (current != nullptr) {
            if (!current->getPointList().isUniqueName(name)) {
                return false;
            }
            current = current->getNext();
        }
        return true;
    }
    void insertPointToRoute(std::string name) {
        RouteNode* current = head;
        while (current != nullptr && current->getName() != name) {
            current = current->getNext();
        }
        if (current != nullptr) {
            std::string name;
            std::cout << "Nombre del punto: ";
            std::cin >> name;
            if (isUniqueName(name)) {
                current->getPointList().insertPoint(name, 50, 100);
            }
        }
    }
    void removeRoute(std::string name) {
        if (head == nullptr) return;
        if (head->getName() == name) {
            RouteNode* temp = head;
            head = head->getNext();
            delete temp;
            return;
        }
        RouteNode* current = head->getNext();
        while (current != nullptr) {
            if (current->getName() == name) {
                current->getPrev()->setNext(current->getNext());
                current->getNext()->setPrev(current->getPrev());
                delete current;
                return;
            }
            current = current->getNext();
        }
    }
    void showRoutes(sf::RenderWindow& window) {
        int counter = 330;

        sf::Font font;
        if (!font.loadFromFile("Nobile-Regular.ttf")) {
            std::cerr << "no se cargo la fuente jijijija\n";
            return;
        }
        RouteNode* current = head;
        while (current != nullptr) {
            sf::Text currentText;
            currentText.setFont(font);
            currentText.setFillColor(sf::Color::White);
            currentText.setCharacterSize(10);
            currentText.setString(current->getName());
            currentText.setPosition(5, counter);

            window.draw(currentText);
            counter = counter + 11;
            current = current->getNext();
        }
    }
    void drawRoute(sf::RenderWindow& window) {
        RouteNode* current = head;
        while (current != nullptr) {
            current->drawList(window);
            current = current->getNext();
        }
    }
    RouteNode* getRoute(std::string nName) {
        RouteNode* current = head;
        while (current != nullptr and current->getName() != nName) {
            current = current->getNext();
        }
        if (current == nullptr) {
            std::cout << "no se encontro esta ruta\n";
        }
        else {
            return current;
        }
    }
};
int main() {
    RouteList routes;
    sf::Font font;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mapa turistico");
    //boton crear rutas nueevcas
    sf::RectangleShape bCreateRoutes(sf::Vector2f(120, 30));
    bCreateRoutes.setPosition(5, 560);
    bCreateRoutes.setFillColor(sf::Color::Black);
    if (!font.loadFromFile("Nobile-Regular.ttf")) {
        std::cerr << "no se cargo la fuente jijijija\n";
        return -1;
    }
    sf::Text createText;
    createText.setFont(font);
    createText.setString("Crear nueva ruta");
    createText.setCharacterSize(14);
    createText.setFillColor(sf::Color::White);
    createText.setPosition(
        bCreateRoutes.getPosition().x + (bCreateRoutes.getSize().x / 2) - createText.getGlobalBounds().width / 2,
        bCreateRoutes.getPosition().y + (bCreateRoutes.getSize().y / 2) - createText.getGlobalBounds().height / 2
    );
    //pantalla de lista de rutas
    sf::RectangleShape listScreen(sf::Vector2f(110, 200));
    listScreen.setPosition(5, 315);
    listScreen.setFillColor(sf::Color::Black);
    if (!font.loadFromFile("Nobile-Regular.ttf")) {
        std::cerr << "no se cargo la fuente jijijija\n";
        return -1;
    }
    sf::Text listText;
    listText.setFont(font);
    listText.setString("Lista de rutas:");
    listText.setCharacterSize(11);
    listText.setFillColor(sf::Color::Yellow);
    listText.setPosition(
        listScreen.getPosition().x + (listScreen.getSize().x / 2) - listText.getGlobalBounds().width + 17,
        listScreen.getPosition().y + (listScreen.getSize().y / 2) - listText.getGlobalBounds().height - 90
    );
    //botonsito negro
    sf::CircleShape blackB;
    blackB.setRadius(18);
    blackB.setPosition(695, 560);
    blackB.setFillColor(sf::Color::Black);
    //boton rojo
    sf::CircleShape redB;
    redB.setRadius(18);
    redB.setPosition(695, 520);
    redB.setFillColor(sf::Color::Red);
    // botonsito azul
    sf::CircleShape blueB;
    blueB.setRadius(18);
    blueB.setPosition(695, 480);
    blueB.setFillColor(sf::Color::Blue);
    // botonsito blanco
    sf::CircleShape whiteB;
    whiteB.setRadius(18);
    whiteB.setPosition(695, 440);
    whiteB.setFillColor(sf::Color::White);
    //botonsito marcar puntos
    sf::RectangleShape bPutPoints(sf::Vector2f(120, 30));
    bPutPoints.setPosition(5, 525);
    bPutPoints.setFillColor(sf::Color::Black);
    if (!font.loadFromFile("Nobile-Regular.ttf")) {
        std::cerr << "no se cargo la fuente jijijija\n";
        return -1;
    }
    sf::Text putPointsText;
    putPointsText.setFont(font);
    putPointsText.setString("Marcar puntos");
    putPointsText.setCharacterSize(14);
    putPointsText.setFillColor(sf::Color::White);
    putPointsText.setPosition(
        bPutPoints.getPosition().x + (bPutPoints.getSize().x / 2) - bPutPoints.getGlobalBounds().width / 2,
        bPutPoints.getPosition().y + (bPutPoints.getSize().y / 2) - bPutPoints.getGlobalBounds().height / 2
    );
    // botn para eliminar rutas
    sf::RectangleShape deleteRouteB(sf::Vector2f(120, 30));
    deleteRouteB.setPosition(130, 560);
    deleteRouteB.setFillColor(sf::Color::Black);
    if (!font.loadFromFile("Nobile-Regular.ttf")) {
        std::cerr << "no se cargo la fuente jijijija\n";
        return -1;
    }
    sf::Text deleteText;
    deleteText.setFont(font);
    deleteText.setString("Eliminar Ruta");
    deleteText.setCharacterSize(14);
    deleteText.setFillColor(sf::Color::White);
    deleteText.setPosition(
        deleteRouteB.getPosition().x + (deleteRouteB.getSize().x / 2) - deleteRouteB.getGlobalBounds().width / 2,
        deleteRouteB.getPosition().y + (deleteRouteB.getSize().y / 2) - deleteRouteB.getGlobalBounds().height / 2
    );
    //mapa
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("map.jpeg")) {
        std::cerr << "no se cargo el mapa\n";
        return -1;
    }
    bool isAllowedToMark = false;
    std::string pointColor = "Negro";
    std::string auxName;
    sf::Sprite fondoSprite;
    fondoSprite.setTexture(fondoTexture);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left and isAllowedToMark == true) {
                std::string namePoint;
                std::cout << "Ingrese el nombre del punto: ";
                getline(std::cin, namePoint);
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                routes.getRoute(auxName)->getPointList().insertPoint(namePoint, x, y);
                routes.getRoute(auxName)->getPointList().paintPoints(namePoint, pointColor);
                std::cout << "Punto agregado en (" << x << ", " << y << ")\n";
                isAllowedToMark = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (bCreateRoutes.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "se ha presionado el boton de crear nueva ruta\n";
                        std::string nameRoute1;
                        std::cout << "Ingrese el nombre de la ruta: ";
                        getline(std::cin, nameRoute1);
                        routes.insertRoute(nameRoute1);
                    }
                    else if (bPutPoints.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::string nameRoute2;
                        std::cout << "Ingrese el nombre de la ruta que quiere modificar: ";
                        getline(std::cin, nameRoute2);
                        auxName = nameRoute2;
                        std::cout << "Toque el punto que desea agregar a la ruta" << std::endl;
                        isAllowedToMark = true;
                    }
                    else if (deleteRouteB.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::string aux;
                        std::cout << "\nEscriba el nombre de la ruta que desea eliminar: ";
                        getline(std::cin, aux);
                        routes.removeRoute(aux);
                    }
                    else if (blackB.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        pointColor = "Negro";
                    }
                    else if (redB.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        pointColor = "Rojo";
                    }
                    else if (blueB.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        pointColor = "Azul";
                    }
                    else if (whiteB.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        pointColor = "Blanco";
                    }
                }
            }
        }
        window.clear();
        window.draw(fondoSprite);
        window.draw(listScreen);
        window.draw(listText);
        window.draw(deleteRouteB);
        window.draw(deleteText);
        window.draw(bCreateRoutes);
        window.draw(createText);
        window.draw(bPutPoints);
        window.draw(blackB);
        window.draw(redB);
        window.draw(blueB);
        window.draw(whiteB);
        window.draw(putPointsText);
        routes.drawRoute(window);
        routes.showRoutes(window);
        window.display();
    }
    return 0;
}



