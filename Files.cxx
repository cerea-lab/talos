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

  //! Returns a file size.
  /*!
    \param file_name file name.
    \return the file size in bytes.
  */
  unsigned long file_size(string file_name)
  {
    ifstream file_stream(file_name.c_str(), ifstream::in);
    streampos position = file_stream.tellg();
    file_stream.seekg(0, ios::end);

    return (file_stream.tellg() - position);
  }

  //! Returns a stream size.
  /*!
    \param stream the stream.
    \return the stream size in bytes.
  */
  unsigned long stream_size(istream& stream)
  {
    streampos position = stream.tellg();
    stream.seekg(0, ios::end);
    unsigned long length = stream.tellg() - position;
    stream.seekg(position, ios::beg);

    return length;
  }

  //! Checks whether a stream is empty.
  /*!
    \param stream the stream.
    \return true if the stream is empty, false otherwise.
  */
  bool is_empty(istream& stream)
  {
    streampos position = stream.tellg();
    istream::iostate state = stream.rdstate();

    stream.get();
    bool res = !stream.good();

    stream.clear(state);
    stream.seekg(position);

    return res;
  }

  //! Checks whether a stream contains an element.
  /*!
    Checks whether a stream contains an element that may be extracted
    through 'operator <<'.
    \param stream the stream.
    \return true if the stream has an element, false otherwise.
  */
  bool has_element(istream& stream)
  {
    streampos position = stream.tellg();
    istream::iostate state = stream.rdstate();

    string element;
    bool res = (stream >> element);

    stream.clear(state);
    stream.seekg(position);

    return res;
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

  //! Skips discarded lines.
  /*!
    Extracts discarded lines.
    \return A reference to the current stream.
  */
  ConfigStream& ConfigStream::SkipDiscarded()
  {
    streampos position;
    while ( (this->good()) && (Discard(PeekFullLine(position))) )
      this->seekg(position);
    return *this;
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

  //! Skips delimiters.
  /*!
    Extracts following delimiters from the string, until another character
    is found.
    \return A reference to the current stream.
  */
  ConfigStream& ConfigStream::SkipDelimiters()
  {
    while ( this->good()
	    && (delimiters_.find_first_of(char(this->peek())) != string::npos) )
      this->get();
    return *this;
  }

  //! Removes delimiters at both ends of a string.
  /*!
    Removes delimiters at the beginning and at the end of a string.
    \param 
  */
  string ConfigStream::RemoveDelimiters(const string& str) const
  {
    string::size_type index = str.find_first_not_of(delimiters_);
    if (index == string::npos)
      return "";
    return str.substr(index,
		      str.find_last_not_of(delimiters_) - index + 1);
  }

  //! Skips discarded lines and delimiters.
  /*!
    Extracts discarded lines and delimiters.
    \return A reference to the current stream.
  */
  ConfigStream& ConfigStream::Skip()
  {
    this->SkipDiscarded();
    return this->SkipDelimiters();
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

  //! Rewinds the stream.
  /*!
    Goes back to the beginning of the stream and clears the control state.
    \return A reference to the current stream.
  */
  ConfigStream& ConfigStream::Rewind()
  {
    this->seekg(0, ifstream::beg);
    this->clear();

    return *this;
  }

  //! Returns the next line.
  /*!
    \return The next line.
  */
  string ConfigStream::GetFullLine()
  {
    string line;

    std::getline(*this, line);

    return line;
  }

  //! Returns the next line.
  /*!
    \param line (output) the next line.
  */
  bool ConfigStream::GetFullLine(string& line)
  {
    return std::getline(*this, line);
  }

  //! Returns the next line without extracting it from the stream.
  /*!
    \return The next line.
  */
  string ConfigStream::PeekFullLine()
  {
    streampos position = this->tellg();
    iostate state = this->rdstate();

    string line;
    std::getline(*this, line);

    this->seekg(position);
    this->clear(state);

    return line;
  }

  //! Returns the next line without extracting it from the stream.
  /*!
    \param position (output) the position of the line following the next line.
    \return The next line.
  */
  string ConfigStream::PeekFullLine(streampos& position)
  {
    streampos position_back = this->tellg();
    iostate state = this->rdstate();

    string line;
    std::getline(*this, line);

    position = this->tellg();

    this->seekg(position_back);
    this->clear(state);

    return line;
  }

  //! Returns the next line without extracting it from the stream.
  /*!
    \param line (output) the next line.
  */
  bool ConfigStream::PeekFullLine(string& line)
  {
    streampos position = this->tellg();
    iostate state = this->rdstate();

    bool success = std::getline(*this, line);

    this->seekg(position);
    this->clear(state);

    return success;
  }

  //! Returns the next valid line.
  /*!
    Returns the next valid line, i.e. the next line that is
    not a line to be discarded and from which comments have been extracted.
    \return The next valid line.
  */
  string ConfigStream::GetLine()
  {
    streampos position;
    bool not_end;
    string line;
    string::size_type index(0), index_tmp;

    this->Skip();
    line = GetFullLine();

    while ( (not_end = ( (index_tmp = line.substr(index).find_first_of(comments_))
			 != string::npos ))
	    && (delimiters_.find_first_of(line[(index+=index_tmp)-1]) == string::npos)
	    && (not_end = (++index != line.size())) );

    if (not_end)
      index --;
    else
      index = line.size();
    
    while (delimiters_.find_first_of(line[--index]) != string::npos);

    return line.substr(0, index + 1);
  }

  //! Returns the next valid line.
  /*!
    Returns the next valid line, i.e. the next line that is
    not a line to be discarded and from which comments have been extracted.
    \param line (output) the next valid line.
  */
  bool ConfigStream::GetLine(string& line)
  {
    streampos position;
    bool not_end, success;
    string::size_type index(0), index_tmp;

    this->Skip();
    success = GetFullLine(line);

    while ( (not_end = ( (index_tmp = line.substr(index).find_first_of(comments_))
			 != string::npos ))
	    && (delimiters_.find_first_of(line[(index+=index_tmp)-1]) == string::npos)
	    && (not_end = (++index != line.size())) );

    if (not_end)
      index --;
    else
      index = line.size();
    
    while (delimiters_.find_first_of(line[--index]) != string::npos);

    line = line.substr(0, index + 1);

    return success;
  }

  //! Returns the next valid line without extracting it from the stream.
  /*!
    Returns the next valid line, i.e. the next line that is
    not a line to be discarded and from which comments have been extracted.
    Nothing is extracted from the stream.
    \return The next valid line.
  */
  string ConfigStream::PeekLine()
  {
    string line;

    streampos initial_position = this->tellg();
    iostate state = this->rdstate();

    line = GetLine();

    this->seekg(initial_position);
    this->clear(state);

    return line;
  }

  //! Returns the next valid line without extracting it from the stream.
  /*!
    Returns the next valid line, i.e. the next line that is
    not a line to be discarded and from which comments have been extracted.
    Nothing is extracted from the stream.
    \param position (output) the position of the line following the next valid line.
    \return The valid line.
  */
  string ConfigStream::PeekLine(streampos& position)
  {
    streampos position_back = this->tellg();
    iostate state = this->rdstate();

    string line = GetLine();

    position = this->tellg();

    this->seekg(position_back);
    this->clear(state);

    return line;
  }

  //! Returns the next valid line without extracting it from the stream.
  /*!
    Returns the next valid line, i.e. the next line that is
    not a line to be discarded and from which comments have been extracted.
    Nothing is extracted from the stream.
    \param line (output) the next valid line.
  */
  bool ConfigStream::PeekLine(string& line)
  {
    streampos initial_position = this->tellg();
    iostate state = this->rdstate();

    bool success = GetLine(line);

    this->seekg(initial_position);
    this->clear(state);

    return success;
  }

  //! Sets the position of the get pointer after a given element.
  /*!
    Sets the position of the get pointer exactly after a given element.
    \param element the element to be found.
    \return true if the element was found, false otherwise.
  */
  bool ConfigStream::Find(string element)
  {
    string elt;
    while (GetElement(elt) && elt!=element);

    return elt == element;
  }

  //! Returns the next valid element.
  /*!
    Returns the next valid element, i.e. the next element that is
    not in a line to be discarded.
    \return The next valid element.
  */
  string ConfigStream::GetElement()
  {
    streampos position;
    string element;
    string::size_type index, length;

    while ( (this->good()) && (Discard(PeekFullLine(position))) )
      this->seekg(position);
    element = PeekFullLine();

    index = element.find_first_not_of(delimiters_);
    if (index != string::npos)
      {
	length = element.find_first_of(delimiters_, index);
	length = length==string::npos ? element.size() - index : length - index;
	element = element.substr(index, length);
      }
    else
      {
	index = element.size();
	length = 0;
	element = "";
      }

    this->seekg(index + length, ifstream::cur);

    return element;
  }

  //! Gets the next valid element.
  /*!
    Gets the next valid element, i.e. the next element that is
    not in a line to be discarded.
    \param element (output) the next valid element.
  */
  template <class T>
  bool ConfigStream::GetElement(T& element)
  {
    streampos position;
    string line;

    while ( (this->good()) && (Discard(PeekFullLine(position))) )
      this->seekg(position);

    this->SkipDelimiters();

    return ((*this) >> element);
  }

  //! Returns the next valid element without extracting it from the stream.
  /*!
    Returns the next valid element, i.e. the next element that is
    not in a line to be discarded.
    \return The next valid element.
  */
  string ConfigStream::PeekElement()
  {
    streampos initial_position, position;
    string element;
    string::size_type index, length;

    initial_position = this->tellg();
    iostate state = this->rdstate();

    while ( (this->good()) && (Discard(PeekFullLine(position))) )
      this->seekg(position);
    element = PeekFullLine();

    index = element.find_first_not_of(delimiters_);
    if (index != string::npos)
      {
	length = element.find_first_of(delimiters_, index);
	length = length==string::npos ? element.size() - index : length - index;
	element = element.substr(index, length);
      }
    else
      {
	index = element.size();
	length = 0;
	element = "";
      }

    this->seekg(initial_position);
    this->clear(state);

    return element;
  }

  //! Gets the next valid element without extracting it from the stream.
  /*!
    Gets the next valid element, i.e. the next element that is
    not in a line to be discarded.
    \param element (output) the next valid element.
  */
  template <class T>
  bool ConfigStream::PeekElement(T& element)
  {
    streampos initial_position, position;
    string line;
    bool success;

    initial_position = this->tellg();
    iostate state = this->rdstate();

    while ( (this->good()) && (Discard(PeekFullLine(position))) )
      this->seekg(position);

    this->SkipDelimiters();

    success = ((*this) >> element);

    this->seekg(initial_position);
    this->clear(state);

    return success;
  }

  //! Returns the next valid number.
  /*!
    Returns the next valid number, i.e. the next number that is
    not in a line to be discarded.
    \return The next valid number.
  */
  double ConfigStream::GetNumber()
  {
    string element;
    while (GetElement(element) && !is_num(element));

    return is_num(element) ? to_num<double>(element) : 0.;
  }

  //! Gets the next valid number.
  /*!
    Gets the next valid number, i.e. the next number that is
    not in a line to be discarded.
    \param element (output) the next valid number.
  */
  template <class T>
  bool ConfigStream::GetNumber(T& number)
  {
    string element;
    bool success;
    while ((success = GetElement(element)) && !is_num(element));

    number = is_num(element) ? to_num<T>(element) : T(0);

    return success;
  }

  //! Returns the next valid number without extracting it from the stream.
  /*!
    Returns the next valid number, i.e. the next number that is
    not in a line to be discarded.
    \return The next valid number.
  */
  double ConfigStream::PeekNumber()
  {
    streampos initial_position = this->tellg();
    iostate state = this->rdstate();

    string element;
    while (GetElement(element) && !is_num(element));

    this->seekg(initial_position);
    this->clear(state);

    return is_num(element) ? to_num<double>(element) : 0.;
  }

  //! Gets the next valid number without extracting it from the stream.
  /*!
    Gets the next valid number, i.e. the next number that is
    not in a line to be discarded.
    \param number (output) the next valid number.
  */
  template <class T>
  bool ConfigStream::PeekNumber(T& number)
  {
    streampos initial_position = this->tellg();
    iostate state = this->rdstate();

    string element;
    bool success;
    while ((success = GetElement(element)) && !is_num(element));

    number = is_num(element) ? to_num<T>(element) : T(0);

    this->seekg(initial_position);
    this->clear(state);

    return success;
  }

  //! Gets the value of a given variable.
  /*!
    Gets the (numerical) value of a given variable, i.e. the next valid
    (not in a discarded line) number or element following the variable name.
    \param name the name of the variable.
    \param value value associated with the variable.
  */
  template <class T>
  bool ConfigStream::GetValue(string name, T& value)
  {
    string element;
    while (GetElement(element) && element!=name);

    return GetNumber(value);
  }

  //! Gets the value of a given variable without extracting them from the stream.
  /*!
    Gets the (numerical) value of a given variable, i.e. the next valid
    (not in a discarded line) number or element following the variable name.
    Nothing is extracted from the stream.
    \param name the name of the variable.
    \param value value associated with the variable.
  */
  template <class T>
  bool ConfigStream::PeekValue(string name, T& value)
  {
    streampos initial_position = this->tellg();
    iostate state = this->rdstate();

    string element;
    while (GetElement(element) && element!=name);

    bool success = GetNumber(value);

    this->seekg(initial_position);
    this->clear(state);

    return success;
  }

  //! Gets the value of a given variable.
  /*!
    Gets the value of a given variable, i.e. the next valid
    (not in a discarded line) number or element following the variable name.
    \param name the name of the variable.
    \param value value associated with the variable.
  */
  bool ConfigStream::GetValue(string name, string& value)
  {
    string element;
    while (GetElement(element) && element!=name);

    return GetElement(value);
  }

  //! Gets the value of a given variable without extracting them from the stream.
  /*!
    Gets the value of a given variable, i.e. the next valid
    (not in a discarded line) number or element following the variable name.
    Nothing is extracted from the stream.
    \param name the name of the variable.
    \param value value associated with the variable.
  */
  bool ConfigStream::PeekValue(string name, string& value)
  {
    streampos initial_position = this->tellg();
    iostate state = this->rdstate();

    string element;
    while (GetElement(element) && element!=name);

    bool success = GetElement(value);

    this->seekg(initial_position);
    this->clear(state);

    return success;
  }

}  // namespace Talos.


#define TALOS_FILE_FILES_CXX
#endif
