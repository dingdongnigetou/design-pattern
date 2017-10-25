
// 正常的observer模式会有一个observer的基类，所有的观察者均需继承这个基类
// 我们消除这层继承，面向函数注册观察者，观察者无需继承只需join一个触发的方法即可

#include <map>

template<typename Func>
class events
{
public:
    events(){}
    ~events(){}
    
    int join(Func&& f)
    {
        return assgin_(f);
    }

    int join(Func& f)
    {
        return assgin_(f);
    }
    
    void depatch(int key)
    {
        connections_.erase(key);
    }

	void clear()
	{
		next_key_ = 0;
		connections_.clear();
	}
 
    template<typename... Args>
    void notify(Args&&... args)
    {
        for (auto& it: connections_) {
            it.second(std::forward<Args>(args)...);
        }
    }
 
private:

    template<typename F>
    int assgin_(F&& f)
    {
        int k=next_key_++;
        connections_[k]=f;
        return k;
    }
    
    int next_key_ = 0;
    std::map<int, Func> connections_;
}; 

