#ifndef JAVA_SINGLETON_H_
#define JAVA_SINGLETON_H_

#include <jni.h>

class JavaSingleton {
  friend class DefaultSingletonTraits<JavaSingleton>;
  private:
    JavaSingleton();
    ~JavaSingleton();
  public:
    static JavaSingleton* GetInstance();

    void set_env(JNIEnv* env) { env_ = env; }
    JNIEnv* env() { return env_; }

  private:
    JNIEnv* env_;
    DISALLOW_COPY_AND_ASSIGN(JavaSingleton);
};

#endif