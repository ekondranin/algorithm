#include <bits/stdc++.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif // M_PI
#define endl "\n"
#define S struct
#define X first
#define Y second
#define V vector
#ifndef __linux__
#define LLD "%I64d"
#else
#define LLD "%ll""d"
#endif
#define FOR(x, y, z) for (int x = (y); x < (z); ++x)
#define FORR(x, y, z) for (int x = (y); x > (z); --x)
#define GET(a, n) for (int __i = 0; __i < (n); ++__i) cin >> a[__i];
#define GETM(a, n, m) for (int __i = 0; __i < (n); ++__i) for (int __j = 0; __j < m; ++__j) cin >> a[__i][__j];
#define PRINTM(a, n, m) for (int __i = 0; __i < (n); ++__i) { for (int __j = 0; __j < m; ++__j) cout << a[__i][__j] << " ";  cout << endl; };
#define PRINT(a, n) for (int __i = 0; __i < (n); ++__i) cout << a[__i] << " ";
#define IT(a) a.begin(), a.end()
#define SQR(x) (x) * (x)
#define CASE(a, s) cout << "Case #" << a << ": " << s << endl;
#define DEB(a) cout << #a << " = " << (a) << endl; cout.flush();
#define DEBA(a) for (auto __i: a) cout << __i << " "; cout << endl; cout.flush();
#define IFDEB(b, a) if (b) { cout << #a << " = " << (a) << endl; cout.flush(); }
#define YESNO(cond) cout << ((cond) ? "Yes" : "No") << endl;
#define UMAX(left, right) left = max(left, right);
#define UMIN(left, right) left = min(left, right);
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair <int, int> PII;
typedef pair <LL, LL> PLL;
const int MOD = 1000000007;
void yes() { cout << "Yes" << endl;}
void no() { cout << "No" << endl;}
S Sync_stdio { Sync_stdio() { cin.tie(NULL); ios_base::sync_with_stdio(false); } } _sync_stdio;
S FAIL { FAIL () { cout << "CHANGE!!!" << endl;}};

template<class T, int ALPHA_SIZE>
class TrieNode {
  public:
    TrieNode(T value): value(value) {}

    const TrieNode *get_transition(T value) const
    {
        return next[value].get();
    }

    TrieNode *get_transition(T value)
    {
        return next[value].get();
    }

    TrieNode *go_transition(T value, int weight)
    {
        next[value]->counter += weight;
        return next[value].get();
    }

    bool is_transition(T value) const
    {
        return next[value] != nullptr && next[value]->counter > 0;
    }

    void add_transition(T value)
    {
        next[value] = unique_ptr<TrieNode>(new TrieNode(value));
    }

    vector<const TrieNode *> get_transitions() const
    {
        vector<const TrieNode *> res;
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            if (is_transition(i)) {
                res.push_back(next[i].get());
            }
        }
        return res;
    }

  private:
    T value;
    int counter = 0;
    array<unique_ptr<TrieNode>, ALPHA_SIZE> next;
};

template<class T, int ALPHA_SIZE>
class Trie
{
  public:
    typedef TrieNode<T, ALPHA_SIZE> * TrieNodePtr;

    explicit Trie(T min_value)
        : root(new TrieNode<T, ALPHA_SIZE>(0))
        , min_value(min_value)
    {
    }

    template<class InputIterator>
    void add(InputIterator begin, InputIterator end)
    {
        go_tree(begin, end, 1);
    }

    template<class InputIterator>
    void remove(InputIterator begin, InputIterator end)
    {
        go_tree(begin, end, -1);
    }

    TrieNodePtr get_root() const
    {
        return root.get();
    }

  private:
    TrieNodePtr go_symbol(TrieNodePtr node_ptr, T value, int weight)
    {
        if (!node_ptr->is_transition(value)) {
            node_ptr->add_transition(value);
        }
        return node_ptr->go_transition(value, weight);
    }

    template<class InputIterator>
    void go_tree(InputIterator begin, InputIterator end, int weight)
    {
        TrieNodePtr node_ptr = root.get();
        while (begin != end) {
            node_ptr = go_symbol(node_ptr, *begin - min_value, weight);
            ++begin;
        }
    }

    unique_ptr<TrieNode<T, ALPHA_SIZE>> root;
    T min_value;
};

//! better use unsigned types for T
template<class T>
class MinMaxXor
{
  public:
    MinMaxXor(): trie('0') {}

    template<class InputIterator>
    MinMaxXor(InputIterator begin, InputIterator end): trie('0') {
        while (begin != end) {
            insert(*begin);
            ++begin;
        }
    }

    string binarize(T elem)
    {
        string res;
        res.reserve(bits_count());
        for (int j = bits_count() - 1; j >= 0; --j) {
            res.push_back('0' + ((elem >> j) & 1));
        }
        return res;
    }

    void insert(T value)
    {
        string binarized = binarize(value);
        trie.add(IT(binarized));
    }

    T calc_max_xor_best(T value)
    {
        TrieNode<char, 2> *node_ptr = trie.get_root();
        T current = 0;
        for (int j = bits_count() - 1; j >= 0; --j) {
            T shift = (1ULL << j);
            if (value & shift) {
                if (node_ptr->is_transition(0)) {
                    node_ptr = node_ptr->get_transition(0);
                    current |= 0;
                } else {
                    node_ptr = node_ptr->get_transition(1);
                    current |= shift;
                }
            } else {
                if (node_ptr->is_transition(1)) {
                    node_ptr = node_ptr->get_transition(1);
                    current |= shift;
                } else {
                    node_ptr = node_ptr->get_transition(0);
                    current |= 0;
                }
            }
        }
        return current;
    }

    T calc_min_xor_best(T value)
    {
        TrieNode<char, 2> *node_ptr = trie.get_root();
        T current = 0;
        for (int j = bits_count() - 1; j >= 0; --j) {
            T shift = (1ULL << j);
            if (value & shift) {
                if (node_ptr->is_transition(1)) {
                    node_ptr = node_ptr->get_transition(1);
                    current |= shift;
                } else {
                    node_ptr = node_ptr->get_transition(0);
                    current |= 0;
                }
            } else {
                if (node_ptr->is_transition(0)) {
                    node_ptr = node_ptr->get_transition(0);
                    current |= 0;
                } else {
                    node_ptr = node_ptr->get_transition(1);
                    current |= shift;
                }
            }
        }
        return current;
    }

    void erase(T value)
    {
        string binarized = binarize(value);
        trie.remove(IT(binarized));
    }

  private:
    constexpr int bits_count() {
        return __builtin_clzll((unsigned long long)std::numeric_limits<T>::max());
    }

    Trie<char, 2> trie;
};

int main()
{
    int n;
    cin >> n;
    MinMaxXor<unsigned> min_max_xor;
    min_max_xor.insert(0);
    FOR (i, 0, n) {
        string s;
        unsigned x;
        cin >> s >> x;
        if (s == "+") {
            min_max_xor.insert(x);
        } else if (s == "-") {
            min_max_xor.erase(x);
        } else {
            cout << (x ^ min_max_xor.calc_max_xor_best(x)) << endl;
        }
    }
}
