#ifndef FONTVIEW_NAME_TABLE_
#define FONTVIEW_NAME_TABLE_

#include <map>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace fontview {
typedef std::map<int, std::string> NameTable;

NameTable* BuildNameTable(FT_Face face);
const std::string& GetFontName(const NameTable& names, int id);
const std::string& GetFontFamilyName(const NameTable& names);
}  // namespace fontview

#endif // FONTVIEW_NAME_TABLE
