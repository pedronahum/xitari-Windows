/* File : xitari_cs.i */
%include "XitariManagedCommon.i"
%include <std_shared_ptr.i>
%{
#include "XitariALE.h"
%}
%include "XitariALE.h"

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

#ifdef SWIGCSHARP
%pragma(csharp) moduleclassmodifiers="public partial class"
%typemap(csclassmodifiers) XitariALE "public partial class"
#endif
%shared_ptr(XitariALE);

