{
    'targets': [
        {
            'target_name': 'ucdn',
            'type': 'static_library',
            'sources': [
                'ucdn/ucdn.c',
            ],
            'include_dirs': [
                'ucdn',
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'ucdn',
                    '.',  # raqm includes <ucdn/ucdn.h>; harfbuzz just ucdn.h
                ],
            },
        },
    ]
}
