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


#ifndef TALOS_FILE_STRING_HXX


namespace Talos
{

  template<typename T>
  string to_str(const T& input);

  template <class T>
  void to_num(const string& s, T& num);

  template <class T>
  T to_num(const string& s);

  bool is_num(const string& s);

  bool is_integer(const string& s);

  bool is_unsigned_integer(const string& s);

}  // namespace Talos.


#define TALOS_FILE_STRING_HXX
#endif
