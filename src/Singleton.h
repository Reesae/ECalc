#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace core {

template<typename T>
class Singleton {
  public:
    static auto getInstance() -> T &{
      static T inst;
      return inst;
    }

  private:
    friend T;
    Singleton() = default;
    virtual ~Singleton() = default;

};

} /* namespace core */

#endif /* SINGLETON_H_ */
