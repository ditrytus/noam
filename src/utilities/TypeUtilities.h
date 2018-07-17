#pragma once


namespace noam::utils {

    template<typename TBase, typename UDerived>
    bool isInstanceOf(TBase* obj) {
        return dynamic_cast<UDerived*>(obj) != nullptr;
    };

}