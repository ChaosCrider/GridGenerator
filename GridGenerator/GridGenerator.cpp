#include <iostream>
#include <memory>
#include <cassert>
#include <iomanip>
#include <ostream>
#include "GridManager.h"
#include "BasicLayoutGenerator.h"
#include "ILayoutGenerator.h"
#include "BasicTileProcessor.h"
#include "ITileProcessor.h"
#include "eTileType.h"

int main() {
    GridBlueprint blueprint(50, 50, 3, 5, 3, 16);
    auto layoutManager = std::make_shared<BasicLayoutGenerator>();
    auto tileProcessor = std::make_shared<BasicTileProcessor>();

    std::shared_ptr<ILayoutGenerator> layoutInterface;
    std::shared_ptr<ITileProcessor> tileInterface;


#ifdef _DEBUG
    layoutInterface = std::dynamic_pointer_cast<ILayoutGenerator>(layoutManager);
    tileInterface = std::dynamic_pointer_cast<ITileProcessor>(tileProcessor);
    assert(layoutInterface && "layoutManager does not implement ILayoutGenerator");
    assert(tileInterface && "tileProcessor does not implement ITileProcessor");
#else
    layoutInterface = std::static_pointer_cast<ILayoutGenerator>(layoutManager);
    tileInterface = std::static_pointer_cast<ITileProcessor>(tileProcessor);
#endif

    GridManager generator(blueprint, tileInterface, layoutInterface);

    do {

        const GridData grid = generator.generate();

        int s = grid.debugLength();

        std::cout << s << std::endl;

		std::cout << " *|";
        for (int i = 0 ; i < grid.getWidth(); i++) {
            std::cout << std::setw(2)  << i << "|";
		}
		std::cout << "\n";

        for (int i = 0; i < grid.getWidth(); i++) {
            std::cout << std::setw(2) << i << "|";
            for (int y = 0; y < grid.getHeight(); y++)
            {

				std::cout << std::setw(2) << to_string(grid.getTile(i, y)) << "|";
            }
            std::cout << "\n";
        }

        std::cin.get();

    } while (true);

}