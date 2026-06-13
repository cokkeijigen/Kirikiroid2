#include <tjs.h>
#include <k2atvp.hpp>
#include <kr2android.hpp>


decltype(TJSCreateTextStreamForRead )  TJSCreateTextStreamForRead = k2a::tvp::stream:: create_text_for_read;
decltype(TJSCreateTextStreamForWrite) TJSCreateTextStreamForWrite = k2a::tvp::stream::create_text_for_write;

decltype(TJSCreateBinaryStreamForRead )  TJSCreateBinaryStreamForRead = k2a::tvp::stream::create_binary_for_read;
decltype(TJSCreateBinaryStreamForWrite) TJSCreateBinaryStreamForWrite = k2a::tvp::stream::create_binary_for_write;

//iTJSTextReadStream* (*   TJSCreateTextStreamForRead)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_text_stream_for_read   ;
//iTJSTextWriteStream*(*  TJSCreateTextStreamForWrite)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_text_stream_for_write  ;
//tTJSBinaryStream*   (* TJSCreateBinaryStreamForRead)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_binary_stream_for_read ;
//tTJSBinaryStream*   (*TJSCreateBinaryStreamForWrite)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_binary_stream_for_write;