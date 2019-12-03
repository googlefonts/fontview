{
    'includes': ['../../common.gypi'],
    'targets': [
        {
            'target_name': 'harfbuzz',
            'type': 'static_library',
	    'defines': [
	        'HAVE_FREETYPE',
                'HAVE_FT_GET_VAR_BLEND_COORDINATES',
                'HAVE_INTEL_ATOMIC_PRIMITIVES',
		'HAVE_OT',
	    ],
            'sources': [
                'harfbuzz/src/harfbuzz.cc',
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'harfbuzz/src',
                ],
            },
            'include_dirs': [
		'harfbuzz/src',
		'<(INTERMEDIATE_DIR)',
	    ],
	    'dependencies': [
                '../freetype/freetype.gyp:freetype',
	    ],
        },
    ]
}
