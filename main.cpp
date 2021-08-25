#include <cstdlib>
#include <type_traits>

struct my_type{};

struct stream{
    virtual ~stream() = default;
protected:
    void write(my_type t){}
};


struct stream_helper : public stream
{
    void write(my_type t){
        stream::write(t);
    }
};


template <typename, typename = void>
struct has_stream_write : std::false_type {};

template <typename T>
struct has_stream_write<T, decltype(std::declval<stream_helper>().write(std::declval<T>()))> : std::true_type {};

int main()
{
    static_assert(has_stream_write<my_type>::value, "stream has no public write member");
    return EXIT_SUCCESS;
}