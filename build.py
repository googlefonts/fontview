#!/usr/bin/python2.7
#
# Copyright 2017 Google Inc. All rights reserved.
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

import argparse, codecs, shutil, subprocess, os, sys

def main():
    parser = argparse.ArgumentParser(
        description='build the FontView application')
    parser.add_argument('--release', help='current release, eg. "v1.2"')
    args = parser.parse_args()
    success = False

    platform = os.uname()[0]
    release = args.release if args.release else ''
    if platform == 'Linux':
        success = build_linux(release)
    elif platform == 'Darwin':
        success = build_mac(release) and package_mac(release)
    else:
        sys.stderr.write('Unsupported platform \"%s\"' % platform + os.linesep)
    sys.exit(0 if success else 1)


def build_mac(release):
    if os.system('FONTVIEW_VERSION=\"%s\" '
                 './src/third_party/gyp/gyp -f make --depth . '
                 '--generator-output build  src/fontview/fontview.gyp' %
                 (release, )) != 0:
        return False
    if os.system('make --directory build') != 0:
        return False
    return True

def check_pkgconfig(lib, min_version):
    try:
        subprocess.check_output(
            ['pkg-config', '--atleast-version', min_version, lib])
    except subprocess.CalledProcessError:
        print("%s >= %s is missing" % (lib, min_version))
        return False

    return True

def build_linux(release):
    if os.path.exists('build'):
        shutil.rmtree('build')
    os.mkdir('build')

    if not check_pkgconfig("harfbuzz", "1.4.5") or \
       not check_pkgconfig("freetype2", "19.0.13"):
        return False

    pkg_cflags = subprocess.check_output(
        'pkg-config --cflags freetype2 harfbuzz fribidi'.split()).split()
    pkg_libs = subprocess.check_output(
        'pkg-config --libs freetype2 harfbuzz fribidi'.split()).split()
    wx_config = subprocess.check_output(
        'wx-config --cflags --libs base,std,propgrid,qa'.split()).split()
    if check_pkgconfig("raqm", "0.2.0"):
        pkg_cflags += subprocess.check_output(
            ['pkg-config', '--cflags', 'raqm']).split()
        pkg_libs += subprocess.check_output(
            ['pkg-config', '--libs', 'raqm']).split()
    else:
        subprocess.check_call(['cc', '-c', '-std=c99'] + pkg_cflags + [
            '-Isrc/third_party/raqm/libraqm/src',
            '-o', 'build/raqm.o', 'src/third_party/raqm/libraqm/src/raqm.c'])
        pkg_cflags.append('-Isrc/third_party/raqm/libraqm/src')
        pkg_libs.append('build/raqm.o')

    fontview_path = 'src/fontview'
    fontview_sources = ['%s/%s' % (fontview_path, s)
                        for s in os.listdir(fontview_path)
                        if s.endswith('.cpp')]
    subprocess.check_call([
        os.getenv("CXX", "c++"), '-std=c++11'] + pkg_cflags + pkg_libs + wx_config + [
        '-Isrc',
        '-DFONTVIEW_VERSION=%s' % release,
        '-o', 'build/fontview'] + fontview_sources)
    if release:
        subprocess.check_call([
            'zip', 'build/fontview-linux.zip', 'build/fontview'])
    return True


def package_mac(release):
    shutil.rmtree('build/FontView.app', ignore_errors=True)
    shutil.rmtree('build/fontview-osx.zip', ignore_errors=True)
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
    if os.system('/usr/bin/iconutil --convert icns '
                 '--output build/FontView.app/Contents/Resources/app.icns '
                 'src/fontview/mac/app.iconset') != 0:
        return False
    if release:
        cwd = os.getcwd()
        os.chdir('build')
        if os.system('zip -r fontview-osx.zip FontView.app') != 0:
            return False
        os.chdir(cwd)
    return True


if __name__ == '__main__':
    main()
