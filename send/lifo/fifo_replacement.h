#pragma once

#include <vector>
#include <queue>
#include <unordered_map>

int simulate_FIFO(const std::vector<int>& references, int num_frames) {
    std::unordered_map<int, bool> page_table;
    std::queue<int> fifo_queue;

    int page_faults = 0;

    for (int page : references) {
        if (page_table.find(page) == page_table.end()) {
            if (fifo_queue.size() == num_frames) {
                int evicted_page = fifo_queue.front();
                fifo_queue.pop();
                page_table.erase(evicted_page);
            }
            fifo_queue.push(page);
            page_table[page] = true;
            ++page_faults;
        }
    }

    std::cout << "FIFO Page Faults: " << page_faults << std::endl;
}