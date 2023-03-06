#include <iostream>
#include <vector>

using namespace std;

template<typename V>
class Dictionary {
private:
    vector<pair<int, V>> container;
    int size = 0;

public:
    Dictionary();
    Dictionary(int size);

    ~Dictionary();

    int hash(int k, int i);

    bool insert(int key, V value);
    bool remove(int key);

    typename vector<pair<int, V>>::iterator search(int key) const;

    void print() const;

    typename vector<pair<int, V>>::iterator begin() const;
    typename vector<pair<int, V>>::iterator end() const;

};


template<typename V>
Dictionary<V>::Dictionary() {}

template<typename V>
Dictionary<V>::~Dictionary() {}

template<typename V>
Dictionary<V>::Dictionary(int size) {

    for (int i = 0; i < size; ++i) {
        container.push_back({-1, V()});
    }
}


template<typename V>
int Dictionary<V>::hash(int k, int i) {

    int m = container.size();

    int hash1 = k % m;
    int hash2 = i * (1 + (k % (m - 1)));

    return (hash1 + hash2) % m;
}


template<typename V>
bool Dictionary<V>::insert(int key, V value) {
    if (size < container.size()) {
        int i = 0;

        while (true) {
            int x = hash(key, i);

            if (container[x].first == -1) {
                container[x].first = key;
                container[x].second = value;

                ++size;

                return true;
            }
            else if (container[x].first == key) {
                container[x].second = value;

                return true;
            }

            ++i;
        }
    }
    else {
        return false;
    }
}

template<typename V>
bool Dictionary<V>::remove(int key) {
    int i = 0;

    while (true) {
        int x = hash(key, i);

        if (container[x].first == -1) {
            return false;
        }
        else if (container[x].first == key) {
            container[x].first = -1;
            container[x].second = V();

            return true;
        }

        i++;
    }
}

template<typename V>
typename vector<pair<int, V>>::iterator Dictionary<V>::search(int key) const {
    int i = 0;

    while (true) {
        int x = hash(key, i);

        if (container[x].first == -1) {
            return container.end();
        } else if (container[x].first == key) {
            return container.begin() + x;
        }

        ++i;
    }
}


template<typename V>
void Dictionary<V>::print() const {
    for (pair<int, V> p : container) {
        if (p.first == -1) {
            cout << "nil ";
        }
        else {
            cout << "K:" << p.first << " V:" << p.second << " ";
        }
    }

    cout << endl;
}


template<typename V>
typename vector<pair<int, V>>::iterator Dictionary<V>::begin() const {
    return container.begin();
}

template<typename V>
typename vector<pair<int, V>>::iterator Dictionary<V>::end() const {
    return container.end();
}


int main()
{
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    Dictionary<float> dictionary(19);

    for (int i = 0; i < 10; ++i)
        cin >> keys[i];

    for (int i = 0; i < 10; ++i)
        dictionary.insert(keys[i], values[i]);

    dictionary.remove(keys[6]);
    dictionary.insert(keys[2], 1.1);
    dictionary.print();

    return 0;
}