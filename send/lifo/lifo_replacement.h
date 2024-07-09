#pragma once

#include <vector>
#include <list>
#include <unordered_map>

int simulate_LIFO(const std::vector<int>& references, int num_frames) {
    std::unordered_map<int, bool> page_table;
    std::list<int> lifo_stack;

    int page_faults = 0;

    for (int page : references) {
        if (page_table.find(page) == page_table.end()) {
            if (lifo_stack.size() == num_frames) {
                int evicted_page = lifo_stack.back();
                lifo_stack.pop_back();
                page_table.erase(evicted_page);
            }
            lifo_stack.push_back(page);
            page_table[page] = true;
            ++page_faults;
        }
    }

    std::cout << "LIFO Page Faults: " << page_faults << std::endl;
}
