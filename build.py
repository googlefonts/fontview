#!/usr/bin/python2.7
#
# Copyright 2016 Google Inc. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import shutil, os, sys

def main():
    if os.uname()[0] == 'Darwin':
        build_mac()
    else:
        sys.stderr.write('Unsupported platform' + os.linesep)
        sys.exit(1)


def build_mac():
    os.system('./src/third_party/gyp/gyp -f make --depth . ' +
              '--generator-output build  src/fontview/fontview.gyp')
    os.system('make --directory build')
    shutil.rmtree('build/FontView.app', ignore_errors=True)
    os.mkdir('build/FontView.app')
    os.mkdir('build/FontView.app/Contents')
    os.mkdir('build/FontView.app/Contents/MacOS')
    os.mkdir('build/FontView.app/Contents/Resources')
    shutil.copy('build/out/Default/fontview',
                'build/FontView.app/Contents/MacOS/fontview')
    shutil.copy('src/fontview/mac/Info.plist',
                'build/FontView.app/Contents/Info.plist')
    os.system('/usr/bin/SetFile -t APPL '
              'build/FontView.app/Contents/MacOS/fontview')


if __name__ == '__main__':
    main()
