#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//function that calculates the distance between the two points P1(x1,y1) and P2(x2,y2)
float Distance(int x1, int y1, int x2, int y2){
    int x_diff = x1-x2;
    int y_diff = y1-y2;
    float dist_sq = (x_diff * x_diff) + (y_diff * y_diff);
    return sqrt(dist_sq);
}

class TSP{
    private:
        vector<vector<float> > edges;                               //stores the distances between two cities
        vector<pair<int,int> > coordinates;                         //stores the coordinates of the cities
        vector<pair<int,int> > presentEdges;                        //whether or not an edge is present in the tour
        vector<float> minDistToTour;                                //min distance from a city to a vertex in the tour
        vector<bool> inTour;                                        //whether or not a city is present in the tour 
        vector<int> nextCity;                                       //the next city to visit in the tour
        pair<int,int> minPair;                                      //the closest cities 
        int size;                                                   //number of cities
        int count;                                                  //number of cities added to the tour
        int firstCity;                                              //the smaller indexed city in the closest city pair
        
    public:
        //constructor for the TSP class
        TSP(int n){
            size = n;
            count = 0;
            for(int i=0;i<n;i++){
                //initialisation of vectors
                vector<float> tempVector;
                for(int j=0;j<n;j++) tempVector.push_back(0);
                edges.push_back(tempVector);
                inTour.push_back(false);
                nextCity.push_back(0);
                minDistToTour.push_back(0);
            }
        }
        
        //adds a city of given coordiantes to the list of cities
        void getCoordinates(int x, int y){
            pair<int,int> tempPair(x,y);
            coordinates.push_back(tempPair);
        }

        //stores the distances between any two cities
        void assignEdges(){
            float minDist = 2000;                                   //since max dist is 1000*root(2) ~ 1414
            for(int i=0;i<size-1;i++){
                for(int j=i+1;j<size;j++){
                    float dist = Distance(coordinates[i].first, coordinates[i].second, coordinates[j].first, coordinates[j].second);
                    edges[i][j] = dist;
                    edges[j][i] = dist;

                    //finding the closest pair of cities
                    if(dist < minDist){
                        minPair.first = i;
                        minPair.second = j;
                        minDist = dist;
                    }
                }
            }
        }

        //uses the Nearest Neighbour Insertion Algorithm to find the TSP tour
        void nearestNeighbour(){
            inTour[minPair.first] = true;
            inTour[minPair.second] = true;
            nextCity[minPair.first] = minPair.second;
            nextCity[minPair.second] = minPair.first;
            presentEdges.push_back(minPair);
            count = 2;
            firstCity = minPair.first;

            //initialises the distances from those cities not in the tour, to the closest city in the tour
            for(int i=0;i<size;i++){
                if(inTour[i] == false){
                    if(edges[i][minPair.first] < edges[i][minPair.second]){
                        minDistToTour[i] = edges[i][minPair.first];
                    }else{
                        minDistToTour[i] = edges[i][minPair.second];
                    }
                }
            }

            //iteratively adds the city to the tour, which is closest to the tour
            while(count != size){
                float minDist = 2000;
                int minCity;

                //finds the city that is closest to the tour
                for(int i=0;i<size;i++){
                    if(!inTour[i]){
                        if(minDistToTour[i] < minDist){
                            minDist = minDistToTour[i];
                            minCity = i;
                        }
                    }
                }
                inTour[minCity] = true;                             //adds the city(minCity) to the tour                
                
                //updating the closest distance from those cities not in the tour, to those in the tour..
                //..because of the latest city added
                for(int i=0;i<size;i++){
                    if(!inTour[i]){
                        if(edges[i][minCity] < minDistToTour[i]) minDistToTour[i] = edges[i][minCity];
                    }
                }

                //adding the new city into the tour and making appropriate changes to the variables
                minDist = 2000;
                int prevCity;                                       //city before the newly added city in the tour
                int tempNextCity;                                   //city after the newly added city in the tour
                int tempIndex;
                //finding the cities that should be interrupted by the new city (ie) preceeding and succeeding cities
                for(int i=0;i<(int)presentEdges.size();i++){
                    int city1 = presentEdges[i].first;
                    int city2 = presentEdges[i].second;
                    float tempDist = edges[city1][minCity] + edges[minCity][city2] - edges[city1][city2];
                    //finds the minimum change caused by adding the new city
                    if(tempDist < minDist){
                        minDist = tempDist;
                        prevCity = city1;
                        tempNextCity = city2;
                        tempIndex = i;
                    }
                }

                //updates the list of edges present in the tour
                presentEdges[tempIndex].second = minCity;
                pair<int,int> tempPair(minCity,tempNextCity);
                presentEdges.push_back(tempPair);

                nextCity[prevCity] = minCity;
                nextCity[minCity] = tempNextCity;

                count++;
            }
        }

        //calculates and prints the TSP value using the TSP tour
        void printTSPValue(){
            float TSPValue = 0;
            int city1 = firstCity;
            int city2 = nextCity[city1];
            for(int i=0;i<size;i++){
                TSPValue += edges[city1][city2];
                city1 = city2;
                city2 = nextCity[city1];
            }
            cout<<floor(TSPValue)<<endl;
        }
};

int main(){
    int n;
    cin>>n;
    TSP obj(n);
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        obj.getCoordinates(x,y);
    }
    obj.assignEdges();
    obj.nearestNeighbour();
    obj.printTSPValue();
    return 0;
}