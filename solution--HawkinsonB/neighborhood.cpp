/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 YOUR_NAME <YOUR_EMAIL>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * Implements of `neighborhood.h`.
 */

#include <random>
#include <iostream>
#include <chrono>
#include <thread>
// TODO: `#include`s for other system headers, if necessary

#include "neighborhood.h"
#include "constants.h"

using std::cerr;
using std::cout;
using std::endl;
// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------
// local helper functions

/**
 * Notes:
 * - If you like, you can start reading about what this "unnamed `namespace`"
 *   is for [here](http://www.comeaucomputing.com/techtalk/#nostatic).
 */
namespace {

    /**
     * Return a uniformly distributed random number in the range [low, high]
     * using the Mersenne Twister engine, seeded with (ideally) the hardware
     * random device.
     *
     * Because `rand()` (and especially `rand() % ...`) maybe shouldn't be
     * used, if we can avoid it:
     * [`rand()` considered harmful]
     * (https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful)
     * (talk by stephan t. lavavej)
     * 
     *
     * Notes:
     * - In C++, `static` function variables are created and initialized once,
     *   when the function is first called, and they remain until the program
     *   is terminated: 
     *   [Static variables in class methods]
     *   (http://stackoverflow.com/questions/6223355/static-variables-in-class-methods)
     * - `std::mt19937` objects are expensive to create.
     *   `std::uniform_int_distribution` objects are said to be pretty cheap.
     */
    unsigned int mtrand(unsigned int low, unsigned int high) {
        static std::random_device rd;
        static std::mt19937 mt(rd());  // engine (mersenne twister)

        return std::uniform_int_distribution<unsigned int>(low, high)(mt);
    }

}

// ----------------------------------------------------------------------------

// TODO: implementations for all functions in `class Neighborhood`

Neighborhood::Neighborhood(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y) {
    // initialize `neighborhood_` and fill with "empty" `Shape`s
    neighborhood_ = new Shape[ size_x * size_y ]();
    
    // fill with non-empty shapes so that the ratio of non-empty to empty
    // shapes is `RATIO_FILLED` (from `constants.h`)
    for (int filled=0; filled < size_x*size_y*RATIO_FILLED; ) {
        unsigned int x = mtrand(0, size_x-1);
        unsigned int y = mtrand(0, size_y-1);
        
        if (this->get(x, y).getType() == "empty") {
            this->set( x, y, mtrand(0, 1) ? Shape("triangle")
                      : Shape("square") );
            filled++;
        }
    }
}
Neighborhood::~Neighborhood() {
    delete[] neighborhood_;
}


Shape Neighborhood::get(unsigned int x, unsigned int y) const {
    if (x <= size_x && y <= size_y) {
        return neighborhood_[ y * size_x + x ]; }
    else {
        cerr << "ERROR: `Neighborhood::get`: index out of bounds\n";
        exit(1);
    }
}


void Neighborhood::set(unsigned int x, unsigned int y, const Shape & s) {
    if (x <= size_x && y <= size_y) {
        neighborhood_[ y * size_x + x ] = s; }
    else {
        cerr << "ERROR: `Neighborhood::set`: index out of bounds\n";
        exit(1);
    }
}

void Neighborhood::move(unsigned int old_x, unsigned int old_y) {
    for (;;) {
        unsigned int x = mtrand(0, size_x-1);
        unsigned int y = mtrand(0, size_y-1);
        
        if (get(x, y).getType() == "empty") {
            set(x, y, get(old_x, old_y));
            set(old_x, old_y, Shape("empty"));
            
            break;
        }
    }
}

void Neighborhood::animate(unsigned int frames) {
        Buffer b(size_x * Shape::size_x, size_y * Shape::size_y);
    
    for (int i=0; i <= frames;i++) {
        for (int y = 0; y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                b.set( x * Shape::size_x,
                      y * Shape::size_y,
                      neighborhood_[ y * size_x + x ].type_art_ );
            }
        }
        b.draw();
        for (int y = 0; y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                      neighborhood_[ y * size_x + x ].isHappy(Neighborhood, x, y));
            }
        }

    }
    }
}
/**
 * 1. Create a buffer.
 * 2. Draw all the shapes in our neighborhood to it, and render it to
 *    the screen.
 * 3. Move all the unhappy shapes, and go back to step (2).
 *
 * Loop from step (3) to step (2) `frames` times; that is, the
 * neighborhood should be rendered to the screen (i.e. output to the
 * terminal) `frames` times.
 *
 * To make it so that each frame can be seen, you should have the
 * program sleep for a little while (probably at least 100
 * milliseconds) at the end of each loop.  To do this, include the
 * `<chrono>` and `<thread>` headers, and use the following code:
 * ```
 * std::this_thread::sleep_for(std::chrono::milliseconds(100));
 * ```
 */

