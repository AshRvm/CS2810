#include <iostream>
#include <string>
#include <vector> 
#include <queue>
using namespace std;

//class used represent the nodes in the adjacency list of the graph
template <class T> class GraphNode{
    public:
        int source;
        int vertex;
        T edge; 
        GraphNode(int s, int v, T w){
            source = s;
            vertex = v;
            edge = w;
        }
        GraphNode(){}
};

//struct used for custom ordering in a priority queue of graph nodes
template <class T> struct CompareNodes{
    bool operator()(GraphNode<T> const& node1, GraphNode<T> const& node2){
        if(node1.edge > node2.edge) return true;
        else if((node1.edge == node2.edge) && (node1.source > node2.source)) return true;
        else if((node1.edge == node2.edge) && (node1.source == node2.source) && (node1.vertex > node2.vertex)) return true;
        else return false;
    }
};


/*------------------------------------------------------GRAPH CLASS-----------------------------------------*/
template <class T> class Graph{
    protected:
        vector<vector<GraphNode<T> > > adjList;
        vector<bool> isIncluded;                        //represents whether a node is included in the current tree
        int currentSize;                                //current number of vertices in the graph
        int edgeChange;                                 //represents whether the edges of the graph have been changed after tree creation
    public:
        Graph<T>(int n){
            for(int i=0;i<n;i++){
                //initialising the adjList
                vector<GraphNode<T> > tempVector;
                adjList.push_back(tempVector);
            }
            currentSize = n;
            edgeChange = 0;
        }
        Graph<T>(){}
        void addV(){
            vector<GraphNode<T> > tempVector;
            adjList.push_back(tempVector);
            isIncluded.push_back(false);
            currentSize ++;
        }
        void addE(int a, int b, T w){
            //checks if the vertices a and b are present in the graph
            if((a >= (int)adjList.size()) || (b >= (int)adjList.size())){
                cerr<<"Invalid Vertex/Vertices"<<endl;
                return;
            }
            GraphNode<T> tempNode1(b,a,w);
            GraphNode<T> tempNode2(a,b,w);
            adjList[a].push_back(tempNode2);
            adjList[b].push_back(tempNode1);
            edgeChange = 1;                             //indicates that the number of edges have changed
        }
        void delE(int a, int b){
            //checks if the vertices a and b are present in the graph
            if((a >= (int)adjList.size()) || (b >= (int)adjList.size())){
                cerr<<"Invalid Vertex/Vertices"<<endl;
                return;
            }
            int flag = 0;
            //checks if the edge connecting vertices a and b are present in the graph
            for(unsigned int i=0;i<adjList[a].size();i++){
                if(adjList[a][i].vertex == b){
                    adjList[a].erase(adjList[a].begin() + i);
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                cerr<<"Invalid edge"<<endl;
                return;
            }
            edgeChange = 1;                             //indicates the number of edges have changed
            for(unsigned int i=0;i<adjList[b].size();i++){
                if(adjList[b][i].vertex == a){
                    adjList[b].erase(adjList[b].begin() + i);
                }
            }
        }
};


//Returns the vertex number of the root of the tree, vertex is present in
int Root(int vertex, vector<int>& parents){
    if(parents[vertex] != -1) return Root(parents[vertex],parents);
    else return vertex;
}

//Joins the two trees, if the two vertices are present in different trees 
void SetUnion(int vertex1, int vertex2, vector<int>& ranks, vector<int>& parents){
    int root1 = Root(vertex1, parents);
    int root2 = Root(vertex2, parents);
    if(ranks[root1] < ranks[root2]){
        parents[root1] = root2;
        ranks[root2]++;
    }else{
        parents[root2] = root1;
        ranks[root1]++;
    }
}


/*------------------------------------------------------MST CLASS--------------------------------------------*/
template <class T> class MST : public Graph<T>{
    private:
        vector<vector<GraphNode<T> > > variableTree;    //adjacency list representation of the tree
        int size;                                       //size of the tree, post tree creation
        int token;                                      //flag bit for first tree creation call
    public:
        MST<T>(int n){
            token = 1;                                  //1 to represent that a tree has not been made
            size = n;
            this->currentSize = n;
            for(int i=0;i<n;i++){
                //initialising the vectors
                this->isIncluded.push_back(false);
                vector<GraphNode<T> > tempVector1;
                vector<GraphNode<T> > tempVector2;
                this->adjList.push_back(tempVector1);
                variableTree.push_back(tempVector2);
            }
        }

        //updates the size of the tree if new vertices have been added to the graph
        void updateSize(){
            for(int i=size;i<this->currentSize;i++){
                vector<GraphNode<T> > tempVector;
                variableTree.push_back(tempVector);
            }
            size = this->currentSize;
        }

        //refreshes the tree and the isIncluded vector for a new tree creation
        void refresh(){
            for(int i=0;i<size;i++){
                this->isIncluded[i] = false;
                while(!variableTree[i].empty()){        //clears the tree
                    variableTree[i].pop_back();
                }
            }
        }

        //creates an MST based on Set Union
        void kruskal(){
            updateSize();
            refresh();
            token = 0;                                  //to represent that a tree will be made
            int sum=0;                                  //sum of the edges of the tree
            int count=0;                                //number of edges included in the tree
            vector<int> parents;                        //stores the parent of a vertex in the tree 
            vector<int> ranks;                          //size of the tree with index as root vertex
            for(int i=0;i<size;i++){
                parents.push_back(-1);
                ranks.push_back(1);
            }
            //priority queue used to order the edges of the graph
            priority_queue<GraphNode<T>, vector<GraphNode<T> >, CompareNodes<T> > pq;
            typename vector<GraphNode<T> >::iterator ptr;
            for(int i=0;i<size;i++){
                for(ptr = this->adjList[i].begin(); ptr != this->adjList[i].end(); ptr++){
                    pq.push(*ptr);
                }
            }
            while(!pq.empty()){
                if(count == size-1) break;              //the tree is then completed
                GraphNode<T> tempNode = pq.top();
                pq.pop();
                int source = tempNode.source;
                int vertex = tempNode.vertex;
                //if the two vertices don't belong to the same set, then we join them
                if(Root(source,parents) != Root(vertex,parents)){
                    SetUnion(source,vertex,ranks,parents);
                    variableTree[tempNode.source].push_back(tempNode);
                    sum += tempNode.edge;
                    count++;
                }
            }
            cout<<sum<<endl;
            this->edgeChange = 0;                       //no change in the number of edges after tree is made
        }

        //creates an MST similar to SSH method
        void prims(int v){
            updateSize();
            refresh();
            if(v >= size){                              //if the vertex is not present in the graph
                cerr<<"Invalid vertex"<<endl;
                return;
            }
            token = 0;                                  //to represent a tree will be made
            int count = 0;                              //number of edges included in the tree
            int sum = 0;                                //sum of the edges of the tree
            vector<int> parent;
            vector<int> d;
            //priority queue used to order the edges of the graph
            priority_queue<pair<T,int>, vector<pair<T,int> >, greater<pair<T,int> > > keys;
            for(int i=0;i<size;i++){
                //initialising the vectors
                d.push_back(10000);
                parent.push_back(-1);
                pair<T,int> tempPair(d[i],i);
                keys.push(tempPair);
            }
            pair<T,int> firstPair(0,v);
            keys.push(firstPair);
            while(count < size){
                pair<T,int> tempPair = keys.top();
                keys.pop();
                //if the vertex has not been included in the tree yet
                if(this->isIncluded[tempPair.second] == false){
                    this->isIncluded[tempPair.second] = true;
                    typename vector<GraphNode<T> >::iterator ptr;
                    //iteration through the set of vertices adjacent to the given vertex
                    for(ptr = this->adjList[tempPair.second].begin(); ptr != this->adjList[tempPair.second].end(); ptr++){
                        
                        //ignores the vertices already present in the tree
                        if(this->isIncluded[ptr->vertex] == false){
                            
                            //if the edge weight is less than the current key value of the vertex
                            if(ptr->edge < d[ptr->vertex]){
                                parent[ptr->vertex] = tempPair.second;
                                d[ptr->vertex] = ptr->edge;
                                pair<T,int> tempPair(d[ptr->vertex], ptr->vertex);
                                keys.push(tempPair);
                            }
                        }
                    }
                    //since no tree edges are added after first iteration
                    if(count != 0){
                        GraphNode<T> tempNode(parent[tempPair.second], tempPair.second, tempPair.first);
                        variableTree[parent[tempPair.second]].push_back(tempNode);
                        sum += tempPair.first;
                    }
                    count++;
                }
            }
            cout<<sum<<endl;
            this->edgeChange = 0;                       //no change in the number of edges after tree is made    
        }

        //displays the tree according to the given criteria
        /*
        pq1 orders the edges as source vertex weight
        pq2 orders the edges as min(source,vertex) max(source,vertex) weight
        */
        void displayTree(){
            
            //used to order the edges according to the weight of the edges 
            priority_queue<GraphNode<T>, vector<GraphNode<T> >, CompareNodes<T> > pq1;

            //used to order the edges according to the vertex indices of the vertices in an edge
            priority_queue<GraphNode<T>, vector<GraphNode<T> >, CompareNodes<T> > pq2;
            typename vector<GraphNode<T> >::iterator ptr2;
            for(int i=0;i<size;i++){
                for(ptr2 = this->variableTree[i].begin(); ptr2 != this->variableTree[i].end(); ptr2++){
                    pq1.push(*ptr2);
                }
            }
            while(!pq1.empty()){
                GraphNode<T> tempNode = pq1.top();
                pq1.pop();
                int min = tempNode.vertex, max = tempNode.source;
                if(max < min){
                    min = max + min;
                    max = min - max;
                    min = min - max;
                }
                GraphNode<T> tempNode2(min,max,tempNode.edge);
                pq2.push(tempNode2);
            }
            while(!pq2.empty()){
                GraphNode<T> tempNode = pq2.top();
                pq2.pop();
                cout<<tempNode.source<<" "<<tempNode.vertex<<" "<<tempNode.edge<<endl;
            }
        }


        void treeUpToDate(){
            if(token == 1) cout<<"NO"<<endl;            //if no tree has been made yet
            //change in number of edges or vertices since last tree was made
            else if((this->edgeChange == 0) && (this->currentSize == size)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;                      //no changes
        }
};

int main(){
    int n;
    cin>>n;
    MST<int> A(n);
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        string query;
        cin>>query;
        if(query == "ADDV"){
            A.addV();
        }else if(query == "ADDE"){
            int a,b,w;
            cin>>a>>b>>w;
            A.addE(a,b,w);
        }else if(query == "DELE"){
            int a,b;
            cin>>a>>b;
            A.delE(a,b);
        }else if(query == "Prims"){
            int v;
            cin>>v;
            A.prims(v);
        }else if(query == "Kruskal"){
            A.kruskal();
        }else if(query == "TreeUptodate"){
            A.treeUpToDate();
        }else if(query == "DisplayTree"){
            A.displayTree();
        }
    }
}