%module talos
%{
#include "String.hxx"
#include "Date.hxx"
#include "Files.hxx"
%}

%include "std_string.i"
%include "std_vector.i"
namespace std {
   %template(VectorString) vector<string>;
   %template(VectorInt) vector<int>;
   %template(VectorDouble) vector<double>;
}

%apply const string& {std::string*};

using namespace std;

// Include the header file with above prototypes
%include "String.hxx"
%include "Date.hxx"
%include "Files.hxx"
