#pragma once
#include <optional>
#include <tjs.h>
#include <tjsUtils.h>
#include <tjsHashSearch.h>


namespace kr2android::tvp::storage
{
    struct iStorageLister // callback class for GetListAt
    {
        virtual auto Add(const ttstr& file) -> void = 0;
    };

    struct iStorageMedia
    {
        virtual ~iStorageMedia() {}
        virtual auto TJS_INTF_METHOD                   AddRef() ->  void = 0;
        virtual auto TJS_INTF_METHOD                  Release() ->  void = 0;
        virtual auto TJS_INTF_METHOD                  GetName(ttstr& name) -> void = 0;
        virtual auto TJS_INTF_METHOD      NormalizeDomainName(ttstr& name) -> void = 0;
        virtual auto TJS_INTF_METHOD        NormalizePathName(ttstr& name) -> void = 0;
        virtual auto TJS_INTF_METHOD     CheckExistentStorage(const ttstr& name) -> bool = 0;
        virtual auto TJS_INTF_METHOD                     Open(const ttstr& name, tjs_uint32 flags) -> tTJSBinaryStream* = 0;
        virtual auto TJS_INTF_METHOD                GetListAt(const ttstr& name, iStorageLister* lister) -> void = 0;
        virtual auto TJS_INTF_METHOD GetLocallyAccessibleName(ttstr &name) -> void = 0;
    };

    struct MediaNameString : public tTJSString
    {
        auto operator == (const MediaNameString &rhs) const noexcept -> bool;
    };

    struct HashFunc
    {
        static auto Make(const MediaNameString &key) noexcept -> tjs_uint32;
    };

    struct MediaRecord
    {
        ttstr                       CurrentDomain;
        ttstr                         CurrentPath;
        tTJSRefHolder<iStorageMedia>    MediaIntf;
        tjs_int                      MediaNameLen;

        MediaRecord(iStorageMedia *media) noexcept;
        auto GetDomainAndPath(const ttstr &name) noexcept -> const tjs_char*;
    };

    struct StorageMediaManager
    {
        tTJSHashTable<MediaNameString, MediaRecord, HashFunc, 16> HashTable;
        auto   Register(iStorageMedia* media) noexcept -> bool;
        auto Unregister(iStorageMedia* media) noexcept -> void;
        auto Open(const ttstr& name, tjs_uint32 flags) noexcept -> tTJSBinaryStream*;

        auto      SetCurrentDirectory(const ttstr &directory) noexcept -> bool;
        auto     NormalizeStorageName(const ttstr& name, ttstr* ret_media = {}, ttstr *ret_domain ={}, ttstr *ret_path ={}) noexcept -> std::optional<ttstr>;
        auto GetLocallyAccessibleName(const ttstr& name) noexcept -> std::optional<ttstr>;
    };
}

namespace TVP::Storage
{
    using namespace kr2android::tvp::storage;
}