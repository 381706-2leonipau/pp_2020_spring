// Copyright 2020 Parshina Sophie

#include <numeric>
#include <utility>
#include <algorithm>
#include "gtest/gtest.h"
#include <iostream>
#include "../../../modules/task_1/parshina_s_quick_sort/quick_sort.h"

TEST(Hoare_Quick_Sort_sequential, Can_Sort_Correctly) {
  int n = 1000000;

  double* arr = new double[n];  
  Get_Random_Array(arr, n);

  qHoareSort(arr, 0, n - 1);

  ASSERT_EQ(1, IsSorted(arr, n));
}

TEST(Hoare_Quick_Sort_sequential, �an_Sort_Empty_Array) {
  int n = 1000000;

  double* arr = new double[n];
  for (int i = 0; i < n; i++) {
    arr[i] = 0;
  }

  qHoareSort(arr, 0, n - 1);

  double mult_element = 0.0;
  for (int i = 0; i < n; i++) {
    mult_element += arr[i];
  }
  
  ASSERT_EQ(mult_element, 0);
}

TEST(Hoare_Quick_Sort_sequential, Can_Sort_Fully_Double_Array) {
  int n = 1000000;

  double* arr = new double[n];
  Get_Random_Array(arr, n);

  for (int i = 0; i < n; i++) {
    arr[i] *= 3, 1415926535;
  }
  qHoareSort(arr, 0, n - 1);

  ASSERT_EQ(1, IsSorted(arr, n));
}

TEST(Hoare_Quick_Sort_sequential, Can_Sort_Opposite_Elements) {
  int n = 1000000;

  double* arr = new double[n];
  Get_Random_Array(arr, n);

  for (int i = 0; i < n; i+=2) {
    arr[i] = arr[i + 1] * (-1); 
  }

  double* arr2 = new double[n];
  for (int i = 0; i < n; i++) {
    arr2[i] = arr[i];
  }

  qHoareSort(arr, 0, n - 1);
  std::sort(&arr2[0], &arr2[n]);

  int equal_result = (int)std::equal(&arr[0], &arr[n], &arr2[0]);

  ASSERT_EQ(equal_result,1);
}

TEST(Hoare_Quick_Sort_sequential, Can_Sort_Already_Sorted_Elements) {
  int n = 1000000;

  double* arr = new double[n];
  Get_Random_Array(arr, n);
  std::sort(&arr[0], &arr[n]);

  double* arr2 = new double[n];
  for (int i = 0; i < n; i++) {
    arr2[i] = arr[i];
  }

  qHoareSort(arr, 0, n - 1);

  int equal_result = (int)std::equal(&arr[0], &arr[n], &arr2[0]);

  ASSERT_EQ(equal_result, 1);
}

TEST(Hoare_Quick_Sort_sequential, Can_Sort_Mixed_Array) {
  int n = 1000000;

  double* arr = new double[n];
  Get_Random_Array(arr, n); 

  std::sort(&arr[0], &arr[n]); 
  
  double* arr2 = new double[n];
  for (int i = 0; i < n; i++) {
    arr2[i] = arr[i];
  } 

  for (int i = 2; i < n; i += 3) {
    double temp = arr[i - 2];
    arr[i - 2] = arr[i];
    arr[i] = temp;
  }

  qHoareSort(arr, 0, n - 1);

  int equal_result = (int)std::equal(&arr[0], &arr[n], &arr2[0]);

  ASSERT_EQ(equal_result, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 