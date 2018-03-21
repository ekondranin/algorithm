class Dsu {
  public:
    void make_set(int vertex) {
        rank[vertex] = 1;
        parent[vertex] = vertex;
    }
    int find_set(int vertex) {
        if (vertex == parent[vertex]) {
            return vertex;
        }
        return parent[vertex] = find_set(parent[vertex]);
    }
    bool union_sets(int first, int second) {
        first = find_set(first);
        second = find_set(second);
        if (first != second) {
            --comps_count_;
            if (rank[first] < rank[second]) {
               std::swap(first, second);
            }
            parent[second] = first;
            if (rank[first] == rank[second]) {
                ++rank[first];
            }
            return true;
        } else {
            return false;
        }
    }
    vector <int> get_parents() {
        for (int i = 0; i < parent.size(); ++i) {
            find_set(i);
        }
        return parent;
    }
    void init(int numbers_count) {
        comps_count_ = numbers_count;
        rank.resize(numbers_count);
        parent.resize(numbers_count);
        for (int i = 0; i < numbers_count; ++i) {
           make_set(i);
        }
    }
    Dsu(int numbers_count) {
       init(numbers_count);
    }
    Dsu() {
       init(0);
    }
    int size() const {
        return parent.size();
    }
    int comps_count() const {
        return comps_count_;
    }

  private:
    vector <int> parent;
    vector <int> rank;
    int comps_count_;
};
