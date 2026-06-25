#pragma once
#include <vector>
#include <tjs.h>
#include "tjsHashSearch.h"

namespace kr2android::tvp::graphic
{

    enum PixelFormat
    {
        gpfLuminance,
        gpfPalette,
        gpfRGB,
        gpfRGBA
    };

    enum LoadMode
    {
        glmNormal,     // normal, ie. 32bit ARGB graphic
        glmPalettized, // palettized 8bit mode
        glmGrayscale   // grayscale 8bit mode
    };

    class NativeBaseBitmap
    {
        struct BaseBitmap;
        struct BaseBitmapVtable
        {
            void* __Unused[0x07];
            const void*(*GetScanLineForRead)(BaseBitmap *self, tjs_uint line);
        };

        struct BaseBitmap
        {
            BaseBitmapVtable* Vtable;
            int32_t __Unused;
            tjs_int    Width;
            tjs_int   Height;
        };

        void* __Unused[0x0B];
        BaseBitmap* bitmap;

    public:

        [[gnu::noinline]]
        auto GetWidth() const noexcept -> tjs_uint
        {
            if(static_cast<const void*>(this) != nullptr)
            {
                return this->bitmap->Width;
            }
            return 0;
        };

        [[gnu::noinline]]
        auto GetHeight() const noexcept -> tjs_uint
        {
            if(static_cast<const void*>(this) != nullptr)
            {
                return this->bitmap->Height;
            }
            return 0;
        }

        [[gnu::noinline]]
        auto GetScanLine(tjs_uint line) const noexcept -> const void*
        {
            if(static_cast<const void*>(this) != nullptr)
            {
                return this->bitmap->Vtable->GetScanLineForRead(this->bitmap, line);
            }
            return nullptr;
        }
    };

    using ScanLineCallback     = void*(*)(void* callbackdata, tjs_int y);
    using SizeCallback         = int  (*)(void* callbackdata, tjs_uint w, tjs_uint h, PixelFormat fmt);
    using MetaInfoPushCallback = void (*)(void* callbackdata, const ttstr& name, const ttstr& value);
    using LoadingHandler       = void (*)
    (
        void* formatdata, void* callbackdata, SizeCallback sizecallback, ScanLineCallback scanlinecallback,
        MetaInfoPushCallback metainfopushcallback, tTJSBinaryStream* src, tjs_int32 keyidx, LoadMode mode
    );
    using SaveHandler          = void (*)
    (
        void* formatdata, tTJSBinaryStream* dst, NativeBaseBitmap* image, const ttstr& mode, iTJSDispatch2* meta
    );
    using AcceptSaveHandler    = bool (*)(void* formatdata, const ttstr&     type, iTJSDispatch2** dic);
    using HeaderLoadingHandler = void (*)(void* formatdata, tTJSBinaryStream* src, iTJSDispatch2** dic);

    struct GraphicLoadingContext
    {
        void*                           formatdata;
        void*                         callbackdata;
        SizeCallback                 sizecallback_;
        ScanLineCallback         scanlinecallback_;
        MetaInfoPushCallback metainfopushcallback_;
        union
        {
            tTJSBinaryStream*                  src;
            tTJSBinaryStream*               stream;
        };
        tjs_int32                           keyidx;
        LoadMode                              mode;

        inline auto sizecallback(tjs_uint w, tjs_uint h, PixelFormat fmt) const noexcept -> int
        {
            return this->sizecallback_(this->callbackdata, w, h, fmt);
        }

        inline auto scanlinecallback(tjs_int y) const noexcept -> void*
        {
            return this->scanlinecallback_(this->callbackdata, y);
        }

        inline auto metainfopushcallback(const ttstr& name, const ttstr& value) const noexcept -> void
        {
            this->metainfopushcallback_(this->callbackdata, name, value);
        }
    };

    struct GraphicSaveContext
    {
        void*              formatdata;
        union
        {
            tTJSBinaryStream*    dst;
            tTJSBinaryStream* stream;
        };
        NativeBaseBitmap*      image;
        const ttstr&            mode;
        iTJSDispatch2*          meta;
    };

    struct GraphicHeaderLoadingContext
    {
        void*               formatdata;
        union
        {
            tTJSBinaryStream*     src;
            tTJSBinaryStream*  stream;
        };
        union
        {
            iTJSDispatch2**      dic;
            iTJSDispatch2** dispatch;
        };
    };

    struct GraphicAcceptSaveContext
    {
        void*             formatdata;
        const ttstr&            type;
        union
        {
            iTJSDispatch2**      dic;
            iTJSDispatch2** dispatch;
        };
    };

    using LoadingHandlerWrapperCallback = void(*)(const GraphicLoadingContext& context);
    using SaveHandlerWrapperCallback    = void(*)(const GraphicSaveContext&    context);
    using HeaderLoadingHandlerWrapperCallback  = void(*)(const GraphicHeaderLoadingContext& context);
    using AcceptSaveHandlerWrapperCallback     = void(*)(const GraphicAcceptSaveContext&    context);

    template<LoadingHandlerWrapperCallback callback = nullptr>
    struct LoadingHandlerWrapper
    {
        [[gnu::noinline]]
        static auto Call
        (
            void* formatdata, void* callbackdata, SizeCallback sizecallback, ScanLineCallback scanlinecallback,
            MetaInfoPushCallback metainfopushcallback, tTJSBinaryStream* src, tjs_int32 keyidx, LoadMode mode
        )   noexcept -> void
        {
            if constexpr (callback != nullptr)
            {
                const GraphicLoadingContext context
                {

                    .formatdata            = formatdata,
                    .callbackdata          = callbackdata,
                    .sizecallback_         = sizecallback,
                    .scanlinecallback_     = scanlinecallback,
                    .metainfopushcallback_ = metainfopushcallback,
                    .src                   = src,
                    .keyidx                = keyidx,
                    .mode                  = mode,
                };
                callback(context);
            }
        }
    };

    template<SaveHandlerWrapperCallback callback = nullptr>
    struct SaveHandlerWrapper
    {
        [[gnu::noinline]]
        static auto Call(void* formatdata, tTJSBinaryStream* dst,  NativeBaseBitmap* image, const ttstr& mode,
                         iTJSDispatch2*  meta)  noexcept -> void
        {
            if constexpr (callback != nullptr)
            {
                const GraphicSaveContext context
                {
                    .formatdata = formatdata,
                    .dst        = dst,
                    .image      = image,
                    .mode       = mode,
                    .meta       = meta
                };
                callback(context);
            }
        }
    };

    template<HeaderLoadingHandlerWrapperCallback callback = nullptr>
    struct HeaderLoadingHandlerWrapper
    {
        [[gnu::noinline]]
        static auto Call(void* formatdata, tTJSBinaryStream* src, iTJSDispatch2** dic) noexcept -> void
        {
            if constexpr (callback != nullptr)
            {
                const GraphicHeaderLoadingContext context
                {
                    .formatdata = formatdata,
                    .src        = src,
                    .dic        = dic
                };
                callback(context);
            }
        }
    };

    template<AcceptSaveHandlerWrapperCallback callback>
    struct AcceptSaveHandlerWrapper
    {
        [[gnu::noinline]]
        static auto Call(void* formatdata, const ttstr& type, iTJSDispatch2** dic) noexcept -> void
        {
            if constexpr (callback != nullptr)
            {
                const GraphicAcceptSaveContext context
                {
                    .formatdata = formatdata,
                    .type       = type,
                    .dic        = dic
                };
                callback(context);
            }
        }
    };

    struct HandlerType
    {
        bool                      IsPlugin;
        TJS::ttstr               Extension;
        LoadingHandler         LoadHandler;
        HeaderLoadingHandler HeaderHandler;
        SaveHandler            SaveHandler;
        AcceptSaveHandler    AcceptHandler;
        void*                   FormatData;
        auto operator == (const HandlerType& ref) const noexcept -> bool;
    };

    struct GraphicType
    {
        tTJSHashTable<ttstr, HandlerType> Hash;
        std::vector<HandlerType>      Handlers;

        auto ReCreateHash() noexcept -> void;
        auto     Register(const HandlerType& hander) noexcept -> void;
        auto   Unregister(const HandlerType& hander) noexcept -> void;
    };

}

namespace TVP::Graphic
{
    using namespace kr2android::tvp::graphic;
};