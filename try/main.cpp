#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "fifo_replacement.h"
#include "lru_replacement.h"
#include "lifo_replacement.h"

bool isPowerOfTwo(unsigned int x) {
    return x && (!(x & (x - 1)));
}

void save_statistics(const std::string& filename, const std::string& statistics) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << statistics;
        file.close();
        std::cout << "Statistics saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::cout << "=================================================================" << std::endl;
    std::cout << "CS 433 Programming assignment 5" << std::endl;
    std::cout << "Author: Your Name" << std::endl;
    std::cout << "Date: XX/XX/XXXX" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description: Program to simulate different page replacement algorithms" << std::endl;
    std::cout << "=================================================================\n" << std::endl;

    if (argc < 3) {
        std::cout << "You have entered too few parameters to run the program. You must enter" << std::endl
                  << "two command-line arguments:" << std::endl
                  << " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
                  << " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
        exit(1);
    }

    unsigned int page_size = atoi(argv[1]);
    if (!isPowerOfTwo(page_size)) {
        std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
                  << "  (must be a power of 2 between 256 and 8192, inclusive)." << std::endl;
        return 1;
    }
    unsigned int phys_mem_size = atoi(argv[2]) << 20;
    if (!isPowerOfTwo(phys_mem_size)) {
        std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
                  << "  (must be a power of 2 between 4 and 64, inclusive)." << std::endl;
        return 1;
    }

    int logic_mem_bits = 27;
    int phys_mem_bits = std::log2(phys_mem_size);
    int page_offset_bits = std::log2(page_size);
    int num_pages = 1 << (logic_mem_bits - page_offset_bits);
    int num_frames = 1 << (phys_mem_bits - page_offset_bits);

    std::cout << "Page size = " << page_size << " bytes" << std::endl;
    std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
    std::cout << "Number of pages = " << num_pages << std::endl;
    std::cout << "Number of frames = " << num_frames << std::endl;

    // Create replacement objects
    FIFOReplacement fifo(num_pages, num_frames);
    LRUReplacement lru(num_pages, num_frames);
    LIFOReplacement lifo(num_pages, num_frames);

    // Simulate page references
    std::ifstream infile("references.txt");
    int page_num;
    char rw;
    while (infile >> std::hex >> page_num >> rw) {
        bool is_write = (rw == 'W');
        fifo.access_page(page_num, is_write);
        lru.access_page(page_num, is_write);
        lifo.access_page(page_num, is_write);
    }

    // Print statistics
    std::cout << "\nFIFO Page Replacement Algorithm Statistics:" << std::endl;
    fifo.print_statistics();
    std::cout << "\nLRU Page Replacement Algorithm Statistics:" << std::endl;
    lru.print_statistics();
    std::cout << "\nLIFO Page Replacement Algorithm Statistics:" << std::endl;
    lifo.print_statistics();

    return 0;
}