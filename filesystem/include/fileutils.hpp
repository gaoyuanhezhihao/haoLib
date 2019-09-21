#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#define DEFINE_HAS_MEMBER(F) \
template <typename T> \
class has_##F \
{\
private:\
    typedef char YesType[1]; \
    typedef char NoType[2]; \
    template <typename C>  \
        static YesType& test( decltype(&C::F) ) ;\
    template <typename C> \
        static NoType& test(...); \
public: \
    enum { value = sizeof(test<T>(0)) == sizeof(YesType) }; \
}; 


DEFINE_HAS_MEMBER(save)
DEFINE_HAS_MEMBER(load)

#define DEFINE_NOT_HAS_MEMBER(F) \
template <typename T> \
class not_has_##F \
{\
private:\
    typedef char YesType[1]; \
    typedef char NoType[2]; \
    template <typename C>  \
        static YesType& test( decltype(&C::F) ) ;\
    template <typename C> \
        static NoType& test(...); \
public: \
    enum { value = sizeof(test<T>(0)) == sizeof(NoType) }; \
};


#define ENABLE_IF_HAS(F, RET) typename std::enable_if<has_##F<T>::value, RET>::type

#define ENABLE_IF_NOT_HAS(F, RET) typename std::enable_if<not_has_##F<T>::value, RET>::type

    DEFINE_NOT_HAS_MEMBER(save)
    DEFINE_NOT_HAS_MEMBER(load)


class FileTools{
    public:
        static std::string join(const std::string & a, const std::string & b) {
            std::string p = a +'/' + b;
            size_t pos = p.find("//");
            //std::cout << "pos=" << pos << std::endl;
            if(pos != std::string::npos) {
                p.replace(pos, 2, "/");
            }
            return p;
        }
        template <class T>
            static void write(std::ostream & out, const T & a)  {
                out.write((const char*)&a, sizeof(T));
            }

        template <class T>
            static void write(std::ostream & out, const std::vector<T> & v) {
                write(out, v.size());
                out.write((const char*)&(v[0]), v.size() * sizeof(T));
            }

        template <class T>
            static void read(std::istream & in, T & a) {
                in.read((char * )&a, sizeof(T));
            }

        template <class T>
            static void read(std::istream & in, std::vector<T> & v) {
                size_t n = 0;
                in.read((char *) &n, sizeof(n));
                v.resize(n);
                in.read((char *) &n, n * sizeof(T));
            }

        template <typename T>
            static ENABLE_IF_NOT_HAS(save, void) save(std::ostream & outf, const std::vector<T> & vec) {
                size_t n = vec.size();
                outf.write((const char *)&n, sizeof(n));
                outf.write((const char *)&vec[0], n * sizeof(T));
            }

        template <class T>
            static ENABLE_IF_HAS(save, void) save(std::ostream& outf, const std::vector<T> & v) {
                size_t n = v.size();
                outf.write((const char *)&n, sizeof(n));
                for(const auto & e: v) {
                    e.save(outf);
                }
            }

        static size_t read_size(std::istream & in) {
            size_t n = -1;
            in.read((char * )&n, sizeof(n));
            return n;
        }

        template <class T>
            static ENABLE_IF_NOT_HAS(load, void) load(std::istream & in, std::vector<T> & v) {
                size_t n = read_size(in);
                v.resize(n);
                in.read((char *)&v[0], n * sizeof(T));
            }

        template <class T>
            static ENABLE_IF_HAS(load, void) load(std::istream & in, std::vector<T> & v) {
                size_t n  = read_size(in);
                v.resize(n);
                for(size_t i = 0; i < n; ++i) {
                    v[i].load(in);
                }
            }
};





#endif //FILEUTILS_H
