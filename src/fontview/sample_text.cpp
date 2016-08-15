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

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <raqm.h>
#include <wx/wx.h>

#include "fontview/sample_text.h"

namespace fontview {

SampleText::SampleText(wxWindow* parent)
  : wxScrolledCanvas(parent, wxID_ANY),
    fontFace_(NULL),
    raqm_(raqm_create()) {
}

SampleText::~SampleText() {
  raqm_destroy(raqm_);
}

void SampleText::SetText(const std::string& text) {
  text_ = text;
  raqm_set_text_utf8(raqm_, text_.c_str(), text_.size());
  raqm_set_par_direction(raqm_, RAQM_DIRECTION_DEFAULT);
  LayoutContent();
}

void SampleText::SetFontFace(FT_Face fontFace) {
  fontFace_ = fontFace;
  raqm_set_freetype_face(raqm_, fontFace_);
  LayoutContent();
}

void SampleText::LayoutContent() {
  raqm_layout(raqm_);
}

wxSize SampleText::DoGetBestSize() const {
  // TODO: Measure the text.
  return wxSize(600, 300);
}

void SampleText::Paint() {
  wxWindowDC dc(this);
  Paint(dc);
}

void SampleText::OnPaint(wxPaintEvent& event) {
  wxPaintDC dc(this);
  Paint(dc);
}

void SampleText::Paint(wxDC& dc) {
  if (!fontFace_ || !raqm_ || !dc.IsOk()) {
    return;
  }
  dc.Clear();
  //wxSize dpi = dc.GetPPI();
  //printf("SampleText::Render(), %d %d\n", dpi.x, dpi.y);

  size_t numGlyphs = 0;
  raqm_glyph_t* glyphs = raqm_get_glyphs(raqm_, &numGlyphs);
  double x = 2, y = 2;
  for (size_t i = 0; i < numGlyphs; ++i) {
    double glyphX = x + glyphs[i].x_offset / 64.0;
    double glyphY = y + glyphs[i].y_offset / 64.0;
    dc.DrawPoint(glyphX, glyphY);
    //printf("%lu %.1f %.1f\n", i, glyphX, glyphY);
    x += glyphs[i].x_advance / 64.0;
    y += glyphs[i].y_advance / 64.0;
  }
}

wxBEGIN_EVENT_TABLE(SampleText, wxScrolledCanvas)
EVT_PAINT(SampleText::OnPaint)
wxEND_EVENT_TABLE()

}  // namespace fontview
