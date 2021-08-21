#include<iostream>
#include<queue>
#include<list>
#include<string>

using namespace std;

class Graph{
        int V;

        //Array of list
        //Assuming that integers are unique name of the person.
        list<int> *l; //using pointer because we don't know the size of array during compile time.
    public:
        Graph(int V){
            this->V = V;
            l = new list<int>[V]; //initiating an array l of size V.
        }

        void addEdge(int x, int y){
            l[x].push_back(y);
            l[y].push_back(x);
        }

        bool areFriends(int person1, int person2){
            // Base case
            if (person1 == person2)
            return true;
        
            // Mark all the vertices as not visited
            bool *visited = new bool[V];
            for (int i = 0; i < V; i++)
                visited[i] = false;
        
            // Create a queue for BFS
            list<int> queue;
        
            // Mark the current node as visited and enqueue it
            visited[person1] = true;
            queue.push_back(person1);
        
            // it will be used to get all adjacent vertices of a vertex
            list<int>::iterator i;
        
            while (!queue.empty())
            {
                // Dequeue a vertex from queue and print it
                person1 = queue.front();
                queue.pop_front();
        
                // Get all adjacent vertices of the dequeued vertex s
                // If a adjacent has not been visited, then mark it visited and enqueue it
                for (i = l[person1].begin(); i != l[person1].end(); ++i)
                {
                    // If this adjacent node is the destination node, then
                    // return true
                    if (*i == person2)
                        return true;
        
                    // Else, continue to do BFS
                    if (!visited[*i])
                    {
                        visited[*i] = true;
                        queue.push_back(*i);
                    }
                }
            }
            return false;
        }

        void printFriendsofAllMembers(){
            //Iterating over all the vertices.
            for (int i = 0; i < V; i++){
                cout << "Friends of Person "<< i << " -> ";
                for (int neighbour: l[i]){
                    cout << neighbour << ", ";
                }
                cout << endl;
            }
        }

        void viewAllMembers(int source){
            // Mark all the vertices as not visited
            bool *visited = new bool[V];
            for(int i = 0; i < V; i++)
                visited[i] = false;
        
            // Create a queue for BFS
            list<int> queue;
            visited[source] = true;
            queue.push_back(source);
        
            // 'i' will be used to get all adjacent
            // vertices of a vertex
            list<int>::iterator i;
        
            while(!queue.empty())
            {
                // Dequeue a vertex from queue and print it
                source = queue.front();
                cout << source << " ";
                queue.pop_front();
        
                // Get all adjacent vertices of the dequeued vertex source. If a adjacent has not been visited,
                // then marking visited and enqueuing.
                for (i = l[source].begin(); i != l[source].end(); ++i)
                {
                    if (!visited[*i])
                    {
                        visited[*i] = true;
                        queue.push_back(*i);
                    }
                }
            }
        }

        void friendsOfFriend(int source, int friendOfSource){
            if(areFriends(source, friendOfSource)){
                cout << "Friends of friends of "<< source << " ->";
                for (int neighbour: l[friendOfSource]){
                    cout << neighbour << ", ";
                }
                cout << endl;
            }
            else{
                cout << source << " and " << friendOfSource << "are not friends. No friends to display.";
            }
        }
           
};


int main(){

    int size;

    cout << "Enter the number of persons you'd like to make a network of: "<< endl;
    cin >> size;
    
    //Initiating a graph of given size.
    Graph g(size + 1); // "size + 1" to avoid the segmentation fault error.

    int a[size], b[size]; //just for addEdge(int, int ) operation.

    //The names of the person are represented by a key integer.
    cout << "Establishing the connections/friendships of the persons."<< endl;
    for(int i = 0; i< size; i++){
    
        cout<<"Connection: ";
        cin >> a[i] >> b[i];
        g.addEdge(a[i], b[i]);
    }
    cout << endl;

    //Listing all the members along with their friends.
    cout << "Viewing the friends of the Members. Person with no connection is taken non-existent. " <<endl;
    g.printFriendsofAllMembers();
    cout<<endl;

    g.viewAllMembers(0);
    cout<<endl;

    char response;
    cout << "Would you like to find the friends of friends? (y/n)"<<endl;
    cin >> response;
    if(response == 'y' || response == 'Y'){
        int source, nbr;
        cout<<"Enter the identity of the source: ";
        cin>> source;
        cout<<endl;
        cout<<"Enter the identity of the friend: ";
        cin>> nbr;
        cout<<endl;
        g.friendsOfFriend(source, nbr);
    }
}