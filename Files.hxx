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
  unsigned long file_size(string file_name);
  unsigned long stream_size(istream& stream);
  bool is_empty(istream& stream);
  bool has_element(istream& stream);

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
		 string delimiters = " \t:=|");

    bool Discard(string line) const;

    void SetDelimiters(string delimiters);
    void SetComments(string comments);

    string GetDelimiters() const;
    string GetComments() const;
    string GetFileName() const;

    ConfigStream& SkipDelimiters();
    string RemoveDelimiters(const string& str) const;

    void Open(string file_name, openmode mode = in);
    void Close();

    ConfigStream& Rewind();

    string GetFullLine();
    bool GetFullLine(string& line);
    string PeekFullLine();
    string PeekFullLine(streampos& position);
    bool PeekFullLine(string& line);

    string GetLine();
    bool GetLine(string& line);
    string PeekLine();
    string PeekLine(streampos& position);
    bool PeekLine(string& line);

    bool Find(string element);

    string GetElement();
    template <class T>
    bool GetElement(T& element);
    string PeekElement();
    template <class T>
    bool PeekElement(T& element);

    double GetNumber();
    template <class T>
    bool GetNumber(T& number);
    double PeekNumber();
    template <class T>
    bool PeekNumber(T& number);

    template <class T>
    bool GetValue(string name, T& value);
    template <class T>
    bool PeekValue(string name, T& value);

    bool GetValue(string name, string& value);
    bool PeekValue(string name, string& value);
  };

}  // namespace Talos.


#define TALOS_FILE_FILES_HXX
#endif
