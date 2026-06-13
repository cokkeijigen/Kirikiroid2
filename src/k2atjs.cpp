#include <tjs.h>
#include <k2atvp.hpp>
#include <kr2android.hpp>

namespace TJS
{
    decltype(TJSCreateTextStreamForRead )   TJSCreateTextStreamForRead    { k2a::tvp::stream:: create_text_for_read   };
    decltype(TJSCreateTextStreamForWrite)   TJSCreateTextStreamForWrite   { k2a::tvp::stream::create_text_for_write   };
    decltype(TJSCreateBinaryStreamForRead ) TJSCreateBinaryStreamForRead  { k2a::tvp::stream::create_binary_for_read  };
    decltype(TJSCreateBinaryStreamForWrite) TJSCreateBinaryStreamForWrite { k2a::tvp::stream::create_binary_for_write };
}

