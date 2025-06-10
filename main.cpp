#include <iostream>
#include "GridGenerator.h"


int main(){

    GridGenerator generator(3,5);

    std::vector<std::vector<int>> grid = generator.generate();

    std::cout << "received grid : " << grid.size() << " x " << grid[0].size() << "\n";

    for (const auto& row :grid) {
        for (int cell : row) {
            std::cout << cell <<", ";
        }
        std::cout << "\n";
    }

}