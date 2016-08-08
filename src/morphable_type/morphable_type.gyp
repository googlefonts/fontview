{
  'targets': [
    {
      'target_name': 'morphable_type',
      'type': 'executable',
      'sources': [
        'font_style.cpp',
        'main.cpp',
        'name_table.cpp',
      ],
      'dependencies': [
        '../third_party/freetype/freetype.gyp:freetype',
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
