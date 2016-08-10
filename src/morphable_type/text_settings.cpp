#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "font_style.h"
#include "font_var_axis.h"
#include "name_table.h"
#include "text_settings.h"

namespace fontview {

FT_Library GetFreeTypeLibrary();

static std::vector<FT_Face>* LoadFaces(const std::string& path) {
  FT_Library freeTypeLib = GetFreeTypeLibrary();
  std::vector<FT_Face>* faces = new std::vector<FT_Face>();
  FT_Long numFaces = 0;
  FT_Face face = NULL;
  FT_Error error = FT_New_Face(freeTypeLib, path.c_str(), -1, &face);
  if (face) {
    if (!error) {
      numFaces = face->num_faces;
    }
    FT_Done_Face(face);
  }
  for (FT_Long faceIndex = 0; faceIndex < numFaces; ++faceIndex) {
    face = NULL;
    if (FT_New_Face(freeTypeLib, path.c_str(), faceIndex, &face)) {
      continue;
    }
    faces->push_back(face);
  }
  return faces;
}


TextSettings::TextSettings() {
  Clear();
}

TextSettings::~TextSettings() {
  Clear();
}

void TextSettings::AddListener(Listener* l) {
  listeners_.push_back(l);
}

void TextSettings::RemoveListener(Listener* l) {
  listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), l));
}

bool TextSettings::SetFontContainer(const std::string& path) {
  std::unique_ptr<std::vector<FT_Face>> faces(LoadFaces(path));
  if (!faces.get() || faces->empty()) {
    return false;
  }
  Clear();
  for (FT_Face face : *faces) {
    faces_.push_back(face);
    faceNameTables_.push_back(BuildNameTable(face));
  }

  for (NameTable* t : faceNameTables_) {
    const std::string& familyName = GetFontFamilyName(*t);
    families_.insert(familyName);
    if (family_.empty()) {
      family_ = familyName;
    }
  }

  for (size_t i = 0; i < faces_.size(); ++i) {
    for (FontStyle* s : FontStyle::GetStyles(faces_[i], *faceNameTables_[i])) {
      styles_.push_back(s);
    }
  }

  variation_[FontVarAxis::weightTag] = 400;
  variation_[FontVarAxis::widthTag] = 100;
  variation_[FontVarAxis::slantTag] = 0;
  style_ = FindBestStyle(family_, variation_);

  NotifyListeners();
  return true;
}

FontStyle* TextSettings::FindBestStyle(
    const std::string& family,
    const FontStyle::Variation& variation) const {
  FontStyle* bestStyle = NULL;
  double bestDistance = std::numeric_limits<double>::infinity();
  for (FontStyle* style : styles_) {
    if (style->GetFamilyName() != family) {
      continue;
    }
    double distance = style->GetDistance(variation);
    if (distance < bestDistance) {
      bestStyle = style;
      bestDistance = distance;
    }
  }
  return bestStyle;
}

void TextSettings::SetFamily(const std::string& family) {
  if (family == family_) {
    return;
  }

  family_ = family;
  style_ = FindBestStyle(family_, variation_);
  NotifyListeners();
}

void TextSettings::SetStyle(FontStyle* style) {
  if (style == style_) {
    return;
  }

  // Reject FontStyles that are not owned by us.
  if (style != NULL &&
      std::find(styles_.begin(), styles_.end(), style) == styles_.end()) {
    return;
  }

  style_ = style;
  NotifyListeners();
}

void TextSettings::Clear() {
  variation_.clear();
  style_ = NULL;
  family_.clear();
  families_.clear();

  for (FontStyle* style : styles_) {
    delete style;
  }
  styles_.clear();

  for (NameTable* table : faceNameTables_) {
    delete table;
  }
  faceNameTables_.clear();

  for (FT_Face face : faces_) {
    FT_Done_Face(face);
  }
  faces_.clear();

  fontContainerPath_.clear();
}

void TextSettings::NotifyListeners() {
  for (Listener* l : listeners_) {
    (*l)();
  }
}

}  // namespace fontview
