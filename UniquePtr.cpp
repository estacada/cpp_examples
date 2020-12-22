#include <cstddef>
#include <memory>
#include <tuple>
#include <utility>

template <typename T, typename D = std::default_delete<T>>
class UniquePtr {
private:
    std::tuple<T*, D>pd;
    void del() {
        D& to_del = get_deleter();
        to_del(get());
    }


public:
    UniquePtr() {
        pd = std::make_tuple(nullptr, D());
    }
    UniquePtr(T* x) {
        pd = std::make_tuple(x, D());
    }
    UniquePtr(UniquePtr&& x) {
        pd = x.pd;
        std::get<0>(x.pd) = nullptr;
    }
    UniquePtr(T* x, const D& y) {
        pd = std::make_tuple(x, y);
    }
    UniquePtr& operator=(std::nullptr_t) {
        del();
        std::get<0>(pd) = nullptr;
        return *this;
    }
    UniquePtr& operator=(UniquePtr&& x) {
        if (&x != this) {
            del();
            pd = x.pd;
            std::get<0>(x.pd) = nullptr;
        }
        return *this;
    }
    UniquePtr(UniquePtr& x) = delete;
    UniquePtr& operator=(UniquePtr& x) = delete;
    T& operator*() const noexcept {
        return *get();
    }
    T* operator->() const noexcept {
        return get();
    }
    T* release() noexcept {
        T* x = get();
        std::get<0>(pd) = nullptr;
        return x;
    }
    void reset(T* x = nullptr) noexcept {
        if (get() != x) del();
        std::get<0>(pd) = x;
    }
    void swap(UniquePtr& x) noexcept {
        std::swap(x.pd, pd);
    }
    T* get() const noexcept {
        return std::get<0>(pd);
    }
    explicit operator bool() const noexcept {
        return (get() != nullptr);
    }
    D& get_deleter() noexcept {
        return std::get<1>(pd);
    }
    const D& get_deleter() const noexcept {
        return std::get<1>(pd);
    }
    ~UniquePtr() {
        reset();
    }
};



