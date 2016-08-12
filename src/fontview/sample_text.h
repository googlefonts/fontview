#ifndef FONTVIEW_SAMPLE_TEXT_
#define FONTVIEW_SAMPLE_TEXT_

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <raqm.h>

#include <wx/wx.h>

namespace fontview {

class SampleText : public wxControl {
 public:
  SampleText(wxWindow* parent);
  virtual ~SampleText();
  void SetText(const std::string& text);
  void SetFontFace(FT_Face fontFace);

 protected:
  virtual wxSize DoGetBestSize() const;
  virtual void OnPaint(wxPaintEvent& event);

 private:
  void LayoutContent();

  std::string text_;
  FT_Face fontFace_;
  raqm_t* raqm_;
};

}  // namespace fontview

#endif  // FONTVIEW_SAMPLE_TEXT_
