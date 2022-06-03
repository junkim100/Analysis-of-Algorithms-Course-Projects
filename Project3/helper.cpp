#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include <vector>
#include <queue>

using namespace std;

void readFile(string filename, int * mazeY, int * mazeX, int * posY, int * posX, int * numVertices, vector< vector<string> > * maze) {
    fstream infile;
    infile.open(filename);

    string temp;
    
    getline(infile, temp, ' ');
    *mazeY = stod(temp); //23

    getline(infile, temp);
    *mazeX = stod(temp); //9

    *numVertices = (*mazeX) * (*mazeY); //207

    getline(infile, temp, ' ');
    *posY = stod(temp) - 1; //0

    getline(infile, temp);
    *posX = stod(temp) - 1; //2

    for (int y = 0; y < *mazeY; y++) {
        vector<string> direction;   
        for (int x = 0; x < *mazeX; x++) {
            string a;
            getline(infile, a, ' ');
            direction.push_back(a);
        }
        (*maze).push_back(direction);
    }

    infile.close();
}

struct adjNode {
    int val;
    adjNode* next;
};

class Graph{
    adjNode* getAdjListNode(int value, adjNode* head)   {
        adjNode* newNode = new adjNode;
        newNode->val = value;
         
        newNode->next = head;
        return newNode;
    }
    int numVertices;
	public:
		adjNode **head;
		Graph(vector<int> adj[], int n, int numVertices)  {
			head = new adjNode*[numVertices]();
			this->numVertices = numVertices;
			for (int i = 0; i < numVertices; ++i)
				head[i] = nullptr;
			for (unsigned i = 0; i < numVertices; i++)  {
				for (int j = 0; j < adj[i].size(); j++) {
					int start_ver = i;
					int end_ver = adj[i].at(j);
					adjNode* newNode = getAdjListNode(end_ver, head[start_ver]);
                    
					head[start_ver] = newNode;

				}
			}
		}
};


// show all the added vertices and edges on the adjacency list
void showAdjList(adjNode* ptr, int i)
{
    while (ptr != nullptr) {
        cout << "(" << i << "," << ptr->val
            << ")";
        ptr = ptr->next;
    }
    cout << endl;
}

bool BFS(vector<int> adj[], int src, int dest, int v, int pred[])
{
    list<int> queue;
 	bool visited[v];
 
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        pred[i] = -1;
    }
 
    visited[src] = true;
    queue.push_back(src);
 
    // BFS
    while (!queue.empty()) {
        int u = queue.front();
		// cout << "jppjpjpjpjpjpjpjpjp: " << u << endl;
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u].at(i)] == false) {
                visited[adj[u].at(i)] = true;
                pred[adj[u].at(i)] = u;
                queue.push_back(adj[u].at(i));

                if (adj[u].at(i) == dest)
                    return true;
            }
        }
    }
 
    return false;
}

void findPath(vector<int> adj[], int tarzan, int jojo, int mazeY, int mazeX)
{
	int numVertices = mazeY*mazeX;
    int prev[numVertices];
 
    if (BFS(adj, tarzan, jojo, numVertices, prev) == false) {
        cout << "Given source and destination"
             << " are not connected";
        return;
    }
 
    vector<int> path;
    int crawl = jojo;
    path.push_back(crawl);
    while (prev[crawl] != -1) {
        path.push_back(prev[crawl]);
        crawl = prev[crawl];
    }
 
	int a[path.size()];
    for (int i = path.size() - 1; i >= 0; i--){
		a[i] = path[i]+1;
	}
	
	// for (int i = path.size() - 1; i >= 0; i--){
	// 	cout << a[i] << " ";
	// }

    ofstream ofile;
    ofile.open ("output.txt");
    ofile << "The following is the coordinates (x,y) of the vertices that tarzan lands in order. " << endl
          << "For example, in the original tarzan.txt file, Tarzan is at (2,0) and Jojo is at (6,22)" << endl << endl;
	for (int i = path.size() - 1; i >= 0; i--) {
        int tempY = a[i]/mazeX;
        int tempX = a[i]%mazeX-1;
        if (tempX==-1)
            tempX = mazeX-1;
		cout << "(" << tempX << "," << tempY << ")" << endl;
		ofile << "(" << tempX << "," << tempY << ")" << endl;
	}


    ofile.close();
}
