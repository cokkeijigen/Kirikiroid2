#include <tjs.h>
#include <k2atvp.hpp>
#include <kr2android.hpp>
#include <tjsRandomGenerator.h>

namespace TJS
{
    static auto _TJSGetRandomBits128(void* dest) -> void { k2a::tvp::get_random_bits128(dest);  }
    decltype(TJSGetRandomBits128) TJSGetRandomBits128 = _TJSGetRandomBits128;

    decltype(TJSCreateTextStreamForRead )   TJSCreateTextStreamForRead    { k2a::tvp::stream:: create_text_for_read   };
    decltype(TJSCreateTextStreamForWrite)   TJSCreateTextStreamForWrite   { k2a::tvp::stream::create_text_for_write   };
    decltype(TJSCreateBinaryStreamForRead ) TJSCreateBinaryStreamForRead  { k2a::tvp::stream::create_binary_for_read  };
    decltype(TJSCreateBinaryStreamForWrite) TJSCreateBinaryStreamForWrite { k2a::tvp::stream::create_binary_for_write };
}

