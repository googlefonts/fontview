#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H
#include FT_TRUETYPE_TABLES_H
#include FT_TYPES_H

#include "font_style.h"
#include "name_table.h"

namespace fontview {

std::vector<FontStyle*> FontStyle::GetStyles(FT_Face face,
                                             const NameTable& names) {
  std::vector<FontStyle*> result;
  const std::string& familyName = GetFontFamilyName(names);
  if (familyName.empty()) {
    return result;
  }

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
	result.push_back(
          new FontStyle(face, familyName, instanceName, variation));
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
      result.push_back(new FontStyle(face, familyName, styleName, variation));
    }
  }

  return result;
}

static double clamp(double value, double min, double max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

static double GetWeight(FT_Face face, const FontStyle::Variation& variation) {
  const FT_Tag weightTag = FT_MAKE_TAG('w', 'g', 'h', 't');
  FontStyle::Variation::const_iterator iter = variation.find(weightTag);
  if (iter != variation.end()) {
    return iter->second;
  }

  const TT_OS2* os2 =
      static_cast<TT_OS2*>(FT_Get_Sfnt_Table(face, ft_sfnt_os2));
  if (os2) {
    // Work around values that can be found in OS/2 tables of some old fonts.
    // Behaves like FontConfig.
    switch (os2->usWeightClass) {
    case 0: return 100;
    case 1: return 100;
    case 2: return 160;
    case 3: return 240;
    case 4: return 320;
    case 5: return 400;
    case 6: return 550;
    case 7: return 700;
    case 8: return 800;
    case 9: return 900;
    default: return clamp(os2->usWeightClass, 10, 1000);
    }
  }

  return 400;
}


static double GetWidth(FT_Face face, const FontStyle::Variation& variation) {
  const FT_Tag widthTag = FT_MAKE_TAG('w', 'd', 't', 'h');
  FontStyle::Variation::const_iterator iter = variation.find(widthTag);
  if (iter != variation.end()) {
    return iter->second;
  }

  const TT_OS2* os2 =
      static_cast<TT_OS2*>(FT_Get_Sfnt_Table(face, ft_sfnt_os2));
  if (os2) {
    // https://www.microsoft.com/typography/otspec/os2.htm#wdc
    switch (os2->usWidthClass) {
    case 1: return 50;
    case 2: return 62.5;
    case 3: return 75;
    case 4: return 87.5;
    case 5: return 100;
    case 6: return 112.5;
    case 7: return 125;
    case 8: return 150;
    case 9: return 200;
    default: break;
    }
  }

  return 100;
}

static double GetSlant(FT_Face face, const FontStyle::Variation& variation) {
  // TODO: It is undefined if negative values are leaning to the left or right.
  // Clarify with the OpenType working group, so the spec becomes clearer.
  const FT_Tag slantTag = FT_MAKE_TAG('s', 'l', 'n', 't');
  FontStyle::Variation::const_iterator iter = variation.find(slantTag);
  if (iter != variation.end()) {
    return iter->second;  // TODO: Unclear if we should negate this value.
  }

  TT_Postscript* post =
    static_cast<TT_Postscript*>(FT_Get_Sfnt_Table(face, ft_sfnt_post));
  if (post) {
    return -static_cast<int32_t>(post->italicAngle) / 65536.0;
  }

  return 0;
}

FontStyle::FontStyle(FT_Face face,
                     const std::string& family,
                     const std::string& styleName,
                     const Variation& variation)
  : face_(face), family_(family), name_(styleName),
    weight_(::fontview::GetWeight(face, variation)),
    width_(::fontview::GetWidth(face, variation)),
    slant_(::fontview::GetSlant(face, variation)),
    variation_(variation) {
}

FontStyle::~FontStyle() {
}

}  // namespace fontview
