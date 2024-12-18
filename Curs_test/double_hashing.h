#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <stdlib.h>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;

template<class T>
class DoubleHashTable {
    template <class TT>
    struct Node {
        TT obj;
        enum class Type {
            Free, Busy, Removed
        } type;

        Node() : type(Type::Free) {}
        Node(const TT& _obj, Type _type = Type::Free)
            : obj(_obj), type(_type) {
        }
    };

protected:
    function<int(const T&, int m)> m_hash_1;
    function<int(const T&, int m)> m_hash_2;
    function<int(const T&, const T&)> m_is_equal_key;
    vector<Node<T>> m_table;
    const size_t m_size;

public:
    DoubleHashTable(size_t size,
                    function<int(const T&, int m)> hash_1,
                    function<int(const T&, int m)> hash_2,
                    function<int(const T&, const T&)> is_equal_key)
        : m_hash_1(hash_1), m_hash_2(hash_2), m_is_equal_key(is_equal_key), m_size(size) {
        assert(size > 10);
        m_table.resize(m_size);
    }

    bool add(const T& obj) {
        int hash_1 = m_hash_1(obj, m_size);
        int hash_2 = m_hash_2(obj, m_size);
        for (size_t i = 0; i < m_size; ++i) {
            int index = (hash_1 + i * hash_2) % m_size;
            if (m_table[index].type == Node<T>::Type::Free) {
                // Создаем объект Node с правильным типом
                m_table[index] = Node<T>(obj, Node<T>::Type::Busy);
                return true;
            }
        }
        return false;
    }

    bool search(T& obj) {
        int hash_1 = m_hash_1(obj, m_size);
        int hash_2 = m_hash_2(obj, m_size);
        for (size_t i = 0; i < m_size; ++i) {
            int index = (hash_1 + i * hash_2) % m_size;
            if (m_table[index].type == Node<T>::Type::Free) {
                return false;
            }
            if (m_table[index].type == Node<T>::Type::Removed) {
                continue;
            }
            if (m_is_equal_key(obj, m_table[index].obj)) {
                obj = m_table[index].obj;
                return true;
            }
        }
        return false;
    }

};


#endif // DOUBLE_HASHING_H
