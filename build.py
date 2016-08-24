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

import argparse, codecs, shutil, os, sys

def main():
    parser = argparse.ArgumentParser(
        description='build the FontView application')
    parser.add_argument('--release', help='current release, eg. "v1.2"')
    args = parser.parse_args()
    success = False

    platform = os.uname()[0]
    release = args.release if args.release else ''
    if platform == 'Linux':
        success = build_unix(release)
    elif platform == 'Darwin':
        success = build_unix(release) and package_mac(release)
    else:
        sys.stderr.write('Unsupported platform \"%s\"' % platform + os.linesep)
    sys.exit(0 if success else 1)


def build_unix(release):
    if os.system('FONTVIEW_VERSION=\"%s\" '
                 './src/third_party/gyp/gyp -f make --depth . '
                 '--generator-output build  src/fontview/fontview.gyp' %
                 (release, )) != 0:
        return False
    if os.system('make --directory build') != 0:
        return False
    return True


def package_mac(release):
    shutil.rmtree('build/FontView.app', ignore_errors=True)
    os.mkdir('build/FontView.app')
    os.mkdir('build/FontView.app/Contents')
    os.mkdir('build/FontView.app/Contents/MacOS')
    os.mkdir('build/FontView.app/Contents/Resources')
    shutil.copy('build/out/Default/fontview',
                'build/FontView.app/Contents/MacOS/fontview')
    with codecs.open('src/fontview/mac/Info.plist', 'r', 'utf-8') as info_file:
        info = info_file.read()
    info = info % {
        'SHORT_VERSION': release.replace('v', ''),
        'LONG_VERSION': release.replace('v', 'Version ')
    }
    with codecs.open('build/FontView.app/Contents/Info.plist', 'w',
                     'utf-8') as out_info_file:
        out_info_file.write(info)
    if os.system('/usr/bin/SetFile -t APPL '
                 'build/FontView.app/Contents/MacOS/fontview') != 0:
        return False
    if release:
        cwd = os.getcwd()
        os.chdir('build')
        if os.system('zip -r FontView-MacOS.zip FontView.app') != 0:
            return False
        os.chdir(cwd)
    else:
        shutil.rmtree('build/FontView-MacOS.zip', ignore_errors=True)
    return True


if __name__ == '__main__':
    main()
