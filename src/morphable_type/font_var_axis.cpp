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
  if (FT_HAS_MULTIPLE_MASTERS(face)) {
    FT_Get_MM_Var(face, &mmvar);
  }
  if (!mmvar) {
    return result.release();
  }

  result->reserve(mmvar->num_axis);
  for (FT_UInt axisIndex = 0; axisIndex < mmvar->num_axis;
       ++axisIndex) {
    const FT_Var_Axis& ftAxis = mmvar->axis[axisIndex];
    const std::string& name = GetFontName(names, ftAxis.strid);
    FontVarAxis* axis = new FontVarAxis(ftAxis.tag, name,
                                        FTFixedToDouble(ftAxis.def),
                                        FTFixedToDouble(ftAxis.minimum),
                                        FTFixedToDouble(ftAxis.maximum));
    result->push_back(axis);
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
