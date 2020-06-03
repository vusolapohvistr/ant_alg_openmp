#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <random>
#include <chrono>

#include "Ant.h"
#include "AntAlg.h"

#define GRAPH_NODES 100

auto get_mat_from_file(std::string file_path) -> std::vector<std::vector<double_t>>;
auto gen_graph(int size, int additional_edges, double_t max_weight) -> std::vector<std::vector<double_t>>;

template <class T>
void print_vector(std::vector<T> &vec) {
    for (auto& val : vec) {
        std::cout << val << " ";
    }
}


int main() {
    Config config = Config {
        .alfa = 0.7,
        .beta = 0.3,
        .ant_capacity = 1000.0,
        .ro = 0.3,
        .ant_num = 30,
        .iters = 100
    };

    // auto weight_mat = get_mat_from_file("matrix.txt");
    auto weight_mat = gen_graph(GRAPH_NODES, 100, 1000.0);
    auto targets = std::vector<int> ({0, 2, 4});
    // print_vector(weight_mat[0]);

    auto start = std::chrono::high_resolution_clock::now();

    auto result = ant_alg_openmp(weight_mat, &config, 0, targets);

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Time spent "
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
        << "ms" << std::endl;
    std::cout << "Total way " << result.total_way << std::endl;
    std::cout << "Path: ";
    print_vector(result.path);
    return 0;
}

auto get_mat_from_file(std::string file_path) -> std::vector<std::vector<double_t>> {
    std::vector<std::vector<double_t>> answer;
    std::ifstream infile(file_path);
    if (!infile.is_open()) {
        throw new FILE;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<double_t> row;
        while (iss) {
            double_t a;
            iss >> a;
            row.push_back(a);
        }
        answer.push_back(row);
    }

    return answer;
}

auto gen_graph(int size, int additional_edges, double_t max_weight) -> std::vector<std::vector<double_t>> {
    auto result = std::vector<std::vector<double_t>> (size, std::vector<double_t> (size, 0.0));
    std::set<int> used_nodes;

    std::default_random_engine generator;
    std::uniform_real_distribution<double_t> uniform_double(0.0 , max_weight);
    std::uniform_int_distribution<int> uniform_int(0, size - 1);

    auto current_node = 0;

    while (used_nodes.size() < size) {
        auto next_node = current_node;
        while (next_node == current_node) {
            next_node = uniform_int(generator);
        }
        auto weight = uniform_double(generator);
        result[current_node][next_node] = weight;
        result[next_node][current_node] = weight;
        used_nodes.insert(current_node);
        current_node = next_node;
    }

    if (current_node != 0) {
        result[current_node][0] = max_weight / 2;
        result[0][current_node] = max_weight / 2;
    }

    for (int i = 0; i < additional_edges; i++) {
        auto next_node = current_node;
        while (next_node == current_node) {
            next_node = uniform_int(generator);
        }
        auto weight = uniform_double(generator);
        result[current_node][next_node] = weight;
        result[next_node][current_node] = weight;
        used_nodes.insert(current_node);
        current_node = next_node;
    }

    if (current_node != 0) {
        result[current_node][0] = max_weight / 2;
        result[0][current_node] = max_weight / 2;
    }

    return result;
}