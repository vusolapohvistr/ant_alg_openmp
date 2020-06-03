//
// Created by news on 27.05.2020.
//
#include <vector>
#include <omp.h>
#include <memory>
#include <iostream>
#include <random>
#include <math.h>

#ifndef ANT_ALG_OPENMP_ANT_H
#define ANT_ALG_OPENMP_ANT_H

struct Config {
    float alfa;
    float beta;
    float ant_capacity;
    float ro;
    float ant_num;
    float iters;
};

class Ant {
private:
    Config* config{};
public:
    std::vector<int> path;
    double_t total_way = 0.0;
    bool cant_find_way = false;

    explicit Ant (Config* conf);
    void go(int32_t start_point,
            std::vector<int> &targets,
            std::vector<std::vector<double_t>> &weight_mat,
            std::vector<std::vector<double_t>> &pheromones_mat);
    void change_pheromones_mat(std::vector<std::vector<double_t>> pheromones_mat);
    void print_config();
};


#endif //ANT_ALG_OPENMP_ANT_H
