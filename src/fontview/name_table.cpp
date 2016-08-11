#include <map>
#include <string>

#include "name_table.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H

#include <wx/string.h>

namespace fontview {

static const wxFontEncoding UNSUPPORTED_ENCODING =
    static_cast<wxFontEncoding>(-1);
static wxFontEncoding GetFontNameEncoding(const FT_SfntName& name);
static int GetFontNameQuality(const FT_SfntName& name);


NameTable* BuildNameTable(FT_Face face) {
  NameTable* result = new NameTable();
  const FT_UInt numNames = FT_Get_Sfnt_Name_Count(face);
  std::map<int, int> nameQuality;
  FT_SfntName name;
  for (FT_UInt i = 0; i < numNames; ++i) {
    if (FT_Get_Sfnt_Name(face, i, &name) != 0) {
      continue;
    }

    int curQuality = GetFontNameQuality(name);
    if (curQuality == 0) {
      continue;
    }

    int bestQuality = nameQuality[name.name_id];
    if (curQuality < bestQuality) {
      continue;
    }

    const wxFontEncoding encoding = GetFontNameEncoding(name);
    if (encoding == UNSUPPORTED_ENCODING) {
      continue;
    }

    wxCSConv converter(encoding);
    if (!converter.IsOk()) {
      continue;
    }

    wxString convertedName(name.string, converter, name.string_len);
    nameQuality[name.name_id] = curQuality;
    (*result)[name.name_id] = convertedName.ToStdString();
  }

  // Add a family name if we haven't one yet, eg. for Type 1 PostScript fonts.
  if (result->count(1) == 0 && face->family_name) {
    (*result)[1] = std::string(face->family_name);
  }

  // Add a style name if we haven't one yet, eg. for Type 1 PostScript fonts.
  if (result->count(2) == 0 && face->style_name) {
    (*result)[2] = std::string(face->style_name);
  }

  return result;
}


static const std::string EMPTY_STRING;

const std::string& GetFontName(const NameTable& names, int id) {
  NameTable::const_iterator iter = names.find(id);
  if (iter != names.end()) {
    return iter->second;
  } else {
    return EMPTY_STRING;
  }
}

const std::string& GetFontFamilyName(const NameTable& names) {
  const std::string& name = GetFontName(names, 16);
  if (!name.empty()) {
    return name;
  }

  return GetFontName(names, 1);
}

const std::string& GetFontStyleName(const NameTable& names) {
  const std::string& name = GetFontName(names, 17);
  if (!name.empty()) {
    return name;
  }

  return GetFontName(names, 2);
}

wxFontEncoding GetFontNameEncoding(const FT_SfntName& name) {
  if (name.platform_id == TT_PLATFORM_MICROSOFT) {
    switch (name.encoding_id) {
    case TT_MS_ID_UNICODE_CS: return wxFONTENCODING_UTF16BE;
    case TT_MS_ID_SJIS: return wxFONTENCODING_SHIFT_JIS;
    case TT_MS_ID_GB2312: return wxFONTENCODING_GB2312;
    case TT_MS_ID_BIG_5: return wxFONTENCODING_BIG5;
    case TT_MS_ID_JOHAB: return wxFONTENCODING_JOHAB;
    default: break;
    }
  }

  if (name.platform_id == TT_PLATFORM_APPLE_UNICODE) {
    return wxFONTENCODING_UTF16BE;
  }

  if (name.platform_id == TT_PLATFORM_MACINTOSH) {
    switch (name.encoding_id) {
    case TT_MAC_ID_ROMAN: return wxFONTENCODING_MACROMAN;
    case TT_MAC_ID_JAPANESE: return wxFONTENCODING_MACJAPANESE;
    case TT_MAC_ID_TRADITIONAL_CHINESE: return wxFONTENCODING_MACCHINESETRAD;
    case TT_MAC_ID_KOREAN: return wxFONTENCODING_MACKOREAN;
    case TT_MAC_ID_ARABIC: return wxFONTENCODING_MACARABIC;
    case TT_MAC_ID_HEBREW: return wxFONTENCODING_MACHEBREW;
    case TT_MAC_ID_GREEK: return wxFONTENCODING_MACGREEK;
    case TT_MAC_ID_RUSSIAN: return wxFONTENCODING_MACCYRILLIC;
    case TT_MAC_ID_DEVANAGARI: return wxFONTENCODING_MACDEVANAGARI;
    case TT_MAC_ID_GURMUKHI: return wxFONTENCODING_MACGURMUKHI;
    case TT_MAC_ID_GUJARATI: return wxFONTENCODING_MACGUJARATI;
    case TT_MAC_ID_ORIYA: return wxFONTENCODING_MACORIYA;
    case TT_MAC_ID_BENGALI: return wxFONTENCODING_MACBENGALI;
    case TT_MAC_ID_TAMIL: return wxFONTENCODING_MACTAMIL;
    case TT_MAC_ID_TELUGU: return wxFONTENCODING_MACTELUGU;
    case TT_MAC_ID_KANNADA: return wxFONTENCODING_MACKANNADA;
    case TT_MAC_ID_MALAYALAM: return wxFONTENCODING_MACMALAJALAM;
    case TT_MAC_ID_SINHALESE: return wxFONTENCODING_MACSINHALESE;
    case TT_MAC_ID_BURMESE: return wxFONTENCODING_MACBURMESE;
    case TT_MAC_ID_KHMER: return wxFONTENCODING_MACKHMER;
    case TT_MAC_ID_THAI: return wxFONTENCODING_MACTHAI;
    case TT_MAC_ID_LAOTIAN: return wxFONTENCODING_MACLAOTIAN;
    case TT_MAC_ID_GEORGIAN: return wxFONTENCODING_MACGEORGIAN;
    case TT_MAC_ID_ARMENIAN: return wxFONTENCODING_MACARMENIAN;
    case TT_MAC_ID_SIMPLIFIED_CHINESE: return wxFONTENCODING_MACCHINESESIMP;
    case TT_MAC_ID_TIBETAN: return wxFONTENCODING_MACTIBETAN;
    case TT_MAC_ID_MONGOLIAN: return wxFONTENCODING_MACMONGOLIAN;
    case TT_MAC_ID_GEEZ: return wxFONTENCODING_MACETHIOPIC;
    case TT_MAC_ID_SLAVIC: return wxFONTENCODING_MACCENTRALEUR;
    case TT_MAC_ID_VIETNAMESE: return wxFONTENCODING_MACVIATNAMESE;
    default: break;
    }
  }

  return UNSUPPORTED_ENCODING;
}


int GetFontNameQuality(const FT_SfntName& name) {
  const wxFontEncoding encoding = GetFontNameEncoding(name);
  if (encoding == UNSUPPORTED_ENCODING) {
    return 0;
  }

  wxCSConv converter(encoding);
  if (!converter.IsOk()) {
    return 0;
  }

  // Give a slight preference to Unicode-encoded names.
  int encodingQuality = 0;
  if (encoding == wxFONTENCODING_UTF16BE) {
    encodingQuality = 2;
  }

  // TODO: Run a language matcher against the user's preferred languages.
  // Currently, we prefer US English and penalize everything else.
  if (name.platform_id == TT_PLATFORM_MICROSOFT) {
    encodingQuality += name.language_id == 1033 ? 10 : 5;
    return encodingQuality;
  }

  if (name.platform_id == TT_PLATFORM_MACINTOSH) {
    encodingQuality += name.language_id == 0 ? 10 : 5;
    return encodingQuality;
  }

  return 0;
}

}  // namespace fontview
