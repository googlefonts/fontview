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

#ifndef FONTVIEW_NAME_TABLE_
#define FONTVIEW_NAME_TABLE_

#include <map>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace fontview {
typedef std::map<int, std::string> NameTable;

NameTable* BuildNameTable(FT_Face face);
const std::string& GetFontName(const NameTable& names, int id);
const std::string& GetFontFamilyName(const NameTable& names);
const std::string& GetFontStyleName(const NameTable& names);
}  // namespace fontview

#endif // FONTVIEW_NAME_TABLE
