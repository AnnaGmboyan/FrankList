# FrankList

FrankList is a C++ template class that implements a doubly linked list with additional features such as sorting and reversing.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
  - [Installation](#installation)
  - [Including in Your Project](#including-in-your-project)
  - [Creating a FrankList Object](#creating-a-franklist-object)
  - [Manipulating the List](#manipulating-the-list)
  - [Iterating Through the List](#iterating-through-the-list)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

`FrankList` is a versatile C++ template class that provides a doubly linked list implementation with various features such as sorting, reversing, and multiply iterators. 
 It offers flexibility and efficiency for managing collections of elements in C++ applications.

## Features

- **Doubly Linked List**: Implements a doubly linked list data structure for efficient element management.
- **Sorting**: Provides methods for sorting elements in ascending and descending order.
- **Reversing**: Supports reversing the order of elements in the list.
- **Iterators**: Offers a range of iterators for traversing the list in different orders.
- **Initializer Lists**: Supports initialization using initializer lists for convenient list creation.
- **Size Management**: Allows resizing, pushing, and popping elements efficiently.
- **Comparison Operators**: Supports comparison operators for comparing lists.

## Usage

### Installation

There's no separate installation required for FrankList. You simply need to include the `FrankList.hpp` header file in your project

```cpp
#include "FrankList.hpp"
```
## Examples
```cpp
FrankList<int> mylist;
mylist.push_back(10);
mylist.push_back(20);
mylist.pop_front();
for (auto it = mylist.begin(); it != mylist.end(); ++it) {
    std::cout << *it << " ";
}
FrankList<int> mylist = {3, 1, 4, 1, 5, 9, 2, 6, 5};
mylist.sort();
FrankList<int> mylist = {1, 2, 3, 4, 5};
mylist.reverse();
FrankList<int> mylist = {1, 2, 3, 4, 5};
for (auto it = mylist.begin(); it != mylist.end(); ++it) {
    std::cout << *it << " ";
}
```
