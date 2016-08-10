#ifndef FONTVIEW_FONT_STYLE_
#define FONTVIEW_FONT_STYLE_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_TYPES_H

namespace fontview {
typedef std::map<int, std::string> NameTable;
class FontVarAxis;

class FontStyle {
 public:
  typedef std::map<FT_Tag, double> Variation;
  static std::vector<FontStyle*> GetStyles(
      FT_Face face, const NameTable& names);
  ~FontStyle();

  const std::string& GetFamilyName() const { return family_; }
  const std::string& GetStyleName() const { return name_; }
  double GetWeight() const { return weight_; }
  double GetWidth() const { return width_; }
  double GetSlant() const { return slant_; }

  const std::vector<FontVarAxis*>& GetAxes() const { return *axes_; }
  double GetDistance(const Variation& var) const;

 private:
  FontStyle(FT_Face face, const std::string& family, const std::string& name,
            std::vector<FontVarAxis*>* axes,  // takes ownership
            const Variation& variation);

  FT_Face face_;
  const std::string family_;
  const std::string name_;
  const double weight_, width_, slant_;
  std::unique_ptr<std::vector<FontVarAxis*>> axes_;  // also owning elements
  const Variation variation_;
};

}  // namespace fontview

#endif // FONTVIEW_FONT_STYLE_
