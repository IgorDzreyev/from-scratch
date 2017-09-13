
#include <exception>
#include <typeinfo>
#include <type_traits>

class bad_any_cast : public std::bad_cast {
    const char *what() const noexcept override { return "bad_any_cast"; }
};

template<class T, class DT = std::decay_t<T>>
T any_cast(const any& a) {
    static_assert(std::is_constructible_v<T, const DT&>, "bad any_cast");
    if (a.has_value() && a.type() == typeid(DT)) {
        return static_cast<T>(*a.target<DT>());
    }
    throw bad_any_cast{};
}

template<class T, class DT = std::decay_t<T>>
T any_cast(any& a) {
    static_assert(std::is_constructible_v<T, DT&>, "bad any_cast");
    if (a.has_value() && a.type() == typeid(DT)) {
        return static_cast<T>(*a.target<DT>());
    }
    throw bad_any_cast{};
}

template<class T, class DT = std::decay_t<T>>
T any_cast(any&& a) {
    static_assert(std::is_constructible_v<T, DT>, "bad any_cast");
    if (a.has_value() && a.type() == typeid(DT)) {
        return static_cast<T>(*a.target<DT>());
    }
    throw bad_any_cast{};
}

template<class T>
const T *any_cast(const any *a) {
    if (a->has_value() && a->type() == typeid(T)) {
        return static_cast<const T *>(a->target<T>());
    }
    return nullptr;
}

template<class T>
T *any_cast(any *a) {
    if (a->has_value() && a->type() == typeid(T)) {
        return static_cast<T *>(a->target<T>());
    }
    return nullptr;
}
