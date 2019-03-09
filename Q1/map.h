#if !defined(MAP_H)
#define MAP_H
#include<string>

class CMap
{
private:
    struct Node //for constructing the map
    {
        int value; //height of the point
        bool inRoute; //used in finding route, if "true" its in route, if not its not
    };
    Node** map; 

    std::string route; //used in finding best route, ex: rrdd means right right down down

    int number; //number of one dimention
    int distance; //distance of founded route
    int minDistance; //distance calculated in part c

    int type; //1 is for part a 2 is for part 2

    void showMap(); //prints the map
    int findRoute(); //calls function below
    int findRoute(int i, int j); //finds a route
    
    void findBestRoute(); //Calls function below
    void findBestRoute(int i, int j, int currentDistance, std::string path); //finds best route in part c
    
    void showRoute(); //prints the route
    void pathToRoute(); //gives value to Node.inRoute based on string path
    
public:
    CMap(int n);
    CMap();
    ~CMap();
};


#endif // MAP_H
