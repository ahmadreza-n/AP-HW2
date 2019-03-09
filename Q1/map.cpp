#include"map.h"
#include<iostream>
#include<iomanip>

CMap::CMap(int n) : number{n} {
    //implemeting dynamic array
    map = new Node*[number];
    for(int i = 0; i < number; i++)
        map[i] = new Node[number];

    //randomly initialise height of each point
    std::srand(std::time(NULL));
    for(int i = 0; i < number; i++)
        for(int j = 0; j < number; j++){
            map[i][j].value = std::rand() % 100;
            map[i][j].inRoute = false;
        }

    //part a
    type = 1;
    showMap();
    distance = findRoute();
    showRoute();

    for(int i = 0; i < number; i++)
        for(int j = 0; j < number; j++)
            map[i][j].inRoute = false;

    //part b
    type = 2;
    distance = findRoute();
    showRoute();
    
    for(int i = 0; i < number; i++)
        for(int j = 0; j < number; j++)
            map[i][j].inRoute = false;

    //part c
    type = 3;
    minDistance = 2*(number - 1) * 100;
    findBestRoute();
    distance = minDistance;
    pathToRoute();
    showRoute();
}

CMap::CMap() : CMap(0) {
}

CMap::~CMap(){
    for(int i = 0; i < number; i++)
        delete[] map[i];
    
    delete[] map;
}

void CMap::showMap() {
    for(int i = 0; i < number; i++)
    {
        for(int j = 0; j < number; j++)
            std::cout << std::setw(3) << std::setfill(' ') << map[i][j].value;

        std::cout << std::endl;
    }
}

int CMap::findRoute() {
    return findRoute(0, 0);
}

int CMap::findRoute(int i, int j) {
    map[i][j].inRoute = true; //we have passed here

    if((i == number - 1) && (j == number - 1))
        return 0;

    int rightCost{}, downCost{}, diagonalCost{};
    if (i == number - 1) {
        downCost = std::abs(map[i][j + 1].value - map[i][j].value);
        return downCost + findRoute(i, j + 1); //move down
    }

    if (j == number - 1) {
        rightCost = std::abs(map[i + 1][j].value - map[i][j].value);
        return rightCost + findRoute(i + 1, j); //move right
    }

    downCost = std::abs(map[i][j + 1].value - map[i][j].value);
    rightCost = std::abs(map[i + 1][j].value - map[i][j].value);
    diagonalCost = std::abs(map[i + 1][j + 1].value - map[i][j].value);
    if(downCost > rightCost){
        if(type == 1) 
            return rightCost + findRoute(i + 1, j); //move right

        else {    
            if (rightCost > diagonalCost)
                return diagonalCost + findRoute(i + 1, j + 1); //move diagonal         
            else
                return rightCost + findRoute(i + 1, j); //move right
        }
    }

    else
    {
        if(type == 1) 
            return downCost + findRoute(i, j + 1); //move down
        else {
            if (downCost > diagonalCost)
                return diagonalCost + findRoute(i + 1, j + 1); //move diagonal
            else
                return downCost + findRoute(i, j + 1); //move down
        }
    } 

}

void CMap::showRoute() {

    std::cout << "\n Distance: " << distance << "\n" << std::endl;
    char temp = '-';
    for(int i = 0; i < number; i++)
    {
        for(int j = 0; j < number; j++){
            if(map[i][j].inRoute)
                temp = '*';
            else
                temp = '-';
            
            
            std::cout << std::setw(3) << std::setfill(' ') << temp;

        }
        std::cout << std::endl;
    }
}

void CMap::findBestRoute() {
    findBestRoute(0, 0, 0, "");
}

void CMap::findBestRoute(int i, int j, int currentDistance, std::string path) {
    if(currentDistance >= minDistance) //this is not the best route
        return; 
    
    if(i == number - 1 && j == number - 1) {
        minDistance = currentDistance;
        route = path;
        return;
    }   

    int rightCost{}, downCost{};

    if (i == number - 1) {
        rightCost = std::abs(map[i][j + 1].value - map[i][j].value);
        findBestRoute(i, j + 1, currentDistance + rightCost, path + "r"); //move right
        
    }
    else if (j == number - 1) {
        downCost = std::abs(map[i + 1][j].value - map[i][j].value);
        findBestRoute(i + 1, j, currentDistance + downCost, path + "d"); //move down
        
    }
    else
    {
        downCost = std::abs(map[i + 1][j].value - map[i][j].value);
        findBestRoute(i + 1, j, currentDistance + downCost, path + "d"); //move down

        rightCost = std::abs(map[i][j + 1].value - map[i][j].value);
        findBestRoute(i, j + 1, currentDistance + rightCost, path + "r"); //move right
    }
}

void CMap::pathToRoute() {
    size_t rowIndex{}, colIndex{};
    for(size_t i = 0; i < route.length(); i++)
    {
        map[rowIndex][colIndex].inRoute = true;
        if (route[i] == 'r') 
            colIndex++;

        else 
            rowIndex++;        
    }
    map[rowIndex][colIndex].inRoute = true;
}