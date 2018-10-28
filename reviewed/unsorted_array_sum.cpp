#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

std::pair<int, int>
solution(const std::vector<int> &a, int sum)
{
    if (a.size() < 2)
        return std::make_pair(-1, -1);
   
    std::unordered_map<int,int> m;
    m.emplace(a[0], 0);
    for (auto i = 1; i < a.size(); i++ )
    {
        auto it = m.find(sum - a[i]);
        if (it != m.end())
            return std::make_pair(it->second, i);
        m[a[i]] = i;
    }
    return std::make_pair(-1, -1);
}


int main()
{
    std::vector<int> test = {2, 7, 11,15};
    int sum = 9;
    auto ret = solution(test, sum);
    if (ret.first < 0 || ret.second < 0)
    {
        std::cout << "()";
        return 0;
    }
    std::cout << "(" << test[ret.first] << "," << test[ret.second] << ")";
}
