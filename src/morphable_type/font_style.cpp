#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H

#include "font_style.h"
#include "name_table.h"

namespace fontview {

std::vector<FontStyle*> FontStyle::GetStyles(FT_Face face,
                                             const NameTable& names) {
  std::vector<FontStyle*> result;

  FT_MM_Var* mmvar = NULL;
  if (FT_HAS_MULTIPLE_MASTERS(face)) {
    FT_Get_MM_Var(face, &mmvar);
  }

  bool hasNamedInstanceForDefault = false;
  if (mmvar) {
    for (FT_UInt i = 0; i < mmvar->num_namedstyles; ++i) {
      const FT_Var_Named_Style& namedStyle = mmvar->namedstyle[i];
      const std::string& instanceName = GetFontName(names, namedStyle.strid);
      if (!instanceName.empty()) {
	FontStyle::Variation variation;
	bool isDefault = true;
        for (FT_UInt axisIndex = 0; axisIndex < mmvar->num_axis;
             ++axisIndex) {
	  const FT_Var_Axis& axis = mmvar->axis[axisIndex];
	  variation[axis.tag] = namedStyle.coords[axisIndex] / 65536.0;
	  if (namedStyle.coords[axisIndex] != axis.def) {
	    isDefault = false;
	  }
	}
	if (isDefault) {
	  hasNamedInstanceForDefault = true;
	}
	result.push_back(new FontStyle(face, instanceName, variation));
      }
    }
  }

  if (!hasNamedInstanceForDefault) {
    const std::string& styleName = GetFontStyleName(names);
    if (!styleName.empty()) {
      FontStyle::Variation variation;
      if (mmvar) {
        for (FT_UInt axisIndex = 0; axisIndex < mmvar->num_axis;
             ++axisIndex) {
	  const FT_Var_Axis& axis = mmvar->axis[axisIndex];
	  variation[axis.tag] = axis.def / 65536.0;
	}
      }
      result.push_back(new FontStyle(face, styleName, variation));
    }
  }

  return result;
}

FontStyle::FontStyle(FT_Face face, const std::string& name,
                     const Variation& variation)
  : face_(face), name_(name), variation_(variation) {  
}

FontStyle::~FontStyle() {
}

}  // namespace fontview
