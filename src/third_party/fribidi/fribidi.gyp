{
    'targets': [
        {
            'target_name': 'fribidi',
            'type': 'static_library',
	    'defines': ['HAVE_CONFIG_H'],
            'sources': [
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
                'include',
                'fribidi/lib',
                'generated',
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'fribidi/lib',
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
                'include',
                'fribidi/lib',
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
                'include',
                'fribidi/lib',
                'generated',
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
                'include',
                'fribidi/lib',
                'generated',
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
                'include',
                'fribidi/lib',
                'generated',
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
                'include',
                'fribidi/lib',
                'generated',
            ],
        },
    ],
}
