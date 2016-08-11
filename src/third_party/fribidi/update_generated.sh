#!/bin/bash

BUILD_DIR=build/out/Default
GENERATED=src/third_party/fribidi/generated
UNIDATA=src/third_party/fribidi/fribidi/gen.tab/unidata
MAX_DEPTH=3

rm -rf $GENERATED
mkdir $GENERATED

$BUILD_DIR/gen-unicode-version \
    $UNIDATA/*.txt >$GENERATED/fribidi-unicode-version.h

$BUILD_DIR/gen-arabic-shaping-tab \
    $MAX_DEPTH $UNIDATA/UnicodeData.txt >$GENERATED/arabic-shaping.tab.i

$BUILD_DIR/gen-bidi-type-tab \
    $MAX_DEPTH $UNIDATA/UnicodeData.txt >$GENERATED/bidi-type.tab.i

$BUILD_DIR/gen-mirroring-tab \
    $MAX_DEPTH $UNIDATA/BidiMirroring.txt >$GENERATED/mirroring.tab.i

$BUILD_DIR/gen-joining-type-tab \
    $MAX_DEPTH $UNIDATA/UnicodeData.txt $UNIDATA/ArabicShaping.txt \
    >$GENERATED/joining-type.tab.i
