/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Your Name
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {
}

FIFOReplacement::~FIFOReplacement() {
    // Perform cleanup if necessary
}

void FIFOReplacement::load_page(int page_num) {
    for (int i = 0; i < page_table.size(); ++i) {
        if (!page_table[i].validBit) {
            page_table[i].validBit = true;
            return;
        }
    }
}

int FIFOReplacement::replace_page(int page_num) {
    int victimPage = oldestPageIndex;
    oldestPageIndex = (oldestPageIndex + 1) % page_table.size();

    page_table[victimPage].validBit = false;
    return victimPage;
}
