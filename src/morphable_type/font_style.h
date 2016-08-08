#ifndef FONTVIEW_FONT_STYLE_
#define FONTVIEW_FONT_STYLE_

#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace fontview {
typedef std::map<int, std::string> NameTable;

class FontStyle {
 public:
  typedef std::map<FT_ULong, double> Variation;
  static std::vector<FontStyle*> GetStyles(
      FT_Face face, const NameTable& names);
  ~FontStyle();
  const std::string& GetName() const { return name_; }

 private:
  FontStyle(FT_Face face, const std::string& name, const Variation& variation);

  FT_Face face_;
  const std::string name_;
  const Variation variation_;
};

}  // namespace fontview

#endif // FONTVIEW_FONT_STYLE_
