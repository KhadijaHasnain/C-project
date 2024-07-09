/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Your Name
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {
}

LIFOReplacement::~LIFOReplacement() {
    // Perform cleanup if necessary
}

void LIFOReplacement::load_page(int page_num) {
    for (int i = 0; i < page_table.size(); ++i) {
        if (!page_table[i].validBit) {
            page_table[i].validBit = true;
            return;
        }
    }
}

int LIFOReplacement::replace_page(int page_num) {
    int victimPage = -1;

    for (int i = 0; i < page_table.size(); ++i) {
        if (page_table[i].validBit) {
            victimPage = i;
        }
    }

    page_table[victimPage].validBit = false;
    return victimPage;
}
