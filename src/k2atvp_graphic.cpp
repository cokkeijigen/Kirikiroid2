#include <k2atvp_graphic.hpp>

namespace kr2android::tvp::graphic
{
    auto HandlerType::operator==(const HandlerType & ref) const noexcept -> bool
    {
        return bool
        {
                this->FormatData    == ref.FormatData    &&
                this->IsPlugin      == ref.IsPlugin      &&
                this->LoadHandler   == ref.LoadHandler   &&
                this->HeaderHandler == ref.HeaderHandler &&
                this->SaveHandler   == ref.SaveHandler   &&
                this->AcceptHandler == ref.AcceptHandler &&
                this->Extension     == ref.Extension
       };
    }
    auto GraphicType::ReCreateHash() noexcept -> void
    {
        for(auto i = this->Handlers.begin(); i!= this->Handlers.end(); i++)
        {
            this->Hash.Add(i->Extension, *i);
        }
    }

    auto GraphicType::Register(const HandlerType& hander ) noexcept -> void
    {
        this->Handlers.push_back(hander);
        this->ReCreateHash();
    }

    auto GraphicType::Unregister(const HandlerType& hander ) noexcept -> void
    {
        if(this->Handlers.empty())
        {
            return;
        }

        for(auto i = this->Handlers.begin(); i != this->Handlers.end(); i++)
        {
            if(hander == *i)
            {
                this->Handlers.erase(i);
                break;
            }
        }
        this->ReCreateHash();
    }

}