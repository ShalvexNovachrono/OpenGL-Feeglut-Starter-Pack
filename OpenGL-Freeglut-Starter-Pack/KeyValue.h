#ifndef KeyValue
#define KeyValue
#include "main.h"
#include "Array.h"

template <typename K, typename V>
struct  Entry {
    K key;
    V value;
    
    bool operator==(const Entry& other) const {
        return key == other.key;
    }
};

template <typename K, typename V>
class CKeyValue {
private:
    CArray<Entry<K, V>> entries;
    
    int GetIndex(K key) const {
        for (int i = 0; i < entries.Size(); i++) {
            if (entries[i].key == key) return i;
        }
        return -1;
    }
    
public:
    CKeyValue() = default;
    
    void Add(K key, V value) {
        entries.Append({ key, value });
    }
    
    void Remove(K key) {
        int index = GetIndex(key);
        if (index != -1) entries.RemoveAt(index);
    }
    
    void Clear() {
        entries.Clear();
    }
    
    V Get(K key) {
        int index = GetIndex(key);
        if (index != -1) return entries[index].value;
        return V();
    }

    V* GetPtr(K key) {
        int index = GetIndex(key);
        if (index != -1) return &entries[index].value;
        return nullptr;
    }
    
    bool Has(K key) {
        return GetIndex(key) != -1;
    }
    
    int GetSize() const {
        return entries.Size();
    }
    
    bool operator==(CKeyValue const& other) const {
        return entries == other.entries;
    }
    
    V& operator[](K key) {
        int index = GetIndex(key);
        if (index == -1) {
            entries.Append({ key, V() });
            index = entries.Size() - 1;
        }
        return entries.GetReference(index).value;
    }
    
    using iterator = typename CArray<Entry<K, V>>::iterator;
    using const_iterator = typename CArray<Entry<K, V>>::const_iterator;

    iterator find(K key) {
        return std::find_if(entries.begin(), entries.end(), [key](Entry<K, V> const& entry) { return entry.key == key; });
    } 
    
    const_iterator find(K key) const {
        return std::find_if(entries.begin(), entries.end(), [key](Entry<K, V> const& entry) { return entry.key == key; });
    }

    iterator begin() {
        return entries.begin();
    }
    
    iterator end() {
        return entries.end();
    }
    
    const_iterator begin() const {
        return entries.begin();
    }

    const_iterator end() const {
        return entries.end();
    }

    CArray<Entry<K, V>>& GetEntries() {
        return entries;
    }

    const CArray<Entry<K, V>>& GetEntries() const {
        return entries;
    }
};

#endif
