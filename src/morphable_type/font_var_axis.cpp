#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H
#include FT_TYPES_H

#include "font_var_axis.h"
#include "name_table.h"
#include "util.h"

namespace fontview {

const FT_Tag FontVarAxis::weightTag = FT_MAKE_TAG('w', 'g', 'h', 't');
const FT_Tag FontVarAxis::widthTag = FT_MAKE_TAG('w', 'd', 't', 'h');
const FT_Tag FontVarAxis::slantTag = FT_MAKE_TAG('s', 'l', 'n', 't');

std::vector<FontVarAxis*>* FontVarAxis::MakeAxes(FT_Face face,
                                                 const NameTable& names) {
  std::unique_ptr<std::vector<FontVarAxis*>> result(
      new std::vector<FontVarAxis*>());

  FT_MM_Var* mmvar = NULL;
  FT_Multi_Master mmtype1;
  bool isMMType1 = false;
  if (FT_HAS_MULTIPLE_MASTERS(face)) {
    if (FT_Get_MM_Var(face, &mmvar) != 0) {
      mmvar = NULL;
    }
    if (FT_Get_Multi_Master(face, &mmtype1) == 0) {
      isMMType1 = true;
    }
  }

  if (!mmvar) {
    return result.release();
  }

  result->reserve(mmvar->num_axis);
  if (isMMType1) {
    FT_UInt numAxes = mmtype1.num_axis;
    if (numAxes > 4) numAxes = 4;
    for (FT_UInt axisIndex = 0; axisIndex < numAxes; ++axisIndex) {
      const FT_MM_Axis& mmAxis = mmtype1.axis[axisIndex];
      FT_Tag axisTag = FT_MAKE_TAG('V', 'A', 'R', '0' + axisIndex);
      std::string name = std::string(mmAxis.name ? mmAxis.name : "");
      if (name.empty()) {
        continue;
      }
      const int32_t minValue = static_cast<int32_t>(mmAxis.minimum);
      const int32_t maxValue = static_cast<int32_t>(mmAxis.maximum);
      const int32_t defaultValue = minValue + (maxValue - minValue) / 2;
      FontVarAxis* axis = new FontVarAxis(axisTag, name, defaultValue,
                                          minValue, maxValue);
      result->push_back(axis);
    }
  } else {
    for (FT_UInt axisIndex = 0; axisIndex < mmvar->num_axis;
         ++axisIndex) {
      const FT_Var_Axis& ftAxis = mmvar->axis[axisIndex];
      std::string name = GetFontName(names, ftAxis.strid);
      if (name.empty() && ftAxis.name != NULL) {
        name.assign(ftAxis.name);
      }
      if (name.empty()) {
        continue;
      }
      FontVarAxis* axis = new FontVarAxis(ftAxis.tag, name,
                                          FTFixedToDouble(ftAxis.def),
                                          FTFixedToDouble(ftAxis.minimum),
                                          FTFixedToDouble(ftAxis.maximum));
      result->push_back(axis);
    }
  }

  return result.release();
}

FontVarAxis::FontVarAxis(
    FT_Tag tag, const std::string& name,
    double defaultValue, double minValue, double maxValue)
  : tag_(tag), name_(name),
    defaultValue_(defaultValue), minValue_(minValue), maxValue_(maxValue) {
}

FontVarAxis::~FontVarAxis() {
}

}  // namespace fontview
