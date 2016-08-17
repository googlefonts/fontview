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

#ifndef FONTVIEW_MAC_CARET_H_
#define FONTVIEW_MAC_CARET_H_

namespace fontview_mac {

// Returns how many milliseconds the caret should stay visible.
int GetCaretBlinkPeriodOn();

// Returns how many milliseconds the caret should stay invisible.
int GetCaretBlinkPeriodOff();

};  // namespace fontview_mac

#endif // FONTVIEW_MAC_CARET_H_
