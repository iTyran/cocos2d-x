/*===--- ConvertUTF.h - Universal Character Names conversions ---------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 *==------------------------------------------------------------------------==*/
/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------

    Conversions between UTF32, UTF-16, and UTF-8.  Header file.

    Several funtions are included here, forming a complete set of
    conversions between the three formats.  UTF-7 is not included
    here, but is handled in a separate source file.

    Each of these routines takes pointers to input buffers and output
    buffers.  The input buffers are const.

    Each routine converts the text between *sourceStart and sourceEnd,
    putting the result into the buffer between *targetStart and
    targetEnd. Note: the end pointers are *after* the last item: e.g.
    *(sourceEnd - 1) is the last item.

    The return result indicates whether the conversion was successful,
    and if not, whether the problem was in the source or target buffers.
    (Only the first encountered problem is indicated.)

    After the conversion, *sourceStart and *targetStart are both
    updated to point to the end of last text successfully converted in
    the respective buffers.

    Input parameters:
        sourceStart - pointer to a pointer to the source buffer.
                The contents of this are modified on return so that
                it points at the next thing to be converted.
        targetStart - similarly, pointer to pointer to the target buffer.
        sourceEnd, targetEnd - respectively pointers to the ends of the
                two buffers, for overflow checking only.

    These conversion functions take a ConversionFlags argument. When this
    flag is set to strict, both irregular sequences and isolated surrogates
    will cause an error.  When the flag is set to lenient, both irregular
    sequences and isolated surrogates are converted.

    Whether the flag is strict or lenient, all illegal sequences will cause
    an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
    or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
    must check for illegal sequences.

    When the flag is set to lenient, characters over 0x10FFFF are converted
    to the replacement character; otherwise (when the flag is set to strict)
    they constitute an error.

    Output parameters:
        The value "sourceIllegal" is returned from some routines if the input
        sequence is malformed.  When "sourceIllegal" is returned, the source
        value will point to the illegal value that caused the problem. E.g.,
        in UTF-8 when a sequence is malformed, it points to the start of the
        malformed sequence.

    Author: Mark E. Davis, 1994.
    Rev History: Rick McGowan, fixes & updates May 2001.
         Fixes & updates, Sept 2001.

------------------------------------------------------------------------ */

#ifndef LLVM_SUPPORT_CONVERTUTF_H
#define LLVM_SUPPORT_CONVERTUTF_H

#include <stddef.h>   /* ptrdiff_t */
/* ---------------------------------------------------------------------
    The following 4 definitions are compiler-specific.
    The C standard does not guarantee that wchar_t has at least
    16 bits, so wchar_t is no less portable than unsigned short!
    All should be unsigned values to avoid sign extension during
    bit mask & shift operations.
------------------------------------------------------------------------ */

typedef unsigned int    UTF32;  /* at least 32 bits */
typedef unsigned short  UTF16;  /* at least 16 bits */
typedef unsigned char   UTF8;   /* typically 8 bits */
typedef unsigned char   Boolean; /* 0 or 1 */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF

#define UNI_MAX_UTF8_BYTES_PER_CODE_POINT 4

#define UNI_UTF16_BYTE_ORDER_MARK_NATIVE  0xFEFF
#define UNI_UTF16_BYTE_ORDER_MARK_SWAPPED 0xFFFE

typedef enum {
  conversionOK,           /* conversion successful */
  sourceExhausted,        /* partial character in source, but hit end */
  targetExhausted,        /* insuff. room in target for conversion */
  sourceIllegal           /* source sequence is illegal/malformed */
} ConversionResult;

typedef enum {
  strictConversion = 0,
  lenientConversion
} ConversionFlags;

/* This is for C++ and does no harm in C */
#ifdef __cplusplus
extern "C" {
#endif

ConversionResult ConvertUTF8toUTF16 (
  const UTF8** sourceStart, const UTF8* sourceEnd,
  UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF8toUTF32 (
  const UTF8** sourceStart, const UTF8* sourceEnd,
  UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8 (
  const UTF16** sourceStart, const UTF16* sourceEnd,
  UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF8 (
  const UTF32** sourceStart, const UTF32* sourceEnd,
  UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF32 (
  const UTF16** sourceStart, const UTF16* sourceEnd,
  UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF16 (
  const UTF32** sourceStart, const UTF32* sourceEnd,
  UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

Boolean isLegalUTF8String(const UTF8 **source, const UTF8 *sourceEnd);

unsigned getNumBytesForUTF8(UTF8 firstByte);
    
int getUTF8StringLength(const UTF8* utf8);

#ifdef __cplusplus
}

/*************************************************************************/
/* Below are LLVM-specific wrappers of the functions above. */

//#include "llvm/ADT/ArrayRef.h"
//#include "llvm/ADT/StringRef.h"

#include <vector>
#include <string>

namespace llvm {

/**
 * 根据WideCharWidth转换UTF8的StringRef为UTF8, UTF16, 或UTF32。
 * 转换的数据将被写入到ResultPtr，
 * ResultPtr需要调用者预先分配至少 WideCharWidth * (Source.Size() + 1)字节的空间。
 * 如果转换成功，ResultPtr指向一个复制字符串的结尾。
 * 如果失败，ResultPtr将不被改变，ErrorPtr会指向第一个出错的字符。
 * \return 成功返回true。
 */
bool ConvertUTF8toWide(unsigned WideCharWidth, const std::string& Source,
                       char *&ResultPtr, const UTF8 *&ErrorPtr);

/**
 * 转换一个Unicode字符为UTF8序列
 *
 * \param Source Unicode码。
 * \param [in,out] ResultPtr 指向输出buffer，至少需要UNI_MAX_UTF8_BYTES_PER_CODE_POINT字节
 *
 * \returns 成功返回true。
 */
bool ConvertCodePointToUTF8(unsigned Source, char *&ResultPtr);

/**
 * Convert the first UTF8 sequence in the given source buffer to a UTF32
 * code point.
 * 转换source指向的第一个UTF8序列为UTF32。
 *
 * \param [in,out] source 指向源buffer头. 如果成功转换，
 * 该指针将被更新以指向字节刚刚过去的经转换的序列的末尾。
 * \param sourceEnd 指向源buffer尾。
 * \param [out] target 转换后的编码
 * \param flags 转换是严谨还是宽松。
 *
 * \returns 成功返回conversionOK
 *
 * \sa ConvertUTF8toUTF32
 */
static inline ConversionResult convertUTF8Sequence(const UTF8 **source,
                                                   const UTF8 *sourceEnd,
                                                   UTF32 *target,
                                                   ConversionFlags flags) {
  if (*source == sourceEnd)
    return sourceExhausted;
  unsigned size = getNumBytesForUTF8(**source);
  if ((ptrdiff_t)size > sourceEnd - *source)
    return sourceExhausted;
  return ConvertUTF8toUTF32(source, *source + size, &target, target + 1, flags);
}

/**
 * 如果一个二进制的文本是UTF-16大端或小端开头，返回true。
 */
bool hasUTF16ByteOrderMark(const char* SrcBytes, size_t len);

/**
 * 转换一假设为UTF16的裸数据了流到UTF8的std::string。
 *
 * \param [in] SrcBytes 指向假设为UTF16的数据流。
 * \param [out] Out 转换后的UTF8输出。
 * \returns 成功返回true。
 */
bool convertUTF16ToUTF8String(const std::u16string& utf16, std::string &Out);

} /* end namespace llvm */

#endif

/* --------------------------------------------------------------------- */

#endif
