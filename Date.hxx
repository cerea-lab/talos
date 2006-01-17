// Copyright (C) 2004-2005 Vivien Mallet
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


#ifndef TALOS_FILE_DATE_HXX


namespace Talos
{

  //! Class Date.
  class Date
  {
  private:
    //! Year.
    int year_;
    //! Month.
    int month_;
    //! Day.
    int day_;
    //! Hour.
    int hour_;
    //! Minutes.
    int minutes_;
    //! Seconds.
    int seconds_;
    //! Month lengths;
    vector<int> month_lengths_;

    void LeapYearAdjust();
    void Adjust();

  public:
    Date();
    Date(const Date& date);
    Date(int yyyymmdd);
    Date(int yyyy, int mm, int dd = 1,
	 int hh = 0, int mn = 0, int sc = 0);

    Date& operator=(const Date&);
    void SetDate(int yyyymmdd);
    void SetDate(int yyyy, int mm, int dd = 1,
		 int hh = 0, int mn = 0, int sc = 0);

    bool LeapYear(int year) const;
    bool LeapYear() const;

    int GetDate() const;
    
    string GetDate(const string& format) const;
    template <class T>
    void GetDate(const string& format, T& date) const;

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinutes() const;
    int GetSeconds() const;

    void AddYears(int nb_yy);
    void AddMonths(int nb_mm);
    void AddDays(int nb_dd);
    void AddHours(int nb_hh);
    void AddMinutes(int nb_mn);
    void AddSeconds(int nb_sc);

    void SetYear(int yyyy);
    void SetMonth(int mm);
    void SetDay(int dd);
    void SetHour(int hh);
    void SetMinutes(int mn);
    void SetSeconds(int sc);

    int GetDayNumber() const;
    int GetNumberOfDays() const;
    int GetDaysFrom(Date date) const;
    double GetSecondsFrom(Date date) const;

    int GetNumberOfHours() const;
    int GetNumberOfMinutes() const;
    int GetNumberOfSeconds() const;

    int GetWeekDay() const;
  };

}  // namespace Talos.


#define TALOS_FILE_DATE_HXX
#endif
