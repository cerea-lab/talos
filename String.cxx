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


#ifndef TALOS_FILE_STRING_CXX

#include "String.hxx"

namespace Talos
{

  //! Converts most types to string.
  /*!
    \param input variable to be converted.
    \return A string containing 'input'.
  */
  template<typename T>
  string to_str(const T& input)
  {
    ostringstream output;
    output << input;
    return output.str();
  }

  //! Converts string to most types, specially numbers.
  /*!
    \param input string to be converted.
    \param num 'input' converted to 'T'.
  */
  template <class T>
  void to_num(const string& s, T& num)
  {
    istringstream str(s);
    str >> num;
  }

  //! Converts string to most types, specially numbers.
  /*!
    \param input string to be converted.
    \return 'input' converted to 'T'.
  */
  template <class T>
  T to_num(const string& s)
  {
    T num;
    istringstream str(s);
    str >> num;
    return num;
  }

}  // namespace Talos.


#define TALOS_FILE_STRING_CXX
#endif
