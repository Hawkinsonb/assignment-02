/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 YOUR_NAME <YOUR_EMAIL>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * Implements `buffer.h`.
 */

// TODO: `#include`s for system headers, if necessary
#include <iostream>
#include "buffer.h"

using std::cerr;
using std::cout;
using std::endl;
// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------


Buffer::Buffer(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y) {
    data_ = new char[size_x * size_y];
    clear();
}


Buffer::~Buffer() {
    delete[] data_;
}


char Buffer::get(unsigned int x, unsigned int y) const {
    if (x >= size_x || y >= size_y) {
        cerr << "ERROR: 'Buffer::get':index out of bounds";
        exit(1);
    }
    return data_[y * size_x + x];
}


void Buffer::set(unsigned int x, unsigned int y, char c) {
    if (x >= size_x || y >= size_y) {
        cerr << "ERROR: 'Buffer::set':index out of boundss";
        exit(1);
    }
    
    data_[ y * size_x + x] = c;
}


void Buffer::set(unsigned int pos_x, unsigned int pos_y, std::string s){
    unsigned int original_x = pos_x;
    for (int i = 0; i < s.length(); i++) {
        if (s[i]=='\n') {
            pos_y++;
            pos_x=original_x;
        } else {
            set (pos_x, pos_y, s[i]);
            pos_x++;
        }
    }
    
}

void Buffer::draw() const {
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            cout << get(x,y);
        }
        cout << endl;
    }
        
}

void Buffer::clear() {
    for (int i=0; i < (size_x * size_y); i++)
        data_[i] = ' ';
}




