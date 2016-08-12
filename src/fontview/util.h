/*
 * Copyright 2016 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

inline FT_Fixed FTDoubleToFixed(double value) {
  return static_cast<FT_Fixed>(value * 65536);
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
