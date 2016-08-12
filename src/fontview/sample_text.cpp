#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <raqm.h>
#include <wx/wx.h>

#include "fontview/sample_text.h"

namespace fontview {

SampleText::SampleText(wxWindow* parent)
  : wxControl(parent, wxID_ANY),
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
  if (!raqm_layout(raqm_)) {
    return;
  }
  size_t numGlyphs = 0;
  raqm_glyph_t* glyphs = raqm_get_glyphs(raqm_, &numGlyphs);
  printf("SampleText::LayoutContent(); numGlyphs: %lu\n", numGlyphs);
  if (numGlyphs > 0) {
    size_t i = numGlyphs - 1;
    printf("  glyphs[%lu]: advance=(%d,%d)\n",
	   i, glyphs[i].x_advance, glyphs[i].y_advance);
  }
  // TODO: Destroy glyphs?
}

wxSize SampleText::DoGetBestSize() const {
  // TODO: Measure the text.
  return wxSize(600, 300);
}

void SampleText::OnPaint(wxPaintEvent& event) {
  printf("OnPaint\n");
  if (!fontFace_ || !raqm_) {
    return;
  }
  printf("SampleText::OnPaint()\n");
}

}  // namespace fontview
