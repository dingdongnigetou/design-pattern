template<typename Func>
class Events
{
public:
    Events():m_nextKey(0)
    {}
    ~Events(){}
    
    int Connect(Func&& f)
    {
        return assgin(f);
    }

    int Connect(Func& f)
    {
        return assgin(f);
    }
    
    void Disconnect(int key)
    {
        m_connections.erase(key);
    }
 
    template<typename... Args>
    void Notify(Args&&... args)
    {
        for (auto& it: m_connections) {
            it.second(std::forward<Args>(args)...);
        }
    }
 
private:

    template<typename F>
    int assgin(F&& f)
    {
        int k=m_nextKey++;
        m_connections[k]=f;
        return k;
    }
    
    int m_nextKey;
    std::map<int, Func> m_connections;
}; 
