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

#include <wx/wx.h>
#include <wx/caret.h>

#if defined(__WXOSX__) && __WXOSX__
#include "fontview/mac/caret.h"
#endif

namespace fontview {

int GetCaretBlinkPeriodOn() {
#if defined(__WXOSX__) && __WXOSX__
  return ::fontview_mac::GetCaretBlinkPeriodOn();
#else
  return wxCaret::GetBlinkTime() / 2;
#endif
}

int GetCaretBlinkPeriodOff() {
#if defined(__WXOSX__) && __WXOSX__
  return ::fontview_mac::GetCaretBlinkPeriodOff();
#else
  return wxCaret::GetBlinkTime() / 2;
#endif
}

}  // namespace fontview
