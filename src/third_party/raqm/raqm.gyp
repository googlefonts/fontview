{
    'targets': [
        {
            'target_name': 'raqm',
            'type': 'static_library',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'libraqm/src/raqm.c',
            ],
            'include_dirs': [
                'internal_config',
                'libraqm/src',
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'libraqm/src',
                ],
            },
	    'dependencies': [
                '../freetype/freetype.gyp:freetype',
                '../fribidi/fribidi.gyp:fribidi',
                '../harfbuzz/harfbuzz.gyp:harfbuzz',
            ],
        },
    ],
}
