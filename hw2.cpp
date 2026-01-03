#include <iostream>
#include "MyString.h"
#include <string>
#include "BinaryTree.h"
#include "Graph.h"
#include "Forest.h"
#include "MyVector.h"

using namespace std;

int main() {
    try {
        int numTrees, numEdges;
        cin >> numTrees >> numEdges;
        cin.ignore(); // skip newline after numbers

        Forest forest;

        // Read each tree
        for (int i = 0; i < numTrees; i++) {
            string line;
            getline(cin, line);
            MyString treeStr(line.c_str());

            BinaryTree tree;
            tree.readFromString(treeStr);

            forest.addTree(tree);
        }

        // Add vertices to the graph
        for (int i = 0; i < numTrees; i++)
            forest.getGraph().addVertex();

        // Read edges
        for (int i = 0; i < numEdges; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            forest.getGraph().addEdge(u, v, w);
        }

        // Compute total apples and time
        int totalApples = 0, totalTime = 0;
        bool success = forest.computeTotalApplesAndTime(totalApples, totalTime);

        if (!success) {
            cout << "Some trees are unreachable!" << endl;
        }
        else {
            cout << totalApples << " " << totalTime << endl;
        }
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
