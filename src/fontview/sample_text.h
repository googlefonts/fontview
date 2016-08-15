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

#include <ft2build.h>
#include FT_FREETYPE_H

#include <raqm.h>

#include <wx/wx.h>

namespace fontview {

class SampleText : public wxScrolledCanvas {
 public:
  SampleText(wxWindow* parent);
  virtual ~SampleText();
  void SetText(const std::string& text);
  void SetFontFace(FT_Face fontFace);
  void SetFontSize(double size);
  void Paint();
  wxDECLARE_EVENT_TABLE();

 protected:
  virtual wxSize DoGetBestSize() const;

 private:
  void OnPaint(wxPaintEvent& event);
  void Paint(wxDC& dc);

  std::string text_;
  FT_Face fontFace_;
  double fontSize_;
  raqm_t* raqm_;
};

}  // namespace fontview

#endif  // FONTVIEW_SAMPLE_TEXT_
