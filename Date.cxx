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


#ifndef TALOS_FILE_DATE_CXX

#include "Date.hxx"

namespace Talos
{

  //////////
  // DATE //
  //////////

  //! Constructor.
  /*!
    \param yyyymmdd date in format YYYYMMDD.
  */
  Date::Date(int yyyymmdd):
    hour_(0), minutes_(0), seconds_(0),
    month_lengths_(12)
  {
    year_ = yyyymmdd / 10000;
    month_ = (yyyymmdd % 10000) / 100;
    day_ = yyyymmdd % 100;

    int month_lengths[12] = {31, 28, 31, 30, 31, 30,
			     31, 31, 30, 31, 30, 31};
    for (int i=0; i<12; ++i)
      month_lengths_[i] = month_lengths[i];

    this->Adjust();
  }

  //! Constructor.
  /*!
    \param yyyy year.
    \param mm month.
    \param dd day.
    \param hh hour.
    \param mn minutes.
    \param sc seconds.
  */
  Date::Date(int yyyy, int mm, int dd,
	     int hh, int mn, int sc):
    year_(yyyy), month_(mm), day_(dd),
    hour_(hh), minutes_(mn), seconds_(sc),
    month_lengths_(12)
  {
    int month_lengths[12] = {31, 28, 31, 30, 31, 30,
			     31, 31, 30, 31, 30, 31};
    for (int i=0; i<12; ++i)
      month_lengths_[i] = month_lengths[i];

    this->Adjust();
  }

  //! Sets the date.
  /*!
    \param yyyymmdd date in format YYYYMMDD.
  */
  void Date::SetDate(int yyyymmdd)
  {
    year_ = yyyymmdd / 10000;
    month_ = (yyyymmdd % 10000) / 100;
    day_ = yyyymmdd % 100;

    this->Adjust();
  }

  //! Sets the date.
  /*!
    \param yyyy year.
    \param mm month.
    \param dd day.
    \param hh hour.
    \param mn minutes.
    \param sc seconds.
  */
  void Date::SetDate(int yyyy, int mm, int dd,
		     int hh, int mn, int sc)
  {
    year_ = yyyy;
    month_ = mm;
    day_ = dd;
    hour_ = hh;
    minutes_ = mn;
    seconds_ = sc;

    this->Adjust();
  }

  //! Adjusts month lengths according to the year.
  void Date::LeapYearAdjust()
  {
    if (LeapYear())
      month_lengths_[1] = 29;
    else
      month_lengths_[1] = 28;
  }

  //! Adjusts the date to make it valid.
  void Date::Adjust()
  {
    // Minutes.
    if (seconds_ > 59)
      {
	minutes_ += seconds_ / 60;
	seconds_ = seconds_ % 60;
      }
    else if (seconds_ < 0)
      {
	minutes_ += seconds_ / 60 - 1;
	seconds_ = 60 + seconds_ % 60;
      }

    // Hours.
    if (minutes_ > 59)
      {
	hour_ += minutes_ / 60;
	minutes_ = minutes_ % 60;
      }
    else if (minutes_ < 0)
      {
	hour_ += minutes_ / 60 - 1;
	minutes_ = 60 + minutes_ % 60;
      }

    // Days.
    if (hour_ > 23)
      {
	day_ += hour_ / 24;
	hour_ = hour_ % 24;
      }
    else if (hour_ < 0)
      {
	day_ += hour_ / 24 - 1;
	hour_ = 24 + hour_ % 24;
      }

    // Months.
    if (month_ > 12)
      {
	year_ += month_ / 12;
	month_ = month_ % 12;
      }
    else if (month_ < 0)
      {
	year_ += month_ / 12 - 1;
	month_ = 12 + month_ % 12;
      }
    this->LeapYearAdjust();

    // Months again.
    while (day_ > month_lengths_[month_ - 1])
      {
	day_ -= month_lengths_[month_ - 1];
	++month_;
	if (month_ == 13)
	  {
	    month_ = 1;
	    ++year_;
	    this->LeapYearAdjust();
	  }
      }

    while (day_ <= 0)
      {
	--month_;
	if (month_ == 0)
	  {
	    month_ = 12;
	    --year_;
	    this->LeapYearAdjust();
	  }
	day_ += month_lengths_[month_ - 1];
      }

  }

  //! Is a given year a leap year?
  /*!
    \param year year.
    \return true if the year 'year' is a leap year, false otherwise.
  */
  bool Date::LeapYear(int year) const
  {
    return ( year % 4 == 0
	     && ( year % 100 != 0 || year % 400 == 0 ) );
  }

  //! Is the current year a leap year?
  /*!
    \return true if the current year is a leap year, false otherwise.
  */
  bool Date::LeapYear() const
  {
    return this->LeapYear(year_);
  }

  //! Returns the date in format YYYYMMDD.
  /*!
    \return The date in format YYYYMMDD.
  */
  int Date::GetDate() const
  {
    return year_ * 10000 + month_ * 100 + day_;
  }

  //! Returns the date in a given format.
  /*!
    'format' defines the format of the output. Special sequences are
    %y, %m, %d, %h, %i, %s for the year, the month, the day, the hour,
    the minutes and the seconds respectively.
    \param format format.
    \return The date in format 'format'.
  */
  string Date::GetDate(const string& format) const
  {
    string output("");
    string::size_type index_b(0), index_e;

    while ( (index_b != string::npos)
	    || (index_b < format.size()) )
      {
	index_e = index_b + format.substr(index_b).find_first_of("%");
	if ( (index_e != string::npos) && (index_e != format.size() - 1) )
	  {
	    output += format.substr(index_b, index_e - index_b);
	    if ( format[index_e+1] == 'y')
	      output += to_str_fill(year_, '0', 4);
	    else if ( format[index_e+1] == 'm')
	      output += to_str_fill(month_, '0', 2);
	    else if ( format[index_e+1] == 'd')
	      output += to_str_fill(day_, '0', 2);
	    else if ( format[index_e+1] == 'h')
	      output += to_str_fill(hour_, '0', 2);
	    else if ( format[index_e+1] == 'i')
	      output += to_str_fill(minutes_, '0', 2);
	    else if ( format[index_e+1] == 's')
	      output += to_str_fill(seconds_, '0', 2);
	    else
	      output += format.substr(index_e, 2);
	    index_b = index_e + 2;
	  }
	else
	  {
	    output += format.substr(index_b);
	    index_b = string::npos;
	  }
      }

    return output;
  }

  //! Returns the date in a given format.
  /*!
    'format' defines the format of the output. Special sequences are
    %y, %m, %d, %h, %i, %s for the year, the month, the day, the hour,
    the minutes and the seconds respectively.
    \param format format.
    \param date (output) the date in format 'format'.
  */
  template <class T>
  void Date::GetDate(const string& format, T& date) const
  {
    date = to_num<T>(this->GetDate(format));
  }

  //! Returns the year.
  /*!
    \return The year.
  */
  int Date::GetYear() const
  {
    return year_;
  }

  //! Returns the month.
  /*!
    \return The month.
  */
  int Date::GetMonth() const
  {
    return month_;
  }

  //! Returns the day.
  /*!
    \return The day.
  */
  int Date::GetDay() const
  {
    return day_;
  }

  //! Returns the hour.
  /*!
    \return The hour.
  */
  int Date::GetHour() const
  {
    return hour_;
  }

  //! Returns the minutes.
  /*!
    \return The minutes.
  */
  int Date::GetMinutes() const
  {
    return minutes_;
  }

  //! Returns the seconds.
  /*!
    \return The seconds.
  */
  int Date::GetSeconds() const
  {
    return seconds_;
  }

  //! Adds years to the current date.
  /*!
    \param nb_yy number of years.
  */
  void Date::AddYears(int nb_yy)
  {
    year_ += nb_yy;
    this->Adjust();
  }

  //! Adds months to the current date.
  /*!
    \param nb_mm number of months.
  */
  void Date::AddMonths(int nb_mm)
  {
    month_ += nb_mm;
    this->Adjust();
  }

  //! Adds days to the current date.
  /*!
    \param nb_dd number of days.
  */
  void Date::AddDays(int nb_dd)
  {
    day_ += nb_dd;
    this->Adjust();
  }

  //! Adds hours to the current date.
  /*!
    \param nb_hh number of hours.
  */
  void Date::AddHours(int nb_hh)
  {
    hour_ += nb_hh;
    this->Adjust();
  }

  //! Adds minutes to the current date.
  /*!
    \param nb_mn number of minutes.
  */
  void Date::AddMinutes(int nb_mn)
  {
    minutes_ += nb_mn;
    this->Adjust();
  }

  //! Adds seconds to the current date.
  /*!
    \param nb_sc number of seconds.
  */
  void Date::AddSeconds(int nb_sc)
  {
    seconds_ += nb_sc;
    this->Adjust();
  }

  //! Sets the year.
  /*!
    \param yyyy the year.
  */
  void Date::SetYear(int yyyy)
  {
    year_ = yyyy;
    this->Adjust();
  }

  //! Sets the month.
  /*!
    \param mm the month.
  */
  void Date::SetMonth(int mm)
  {
    month_ = mm;
    this->Adjust();
  }

  //! Sets the day.
  /*!
    \param dd the day.
  */
  void Date::SetDay(int dd)
  {
    day_ = dd;
    this->Adjust();
  }

  //! Sets the hour.
  /*!
    \param hh the hour.
  */
  void Date::SetHour(int hh)
  {
    hour_ = hh;
    this->Adjust();
  }

  //! Sets the minutes.
  /*!
    \param mn minutes.
  */
  void Date::SetMinutes(int mn)
  {
    minutes_ = mn;
    this->Adjust();
  }

  //! Sets the seconds.
  /*!
    \param sc seconds.
  */
  void Date::SetSeconds(int sc)
  {
    seconds_ = sc;
    this->Adjust();
  }

  //! Returns the number of the day in the year (between 1 and 366).
  /*!
    \return The number of the day in the year (between 1 and 366).
  */
  int Date::GetDayNumber() const
  {
    int res(0);
    for (int i=1; i<month_; i++)
      res += month_lengths_[i - 1];
    return res + day_ - 1;
  }

  //! Returns the number of days from a given date.
  /*!
    \param date the reference date.
    \return The number of days between 'date' and the current date
    (positive if the current date is greater than 'date').
  */
  int Date::GetDaysFrom(Date date) const
  {
    int min_year = min(year_, date.GetYear());
    int nb_days(0), nb_days_date(0);
    for (int i=min_year; i<year_; i++)
      nb_days += this->LeapYear(i) ? 366 : 365;
    nb_days += this->GetDayNumber();
    for (int i=min_year; i<date.GetYear(); i++)
      nb_days_date += this->LeapYear(i) ? 366 : 365;
    nb_days_date += date.GetDayNumber();

    return nb_days - nb_days_date;
  }

}  // namespace Talos.


#define TALOS_FILE_DATE_CXX
#endif
