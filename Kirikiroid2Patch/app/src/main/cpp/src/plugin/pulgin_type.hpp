#pragma once
#include <functional>
#include <kr2android.hpp>
#include <k2atvp.hpp>

namespace TVP
{

//    #pragma pack(push, 4)
//    struct tTVPXP3ExtractionFilterInfo
//    {
//        const tjs_uint SizeOfSelf; // structure size of tTVPXP3ExtractionFilterInfo itself
//        const tjs_uint64 Offset; // offset of the buffer data in uncompressed stream position
//        void * Buffer; // target data buffer
//        const tjs_uint BufferSize; // buffer size in bytes pointed by "Buffer"
//        const tjs_uint32 FileHash; // hash value of the file (since inteface v2)
//        const ttstr &FileName;
//
//        inline tTVPXP3ExtractionFilterInfo(tjs_uint64 offset, void *buffer, tjs_uint buffersize, tjs_uint32 filehash, const ttstr& filename)
//        : Offset(offset), Buffer(buffer), BufferSize(buffersize), FileHash(filehash), FileName(filename), SizeOfSelf(sizeof(tTVPXP3ExtractionFilterInfo)) {;}
//
//    };
//    #pragma pack(pop)

//    typedef void (*tTVPXP3ArchiveExtractionFilter)(tTVPXP3ExtractionFilterInfo *info, tTJSVariant *ctx);
//
//    typedef tjs_int(*tTVPXP3ArchiveContentFilter)(const ttstr &filepath, const ttstr &archivename, tjs_uint64 filesize, tTJSVariant *ctx);



    /*]*/
    //---------------------------------------------------------------------------

    /*[*/
    //---------------------------------------------------------------------------
    // data types for TVPDoTryBlock
    //---------------------------------------------------------------------------
    // TVPDoTryBlock executes specified 'tryblock' in try block.
    // If any exception occured,
    // 'catchblock' is to be executed. 'data' is applicatoin defined data
    // block passed to 'tryblock' and 'catchblock' and 'finallyblock'.
    // if the 'catchblock' returns true, the exception is to be rethrown.
    // if false then the exception is to be vanished.
    // 'finallyblock' can be null, is to be executed whatever the exception
    // is generated or not.

    struct tTVPExceptionDesc
    {
        ttstr type; // the exception type, currently 'eTJS' or 'unknown'
        ttstr message; // the exception message (if exists. otherwise empty).
    };

    typedef void (TJS_USERENTRY *tTVPTryBlockFunction)(void * data);
    typedef bool (TJS_USERENTRY *tTVPCatchBlockFunction)(void * data, const tTVPExceptionDesc & desc);
    typedef void (TJS_USERENTRY *tTVPFinallyBlockFunction)(void *data);
    //---------------------------------------------------------------------------

    enum tTVPClipboardFormat
    {
        cbfText = 1
    };

    enum tTVPGraphicPixelFormat
    {
        gpfLuminance,
        gpfPalette,
        gpfRGB,
        gpfRGBA
    };

    /*[*/
    //---------------------------------------------------------------------------
    // Graphic Loading Handler Type
    //---------------------------------------------------------------------------
    typedef int (*tTVPGraphicSizeCallback) // return line pitch
            (void *callbackdata, tjs_uint w, tjs_uint h, tTVPGraphicPixelFormat fmt);
    /*
        callback type to inform the image's size.
        call this once before TVPGraphicScanLineCallback.
    */

    typedef void * (*tTVPGraphicScanLineCallback)
            (void *callbackdata, tjs_int y);
    /*
        callback type to ask the scanline buffer for the decoded image, per a line.
        returning null can stop the processing.

        passing of y=-1 notifies the scan line image had been written to the buffer that
        was given by previous calling of TVPGraphicScanLineCallback. in this time,
        this callback function must return NULL.
    */

    typedef const void * (*tTVPGraphicSaveScanLineCallback)
            (void *callbackdata, tjs_int y);

    typedef void (*tTVPMetaInfoPushCallback)
            (void *callbackdata, const ttstr & name, const ttstr & value);
    /*
        callback type to push meta-information of the image.
        this can be null.
    */

    enum tTVPGraphicLoadMode
    {
        glmNormal, // normal, ie. 32bit ARGB graphic
        glmPalettized, // palettized 8bit mode
        glmGrayscale // grayscale 8bit mode
    };
    /*]*/

    /*[*/
    /* For grahpic load and save */
    typedef void (*tTVPGraphicLoadingHandlerForPlugin)(void* formatdata,
                                                       void *callbackdata,
                                                       tTVPGraphicSizeCallback sizecallback,
                                                       tTVPGraphicScanLineCallback scanlinecallback,
                                                       tTVPMetaInfoPushCallback metainfopushcallback,
                                                       struct IStream *src,
                                                       tjs_int32 keyidx,
                                                       tTVPGraphicLoadMode mode);
    typedef void (*tTVPGraphicHeaderLoadingHandlerForPlugin)(void* formatdata, struct IStream* src, class iTJSDispatch2** dic );
    typedef void (*tTVPGraphicSaveHandlerForPlugin)(void* formatdata, void* callbackdata, struct IStream* dst, const ttstr & mode,
                                                    tjs_uint width, tjs_uint height,
                                                    tTVPGraphicSaveScanLineCallback scanlinecallback,
                                                    class iTJSDispatch2* meta );
    /*]*/

    typedef bool (*tTVPGraphicAcceptSaveHandler)(void* formatdata, const ttstr & type, class iTJSDispatch2** dic );

    //---------------------------------------------------------------------------
    // iTVPScanLineProvider
    //---------------------------------------------------------------------------
    // provides layer scanline
    class iTVPTexture2D;
    class iTVPScanLineProvider
    {
    public:
        virtual tjs_error TJS_INTF_METHOD AddRef() = 0;
        virtual tjs_error TJS_INTF_METHOD Release() = 0;
        // call "Release" when done with this object
        virtual tjs_error TJS_INTF_METHOD GetWidth(/*out*/tjs_int *width) = 0;
        // return image width
        virtual tjs_error TJS_INTF_METHOD GetHeight(/*out*/tjs_int *height) = 0;
        // return image height
        virtual iTVPTexture2D * GetTexture() = 0;
        virtual iTVPTexture2D * GetTextureForRender() = 0;
    };
    //---------------------------------------------------------------------------


    //---------------------------------------------------------------------------
    // iTVPSimpleOptionProvider
    //---------------------------------------------------------------------------
    // provides option set
    class iTVPSimpleOptionProvider
    {
    public:
        virtual tjs_error TJS_INTF_METHOD AddRef() = 0;
        virtual tjs_error TJS_INTF_METHOD Release() = 0;
        // call this when done with this object

        virtual tjs_error TJS_INTF_METHOD GetAsNumber(
                /*in*/const tjs_char *name, /*out*/tjs_int64 *value) = 0;
        // retrieve option as a number.
        virtual tjs_error TJS_INTF_METHOD GetAsString(
                /*in*/const tjs_char *name, /*out*/const tjs_char **out) = 0;
        // retrieve option as a string.
        // note that you must use the returned string as an one time string
        // pointer; you cannot hold its pointer and/or use it later.

        virtual tjs_error TJS_INTF_METHOD GetValue(
                /*in*/const tjs_char *name, /*out*/tTJSVariant *dest) = 0;
        // retrieve option as a tTJSVariant.

        virtual tjs_error TJS_INTF_METHOD Reserved2() = 0;

        virtual tjs_error TJS_INTF_METHOD GetDispatchObject(iTJSDispatch2 **dsp)
        = 0;
        // retrieve internal dispatch object ( if exists )
    };
    //---------------------------------------------------------------------------


    //---------------------------------------------------------------------------
    // iTVPSimpleImageProvider
    //---------------------------------------------------------------------------
    // image loader
    class iTVPSimpleImageProvider
    {
    public:
        virtual tjs_error TJS_INTF_METHOD LoadImage(
                /*in*/const tjs_char *name, /*in*/tjs_int bpp,
                /*in*/tjs_uint32 key,
                /*in*/tjs_uint w,
                /*in*/tjs_uint h,
                /*out*/iTVPScanLineProvider ** scpro) = 0;
        // load an image.
        // returned image be an 8bpp bitmap when bpp == 8, otherwise
        // 32bpp.
        // key is a color key. pass 0x02ffffff for not to apply color key.
        // you must release "scpro" when you done with it.
        // w and h are desired size of the image. if the actual size is smaller
        // than these, the image is to be tiled. give 0, 0 to obtain original
        // sized image.
    };
    //---------------------------------------------------------------------------

    /*[*/
    //---------------------------------------------------------------------------
    // layer / blending types
    //---------------------------------------------------------------------------
    enum tTVPLayerType
    {
        ltBinder = 0,
        ltCoverRect = 1,
        ltOpaque = 1, // the same as ltCoverRect
        ltTransparent = 2, // alpha blend
        ltAlpha = 2, // the same as ltTransparent
        ltAdditive = 3,
        ltSubtractive = 4,
        ltMultiplicative = 5,
        ltEffect = 6,
        ltFilter = 7,
        ltDodge = 8,
        ltDarken = 9,
        ltLighten = 10,
        ltScreen = 11,
        ltAddAlpha = 12, // additive alpha blend
        ltPsNormal = 13,
        ltPsAdditive = 14,
        ltPsSubtractive = 15,
        ltPsMultiplicative = 16,
        ltPsScreen = 17,
        ltPsOverlay = 18,
        ltPsHardLight = 19,
        ltPsSoftLight = 20,
        ltPsColorDodge = 21,
        ltPsColorDodge5 = 22,
        ltPsColorBurn = 23,
        ltPsLighten = 24,
        ltPsDarken = 25,
        ltPsDifference = 26,
        ltPsDifference5 = 27,
        ltPsExclusion = 28
    };
    //---------------------------------------------------------------------------
    enum tTVPTransType
    {
        ttSimple, // transition using only one(self) layer ( eg. simple fading )
        ttExchange // transition using two layer ( eg. cross fading )
    };
    enum tTVPTransUpdateType
    {
        tutDivisibleFade,
        tutDivisible,
        tutGiveUpdate
    };
    class iTVPBaseTransHandler
    {
    public:
        virtual tjs_error TJS_INTF_METHOD AddRef() = 0;
        virtual tjs_error TJS_INTF_METHOD Release() = 0;

        virtual tjs_error TJS_INTF_METHOD SetOption(
                /*in*/iTVPSimpleOptionProvider *options // option provider
        ) = 0;
        // Set option for current processing transition
    };
    //---------------------------------------------------------------------------
    // iTVPTransHandlerProvider
    //---------------------------------------------------------------------------
    // transition handler provider abstract class
    class iTVPTransHandlerProvider
    {
    public:
        virtual ~iTVPTransHandlerProvider() {} // add by ZeaS
        virtual tjs_error TJS_INTF_METHOD AddRef() = 0;
        virtual tjs_error TJS_INTF_METHOD Release() = 0;

        virtual tjs_error TJS_INTF_METHOD GetName(
                /*out*/const tjs_char ** name) = 0;
        // return this transition name

        virtual tjs_error TJS_INTF_METHOD StartTransition(
                /*in*/iTVPSimpleOptionProvider *options, // option provider
                /*in*/iTVPSimpleImageProvider *imagepro, // image provider
                /*in*/tTVPLayerType layertype, // destination layer type
                /*in*/tjs_uint src1w, tjs_uint src1h, // source 1 size
                /*in*/tjs_uint src2w, tjs_uint src2h, // source 2 size
                /*out*/tTVPTransType *type, // transition type
                /*out*/tTVPTransUpdateType * updatetype, // update typwe
                /*out*/iTVPBaseTransHandler ** handler // transition handler
        ) = 0;
        // start transition and return a handler.
        // "handler" is an object of iTVPDivisibleTransHandler when
        // updatetype is tutDivisibleFade or tutDivisible.
        // Otherwise is an object of iTVPGiveUpdateTransHandler ( cast to
        // each class to use it )
        // layertype is the destination layer type.
    };
    //---------------------------------------------------------------------------
    /*]*/

}