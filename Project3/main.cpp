#include "helper.cpp"

// To run the program, type the following in the command line
// alias g++="g++ -std=c++17"
// g++ main.cpp
// ./a.out 

int main() {
    string filename = "tarzan.txt";
    string temp;
    int mazeY, mazeX, posY, posX, numVertices;
    vector< vector<string> > maze;

    readFile(filename, &mazeY, &mazeX, &posY, &posX, &numVertices, &maze);
    // cout << mazeY << ' ' << mazeX << ' ' << posY << ' ' << posX << ' ' << numVertices << endl; 

    // adding vertices to adjlist
    int jY, jX;
    int n = 0; //number of edges
    vector<int> adj[mazeY*mazeX];
    for (int u = 0; u < mazeY; u++) {
        
        // cout << "\n line " << u << endl;
        for (int v = 0; v < mazeX; v++) {
            // cout << " hohoho " << endl;
            if (maze.at(u).at(v) == "J" || maze.at(u).at(v) == "\nJ") {
                // cout << " loop J " << endl;
                jY = u;
                jX = v;
                // cout << "Jojo position: " << jY << " " << jX << endl;
            } 
            else if (maze.at(u).at(v) == "X" || maze.at(u).at(v) == "\nX") {
                // cout << " loop X " << endl;
                continue;
            }
            else if (maze.at(u).at(v) == "N" || maze.at(u).at(v) == "\nN") {
                // cout << " loop N " << endl;
                int a = u*mazeX + v + 1;
                int b = (u-3)*mazeX + v + 1;
                int c = (u-4)*mazeX + v + 1;
                int bx = b/mazeX; // not -1
                int by = b%mazeX - 1;
                int cx = b/mazeX; // not -1
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (u >= 3) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (u >= 4) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            } 
            else if (maze.at(u).at(v) == "E" || maze.at(u).at(v) == "\nE") {
                // cout << " loop E " << endl;
                int a = u*mazeX + v + 1;
                int b = u*mazeX + v + 1 + 3;
                int c = u*mazeX + v + 1 + 4;
                int bx = b/mazeX;
                int by = b%mazeX - 1;
                int cx = b/mazeX;
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (mazeX - a%mazeX >= 3) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                        // cout << " b: " << b;
                    }
                        // addEdge(adjlist, a, b);
                }
                if (mazeX - a%mazeX >= 4) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                        // cout << " c: " << c;
                    }
                    // cout << " ha: " << maze.at(cx).at(cy) << " cx: " << cx << " cy: " << cy;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            }
            else if (maze.at(u).at(v) == "S" || maze.at(u).at(v) == "\nS") {
                // cout << " loop S " << endl;
                int a = u*mazeX + v + 1;
                int b = (u+3)*mazeX + v + 1;
                int c = (u+4)*mazeX + v + 1;
                // cout << a << ' ' << b << ' ' << c << endl;
                int bx = b/mazeX - 1;
                int by = b%mazeX - 1;
                int cx = c/mazeX - 1;
                int cy = c%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (mazeY - u >= 4) { //여기까지 오지도 않음
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (mazeY - u >= 5) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            }
            else if (maze.at(u).at(v) == "W" || maze.at(u).at(v) == "\nW") {
                // cout << " loop W " << endl;
                int a = u*mazeX + v + 1;
                int b = u*mazeX + v + 1 - 3;
                int c = u*mazeX + v + 1 - 4;
                int bx = b/mazeX;
                int by = b%mazeX - 1;
                int cx = b/mazeX;
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (a%mazeX >= 4 || a%mazeX == 0) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (a%mazeX >= 5 || a%mazeX == 0) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            } 
            else if (maze.at(u).at(v) == "NE" || maze.at(u).at(v) == "\nNE") {
                int a = u*mazeX + v + 1;
                int b = (u-3)*mazeX + v + 1 + 3;
                int c = (u-4)*mazeX + v + 1 + 4;
                int bx = b/mazeX;
                int by = b%mazeX - 1;
                int cx = b/mazeX - 1;
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (u >= 3 && mazeX - a%mazeX >= 3) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (u >= 4 && mazeX - a%mazeX >= 4) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            } 
            else if (maze.at(u).at(v) == "SE" || maze.at(u).at(v) == "\nSE") {
                int a = u*mazeX + v + 1;
                int b = (u+3)*mazeX + v + 1 + 3;
                int c = (u+4)*mazeX + v + 1 + 4;
                int bx = b/mazeX;
                int by = b%mazeX - 1;
                int cx = b/mazeX - 1;
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (mazeY - u >= 4 && mazeX - a%mazeX >= 3) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (mazeY - u >= 5 && mazeX - a%mazeX >= 4) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            } 
            else if (maze.at(u).at(v) == "SW" || maze.at(u).at(v) == "\nSW") {
                int a = u*mazeX + v + 1;
                int b = (u+3)*mazeX + v + 1 - 3;
                int c = (u+4)*mazeX + v + 1 - 4;
                int bx = b/mazeX;
                int by = b%mazeX - 1;
                int cx = b/mazeX - 1;
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (mazeY - u >= 4 && (a%mazeX >= 4 || a%mazeX == 0)) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (mazeY - u >= 5 && (a%mazeX >= 5 || a%mazeX == 0)) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            } 
            else if (maze.at(u).at(v) == "NW" || maze.at(u).at(v) == "\nNW") {
                int a = u*mazeX + v + 1;
                int b = (u-3)*mazeX + v + 1 - 3;
                int c = (u-4)*mazeX + v + 1 - 4;
                int bx = b/mazeX;
                int by = b%mazeX - 1;
                int cx = b/mazeX - 1;
                int cy = b%mazeX - 1;
                if (by == -1)
                    by = mazeX-1;
                if (cy == -1)
                    cy = mazeX-1;
                
                // cout << "a: " << a;
	            vector<int> temp;
                if (u >= 3 && (a%mazeX >= 4 || a%mazeX == 0)) {
                    if (maze.at(bx).at(by) != "X" && maze.at(bx).at(by) != "\nX") {
	                    temp.push_back(b-1);
	                    n++;
                    }
                        // cout << " b: " << b;
                        // addEdge(adjlist, a, b);
                }
                if (u >= 4 && (a%mazeX >= 5 || a%mazeX == 0)) {
                    if (maze.at(cx).at(cy) != "X" && maze.at(cx).at(cy) != "\nX") {
	                    temp.push_back(c-1);
	                    n++;
                    }
                        // cout << " c: " << c;
                        // addEdge(adjlist, a, c);
                }
                adj[a-1] = temp;
                // cout << endl;
            }
        }

    }

    // create graph
    Graph graph(adj, n, numVertices);
    
    // for (int i = 0; i < numVertices; i++)
    //     showAdjList(graph.head[i], i);


    int tarzan = posY*mazeX + posX;
    int jojo = jY*mazeX + jX;
    // cout << tarzan << ' ' << jojo;
	// findPath(adj, tarzan, jojo, mazeY*mazeX);

    findPath(adj, tarzan, jojo, mazeY, mazeX);


    return 0;

}
