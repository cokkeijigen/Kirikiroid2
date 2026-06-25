#pragma once
#include <tjs.h>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>

namespace TJS
{
    class TJSDumpFileOutput : public iTJSConsoleOutput
    {
        std::u16string m_buffer{};
        std::ofstream      m_out{};

    public:

        ~TJSDumpFileOutput() noexcept;
        TJSDumpFileOutput () noexcept{};
        TJSDumpFileOutput (const std::filesystem::path& path) noexcept;

        virtual void ExceptionPrint(const tjs_char* msg) override;
        virtual void          Print(const tjs_char* msg) override;

        auto Close() noexcept -> void;
        auto Open (const std::filesystem::path& path) noexcept -> bool;

        inline auto IsOpen() noexcept -> bool { return this->m_out.is_open(); }

    private:
        auto Write() noexcept -> void;
    };
}