{
    'targets': [
        {
            'target_name': 'harfbuzz',
            'type': 'static_library',
	    'defines': [
	        'HAVE_FREETYPE',
                'HAVE_FT_GET_VAR_BLEND_COORDINATES',
                'HAVE_INTEL_ATOMIC_PRIMITIVES',
		'HAVE_OT',
                'HAVE_UCDN',
	    ],
            'sources': [
                'harfbuzz/src/hb-blob.cc',
                'harfbuzz/src/hb-buffer-serialize.cc',
                'harfbuzz/src/hb-buffer.cc',
                'harfbuzz/src/hb-common.cc',
                #'harfbuzz/src/hb-coretext.cc',
                #'harfbuzz/src/hb-directwrite.cc',
                'harfbuzz/src/hb-face.cc',
                'harfbuzz/src/hb-fallback-shape.cc',
                'harfbuzz/src/hb-font.cc',
                'harfbuzz/src/hb-ft.cc',
                #'harfbuzz/src/hb-glib.cc',
                #'harfbuzz/src/hb-gobject-structs.cc',
                #'harfbuzz/src/hb-graphite2.cc',
                #'harfbuzz/src/hb-icu.cc',
                'harfbuzz/src/hb-ot-font.cc',
                'harfbuzz/src/hb-ot-layout.cc',
                'harfbuzz/src/hb-ot-map.cc',
                'harfbuzz/src/hb-ot-shape-complex-arabic.cc',
                'harfbuzz/src/hb-ot-shape-complex-default.cc',
                'harfbuzz/src/hb-ot-shape-complex-hangul.cc',
                'harfbuzz/src/hb-ot-shape-complex-hebrew.cc',
                'harfbuzz/src/hb-ot-shape-complex-indic-table.cc',
                'harfbuzz/src/hb-ot-shape-complex-indic.cc',
                'harfbuzz/src/hb-ot-shape-complex-myanmar.cc',
                'harfbuzz/src/hb-ot-shape-complex-thai.cc',
                'harfbuzz/src/hb-ot-shape-complex-tibetan.cc',
                'harfbuzz/src/hb-ot-shape-complex-use-table.cc',
                'harfbuzz/src/hb-ot-shape-complex-use.cc',
                'harfbuzz/src/hb-ot-shape-fallback.cc',
                'harfbuzz/src/hb-ot-shape-normalize.cc',
                'harfbuzz/src/hb-ot-shape.cc',
                'harfbuzz/src/hb-ot-tag.cc',
                'harfbuzz/src/hb-set.cc',
                'harfbuzz/src/hb-shape-plan.cc',
                'harfbuzz/src/hb-shape.cc',
                'harfbuzz/src/hb-shaper.cc',
                'harfbuzz/src/hb-ucdn.cc',
                'harfbuzz/src/hb-ucdn/ucdn.c',
                'harfbuzz/src/hb-unicode.cc',
                #'harfbuzz/src/hb-uniscribe.cc',
                'harfbuzz/src/hb-warning.cc',

	        'harfbuzz/src/hb-buffer-deserialize-json.rl',
	        'harfbuzz/src/hb-buffer-deserialize-text.rl',
	        'harfbuzz/src/hb-ot-shape-complex-indic-machine.rl',
	        'harfbuzz/src/hb-ot-shape-complex-myanmar-machine.rl',
	        'harfbuzz/src/hb-ot-shape-complex-use-machine.rl',
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'autoconf_generated',
                    'harfbuzz/src',
                ],
            },
            'include_dirs': [
                'autoconf_generated',
		'harfbuzz/src',
		'harfbuzz/src/hb-ucdn',
		'<(INTERMEDIATE_DIR)',
	    ],
      	    'rules': [
                {
		    'rule_name': 'ragel',
		    'extension': 'rl',
	      	    'outputs': [
 		        '<(INTERMEDIATE_DIR)/<(RULE_INPUT_ROOT).hh'
		    ],
                    'action': [
		         '<(PRODUCT_DIR)/ragel', '-e', '-F1',
		         '-o', '<@(_outputs)',
			 '<(RULE_INPUT_PATH)'
		    ],
        	}
      	    ],
	    'dependencies': [
                '../freetype/freetype.gyp:freetype',
                '../ragel/ragel.gyp:ragel',
	    ],
        },
    ]
}
