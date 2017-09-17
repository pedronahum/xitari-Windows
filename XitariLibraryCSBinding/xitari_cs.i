/* File : xitari_cs.i */
%include "XitariManagedCommon.i"
%include <std_shared_ptr.i>
%{
#include "XitariALE.h"
%}
%include "XitariALE.h"


#ifdef SWIGCSHARP
%pragma(csharp) moduleclassmodifiers="public partial class"
%typemap(csclassmodifiers) XitariALE "public partial class"
#endif
%shared_ptr(XitariALE);