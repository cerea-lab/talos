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


  //////////////////
  // CONFIGSTREAM //
  //////////////////

  //! Default constructor.
  /*! Nothing is performed.
   */
  ConfigStream::ConfigStream():
    comments_("#%"), delimiters_(" \t")
  {
  }

  //! Main constructor.
  /*! Opens a file.
    \param file_name file to be opened.
  */
  ConfigStream::ConfigStream(string file_name,
			     string comments,
			     string delimiters):
    ifstream(file_name.c_str()), file_name_(file_name),
    comments_(comments), delimiters_(delimiters)
  {
  }

  //! Checks whether a line should be discarded.
  /*!
    \param line line to be checked.
  */
  bool ConfigStream::Discard(string line) const
  {
    size_t first = line.find_first_not_of(delimiters_);
    return ( (first == string::npos)
	     || (comments_.find_first_of(line[first]) != string::npos) );
  }

  //! Sets the characters considered as delimiters..
  /*!
    \param delimiters delimiters.
  */
  void ConfigStream::SetDelimiters(string delimiters)
  {
    delimiters_ = delimiters;
  }

  //! Sets the characters that denote a comment line.
  /*!
    \param comments the characters that denote a comment line.
  */
  void ConfigStream::SetComments(string comments)
  {
    comments_ = comments;
  }

  //! Returns the characters considered as delimiters..
  /*!
    \return Delimiters.
  */
  string ConfigStream::GetDelimiters() const
  {
    return delimiters_;
  }

  //! Returns the characters that denote a comment line.
  /*!
    \return The characters that denote a comment line.
  */
  string ConfigStream::GetComments() const
  {
    return comments_;
  }

  //! Returns the name of the file that was opened.
  /*!
    \return The name of the file that was opened.
  */
  string ConfigStream::GetFileName() const
  {
    return file_name_;
  }

  //! Opens a file.
  /*!
    \param file_name file name.
    \param mode (optional) flags describing the requested I/O mode for the file.
    Default: in.
    \note If a file was previously opened, it is closed and the stream is cleared.
  */
  void ConfigStream::Open(string file_name, openmode mode)
  {
    this->close();
    this->clear();
    this->open(file_name.c_str(), mode);

    file_name_ = file_name;
  }

  //! Closes the current file.
  /*!
    \note The stream is cleared.
  */
  void ConfigStream::Close()
  {
    this->close();
    this->clear();

    file_name_ = "";
  }

}  // namespace Talos.


#define TALOS_FILE_FILES_CXX
#endif
