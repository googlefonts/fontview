/*
 * Copyright 2016 Google Inc. All rights reserved.
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

#ifndef FONTVIEW_SAMPLE_TEXT_
#define FONTVIEW_SAMPLE_TEXT_

#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <wx/wx.h>

namespace fontview {

class SampleText : public wxScrolledCanvas {
 public:
  SampleText(wxWindow* parent);
  virtual ~SampleText();
  const std::string& GetText() const { return text_utf8_; }

  // Is the sample text a standard "quick brown fox" pangram (or equivalent
  // from the font's name table)? If this function returns true, the
  // text is something special so it should not be replaced when switching
  // fonts.
  bool HasCustomText() const { return hasCustomText_; }

  void SetText(const std::string& text, bool isCustom);
  void SetTextLanguage(const std::string& language);  // BCP47 code
  void SetFontFace(FT_Face fontFace);
  void SetFontSize(double size);
  void Paint();
  wxDECLARE_EVENT_TABLE();

 protected:
  virtual wxSize DoGetBestSize() const;

 private:
  void OnPaint(wxPaintEvent& event);
  void Paint(wxDC& dc);
  void DrawGlyph(wxDC& dc, FT_Face face, FT_UInt glyph, double x, double y);

  bool hasCustomText_;
  std::string text_utf8_;
  std::vector<uint32_t> text_;
  FT_Face fontFace_;
  double fontSize_;
  std::string textLanguage_;
};

}  // namespace fontview

#endif  // FONTVIEW_SAMPLE_TEXT_
