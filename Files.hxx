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


#ifndef TALOS_FILE_FILES_HXX


namespace Talos
{

  bool exists(string file_name);

  class ConfigStream: public ifstream
  {
  private:
    //! File name associated with the stream.
    string file_name_;
    //! Characters that denote a comment line.
    string comments_;
    //! Characters considered as delimiters.
    string delimiters_;

  public:
    ConfigStream();
    ConfigStream(string file_name,
		 string comments = "#%",
		 string delimiters = " \t");

    bool Discard(string line) const;

    void SetDelimiters(string delimiters);
    void SetComments(string comments);

    string GetDelimiters() const;
    string GetComments() const;
    string GetFileName() const;

    void Open(string file_name, openmode mode = in);
    void Close();

    string GetLine();
    void GetLine(string& line);
    string PeekLine();
    string PeekLine(streampos& position);
    void PeekLine(string& line);

    string GetElement();
    template <class T>
    bool GetElement(T& element);
    string PeekElement();
    template <class T>
    bool PeekElement(T& element);
  };

}  // namespace Talos.


#define TALOS_FILE_FILES_HXX
#endif
