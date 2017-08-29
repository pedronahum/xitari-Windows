%module(directors="1") XitariLib
//%feature("autodoc", "1");


%include <stl.i>
%include <std_wstring.i>
%include <std_vector.i>
%include <std_map.i>
%include <std_pair.i>
%include <std_shared_ptr.i>
%include <windows.i>
%include <attribute.i>
#include <exception.i>

//typedef std::size_t Size;

#ifdef SWIGCSHARP
%include <arrays_csharp.i>
#endif

#ifndef _MSC_VER
IGNORE_FUNCTION _wcsdup;
#endif

//use when the wrapped method returns an idiomatic type
//for non-idiomatic types, such as the default collection wrappers use RENAME_AND_MAKE_PRIVATE below
//and then write custom method in the language specific file
#if defined(SWIGCSHARP)
#define MAKE_PRIVATE(x) %csmethodmodifiers x "private"
#elif defined(SWIGJAVA)
#define MAKE_PRIVATE(x) %javamethodmodifiers x "private"
#else
#error "MAKE_PRIVATE is not defined."
#endif

%define RENAME_AND_MAKE_PRIVATE(namespace, method)
  MAKE_PRIVATE(namespace##::##method);
  %rename (_##method) namespace##::##method
%enddef

#if defined(SWIGCSHARP)
// For C Sharp, property needs to be added as C Sharp code. Here we just rename the corresponding C++ method and make it as private.
#define MAKE_GETTER(namespace, method) RENAME_AND_MAKE_PRIVATE(namespace, method)
#elif defined(SWIGJAVA)
// For Java, we add "get" prefix to the method name.
%define MAKE_GETTER(namespace, method)
    %rename (get ## method) namespace##::##method
%enddef
#else
#error "MAKE_GETTER is not defined."
#endif

// temaplate definitions
#ifdef SWIGCSHARP
// int/bool/double/float are already enabled with SWIG_STD_VECTOR_ENHANCED in std_vector.i
SWIG_STD_VECTOR_ENHANCED(size_t)
#endif //SWIGCSHARP

%template(IntVector) std::vector<int>;
%template(SizeTVector) std::vector<size_t>;
%template(DoubleVector) std::vector<double>;
%template(FloatVector) std::vector<float>;
%template(BoolVector) std::vector<bool>;




// ignore items not needed.
#define IGNORE_FUNCTION %rename("$ignore", %$isfunction, fullname=1)
#define IGNORE_CLASS %rename("$ignore", %$isclass, fullname=1)
#define IGNORE_NAMESPACE %rename("$ignore", %$isnamespace, fullname=1)
#define IGNORE_VARIABLE %rename("$ignore", %$isvariable, fullname=1)
// It seems that SWIG does not understand %$isstruct.
#define IGNORE_STRUCT %rename("$ignore", fullname=1)
#define IGNORE_ENUM_CLASS %rename("$ignore", fullname=1)

#ifndef _MSC_VER
IGNORE_FUNCTION _wcsdup;
#endif

%rename(AreEqual) operator==;
%rename(AreNotEqual) operator!=;
%ignore operator[];