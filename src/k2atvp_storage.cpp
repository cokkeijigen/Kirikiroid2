#include <k2atvp_storage.hpp>
#include <kr2android.hpp>

namespace kr2android::tvp::storage
{

    auto MediaNameString::operator==(const MediaNameString &rhs) const noexcept -> bool
    {
        const tjs_char * l_p = c_str();
        const tjs_char * r_p = rhs.c_str();

        while(*l_p && *r_p)
        {
            if(*l_p == TJS_W(':')) break;
            if(*r_p == TJS_W(':')) break;
            if(*l_p != *r_p) break;
            l_p++;
            r_p++;
        }
        if((*l_p == TJS_W(':') || *l_p == 0) &&
           (*r_p == TJS_W(':') || *r_p == 0)) return true;
        return false;
    }

    auto HashFunc::Make(const MediaNameString &key) noexcept -> tjs_uint32
    {
        if(key.IsEmpty()) return 0;
        const tjs_char *str = key.c_str();
        tjs_uint32 ret = 0;
        while(*str && *str != ':')
        {
            ret += *str;
            ret += (ret << 10);
            ret ^= (ret >> 6);
            str++;
        }
        ret += (ret << 3);
        ret ^= (ret >> 11);
        ret += (ret << 15);
        if(!ret) ret = (tjs_uint32)-1;
        return ret;
    }

    MediaRecord::MediaRecord(iStorageMedia *media) noexcept: MediaIntf{ media }, CurrentDomain{ "." }, CurrentPath{ "/" }
    {
    }

    auto MediaRecord::GetDomainAndPath(const ttstr &name) noexcept -> const tjs_char*
    {
        return name.c_str() + MediaNameLen + 3;
    }

    auto StorageMediaManager::Register(iStorageMedia* media) noexcept -> bool
    {
        ttstr medianame{};
        media->GetName(medianame);

        if(medianame.IsEmpty())
        {
            return false;
        }

        MediaRecord *rec = this->HashTable.Find(*(MediaNameString*)&medianame);
        if(rec != nullptr)
        {
            return false;
        }

        MediaRecord new_rec{ media };
        this->HashTable.Add(*(MediaNameString*)&medianame, new_rec);
        return true;
    }

    auto StorageMediaManager::Unregister(iStorageMedia* media) noexcept -> void
    {
        ttstr medianame;
        media->GetName(medianame);

        MediaRecord *rec =  this->HashTable.Find(*(MediaNameString*)&medianame);
        if(rec != nullptr)
        {
            this->HashTable.Delete(*(MediaNameString*)&medianame);
        }
    }

    auto StorageMediaManager::Open(const ttstr & name, tjs_uint32 flags) noexcept -> tTJSBinaryStream*
    {
        MediaRecord* rec =  this->HashTable.Find(*(MediaNameString*)&name);
        if(rec == nullptr)
        {
            return rec->MediaIntf.GetObjectNoAddRef()->Open(rec->GetDomainAndPath(name), flags);
        }
        return nullptr;
    }

    auto StorageMediaManager::SetCurrentDirectory(const TJS::ttstr &directory) noexcept -> bool
    {
        struct Wrapper : StorageMediaManager
        {
            auto SetCurrentDirectory(const TJS::ttstr&) noexcept -> void;
        };

        static decltype(&Wrapper::SetCurrentDirectory) _ptr{};
        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::StorageMediaManager::SetCurrentDirectory);
        }

        if(_ptr != nullptr)
        {
            const auto wrapper { reinterpret_cast<Wrapper*>(this) };
            return (wrapper->*_ptr)(directory), true;
        }

        return false;
    }

    auto StorageMediaManager::NormalizeStorageName(const ttstr& name, ttstr* ret_media, ttstr *ret_domain, ttstr *ret_path) noexcept -> std::optional<ttstr>
    {
        struct Wrapper : StorageMediaManager
        {
            auto NormalizeStorageName(const ttstr&, ttstr*, ttstr*, ttstr*) noexcept -> ttstr;
        };

        static decltype(&Wrapper::NormalizeStorageName) _ptr{};
        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::StorageMediaManager::NormalizeStorageName);
        }

        if(_ptr != nullptr)
        {
            const auto wrapper { reinterpret_cast<Wrapper*>(this) };
            return (wrapper->*_ptr)(name, nullptr, nullptr, nullptr);
        }
        return std::nullopt;
    }

    auto StorageMediaManager::GetLocallyAccessibleName(const ttstr& name) noexcept -> std::optional<ttstr>
    {
        struct Wrapper : StorageMediaManager
        {
            auto GetLocallyAccessibleName(const ttstr&) noexcept -> ttstr;
        };

        static decltype(&Wrapper::GetLocallyAccessibleName) _ptr{};
        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::StorageMediaManager::GetLocallyAccessibleName);
        }

        if(_ptr != nullptr)
        {
            const auto wrapper { reinterpret_cast<Wrapper*>(this) };
            return (wrapper->*_ptr)(name);
        }

        return std::nullopt;
    }

}