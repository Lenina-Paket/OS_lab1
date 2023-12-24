#pragma once

#include <string>
#include <vector>

const int SIZE = 1024;

std::vector<int> search(const std::string& str, const std::string& ptrn) {
    std::vector<int> ans;
    int n = str.size();
    int m = ptrn.size();

    for (int i = 0; i <= n - m; ++i) {
        bool found = true;

        for (int j = 0; j < m; ++j) {
        if (str[i + j] != ptrn[j]) {
            found = false;
            break;
        }
        }

        if (found) {
            ans.push_back(i);
        }
    }

    return ans;
}
