#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <climits>
using namespace std;

//edge represents the weight of the edge connecting the vertex with vertex1, where this node belongs to adjList[vertex1]
template <class T> class GraphNode{
    public:
        GraphNode(int v, T w){
            vertex = v;
            edge = w;
        }
        GraphNode(){}
        int vertex;
        T edge;
};

//struct used to compare two edges, for setting the order in priority_queue
template <class T> struct CompareNode{
    bool operator()(GraphNode<T> const& node1, GraphNode<T> const& node2){
        if(node1.edge > node2.edge) return true;
        else if((node1.edge == node2.edge) && (node1.vertex > node2.vertex)) return true;
        else return false;
    }
};

template <class T> class Graph{
    private:
        //Adjacency list represented by a vector of vectors, with each element in the sub-vector as a GraphNode object
        vector<vector<GraphNode<T> > > adjList;
    public:
        Graph<T>(int n){
            for(int i=0;i<n;i++){
                vector<GraphNode<T> > tempVector;                   //initialising the first n sub-vectors
                adjList.push_back(tempVector);
            }
        }
        void addV(){
            vector<GraphNode<T> > tempVector;
            adjList.push_back(tempVector);
        }
        void addE(int a, int b, T w){
            //if any of the two vertices have not been added to the adjacency list
            if((a >= (int)adjList.size()) || (b >= (int)adjList.size())){
                cerr<<"Invalid Vertex/Vertices"<<endl;
                return;
            }
            GraphNode<T>tempNode1(a,w);                             //node representing edge to vertex 'a' of weight 'w'
            GraphNode<T>tempNode2(b,w);                             //node representing edge to vertex 'b' of weight 'w'
            adjList[a].push_back(tempNode2);
            adjList[b].push_back(tempNode1);
        }
        void delE(int a, int b){
            if((a >= (int)adjList.size()) || (b >= (int)adjList.size())){
                cerr<<"Invalid Vertex/Vertices"<<endl;
                return;
            }
            int flag = 0;                                           //flag bit to represent whether the edge is present
            for(unsigned int i=0;i<adjList[a].size();i++){
                if(adjList[a][i].vertex == b){
                    adjList[a].erase(adjList[a].begin() + i);       //erases the edge from a to b in the adjacency list of a
                    flag = 1;
                    break;
                }
            }
            //if the edge between a and b is not present in the graph
            if(flag == 0){
                cerr<<"Invalid edge"<<endl;
                return;
            }
            for(unsigned int i=0;i<adjList[b].size();i++){
                if(adjList[b][i].vertex == a){
                    adjList[b].erase(adjList[b].begin() + i);       //erases the edge from b to a in the adjacency list of b
                }
            }
        }
        void BFS(int a){
            bool* isVisited = new bool[adjList.size()];
            for(int i=0;i<(int)adjList.size();i++) isVisited[i] = false;
            isVisited[a] = true;

            //priority queue used to order the children of the node being traversed
            priority_queue<GraphNode<T>, vector<GraphNode<T> >, CompareNode<T> > pq;

            //queue used to represent the order of traversal of nodes
            queue<GraphNode<T> > q;

            GraphNode<T> tempNode;
            cout<<a<<" ";                                           //the vertex from which BFS is initiated
            typename vector<GraphNode<T> >::iterator ptr; 
            
            //adding the children into the priority_queue
            for(ptr=adjList[a].begin();ptr<adjList[a].end();ptr++){
                pq.push((*ptr));
            }

            //sending the children into the queue after being sorted according to weights and indices
            while(!pq.empty()){
                tempNode = pq.top();
                pq.pop();
                q.push(tempNode);
            }

            //BFS on the children nodes
            while(!q.empty()){
                tempNode = q.front();
                q.pop();
                if(isVisited[tempNode.vertex] == false){            //if the node has not been visited yet
                    isVisited[tempNode.vertex] = true;
                    cout<<tempNode.vertex<<" ";
                    //adding the children of the node into a priority queue to sort them
                    for(ptr=adjList[tempNode.vertex].begin();ptr<adjList[tempNode.vertex].end();ptr++){
                        if(isVisited[ptr->vertex] == false){
                            pq.push(*ptr);
                        }
                    }
                }
                //moving the children to the main queue, if they were added
                while(!pq.empty()){
                    tempNode = pq.top();
                    pq.pop();
                    q.push(tempNode);
                }
            }
            cout<<endl;
        }
        void SSP(int a){
            bool* isVisited = new bool[adjList.size()];
            int* d = new int[adjList.size()];                       //array of distances from source vertex

            //priority queue used to maintain the closest vertex to the source vertex, yet to be traversed
            priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
            typename vector<GraphNode<T> >::iterator ptr;
            for(unsigned int i=0;i<adjList.size();i++){
                d[i] = INT_MAX;
                isVisited[i] = false;
            }
            d[a] = 0;                                               //since the distance from a vertex to itself is 0
            
            //adding the children of the source vertex into the priority queue                                          
            for(unsigned int i=0;i<adjList.size();i++){
                pair<int,int> tempPair(d[i],i);
                pq.push(tempPair);
            }
            while(!pq.empty()){
                pair<int,int> tempPair = pq.top();
                int tempDist = tempPair.first;                      //weight of the edge connecting source and vertex
                int tempVertex = tempPair.second;                   //vertex number of the pair 
                pq.pop();
                if(isVisited[tempVertex] == false){
                    isVisited[tempVertex] = true;

                    //adding children of the current vertex being traversed
                    for(ptr=adjList[tempVertex].begin();ptr<adjList[tempVertex].end();ptr++){
                        if(isVisited[ptr->vertex] == false){
                            int edge = ptr->edge;
                            int initialDist = d[ptr->vertex];
                            //min ((d[u] + w[u,v]), d[v])
                            int min = (tempDist + edge < initialDist) ? tempDist+edge : initialDist;
                            d[ptr->vertex] = min;
                            
                            //adding a new pair into the queue, since once this it traversed, the old one will be..
                            //..invalidated
                            pair<int,int> tempPair(d[ptr->vertex],ptr->vertex);
                            pq.push(tempPair);
                        }
                    }
                }
            }
            for(unsigned int i=0;i<adjList.size();i++){
                if(d[i] < 0)d[i] = INT_MAX;
                cout<<d[i]<<" ";
            }
            cout<<endl;
        }
        //prints the adjacency list representation of the graph
        void printGraph(){
            for(unsigned int i=0;i<adjList.size();i++){
                cout<<"vertex :"<<i<<" : ";
                for(unsigned int j=0;j<adjList[i].size();j++){
                    cout<<adjList[i][j].vertex<<","<<adjList[i][j].edge<<" ";
                }
                cout<<endl;
            }
        }
};

int main(){
    int n;
    cin>>n;
    Graph<int> G(n);
    int Q;
    cin>>Q;
    for(int i=0;i<Q;i++){
        string query;
        cin>>query;
        if(query == "ADDV") G.addV();
        else if(query == "ADDE"){
            int a,b,w;
            cin>>a>>b>>w;
            G.addE(a,b,w);
        }else if(query == "DELE"){
            int a,b;
            cin>>a>>b;
            G.delE(a,b);
        }
    }
    for(int i=0;i<2;i++){
        string query;
        int a;
        cin>>query;
        cin>>a;
        if(query == "BFS") G.BFS(a);
        else if(query == "SSP") G.SSP(a);
    }
    return 0;
}