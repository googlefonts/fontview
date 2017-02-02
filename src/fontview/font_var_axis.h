/*
 * Copyright 2017 Google Inc. All rights reserved.
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

#ifndef FONTVIEW_FONT_VAR_AXIS_
#define FONTVIEW_FONT_VAR_AXIS_

#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TYPES_H

namespace fontview {
typedef std::map<int, std::string> NameTable;

class FontVarAxis {
 public:
  static const FT_Tag weightTag, widthTag, slantTag;

  static std::vector<FontVarAxis*>* MakeAxes(
      FT_Face face, const NameTable& names);
  ~FontVarAxis();

  FT_Tag GetTag() const { return tag_; }
  const std::string& GetName() const { return name_; }
  double GetMinValue() const { return minValue_; }
  double GetMaxValue() const { return maxValue_; }
  double GetDefaultValue() const { return defaultValue_; }


 private:
  FontVarAxis(FT_Tag tag, const std::string& name,
              double defaultValue, double minValue, double maxValue);

  FT_Tag tag_;
  std::string name_;
  double minValue_, maxValue_, defaultValue_;
};

}  // namespace fontview

#endif // FONTVIEW_FONT_VAR_AXIS_
