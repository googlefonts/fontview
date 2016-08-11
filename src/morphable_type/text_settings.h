#ifndef FONTVIEW_TEXT_SETTINGS_
#define FONTVIEW_TEXT_SETTINGS_

#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace fontview {

class FontStyle;
typedef std::map<int, std::string> NameTable;

// TODO: Make this a private static function after refactoring,
// it should not be part of the API.
//std::vector<FT_Face>* LoadFaces(const std::string& path);

// Models text-related settings such as font family, font style,
// variation axis values, font size, font features, or text language.
// In the model/view/controller paradigm, this is a model class.
class TextSettings {
 public:
  TextSettings();
  ~TextSettings();

  // Listeners get notified after the model has changed.
  typedef std::function<void ()> Listener;
  void AddListener(Listener* l);
  void RemoveListener(Listener* l);

  // Returns true upon success, false if the file could not be parsed.
  bool SetFontContainer(const std::string& path);

  const std::string& GetFontContainer() const { return fontContainerPath_; }
  const std::set<std::string>& GetFamilies() const { return families_; }
  const std::vector<FontStyle*>& GetStyles() const { return styles_; }
  FontStyle* FindBestStyle(const std::string& family,
			   const FontStyle::Variation& variation) const;

  const std::string& GetFamily() const { return family_; }
  void SetFamily(const std::string& family);

  FontStyle* GetStyle() const { return style_; }
  void SetStyle(FontStyle* style);

  const FontStyle::Variation& GetVariation() const { return variation_; }
  void SetVariation(const FontStyle::Variation& v);

 private:
  void Clear();
  bool SetStyleWithoutNotification(FontStyle* style);
  void NotifyListeners();

  std::vector<Listener*> listeners_;
  std::string fontContainerPath_;
  std::vector<FT_Face> faces_;
  std::vector<NameTable*> faceNameTables_;
  std::vector<FontStyle*> styles_;
  std::set<std::string> families_;
  std::string family_;
  FontStyle* style_;
  FontStyle::Variation variation_;
};

}  // namespace fontview

#endif // FONTVIEW_TEXT_SETTINGS_
