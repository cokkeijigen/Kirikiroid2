
include(CheckFunctionExists)
include(CheckIncludeFiles)
include(CheckTypeSize)

set(HAVE_PROTOTYPES 1)
check_function_exists("alloca"    HAVE_ALLOCA)
check_include_files("alloca.h"    HAVE_ALLOCA_H)
check_include_files("stdarg.h"    HAVE_STDARG_PROTOTYPES)
check_include_files("stdint.h"    HAVE_STDINT_H)
check_include_files("stdlib.h"    HAVE_STDLIB_H)
check_include_files("strings.h"   HAVE_STRINGS_H)
check_include_files("string.h"    HAVE_STRING_H)
check_include_files("sys/times.h" HAVE_SYS_TIMES_H)
check_include_files("sys/time.h"  HAVE_SYS_TIME_H)
check_include_files("sys/types.h" HAVE_SYS_TYPES_H)
check_include_files("unistd.h"    HAVE_UNISTD_H)
check_type_size("int"   SIZEOF_INT)
check_type_size("long"  SIZEOF_LONG)
check_type_size("short" SIZEOF_SHORT)
check_include_files("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)

configure_file(
        "${oniguruma_SOURCE_DIR}/src/config.h.cmake.in"
        "${oniguruma_SOURCE_DIR}/src/config.h"
)

set(ONIGURUMA_SOURCES
        "${oniguruma_SOURCE_DIR}/src/regerror.c"
        "${oniguruma_SOURCE_DIR}/src/regparse.c"
        "${oniguruma_SOURCE_DIR}/src/regext.c"
        "${oniguruma_SOURCE_DIR}/src/regcomp.c"
        "${oniguruma_SOURCE_DIR}/src/regexec.c"
        "${oniguruma_SOURCE_DIR}/src/reggnu.c"
        "${oniguruma_SOURCE_DIR}/src/regenc.c"
        "${oniguruma_SOURCE_DIR}/src/regsyntax.c"
        "${oniguruma_SOURCE_DIR}/src/regtrav.c"
        "${oniguruma_SOURCE_DIR}/src/regversion.c"
        "${oniguruma_SOURCE_DIR}/src/st.c"
        "${oniguruma_SOURCE_DIR}/src/regposix.c"
        "${oniguruma_SOURCE_DIR}/src/regposerr.c"
        "${oniguruma_SOURCE_DIR}/src/onig_init.c"
        "${oniguruma_SOURCE_DIR}/src/unicode.c"
        "${oniguruma_SOURCE_DIR}/src/ascii.c"
        "${oniguruma_SOURCE_DIR}/src/utf8.c"
        "${oniguruma_SOURCE_DIR}/src/utf16_be.c"
        "${oniguruma_SOURCE_DIR}/src/utf16_le.c"
        "${oniguruma_SOURCE_DIR}/src/utf32_be.c"
        "${oniguruma_SOURCE_DIR}/src/utf32_le.c"
        "${oniguruma_SOURCE_DIR}/src/euc_jp.c"
        "${oniguruma_SOURCE_DIR}/src/sjis.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_1.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_2.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_3.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_4.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_5.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_6.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_7.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_8.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_9.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_10.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_11.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_13.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_14.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_15.c"
        "${oniguruma_SOURCE_DIR}/src/iso8859_16.c"
        "${oniguruma_SOURCE_DIR}/src/euc_tw.c"
        "${oniguruma_SOURCE_DIR}/src/euc_kr.c"
        "${oniguruma_SOURCE_DIR}/src/big5.c"
        "${oniguruma_SOURCE_DIR}/src/gb18030.c"
        "${oniguruma_SOURCE_DIR}/src/koi8_r.c"
        "${oniguruma_SOURCE_DIR}/src/cp1251.c"
        "${oniguruma_SOURCE_DIR}/src/euc_jp_prop.c"
        "${oniguruma_SOURCE_DIR}/src/sjis_prop.c"
        "${oniguruma_SOURCE_DIR}/src/unicode_unfold_key.c"
        "${oniguruma_SOURCE_DIR}/src/unicode_fold1_key.c"
        "${oniguruma_SOURCE_DIR}/src/unicode_fold2_key.c"
        "${oniguruma_SOURCE_DIR}/src/unicode_fold3_key.c"
)

set(ONIGURUMA_INCLUDES "${oniguruma_SOURCE_DIR}/src/")

#add_library(oniguruma OBJECT ${ONIGURUMA_SOURCES})
#target_include_directories(oniguruma PUBLIC
#
#       "${oniguruma_SOURCE_DIR}/src/"
#)
#
#target_compile_definitions(oniguruma PRIVATE
#        "_CRT_SECURE_NO_WARNINGS"
#        "ONIG_EXTERN=extern"
#)