#include <iostream>
#include <utility>
#include <string>
using namespace std;

class Node{
    int value;
    Node* next;
    friend class Stack;
    friend class Graph;
};

class Stack{
    private:
        Node* tos;                                      //pointer to top of stack
        Node* tail;                                     //dummy node in start of stack     
    public:
        void makeStack(){
            tos = new Node;
            tos->next = NULL;
            tail = tos;

        }
        void push(int x){
            Node* tempNode = new Node;
            tempNode->value = x;
            tempNode->next = NULL;
            tos->next = tempNode;
            tos = tempNode;
        }
        int pop(){
            if(isEmpty() == 0){
                Node* tempNode;
                tempNode = tail;
                while(tempNode->next != tos){
                    tempNode = tempNode->next;
                }
                tempNode->next = NULL;
                int result = tos->value;
                tos = tempNode;
                return (result);
            }else{
                return (-1);
            }
        }
        int top(){
            if(isEmpty() == 1){
                return (-1);
            }else{
                int temp = tos->value;
                return (temp);
            }
        }
        int isEmpty(){
            if(tail == tos){
                return (1);
            }else{
                return (0);
            }
        }
};

class Graph{
    private:
        int n;
        int* parent;                                    //array storing the parents nodes in the DFS traversal
        Node** adjacencyMatrix;                         //represents the graph, and starts with a dummy node for each vertex
        bool* isVisited;                                //array stating whether the node has been visited in the DFS traversal
        
        //resets the values stored in parent and isVisited arrays for next DFS traversal
        void resetDFS(){
            for(int i=0;i<n;i++){
                parent[i] = -1;
                isVisited[i] = false;
            }
        }
    public:
        Graph(int size){
            n = size;
            parent = new int[n];
            for(int i=0;i<n;i++){
                parent[i] = -1;
            }
            isVisited = new bool[n];
            for(int i=0;i<n;i++){
                isVisited[i] = false;
            }
            adjacencyMatrix = new Node*[n];
            for(int i=0;i<n;i++){
                adjacencyMatrix[i] = new Node;
                adjacencyMatrix[i]->next = NULL;
            }
        }
        void printGraph(){
            for(int i=0;i<n;i++){
                Node* tempNode = adjacencyMatrix[i];
                cout<<i<<" : ";
                while(tempNode->next != NULL){
                    tempNode = tempNode->next;
                    cout<<tempNode->value<<" ";
                }
                cout<<endl;
            }
        }
        void operator += (pair<int,int> edge){
            int u = edge.first;
            int v = edge.second;
            Node* node1 = new Node;
            Node* node2 = new Node;
            node1->value = u;
            node2->value = v;
            node1->next = NULL;
            node2->next = NULL;
            Node* tempNode1 = adjacencyMatrix[u];
            Node* tempNode2 = adjacencyMatrix[v];
            while(tempNode1->next != NULL){
                //if the edge already exits
                if(tempNode1->value == v){
                    break;
                }
                tempNode1 = tempNode1->next;
            }
            if(tempNode1->value != v){
                while(tempNode2->next != NULL){
                    tempNode2 = tempNode2->next;
                }
                tempNode1->next = node2;
                tempNode2->next = node1;
            }
        }
        void operator -= (pair<int,int> edge){
            int u = edge.first;
            int v = edge.second;
            Node* tempNode1 = adjacencyMatrix[u];
            Node* tempNode2 = adjacencyMatrix[v];
            while(tempNode1->next != NULL){
                if(tempNode1->next->value == v){
                    break;
                }
                tempNode1 = tempNode1->next;
            }
            if(tempNode1->next != NULL){
                while(tempNode2->next != NULL){
                    if(tempNode2->next->value == u){
                        break;
                    }
                    tempNode2 = tempNode2->next;
                }
                //if edge with v was the last edge
                if(tempNode1->next->next != NULL){
                    tempNode1->next = tempNode1->next->next;
                }else{
                    tempNode1->next = NULL;
                }

                //if the edge with u was the last edge
                if(tempNode2->next->next != NULL){
                    tempNode2->next = tempNode2->next->next;
                }else{
                    tempNode2->next = NULL;
                }
            }
        }

        /*
        uses recursive dfs calls to check if there is a back-edge in the graph
        */
        int dfs(int vertex){
            int temp=0;
            isVisited[vertex] = true;
            Node* tempNode = adjacencyMatrix[vertex];
            while(tempNode->next != NULL){
                tempNode = tempNode->next;                          //since the first node is a dummy node
                if(isVisited[tempNode->value] == true){
                    //if the already visited vertex isn't the parent of the node (tempNode), then there is a cycle in the graph
                    if(parent[vertex] != tempNode->value){
                        return (1);
                    }
                }else if(isVisited[tempNode->value] == false){
                    parent[tempNode->value] = vertex;
                    temp = dfs(tempNode->value);
                    if(temp == 1){
                        return 1;
                    }
                }
            }
            return (0);
        }
        int detectCycle(){
            for(int i=0;i<n;i++){
                if(isVisited[i] == false){
                    if(dfs(i) == 1){
                        resetDFS();
                        return(1);
                    }
                }
            }
            resetDFS();
            return (0);
        }

        /*
        computes the number of connected components by using a stack to push in the children nodes of the parent node which is popped and continues till the 
        stack becomes empty, (ie) the connected nodes of the current component have exhausted  
        */
        int components(){
            int result=0;
            Stack stack;
            stack.makeStack();
            for(int i=0;i<n;i++){
                //start of a new connected component
                if(isVisited[i] == false){
                    stack.push(i);
                    isVisited[i] = true;

                    //stack becomes empty when all the nodes in the connected component are traversed 
                    while(stack.isEmpty() == 0){
                        int temp = stack.pop();
                        Node* tempNode = adjacencyMatrix[temp];
                        while(tempNode->next != NULL){
                            tempNode = tempNode->next;
                            if(isVisited[tempNode->value] == false){
                                stack.push(tempNode->value);
                                isVisited[tempNode->value] = true;
                            }
                        }
                    }
                    //increments for every connected component 
                    result++;
                }
            }
            resetDFS();
            return (result);
        }
        
        /*
        similar to components(), checks if u and v are in the same connected component
        */
        int reach(int u,int v){
            isVisited[u] = true;
            Stack stack;
            stack.makeStack();
            stack.push(u);
            while(stack.isEmpty() == 0){
                int temp = stack.pop();
                Node* tempNode = adjacencyMatrix[temp];
                while(tempNode->next != NULL){
                    tempNode = tempNode->next;
                    if(tempNode->value == v){
                        resetDFS();
                        return (1);
                    }
                    if(isVisited[tempNode->value] == false){
                        stack.push(tempNode->value);
                        isVisited[tempNode->value] = true;
                    }
                }
            }
            resetDFS();
            return (0);
        }
};

int main(){
    int Q;
    string query;
    cin>>Q;
    Stack stack;
    stack.makeStack();
    for(int i=0;i<Q;i++){
        cin>>query;
        if(query == "push"){
            int x;
            cin>>x;
            stack.push(x);
        }else if(query == "pop"){
            cout<<stack.pop()<<endl;
        }else if(query == "top"){
            cout<<stack.top()<<endl;
        }else if(query == "empty"){
            cout<<stack.isEmpty()<<endl;
        }
    }
    int n,m;
    cin>>n>>m;
    Graph G(n);
    for(int i=0;i<m;i++){
        cin>>query;
        if(query == "add"){
            int u,v;
            cin>>u>>v;
            pair<int,int> edge(u,v);
            G+=edge;
        }else if(query == "del"){
            int u,v;
            cin>>u>>v;
            pair<int,int> edge(u,v);
            G-=edge;
        }else if(query == "cycle"){
            cout<<G.detectCycle()<<endl;
        }else if(query == "components"){
            cout<<G.components()<<endl;
        }else if(query == "reach"){
            int u,v;
            cin>>u>>v;
            cout<<G.reach(u,v)<<endl;
        }
    }
    return 0;
}