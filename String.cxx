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

  //! Checks whether a string is a number.
  /*!
    \param str string to be checked.
    \return true if 'str' is a number, false otherwise.
  */
  bool is_num(const string& str)
  {
    if (str=="")
      return false;

    bool mant, mant_a, mant_b, exp;
    string::size_type pos;
    string m, e, m_a, m_b;

    pos = str.find_first_of("eE");
    // Mantissa.
    m = str.substr(0, pos);
    // Exponent.
    e = pos==string::npos ? "" : str.substr(pos + 1);

    exp = pos!=string::npos;

    pos = m.find_first_of(".");
    // Mantissa in the form: [m_a].[m_b].
    m_a = m.substr(0, pos);
    // Exponent.
    m_b = pos==string::npos ? "" : m.substr(pos + 1);

    mant = m!="" && m!="-" && m!="+";
    mant_a = m_a!="" && m_a!="-" && m_a!="+";
    mant_b = m_b!="";

    return ( mant
	     && ( (mant_a || mant_b)
		  && (!mant_a || is_integer(m_a))
		  && (!mant_b || is_unsigned_integer(m_b)) )
	     && (!exp || is_integer(e)) );
  }

  //! Checks whether a string is an integer.
  /*!
    \param str string to be checked.
    \return true if 'str' is an integer, false otherwise.
  */
  bool is_integer(const string& str)
  {
    bool ans;

    ans = ( str.size() > 0 && isdigit(str[0]) )
      || ( str.size() > 1 && (str[0]=='+' || str[0]=='-') );

    unsigned int i(1);
    while (i<str.size() && ans)
      {
	ans = ans && isdigit(str[i]);
	i++;
      }

    return ans;
  }

  //! Checks whether a string is an unsigned integer.
  /*!
    \param str string to be checked.
    \return true if 'str' is an unsigned integer, false otherwise.
  */
  bool is_unsigned_integer(const string& str)
  {
    bool ans(str.size() > 0);

    unsigned int i(0);
    while (i<str.size() && ans)
      {
	ans = ans && isdigit(str[i]);
	i++;
      }

    return ans;
  }

}  // namespace Talos.


#define TALOS_FILE_STRING_CXX
#endif
