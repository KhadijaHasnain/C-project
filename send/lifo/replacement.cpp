#include <iostream>
#include "replacement.h"

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
    : page_table(num_pages) {
    numPageFaults = 0;
    numPageReplacements = 0;
}

// Destructor
Replacement::~Replacement() {
}

bool Replacement::access_page(int page_num, bool is_write) {
    if (page_table[page_num].validBit) {
        touch_page(page_num);
        return false; // Not a page fault
    } else {
        if (page_table.size() > page_num) {
            load_page(page_num);
            return true; // It's a page fault
        } else {
            int replacedPage = replace_page(page_num);
            if (replacedPage != -1) {
                numPageReplacements++;
                return true; // It's a page fault
            } else {
                std::cerr << "Error: No free frames and replacement failed!" << std::endl;
                return false; 
            }
        }
    }
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
    // Print out the number of references, number of page faults, and number of page replacements
    output << "Number of references: \t\t" << page_table.size() << std::endl;
    output << "Number of page faults: \t\t" << numPageFaults << std::endl;
    output << "Number of page replacements: \t" << numPageReplacements << std::endl;
}
