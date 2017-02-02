/*
 * Copyright 2017 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
  TextSettings(const std::string& defaultSampleText);
  ~TextSettings();

  // Listeners get notified after the model has changed.
  typedef std::function<void ()> Listener;
  void AddListener(Listener* l);
  void RemoveListener(Listener* l);

  // Returns true upon success, false if the file could not be parsed.
  bool SetFontContainer(const std::string& path);
  const std::string& GetFontContainer() const { return fontContainerPath_; }

  // Returns a FreeType face configured for the current settings.
  FT_Face GetFace();

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

  double GetFontSize() const { return fontSize_; }
  void SetFontSize(double size);

  const std::string& GetTextLanguage() const { return textLanguage_; }
  void SetTextLanguage(const std::string& language);
  const std::set<std::string>& GetSupportedTextLanguages() const;

 private:
  static const double defaultFontSize;

  void Clear();
  bool SetStyleWithoutNotification(FontStyle* style);
  void NotifyListeners();

  std::string defaultSampleText_;
  std::vector<Listener*> listeners_;
  std::string fontContainerPath_;
  std::vector<FT_Face> faces_;
  std::vector<NameTable*> faceNameTables_;
  std::vector<FontStyle*> styles_;
  std::set<std::string> families_;
  std::string family_;
  std::string textLanguage_;
  std::set<std::string> supportedTextLanguages_;
  FontStyle* style_;
  FontStyle::Variation variation_;
  double fontSize_;
};

}  // namespace fontview

#endif // FONTVIEW_TEXT_SETTINGS_
