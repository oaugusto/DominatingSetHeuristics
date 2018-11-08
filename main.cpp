#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <dirent.h>
#include <cstring>
#include <memory>
#include <algorithm>
#include "include/Graph.h"
#include "include/Algorithms.h"

using namespace std;

namespace {
    vector<string> GetDirectoryFiles(const string& dir) {
        vector<string> files;
        shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
        struct dirent *dirent_ptr;
        if (!directory_ptr) {
            cout << "Error opening : " << strerror(errno) << dir << endl;
            return files;
        }

        while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
            string file = string(dirent_ptr->d_name);
            if ((file.compare(".") != 0) && (file.compare("..") != 0)) {
                files.push_back(file);
            }
        }
        return files;
    }
}  // namespace

int main(int argc, char* argv[]) {

    //*******************************************************************
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        cerr << "Usage: " << argv[0] << " <directory>" << endl;
        return 1;
    }

    // input directory
    const auto& directory_path = string(argv[1]);
    auto files = GetDirectoryFiles(directory_path);

    sort(files.begin(), files.end());

    for (const auto& file : files) {

        clock_t begin, end;
        double elapsed_secs;

        ifstream in(directory_path + file);

        if (!in.is_open()) {
            cerr << "error while opening file " << file << endl;
            return 1;
        }

        //create a graph from file
        Graph* graph = Graph::creatGraph(in);
        //graph->print_graph();

        cout << "*******************************************************************" << endl;
        cout << "File: " + file << endl;
        //*******************************************************************

        begin = clock();
        VertexSet solution = greedy_classical(graph);
        end = clock();

        cout << "Solution: " << "\t" << solution.getSize() << "\t";
        elapsed_secs = double(end - begin);
        cout << "Time:" << elapsed_secs*1.0/CLOCKS_PER_SEC << endl;

        cout << "*******************************************************************" << endl;
        //append time
        //*******************************************************************

        delete(graph);

        in.close();
    }

    return 0;
}
