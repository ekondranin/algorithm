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
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair <int, int> PII;
typedef pair <LL, LL> PLL;
const int MOD = 1000000007;
S Sync_stdio { Sync_stdio() { cin.tie(NULL); ios_base::sync_with_stdio(false); } } _sync_stdio;
S FAIL { FAIL () { cout << "CHANGE!!!" << endl;}};



//! better use unsigned types for T
//! for MinXor insert ~elem
template<class T>
class MinMaxXor
{
  public:
    MinMaxXor() {}

    MinMaxXor(initializer_list<T> elements): elements(elements) {}

    template<class InputIterator>
    MinMaxXor(InputIterator begin, InputIterator end): elements(begin, end) {}

    void insert(T value)
    {
        elements.insert(value);
    }

    T calc_max_xor_best(T value)
    {
        T current = 0;
        for (int j = bits_count() - 1; j >= 0; --j) {
            T shift = (1ULL << j);
            if (value & shift) {
                if (elements.upper_bound(current + 1 * shift - 1) == elements.lower_bound(current + 0 * shift)) {
                    current |= shift;
                } else {
                    current |= 0;
                }
            } else {
                if (elements.upper_bound(current + 2 * (shift - 1) + 1) == elements.lower_bound(current + 1 * shift)) {
                    current |= 0;
                } else {
                    current |= shift;
                }
            }
        }
        return current;
    }

    T calc_min_xor_best(T value)
    {
        T current = 0;
        for (int j = bits_count() - 1; j >= 0; --j) {
            T shift = (1ULL << j);
            if (value & shift) {
                if (elements.upper_bound(current + 2 * (shift - 1) + 1) == elements.lower_bound(current + 1 * shift)) {
                    current |= 0;
                } else {
                    current |= shift;
                }
            } else {
                if (elements.upper_bound(current + 1 * shift - 1) == elements.lower_bound(current + 0 * shift)) {
                    current |= shift;
                } else {
                    current |= 0;
                }
            }
        }
        return current;
    }

    void erase(T value)
    {
        elements.erase(elements.find(value));
    }

  private:
    constexpr int bits_count() {
        return __builtin_clzll((unsigned long long)std::numeric_limits<T>::max());
    }

    multiset<T> elements;
};

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> a(n);
    GET(v, n);
    GET(a, n);
    MinMaxXor<unsigned> max_xor = {a.begin(), a.end()};
    FOR (i, 0, n) {
        unsigned ans = max_xor.calc_min_xor_best(v[i]);
        max_xor.erase(ans);
        cout << (v[i] ^ ans) << " ";
    }
}
