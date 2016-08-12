{
  'targets': [
    {
      'target_name': 'fontview',
      'type': 'executable',
      'sources': [
        'font_style.cpp',
        'font_var_axis.cpp',
        'main.cpp',
        'name_table.cpp',
        'text_settings.cpp',
      ],
      'include_dirs': [
        '..',
      ],
      'dependencies': [
        '../third_party/freetype/freetype.gyp:freetype',
        '../third_party/fribidi/fribidi.gyp:fribidi',
        '../third_party/harfbuzz/harfbuzz.gyp:harfbuzz',
        '../third_party/raqm/raqm.gyp:raqm',
        '../third_party/wxWidgets/wxWidgets.gyp:core',
      ],
    },
  ],
  'target_defaults': {
    'xcode_settings': {
      'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
      'CLANG_CXX_LIBRARY': 'libc++',
    },
  },
}
