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
#include FT_BITMAP_H
#include FT_FREETYPE_H

#include <raqm.h>
#include <wx/wx.h>

#include "fontview/sample_text.h"
#include "fontview/util.h"

namespace fontview {

SampleText::SampleText(wxWindow* parent)
  : wxScrolledCanvas(parent, wxID_ANY),
    fontFace_(NULL), fontSize_(12.0),
    raqm_(raqm_create()) {
}

SampleText::~SampleText() {
  raqm_destroy(raqm_);
}

void SampleText::SetText(const std::string& text) {
  text_ = text;
  raqm_set_text_utf8(raqm_, text_.c_str(), text_.size());
  raqm_set_par_direction(raqm_, RAQM_DIRECTION_DEFAULT);
}

void SampleText::SetFontFace(FT_Face fontFace) {
  fontFace_ = fontFace;
}

void SampleText::SetFontSize(double size) {
  fontSize_ = clamp(size, 1, 1000);
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

static bool GetGlyphImage(FT_Face face, FT_UInt glyph, wxImage* image) {
  if (!face || !image ||
      FT_Load_Glyph(face, glyph, FT_LOAD_RENDER|FT_LOAD_COLOR)) {
    return false;
  }

  if (!face->glyph || face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
    return false;
  }

  const size_t width = face->glyph->bitmap.width;
  const size_t height = face->glyph->bitmap.rows;
  if (width == 0 || height == 0) {
    return false;
  }

  FT_Bitmap bitmap;
  FT_Bitmap_Init(&bitmap);
  FT_Bitmap_Convert(face->glyph->library, &face->glyph->bitmap, &bitmap, 1);
  const size_t numBytes = width * height * 4;
  unsigned char* data = static_cast<unsigned char*>(malloc(numBytes));
  unsigned char* alpha = data + width * height * 3;
  bzero(data, width * height * 3);
  memcpy(alpha, bitmap.buffer, width * height);
  FT_Bitmap_Done(face->glyph->library, &bitmap);

  image->SetData(data, width, height, false);
  image->SetAlpha(alpha, true);

  return true;
}

void SampleText::Paint(wxDC& dc) {
  if (!fontFace_ || !raqm_ || !dc.IsOk()) {
    return;
  }

  dc.Clear();
  const wxSize dpi = dc.GetPPI();  // dots/pixels per inch
  const FT_F26Dot6 size = static_cast<FT_F26Dot6>(fontSize_ * 64 + 0.5);
  if (FT_Set_Char_Size(fontFace_, size, size, dpi.x, dpi.y)) {
    return;
  }

  if (!raqm_set_freetype_face(raqm_, fontFace_) || !raqm_layout(raqm_)) {
    return;
  }

  const double ascender = fontSize_ *
      (static_cast<double>(fontFace_->ascender) /
       static_cast<double>(fontFace_->units_per_EM));
  size_t numGlyphs = 0;
  raqm_glyph_t* glyphs = raqm_get_glyphs(raqm_, &numGlyphs);
  double x = 2, y = 2 + ascender;
  wxImage image;
  for (size_t i = 0; i < numGlyphs; ++i) {
    if (GetGlyphImage(glyphs[i].ftface, glyphs[i].index, &image)) {
      wxBitmap bitmap(image, dc.GetDepth());
      wxCoord glyphX = x + glyphs[i].x_offset / 64.0 + 0.5;
      wxCoord glyphY = y + glyphs[i].y_offset / 64.0 + 0.5;
      dc.DrawBitmap(bitmap,
                    glyphX + fontFace_->glyph->bitmap_left,
                    glyphY - fontFace_->glyph->bitmap_top,
                    false);  // useMask
    }
    x += glyphs[i].x_advance / 64.0;
    y += glyphs[i].y_advance / 64.0;
  }
}

wxBEGIN_EVENT_TABLE(SampleText, wxScrolledCanvas)
EVT_PAINT(SampleText::OnPaint)
wxEND_EVENT_TABLE()

}  // namespace fontview
