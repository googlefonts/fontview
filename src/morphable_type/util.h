#ifndef FONTVIEW_UTIL_H_
#define FONTVIEW_UTIL_H_

#include <ft2build.h>
#include FT_TYPES_H

namespace fontview {

inline double FTFixedToDouble(FT_Fixed value) {
  // The cast to FT_Int32 is needed because FreeType defines FT_Fixed as
  // 'signed long', which is 64 bits on 64-bit platforms, but without
  // sign-extending negative values returned by its APIs.
  // https://savannah.nongnu.org/bugs/index.php?48732
  return static_cast<FT_Int32>(value) / 65536.0;
}

inline double clamp(double value, double min, double max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

}  // namespace fontview

#endif  // FONTVIEW_UTIL_H_
