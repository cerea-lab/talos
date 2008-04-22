%module talos
%{
#include "String.hxx"
#include "Date.hxx"
#include "Files.hxx"
  %}

%include "std_string.i"
%include "std_vector.i"
namespace std
{
  %template(VectorString) vector<string>;
  %template(VectorInt) vector<int>;
  %template(VectorDouble) vector<double>;
}

using namespace std;

%include "String.hxx"
%include "Date.hxx"
%include "Files.hxx"
