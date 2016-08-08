#include <map>
#include <string>
#include <vector>

#include "font_style.h"
#include "name_table.h"

namespace fontview {

std::vector<FontStyle> FontStyle::GetStyles(FT_Face face,
                                            const NameTable& names) {
  std::vector<FontStyle> result;
  return result;
}

FontStyle::FontStyle(FT_Face face, const std::string& name,
                     const std::map<std::string, double>& axisValues)
  : face_(face), name_(name), axisValues_(axisValues) {  
}

FontStyle::~FontStyle() {
}

}  // namespace fontview
