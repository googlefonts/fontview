{
    'targets': [
        {
            'target_name': 'fribidi',
            'type': 'static_library',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'fribidi/charset/fribidi-char-sets-cap-rtl.c',
                'fribidi/charset/fribidi-char-sets-cp1255.c',
                'fribidi/charset/fribidi-char-sets-cp1256.c',
                'fribidi/charset/fribidi-char-sets-iso8859-6.c',
                'fribidi/charset/fribidi-char-sets-iso8859-8.c',
                'fribidi/charset/fribidi-char-sets-utf8.c',
                'fribidi/charset/fribidi-char-sets.c',
                'fribidi/lib/fribidi-arabic.c',
                'fribidi/lib/fribidi-bidi-types.c',
                'fribidi/lib/fribidi-bidi.c',
                'fribidi/lib/fribidi-deprecated.c',
                'fribidi/lib/fribidi-joining-types.c',
                'fribidi/lib/fribidi-joining.c',
                'fribidi/lib/fribidi-mirroring.c',
                'fribidi/lib/fribidi-run.c',
                'fribidi/lib/fribidi-shape.c',
                'fribidi/lib/fribidi.c',
            ],
            'include_dirs': [
                'fribidi/charset',
                'fribidi/lib',
                'generated',
                'internal_config',
                'include',
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'fribidi/charset',
                    'fribidi/lib',
                    'generated',
                    'include',
                ],
            },
        },
        {
            'target_name': 'gen-unicode-version',
            'type': 'executable',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'fribidi/gen.tab/gen-unicode-version.c',
            ],
            'include_dirs': [
                'fribidi/lib',
                'generated',
                'include',
                'internal_config',
            ],
        },
        {
            'target_name': 'gen-arabic-shaping-tab',
            'type': 'executable',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'fribidi/gen.tab/gen-arabic-shaping-tab.c',
                'fribidi/gen.tab/packtab.c',
            ],
            'include_dirs': [
                'fribidi/lib',
                'generated',
                'include',
                'internal_config',
            ],
        },
        {
            'target_name': 'gen-bidi-type-tab',
            'type': 'executable',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'fribidi/gen.tab/gen-bidi-type-tab.c',
                'fribidi/gen.tab/packtab.c',
            ],
            'include_dirs': [
                'fribidi/lib',
                'generated',
                'include',
                'internal_config',
            ],
        },
        {
            'target_name': 'gen-mirroring-tab',
            'type': 'executable',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'fribidi/gen.tab/gen-mirroring-tab.c',
                'fribidi/gen.tab/packtab.c',
            ],
            'include_dirs': [
                'fribidi/lib',
                'generated',
                'include',
                'internal_config',
            ],
        },
        {
            'target_name': 'gen-joining-type-tab',
            'type': 'executable',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
                'fribidi/gen.tab/gen-joining-type-tab.c',
                'fribidi/gen.tab/packtab.c',
            ],
            'include_dirs': [
                'fribidi/lib',
                'generated',
                'include',
                'internal_config',
            ],
        },
    ],
}
