#pragma once

#ifndef __CDT_PARSER__

// defines for GCC

#define _PRETTY_FUNCTION_ __PRETTY_FUNCTION__

#define CONSTEXPR_DATA constexpr
#define CONSTEXPR_FUNC constexpr
#define NOEXCEPT noexcept

#define IGNORE_WARNINGS_BEGIN \
  _Pragma("GCC diagnostic push") \
  _Pragma("GCC diagnostic ignored \"-fpermissive\"") \
  _Pragma("GCC diagnostic ignored \"-Wall\"") \
  _Pragma("GCC diagnostic ignored \"-Wattributes\"") \
  _Pragma("GCC diagnostic ignored \"-Wconversion\"") \
  _Pragma("GCC diagnostic ignored \"-Wctor-dtor-privacy\"") \
  _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
  _Pragma("GCC diagnostic ignored \"-Wdouble-promotion\"") \
  _Pragma("GCC diagnostic ignored \"-Weffc++\"") \
  _Pragma("GCC diagnostic ignored \"-Wextra\"") \
  _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"") \
  _Pragma("GCC diagnostic ignored \"-Wfloat-conversion\"") \
  _Pragma("GCC diagnostic ignored \"-Wignored-qualifiers\"") \
  _Pragma("GCC diagnostic ignored \"-Winline\"") \
  _Pragma("GCC diagnostic ignored \"-Winvalid-pch\"") \
  _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"") \
  _Pragma("GCC diagnostic ignored \"-Wnarrowing\"") \
  _Pragma("GCC diagnostic ignored \"-Wold-style-cast\"") \
  _Pragma("GCC diagnostic ignored \"-Woverloaded-virtual\"") \
  _Pragma("GCC diagnostic ignored \"-Wpadded\"") \
  _Pragma("GCC diagnostic ignored \"-Wpedantic\"") \
  _Pragma("GCC diagnostic ignored \"-Wredundant-decls\"") \
  _Pragma("GCC diagnostic ignored \"-Wreorder\"") \
  _Pragma("GCC diagnostic ignored \"-Wshadow\"") \
  _Pragma("GCC diagnostic ignored \"-Wstrict-aliasing\"") \
  _Pragma("GCC diagnostic ignored \"-Wstrict-overflow\"") \
  _Pragma("GCC diagnostic ignored \"-Wswitch\"") \
  _Pragma("GCC diagnostic ignored \"-Wunused-but-set-variable\"") \
  _Pragma("GCC diagnostic ignored \"-Wunused-local-typedefs\"") \
  _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"") \
  _Pragma("GCC diagnostic ignored \"-Wunused-variable\"") \
  _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"") \
  _Pragma("GCC diagnostic ignored \"-Wzero-as-null-pointer-constant\"")

#define IGNORE_WARNINGS_END _Pragma("GCC diagnostic pop")

#else
// defines for CDT parser

#define __cplusplus 201103L
#define __GXX_EXPERIMENTAL_CXX0X__
#ifdef _MSC_VER
#undef _MSC_VER
#define _MSC_VER 1700
#endif
#define _PRETTY_FUNCTION_ __PRETTY_FUNCTION__
#define CONSTEXPR_DATA constexpr
#define CONSTEXPR_FUNC constexpr
#define IGNORE_WARNINGS_BEGIN
#define IGNORE_WARNINGS_END
#define __cplusplus 201103L
#define __GXX_EXPERIMENTAL_CXX0X__
#define NOEXCEPT noexcept

#endif
