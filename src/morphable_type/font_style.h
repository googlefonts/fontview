#ifndef FONTVIEW_FONT_STYLE_
#define FONTVIEW_FONT_STYLE_

#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_GLYPH_H

namespace fontview {
typedef std::map<int, std::string> NameTable;

class FontStyle {
 public:
  static std::vector<FontStyle> GetStyles(
      FT_Face face, const NameTable& names);
  ~FontStyle();
  const std::string& GetName() const { return name_; }

 private:
  FontStyle(FT_Face face, const std::string& name,
            const std::map<std::string, double>& axisValues);

  FT_Face face_;
  const std::string name_;
  const std::map<std::string, double>& axisValues_;
};

}  // namespace fontview

#endif // FONTVIEW_FONT_STYLE_
