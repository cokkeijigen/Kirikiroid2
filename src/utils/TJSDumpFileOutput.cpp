#include <TJSDumpFileOutput.hpp>
#include <sys/stat.h>

namespace TJS
{

    TJSDumpFileOutput::~TJSDumpFileOutput() noexcept
    {
        this->Close();
    }

    TJSDumpFileOutput::TJSDumpFileOutput(const std::filesystem::path& path) noexcept
    {
        this->Open(path);
    }

    auto TJSDumpFileOutput::Open(const std::filesystem::path& path) noexcept -> bool
    {
        this->Close();

        auto ref_path{ const_cast<std::string&>(path.native()) };
        if(ref_path.empty())
        {
            return;
        }

        const size_t split{ ref_path.find_last_of("\\/") };
        if(split != std::string::npos)
        {
            ref_path[split] = '\0';

            struct stat path_stat{};
            const bool exists{ (::lstat(ref_path.c_str(), &path_stat) == 0) };
            if (!exists || !S_ISDIR(path_stat.st_mode))
            {
                return;
            }
            else if(!exists)
            {
                std::error_code error{};
                if(!std::filesystem::create_directories(path, error) || error)
                {
                    return;
                }
            }

            ref_path[split] = '/';
        }

        this->m_out.open(path, std::ios::out | std::ios::binary);
        if(this->m_out.is_open())
        {
            this->m_out.write("\xFF\xFE", 2);
            return true;
        }

        return false;
    }

    auto TJSDumpFileOutput::Close() noexcept -> void
    {
        if(this->m_out.is_open())
        {
            this->Write();
            this->m_out.close();
        }
    }

    void TJSDumpFileOutput::ExceptionPrint(const tjs_char* msg)
    {
        this->Print(msg);
    }

    void TJSDumpFileOutput::Print(const tjs_char* msg)
    {
        if(!this->m_out.is_open())
        {
            return;
        }

        std::u16string_view line{ msg };
        if(line.empty())
        {
            return;
        }

        if(this->m_buffer.capacity() < line.size())
        {
            this->Write();
            this->m_buffer.reserve(line.size());
        }
        else if(this->m_buffer.size() + line.size() + 1 > m_buffer.capacity())
        {
            this->Write();
        }

        this->m_buffer.append(line).push_back('\n');
    }

    auto TJSDumpFileOutput::Write() noexcept -> void
    {
        if(this->m_buffer.empty())
        {
            return;
        }

        const auto buffer{ reinterpret_cast<const char*>(this->m_buffer.c_str()) };
        const auto length{ this->m_buffer.size() * sizeof(char16_t) };

        this->m_out   .write(buffer, length);
        this->m_buffer.clear();
    }
}
