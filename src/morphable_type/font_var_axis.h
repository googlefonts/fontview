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
