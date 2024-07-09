#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <sstream>
#include <chrono> // For timing
#include <ctime> // For srand
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
        std::cerr << "Statistics saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void generate_logical_address(int& logical_address, int& page_number, int num_pages) {
    logical_address = rand() % (num_pages * 10); // Generate a random logical address
    page_number = logical_address / 10; // Calculate the page number
}

void generate_output(std::stringstream& output, int logical_address, int page_number, int frame_number, bool is_page_fault) {
    output << "Logical address: " << logical_address << ", \t page number: " << page_number << ", \t frame number = " << frame_number << ", \t is page fault? " << is_page_fault << std::endl;
}

int main(int argc, char *argv[]) {
    srand(time(nullptr)); // Seed for random number generation

    std::stringstream output;

    output << "=================================================================" << std::endl;
    output << "CS 433 Programming assignment 5" << std::endl;
    output << "Author: xxxxxx and xxxxxxx" << std::endl;
    output << "Date: xx/xx/20xx" << std::endl;
    output << "Course: CS433 (Operating Systems)" << std::endl;
    output << "Description : Program to simulate different page replacement algorithms" << std::endl;
    output << "=================================================================\n" << std::endl;

    // Command line arguments validation
    if (argc != 3) {
        output << "Usage: " << argv[0] << " <page_size> <initial_num_frames>" << std::endl;
        return EXIT_FAILURE;
    }

    int page_size = std::atoi(argv[1]);
    int initial_num_frames = std::atoi(argv[2]);

    // Validate page size and initial number of frames
    if (!isPowerOfTwo(page_size) || !isPowerOfTwo(initial_num_frames)) {
        output << "Page size and initial number of frames must be powers of two." << std::endl;
        return EXIT_FAILURE;
    }

    output << "Page size = " << page_size << " bytes" << std::endl;
    output << "Physical Memory size = " << page_size * initial_num_frames << " bytes" << std::endl;

    int num_pages = pow(2, 32) / page_size;
    output << "Number of pages = " << num_pages << std::endl;
    output << "Initial number of physical frames = " << initial_num_frames << "\n" << std::endl;

    output << "================================Test 1==================================================" << std::endl;

    int num_iterations = 100; // Number of iterations for test 1
    int num_frames = initial_num_frames;

    for (int i = 0; i < num_iterations; ++i) {
        int logical_address, page_number;
        generate_logical_address(logical_address, page_number, num_pages);

        // Simulate page fault based on whether the page number exceeds the current number of frames
        bool is_page_fault = page_number >= num_frames;

        // Generate output
        generate_output(output, logical_address, page_number, 0, is_page_fault);
    }

    output << "================================End of Test 1==================================================" << std::endl;

    // Test 2: Simulating FIFO, LIFO, and LRU replacement algorithms
    output << "================================Test 2==================================================" << std::endl;

    num_iterations = 2000000; // Number of iterations for test 2
    num_frames = initial_num_frames;

    std::vector<int> references;
    for (int i = 0; i < num_iterations; ++i) {
        int logical_address, page_number;
        generate_logical_address(logical_address, page_number, num_pages);
        references.push_back(page_number); // Collect page references for simulation
    }

    // Simulating FIFO replacement algorithm
    output<< "****************Simulate FIFO replacement****************************" << std::endl;
    auto start_fifo = std::chrono::high_resolution_clock::now();
    int fifo_page_faults = simulate_FIFO(references, num_frames);
    auto end_fifo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_fifo = end_fifo - start_fifo;
    output << "Number of page faults: \t\t" << fifo_page_faults << std::endl;
    output << "Elapsed time = " << elapsed_seconds_fifo.count() << " seconds" << std::endl;

    // Simulating LIFO replacement algorithm
    output << "****************Simulate LIFO replacement****************************" << std::endl;
    auto start_lifo = std::chrono::high_resolution_clock::now();
    int lifo_page_faults = simulate_LIFO(references, num_frames);
    auto end_lifo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_lifo = end_lifo - start_lifo;
    output << "Number of page faults: \t\t" << lifo_page_faults << std::endl;
    output << "Elapsed time = " << elapsed_seconds_lifo.count() << " seconds" << std::endl;

    // Simulating LRU replacement algorithm
    output << "****************Simulate LRU replacement****************************" << std::endl;
    auto start_lru = std::chrono::high_resolution_clock::now();
    int lru_page_faults = simulate_LRU(references, num_frames);
    auto end_lru = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_lru = end_lru - start_lru;
    output << "Number of page faults: \t\t" << lru_page_faults << std::endl;
    output << "Elapsed time = " << elapsed_seconds_lru.count() << " seconds" << std::endl;

 // Saving output to a file
    save_statistics("output.txt", output.str());

    return EXIT_SUCCESS;
}
