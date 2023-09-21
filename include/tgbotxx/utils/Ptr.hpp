#pragma once
#include <memory>

namespace tgbotxx {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using CPtr = const std::shared_ptr<T>;

    template<typename T>
    using PtrC = std::shared_ptr<const T>;

    template<typename T>
    using CPtrC = const std::shared_ptr<const T>;


    template<typename T>
    struct isPtr : std::false_type {};
    template<typename T>
    struct isPtr<Ptr<T>> : std::true_type {};
    template<typename T>
    struct isPtr<CPtr<T>> : std::true_type {};
    template<typename T>
    struct isPtr<PtrC<T>> : std::true_type {};
    template<typename T>
    struct isPtr<CPtrC<T>> : std::true_type {};

}