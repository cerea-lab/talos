// Copyright (C) 2004 Vivien Mallet
//
// This file is part of Talos library.
// Talos library provides miscellaneous tools to make up for C++
// lacks and to ease C++ programming.
// 
// Talos is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Talos is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (file "license") for more details.
//
// For more information, please see the Talos home page:
//     http://spacetown.free.fr/lib/talos/


#ifndef TALOS_FILE_TALOS_HXX


#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//! To display a message... call Hermes!
#ifndef ERR
#define ERR(x) std::cout << "Hermes - " #x << std::endl
#endif
//! To display a variable (with its name).
#ifndef DISP
#define DISP(x) std::cout << #x ": " << x << std::endl
#endif

namespace Talos
{
  using namespace std;
}

#include "String.cxx"
#include "Date.cxx"
#include "Files.cxx"

#define TALOS_FILE_TALOS_HXX
#endif
