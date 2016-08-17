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
#include <wx/rawbmp.h>
#include <wx/wx.h>

#include "fontview/sample_text.h"
#include "fontview/util.h"

namespace fontview {

SampleText::SampleText(wxWindow* parent)
  : wxScrolledCanvas(parent, wxID_ANY),
    fontFace_(NULL), fontSize_(12.0) {
}

SampleText::~SampleText() {
}

void SampleText::SetText(const std::string& text) {
  text_ = text;
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

static void FillBlack(wxBitmap* bitmap) {
  wxNativePixelData data(*bitmap);
  if (!data) {
    return;
  }

  wxNativePixelData::Iterator pixel(data);
  const int maxX = data.GetWidth(), maxY = data.GetHeight();
  for (int y = 0; y < maxY; ++y) {
    pixel.MoveTo(data, 0, y);
    for (int x = 0; x < maxX; ++x) {
      pixel.Red() = pixel.Green() = pixel.Blue() = 0;
      ++pixel;
    }
  }
}

static void CopyAlpha(const FT_Bitmap& source, wxBitmap* target) {
  wxAlphaPixelData data(*target);
  if (!data) {
    return;
  }

  wxAlphaPixelData::Iterator pixel(data);
  const int maxX = data.GetWidth(), maxY = data.GetHeight();
  for (int y = 0; y < maxY; ++y) {
    pixel.MoveTo(data, 0, y);
    if (y < source.rows) {
      const uint8_t* ftAlpha = source.buffer + y * source.pitch;
      for (int x = 0; x < maxX; ++x) {
	pixel.Alpha() = x < source.width ? ftAlpha[x] : 0;
	++pixel;
      }
    } else {
      pixel.Alpha() = 0;
      ++pixel;
    }
  }
}

void SampleText::DrawGlyph(wxDC& dc, FT_Face face, FT_UInt glyph,
			   double xPos, double yPos) {
  const double scale = dc.GetContentScaleFactor();
  const FT_F26Dot6 size =
    static_cast<FT_F26Dot6>(fontSize_ * 64 * scale + 0.5);
  if (FT_Set_Char_Size(face, size, size, 72, 72) ||
      FT_Load_Glyph(face, glyph, FT_LOAD_RENDER) ||
      !face->glyph) {
    return;
  }

  const size_t width = face->glyph->bitmap.width;
  const size_t height = face->glyph->bitmap.rows;
  if (width == 0 || height == 0) {
    return;
  }

  wxBitmap bitmap;
  if (!bitmap.CreateScaled(ceil(width / scale), ceil(height / scale),
			   32, scale)) {
    return;
  }

  FillBlack(&bitmap);
  FT_Bitmap ftBitmap;
  FT_Bitmap_Init(&ftBitmap);
  FT_Bitmap_Convert(face->glyph->library, &face->glyph->bitmap, &ftBitmap, 1);
  CopyAlpha(ftBitmap, &bitmap);
  FT_Bitmap_Done(face->glyph->library, &ftBitmap);

  dc.DrawBitmap(bitmap,
		xPos + (fontFace_->glyph->bitmap_left / scale),
		yPos - (fontFace_->glyph->bitmap_top / scale));
}

void SampleText::Paint(wxDC& dc) {
  if (!fontFace_ || !dc.IsOk()) {
    return;
  }

  dc.Clear();
  const double scale = dc.GetContentScaleFactor();
  const wxSize dpi = dc.GetPPI();  // dots/pixels per inch
  const FT_F26Dot6 size =
      static_cast<FT_F26Dot6>(fontSize_ * 64 * scale + 0.5);
  if (FT_Set_Char_Size(fontFace_, size, size, dpi.x, dpi.y)) {
    return;
  }

  raqm_t* layout = raqm_create();
  raqm_set_text_utf8(layout, text_.c_str(), text_.size());
  raqm_set_par_direction(layout, RAQM_DIRECTION_DEFAULT);
  if (!raqm_set_freetype_face(layout, fontFace_) || !raqm_layout(layout)) {
    raqm_destroy(layout);
    return;
  }

  const double ascender = fontSize_ *
      (static_cast<double>(fontFace_->ascender) /
       static_cast<double>(fontFace_->units_per_EM));
  size_t numGlyphs = 0;
  raqm_glyph_t* glyphs = raqm_get_glyphs(layout, &numGlyphs);
  const double border =  2 * scale;
  double x = border, y = border + ascender;
  for (size_t i = 0; i < numGlyphs; ++i) {
    double glyphX = x + glyphs[i].x_offset / (scale * 64.0);
    double glyphY = y + glyphs[i].y_offset / (scale * 64.0);
    DrawGlyph(dc, glyphs[i].ftface, glyphs[i].index, glyphX, glyphY);
    x += glyphs[i].x_advance / (scale * 64.0);
    y += glyphs[i].y_advance / (scale * 64.0);
  }

  raqm_destroy(layout);
}

wxBEGIN_EVENT_TABLE(SampleText, wxScrolledCanvas)
EVT_PAINT(SampleText::OnPaint)
wxEND_EVENT_TABLE()

}  // namespace fontview
