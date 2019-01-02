//
// Created by koncord on 08.12.18.
//

#pragma once

#include <Script/Language.hpp>
#include <Script/SystemInterface.hpp>
#include <unordered_map>
#include <mono/metadata/object.h>
#include <boost/variant.hpp>


typedef boost::variant<unsigned int, signed int, unsigned long long, signed long long, double, void*> TMonoArgVariant;
typedef std::vector<TMonoArgVariant> TMonoArgsStore;

template<typename T>
void *MonoStoreAndGetPtr(TMonoArgsStore &argsStore, va_list &vargs, size_t index)
{
    argsStore[index] = va_arg(vargs, T);
    return (void *) &boost::get<T&>(argsStore[index]);
}

template<typename T>
void *MonoStoreAndGetPtr(TMonoArgsStore &argsStore, const std::vector<boost::any> &args, size_t index)
{
    argsStore[index] = boost::any_cast<T>(args.at(index));
    return (void *) &boost::get<T&>(argsStore[index]);
}

struct MethodKey
{
    inline bool operator==(const MethodKey &other) const
    {
        return other.paramsCnt == paramsCnt && other.name == name;
    }

    MethodKey(const std::string &name, int paramsCnt): name(name), paramsCnt(paramsCnt)
    {
    }

    std::string name;
    int paramsCnt;
};


namespace std
{
    template<>
    struct hash<MethodKey>
    {
        std::size_t operator()(const MethodKey &key) const
        {
            return hash<string>()(key.name)
                   ^ (hash<uint32_t>()(key.paramsCnt) >> 1);
        }
    };
}

struct MonoInstance
{
    MonoObject *object;
    MonoClass *klass;
    MonoAssembly *assembly;
    MonoImage *image;
};

class LangMono: public Language
{
    MonoInstance *instance;
    std::unordered_map<MethodKey, MonoMethod *> methodsCache;
public:
    virtual lib_t GetInterface() override;
    LangMono();
    LangMono(MonoInstance *instance);
    ~LangMono();
    virtual void LoadProgram(const char *filename) override;
    virtual int FreeProgram() override;
    virtual bool IsCallbackPresent(const char *name) override;
    virtual boost::any Call(const char *name, const char *argl, int buf, ...) override;
    virtual boost::any Call(const char *name, const char *argl, const std::vector<boost::any> &args) override;

    static int CreateTimerEx(MonoObject *delegate, long msec, MonoString *monoStr, MonoArray *args);
    static void MakePublic(MonoObject *delegate, MonoString *name) noexcept;
    static MonoObject *CallPublic(MonoString *name, MonoArray *args);

    static void Init();
    static void Free();

    template<typename T>
    static T Unbox(MonoObject *obj)
    {
        return *(T *) mono_object_unbox(obj);
    }

    template<typename T>
    static  void ObjectSetValue(MonoObject *obj, T value)
    {
        *(T*) mono_object_unbox(obj) = value;
    }

    static boost::any ObjectToAny(MonoObject *obj);
    static MonoObject *AnyToObject(boost::any any, char ret_type);
};
