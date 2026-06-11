#include <tjs.h>
#include <k2atvp.hpp>
#include <kr2android.hpp>

iTJSTextReadStream* (*   TJSCreateTextStreamForRead)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_text_stream_for_read   ;
iTJSTextWriteStream*(*  TJSCreateTextStreamForWrite)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_text_stream_for_write  ;
tTJSBinaryStream*   (* TJSCreateBinaryStreamForRead)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_binary_stream_for_read ;
tTJSBinaryStream*   (*TJSCreateBinaryStreamForWrite)(const tTJSString &name, const tTJSString &mode) = k2a::tvp::create_binary_stream_for_write;