#include "java_singleton.h"

JavaSingleton::JavaSingleton() 
    : env_(NULL) {
}

JavaSingleton::~JavaSingleton() {

}

JavaSingleton* JavaSingleton::GetInstance() {
    return Singleton<JavaSingleton>().get();
}