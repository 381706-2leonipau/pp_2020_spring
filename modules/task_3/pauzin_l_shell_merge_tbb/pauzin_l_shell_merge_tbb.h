// Copyright 2020 Pauzin Leonid
#ifndef MMODULES_TASK_3_PAUZIN_L_SHELL_MERGE_TBB_PAUZIN_L_SHELL_MERGE_TBB_H_
#define MODULES_TASK_3_PAUZIN_L_SHELL_MERGE_TBB_PAUZIN_L_SHELL_MERGE_TBB_H_

#include <vector>

std::vector <int> ShellSort(const std::vector <int> &vec);
std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2);
std::vector <int> mySortOmp(std::vector<int> vec1, std::size_t nthreads);
std::vector<int> getRandomVector(int n);
std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, size_t nthreads);
std::vector<int> ShellMerge_tbb(const std::vector<int>& A, const int nthreads, int size);
#endif  // MODULES_TASK_3_PAUZIN_L_SHELL_MERGE_TBB_PAUZIN_L_SHELL_MERGE_TBB_H_
