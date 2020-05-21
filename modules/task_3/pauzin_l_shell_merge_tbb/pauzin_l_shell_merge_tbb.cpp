// Copyright 2020 Pauzin Leonid
#include "../../../modules/task_3/pauzin_l_shell_merge_tbb/pauzin_l_shell_merge_tbb.h"
#include <tbb/tbb.h>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

std::vector<int> getRandomVector(int n) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) { vec[i] = gen() % 100; }
  return vec;
}

std::vector <int> ShellSort(const std::vector <int>& vec) {
  int step, i, j, tmp;
  int size = vec.size();
  std::vector <int> resulVec(vec);
  for (step = size / 2; step > 0; step /= 2)
    for (i = step; i < size; i++)
      for (j = i - step; j >= 0 && resulVec[j] > resulVec[j + step]; j -= step) {
        tmp = resulVec[j];
        resulVec[j] = resulVec[j + step];
        resulVec[j + step] = tmp;
      }
  return resulVec;
}


std::vector<int> shellSort(const std::vector<int>& A, int size) {
  int step, i, j, tmp;
  std::vector<int>array(A);
  for (step = size / 2; step > 0; step /= 2) {
    for (i = step; i < size; i++) {
      for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step) {
        tmp = array[j];
        array[j] = array[j + step];
        array[j + step] = tmp;
      }
    }
  }
  return array;
}


std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, size_t nthreads) {
  std::vector<std::vector<int>> outVec;
  size_t length = vec.size() / nthreads;
  size_t remain = vec.size() % nthreads;
  size_t begin = 0;
  size_t end = 0;

  for (size_t i = 0; i < fmin(nthreads, vec.size()); ++i) {
    end += (remain > 0) ? (length + !!(remain--)) : length;
    outVec.push_back(std::vector<int>(vec.begin() + begin, vec.begin() + end));
    begin = end;
  }
  return outVec;
}

std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2) {
  int i = 0, j = 0;
  int k = 0;
  int size1 = vec1.size();
  int size2 = vec2.size();
  std::vector<int> result(size1+size2);

  while (size1 && size2) {
    if (vec1[i] < vec2[j]) {
      result[k] = vec1[i];
      i++;
      size1--;
    } else {
      result[k] = vec2[j];
      j++;
      size2--;
    }
    k++;
  }

  if (size1 == 0) {
    for (int z = j; z < j + size2; z++) {
      result[k] = vec2[z];
      k++;
    }
  } else if (size2 == 0) {
    for (int z = i; z < i + size1; z++) {
      result[k] = vec1[z];
      k++;
    }
  }

  return result;
}

std::vector<int> myMerge_SEQ(const std::vector<std::vector<int>>& A, const int n, int size) {
  std::vector<int> res = A[0];

  for (int i = 1; i < n; i++) {
    res = myMerge(res, A[i]);
  }
  return res;
}

std::vector<int> shellBatcher_seq(const std::vector<int>& A, const int n, int size) {
  std::vector<std::vector<int>> vec = splitVector(A, n);
  std::vector<int> res;
  for (int i = 0; i < static_cast<int> (vec.size()); ++i) {
    vec[i] = shellSort(vec[i], vec[i].size());
  }
  const int thread = n;
  res = myMerge_SEQ(vec, thread, size);

  return res;
}


std::vector<int> ShellMerge_tbb(const std::vector<int>& A, const int nthreads, int size) {
  std::vector<std::vector<int>> vec = splitVector(A, nthreads);
  std::vector<int> res;
  tbb::task_scheduler_init init(nthreads);
  tbb::parallel_for(tbb::blocked_range<size_t>(0, vec.size(), 1),
    [&vec](const tbb::blocked_range<size_t>& r) {
      int begin = r.begin(), end = r.end();
      for (int i = begin; i != end; ++i)
        vec[i] = shellSort(vec[i], vec[i].size());
    }, tbb::simple_partitioner());

  init.terminate();
  res = myMerge_SEQ(vec, nthreads, size);
  return res;
}

//  std::vector <int> mySortOmp(std::vector<int> vec, std::size_t nthreads) {
//  omp_set_num_threads(nthreads);
//  std::vector<int> result = vec;
//  int size = result.size();
//  std::size_t delta = vec.size() / nthreads;
//  std::size_t remainder = vec.size() % nthreads;
//  std::vector<int> localVec;
//  if (size == 1)
//    return vec;
//  if (size < 1)
//    throw "Wrong vector size";
//
//  #pragma omp parallel shared(vec, remainder) private(localVec)
//  {
//    std::size_t tid = omp_get_thread_num();
//    if (tid == 0) {
//      localVec.resize(delta + remainder);
//      std::copy(vec.begin(), vec.begin() + delta + remainder, localVec.begin());
//    } else {
//        localVec.resize(delta);
//    }
//
//    for (std::size_t i = 1; i < nthreads; i++) {
//      if (tid == i) {
//        std::copy(vec.begin() + delta * i + remainder, vec.end() - delta *(nthreads - i - 1), localVec.begin());
//      }
//    }
//
//    localVec = ShellSort(localVec);
//
//  #pragma omp master
//    result = localVec;
//  #pragma omp barrier
//  #pragma omp critical
//    if (tid != 0) {
//      result = myMerge(localVec, result);
//    }
//  }
//  return result;
//}
