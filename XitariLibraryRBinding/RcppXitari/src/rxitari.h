
#ifndef rxitari_src_h
#define rxitari_src_h


// Rcpp Attributes requires a file with package name in inst/include,
// in our case inst/include/RQuantLib.h -- but R does not want us to have
// another header file with the same name, differing only by case
//
// So we place the existing 'rquantlib.h' in src/ instead so that the
// issue of equal names (for everything but the case) no longer
// matters.  This provides us with a backwards compatible
// 'rquantlib.h' file, and its definitons are now in a file
// inst/include/rquantlib_internal.h which we source here.

#include "c:/repos/xitari-vs2017/XitariLibraryCSBinding/XitariALE.h"

#endif