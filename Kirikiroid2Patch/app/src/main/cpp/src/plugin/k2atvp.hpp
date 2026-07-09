#pragma once
#include <tjs.h>
#include <k2atvp_graphic.hpp>
#include <k2atvp_storage.hpp>
#include <variant>
#define unitype_name(type, name1, name2) union{ type name1; type name2; };

namespace kr2android::tvp
{

    namespace system
    {
        extern auto        get_dir() noexcept -> const ttstr*;
        extern auto get_native_dir() noexcept -> const ttstr*;

        extern auto base_path() noexcept -> ttstr;
        extern auto  app_path() noexcept -> ttstr;
    }
    namespace sys = system;

    namespace storage
    {
        struct media_manager
        {
            static auto get() noexcept -> storage::StorageMediaManager*;
        };

        extern auto   register_media(storage::iStorageMedia* media) noexcept -> bool;
        extern auto unregister_media(storage::iStorageMedia* media) noexcept -> bool;

        extern auto   clear_caches() noexcept -> bool;
        extern auto normalize_name(const ttstr& name) noexcept -> std::optional<ttstr>;

        extern auto              is_existent_no_search(const ttstr& name) noexcept -> std::optional<bool>;
        extern auto is_existent_no_search_no_normalize(const ttstr& name) noexcept -> std::optional<bool>;

        extern auto  set_current_directory(const ttstr& directory) noexcept -> bool;

        extern auto    add_auto_path(const ttstr& path) noexcept -> bool;
        extern auto remove_auto_path(const ttstr& path) noexcept -> bool;
        extern auto  get_placed_path(const ttstr& path) noexcept -> std::optional<ttstr>;
        extern auto      is_existent(const ttstr& path) noexcept -> std::optional<bool>;

        extern auto get_local_name(const ttstr& name) noexcept -> std::optional<ttstr>;

        extern auto  extract_ext(const ttstr& name) noexcept -> ttstr;
        extern auto extract_name(const ttstr& name) noexcept -> ttstr;
        extern auto extract_path(const ttstr& name) noexcept -> ttstr;
        extern auto     chop_ext(const ttstr& name) noexcept -> ttstr;
    }

    namespace xp3
    {
        #pragma pack(push, 4)
        struct ExtractionFilterInfo
        {
            // structure size of ExtractionFilterInfo itself
            unitype_name(const tjs_uint,   SizeOfSelf{ sizeof(ExtractionFilterInfo) }, sizeofself);
            unitype_name(const tjs_uint64, Offset,     offset    ); // offset of the buffer data in uncompressed stream position
            unitype_name(void*,            Buffer,     buffer    ); // target data buffer
            unitype_name(const tjs_uint,   BufferSize, buffersize); // buffer size in bytes pointed by "Buffer"
            unitype_name(const tjs_uint32, FileHash,   filehash  ); // hash value of the file (since inteface v2)
            unitype_name(crefttstr,        FileName,   filename  );
        };
        #pragma pack(pop)

        using ExtractionFilterType = void   (*)(ExtractionFilterInfo *info, tTJSVariant *ctx);
        using    ContentFilterType = tjs_int(*)(const ttstr &filepath, const ttstr &archivename, tjs_uint64 filesize, tTJSVariant *ctx);
        using extraction_filter_t  = ExtractionFilterType;
        using    content_filter_t  = ContentFilterType;

        auto    get_content_filter() noexcept -> content_filter_t;
        auto get_extraction_filter() noexcept -> extraction_filter_t;

        auto    set_content_filter(content_filter_t    filter) noexcept -> bool;
        auto set_extraction_filter(extraction_filter_t filter) noexcept -> bool;
    }

    namespace graphic
    {
        struct type
        {
            static auto get() noexcept -> graphic::GraphicType*;
        };
        extern auto   register_loading_handler(const graphic::HandlerType& handler) noexcept -> bool;
        extern auto unregister_loading_handler(const graphic::HandlerType& handler) noexcept -> bool;
        extern auto clear_cache() noexcept -> bool;
    }

    namespace stream
    {
        extern auto    create_text_for_read(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*;
        extern auto   create_text_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*;
        extern auto  create_binary_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;
        extern auto create_binary_for_write(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;
    }

    namespace scripts
    {

        extern auto   get_engine() noexcept -> tTJS*;
        extern auto get_dispatch(bool addref = false) noexcept -> iTJSDispatch2*;

        extern auto  dump_engine(std::string_view name, bool global) noexcept -> bool;
        extern auto  dump_engine(std::string_view name) noexcept -> bool;
        extern auto  dump_engine(bool global) noexcept -> bool;
        extern auto  dump_engine() noexcept -> bool;

        extern auto execute(const ttstr& content, tTJSVariant* result) noexcept -> bool;
        extern auto execute(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;
        extern auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool;
        extern auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto execexpr(const ttstr& content, tTJSVariant* result) noexcept -> bool;
        extern auto execexpr(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;
        extern auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool;
        extern auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto load(const ttstr& name, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool;
        extern auto load(const ttstr& name, iTJSDispatch2* context, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool;
        extern auto loadbytes(const tjs_uint8* content, size_t length, iTJSDispatch2* context, tTJSVariant* result, const tjs_char* name) noexcept -> bool;

        namespace global
        {
            extern auto get(bool addref = false) noexcept -> iTJSDispatch2*;
            extern auto register_object(const tjs_char* name, iTJSDispatch2* dsp) noexcept -> bool;
            extern auto remove_object  (const tjs_char* name) noexcept -> bool;
        }

        extern auto get_text_encoding() noexcept -> std::optional<ttstr>;
        extern auto set_text_encoding(const ttstr& name) noexcept -> bool;
    }

    namespace events
    {
        struct event
        {
            enum flag_t: tjs_uint32
            {
                ept_post		= 0x00,
                ept_remove_post	= 0x01,
                ept_immediate	= 0x02,
                ept_discardable	= 0x10,
                ept_normal		= 0x00,
                ept_exclusive	= 0x20,
                ept_idle		= 0x40,
                ept_prio_mask	= 0xE0,
                ept_method_mask	= 0x00,
                EPT_POST		= 0x00,
                EPT_REMOVE_POST	= 0x01,
                EPT_IMMEDIATE	= 0x02,
                EPT_DISCARDABLE	= 0x10,
                EPT_NORMAL		= 0x00,
                EPT_EXCLUSIVE	= 0x20,
                EPT_IDLE		= 0x40,
                EPT_PRIO_MASK	= 0xE0,
                EPT_METHOD_MASK	= 0x00,
            };

            unitype_name(iTJSDispatch2*, Source,    source   );
            unitype_name(iTJSDispatch2*, Target,    target   );
            unitype_name(crefttstr,      EventName, eventname);
            unitype_name(tjs_uint32,     Tag,       tag      );
            unitype_name(tjs_uint32,     Flag,      flag     );
            unitype_name(tjs_uint,       NumArgs,   numargs  );
            unitype_name(tTJSVariant*,   Args,      args     );
        };

        struct event_base
        {
            unitype_name(iTJSDispatch2*, Source,    source   );
            unitype_name(iTJSDispatch2*, Target,    target   );
            unitype_name(crefttstr,      EventName, eventname);
            unitype_name(tjs_uint32,     Tag,       tag      );
        };

        class uniref_event
        {
            const void* ptr;

        public:

            inline uniref_event(const event_base& e) noexcept : ptr{ &e }{};
            inline uniref_event(const event&      e) noexcept : ptr{ &e }{};
            inline auto operator->() const noexcept -> const event_base*
            {
                return reinterpret_cast<const event_base*>(this->ptr);
            }
        };

        extern auto      post(const event&       e) noexcept -> bool;
        extern auto  in_queue(const uniref_event e) noexcept -> std::optional<bool>;
        extern auto get_count(const uniref_event e) noexcept -> std::optional<tjs_int>;

        extern auto cancel(const uniref_event e) noexcept -> std::optional<tjs_int>;

        extern auto cancel_tag(iTJSDispatch2* source, iTJSDispatch2* target, tjs_uint32 tag)
               noexcept -> std::optional<tjs_int>;

        extern auto cancel_source(iTJSDispatch2* source) noexcept -> std::optional<tjs_int>;

        extern auto create_object(const tjs_char* type, iTJSDispatch2* targthis, iTJSDispatch2* targ)
               noexcept -> std::optional<iTJSDispatch2*>;

        struct ContinuousCallback
        {
            virtual void TJS_INTF_METHOD OnContinuousCallback(tjs_uint64 tick) = 0;
        };

        struct CompactCallback
        {
            enum level: tjs_int
            {
                level_idle       = 5,
                level_deactivate = 10,
                level_minimize   = 15,
                level_max        = 100,
                LEVEL_IDLE       = 5,
                LEVEL_DEACTIVATE = 10,
                LEVEL_MINIMIZE   = 15,
                LEVEL_MAX        = 100,
            };

            using Level = level;
            virtual void TJS_INTF_METHOD OnCompact(Level level) = 0;
        };

        using compact_callback    = CompactCallback;
        using continuous_callback = ContinuousCallback;

        extern auto    add_continuous_hook(const continuous_callback* hook) noexcept -> bool;
        extern auto remove_continuous_hook(const continuous_callback* hook) noexcept -> bool;
        extern auto       add_compact_hook(const compact_callback*    hook) noexcept -> bool;
        extern auto    remove_compact_hook(const compact_callback*    hook) noexcept -> bool;

        extern auto set_system_disabled_state(bool state) noexcept -> bool;
        extern auto get_system_disabled_state() noexcept -> std::optional<bool>;
    }

    using event               = events::event;
    using event_base          = events::event_base;
    using continuous_callback = events::ContinuousCallback;
    using CompactLevel        = events::CompactCallback::Level;
    using compact_level       = events::CompactCallback::Level;
    using compact_callback    = events::CompactCallback;

    namespace sound
    {
        struct WaveFormat
        {
            unitype_name(tjs_uint,   SamplesPerSec,  samplespersec ); // sample granule per sec
            unitype_name(tjs_uint,   Channels,       channels      );
            unitype_name(tjs_uint,   BitsPerSample,  bitspersample ); // per one sample
            unitype_name(tjs_uint,   BytesPerSample, bytespersample); // per one sample
            unitype_name(tjs_uint64, TotalSamples,   totalsamples  ); // in sample granule; unknown for zero
            unitype_name(tjs_uint64, TotalTime,      totaltime     ); // in ms; unknown for zero
            unitype_name(tjs_uint32, SpeakerConfig,  speakerconfig ); // bitwise OR of SPEAKER_* constants
            unitype_name(bool,       IsFloat,        isfloat       ); // true if the data is IEEE floating point
            unitype_name(bool,       Seekable,       seekable      );
        };
        using wave_format = WaveFormat;

        namespace pcm
        {
            extern auto to_16bits(tjs_int16* output, const void* input, const wave_format& format, tjs_int count,
                        bool downmix) noexcept -> bool;
            extern auto to_16bits(tjs_int16* output, const void* input, tjs_int channels, tjs_int bytespersample,
                 tjs_int bitspersample, bool isfloat, tjs_int count, bool downmix) noexcept -> bool;

            extern auto to_float(float* output, const void* input, const wave_format& format, tjs_int count) noexcept -> bool;
            extern auto to_float(float* output, const void* input, tjs_int channels, tjs_int bytespersample,
                        tjs_int bitspersample, bool isfloat, tjs_int count) noexcept -> bool;
        }
    }

    namespace pcm = sound::pcm;
    using WaveFormat  = sound::WaveFormat;
    using wave_format = sound::wave_format;

    extern auto           log(const ttstr& line, bool appendtoimportant = false) noexcept -> bool;
    extern auto important_log(const ttstr& line) noexcept -> bool;

    extern auto inputbox(ttstr& text, const ttstr& caption) noexcept -> std::optional<bool>;
    extern auto inputbox(ttstr& text, const ttstr& caption, const ttstr& prompt) noexcept -> std::optional<bool>;
    extern auto inputbox(ttstr& text, const ttstr& caption, const ttstr& prompt, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>;
    extern auto inputbox(ttstr& text, const ttstr& caption, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>;

    extern auto messagebox(const ttstr& text, const ttstr& caption) noexcept -> std::optional<bool>;
    extern auto messagebox(const ttstr& text, const ttstr& caption, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>;

    extern auto        get_about_string() noexcept -> std::optional<ttstr>;
    extern auto      get_version_string() noexcept -> std::optional<ttstr>;
    extern auto get_version_information() noexcept -> std::optional<ttstr>;

    extern auto     get_tjs_version(tjs_int& major, tjs_int& minor, tjs_int& release) noexcept -> void;
    extern auto  get_system_version(tjs_int& major, tjs_int& minor, tjs_int& release, tjs_int& build) noexcept -> bool;

    extern auto get_random_bits128(void* dest) noexcept -> bool;
    extern auto push_environ_noise(const void* buf, const tjs_int bufsize) noexcept -> bool;

    extern auto set_command_line(const tjs_char* name, const ttstr& value) noexcept -> bool;
    extern auto get_command_line(const tjs_char* name, tTJSVariant* value) noexcept -> std::optional<bool>;
    extern auto get_command_line_argument_generation() noexcept -> std::optional<tjs_int>;

    extern auto get_tick_count() noexcept -> std::optional<tjs_uint64>;
}

#undef unitype_name
