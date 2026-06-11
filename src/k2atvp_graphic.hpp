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

    using ScanLineCallback        = void*(*)(void* callbackdata, tjs_int y);
    using SizeCallback            = int  (*)(void* callbackdata, tjs_uint w, tjs_uint h, PixelFormat fmt);
    using MetaInfoPushCallback    = void (*)(void* callbackdata, const ttstr& name, const ttstr& value);
    using LoadingHandler          = void (*)
    (
            void* formatdata, void* callbackdata, SizeCallback sizecallback, ScanLineCallback scanlinecallback,
            MetaInfoPushCallback metainfopushcallback, tTJSBinaryStream* src, tjs_int32 keyidx, LoadMode mode
    );

    using AcceptSaveHandler    = bool (*)(void* formatdata, const ttstr& type, iTJSDispatch2** dic);
    using SaveHandler          = void (*)(void* formatdata, tTJSBinaryStream* dst, class iTVPBaseBitmap* image, const ttstr& mode, iTJSDispatch2* meta);
    using HeaderLoadingHandler = void (*)(void* formatdata, tTJSBinaryStream* src, iTJSDispatch2** dic);

    struct HandlerType
    {
        bool                 IsPlugin;
        TJS::ttstr           Extension;
        LoadingHandler       LoadHandler;
        HeaderLoadingHandler HeaderHandler;
        SaveHandler          SaveHandler;
        AcceptSaveHandler    AcceptHandler;
        void*                FormatData;

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