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


#ifndef TALOS_FILE_FILES_CXX

#include "Files.hxx"

namespace Talos
{
  
  //! Tests whether a file exists.
  /*!
    \param file_name file name.
    \return true if the file exists, false otherwise.
    \note This function returns false if the user has not the rights to
    read the file, even if the file exists.
   */
  bool exists(string file_name)
  {
    ifstream file_stream(file_name.c_str(), ifstream::in);
    bool ans = file_stream.is_open();
    file_stream.close();
    
    return ans;
  }

}  // namespace Talos.


#define TALOS_FILE_FILES_CXX
#endif
