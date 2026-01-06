#include <iostream>
#include "MyString.h"
#include <string> // just for the user input
#include "BinaryTree.h"
#include "Graph.h"
#include "Forest.h"
#include "MyVector.h"

int main() 
{
    try {
        int numTrees, numEdges;
        
        //handle first input line
        while (true) {
            if (std::cin >> numTrees >> numEdges) 
            {
                if (numTrees == 0 && numEdges == 0)
                {
                    std::cout << numTrees << " " << numEdges << std::endl;
                    return 0;
                }
                else if (numTrees >= 0 && numEdges >= 0) 
                    break;
                else
                    std::cerr << "Numbers must be non-negative.\n";
            }
            else 
                std::cerr << "Invalid input. Please enter two integers: <trees> <edges>\n";
            
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cin.ignore();



        Forest forest;
        for (int i = 0; i < numTrees; i++) 
        {
            std::string line;
            std::getline(std::cin, line);
            MyString treeStr(line.c_str());

            BinaryTree tree;

            //handle tree inputs
            try 
            {
                tree.readFromString(treeStr);
            }
            catch (const std::runtime_error& e)
            {
                --i;
                std::cerr << e.what() << ": Enter a valid tree.\n";
                continue;

            }
            forest.addTree(tree);
        }

  
        for (int i = 0; i < numTrees; i++)
            forest.getGraph().addVertex();

       
        for (int i = 0; i < numEdges; i++) 
        {
            int u, v, w;
            //handle edges input
            if (!(std::cin >> u >> v >> w))
            {
                std::cerr << "Connections between trees must be Integers. Enter valid indexes\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                --i;                      
                continue;
            }
            try 
            {
                forest.getGraph().addEdge(u, v, w);
            }
            catch (const std::out_of_range& e)
            {
                --i;
                std::cerr << e.what() << ": Invalid connection between trees. Enter valid indexes\n";
                continue;
            }
        }


        int totalApples = 0, totalTime = 0;
        bool success = forest.computeTotalApplesAndTime(totalApples, totalTime);

        if (!success) 
            std::cout << "Some trees are disconnected from the forest!" << std::endl;
        
        else 
            std::cout << totalApples << " " << totalTime << std::endl;
        
    }
    catch (const  std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}
