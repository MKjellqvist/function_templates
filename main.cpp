#include <iostream>

#include<algorithm>
#include <vector>
#include <iterator>
#include <typeinfo>
#include <functional>

/**
 *
 * @tparam ForwardIt ++, *, !=
 * @tparam Comp Kräver defaultkonstruktion
 * @param first
 * @param last
 * @param comp function object to compare orders
 * @return
 */
template<typename ForwardIt, typename Comp = std::less<>>
ForwardIt find_min(ForwardIt first, ForwardIt last, Comp comp = Comp()){
    std::cout << typeid(comp).name() << "\n";
    auto current_min = first;
    for(;first != last; ++first){
        if(comp(*first, *current_min)){
            current_min = first;
        }
    }
    return current_min;
}

template<typename ForwardIt, typename Compare = std::less<>>
void selection_sort(ForwardIt first, ForwardIt last, Compare comp = Compare()){
    while(first != last){
        auto min = find_min(first, last, comp);
        auto temp = *first;
        *first = *min;
        *min = temp;
        first++;
    }
}

struct order{
    std::string name;
    double price;

    struct price_predicate{
        bool operator()(order lhs, order rhs){
            return lhs.price < rhs.price;
        }
    };
};

bool pc_function(order lhs, order rhs){
    return lhs.price < rhs.price;
}
int main() {
    std::vector<std::string> texts = {"martin", "Nitram"};
    std::vector data = {5.0, -2.0, 1.0};
    std::vector<order> orders = {{"Martin", 100.0}, {"Nitram", 99.9}};

    order::price_predicate pc_functor;
    auto pc_lambda = [orders](order lhs, order rhs) {
        return lhs.price < rhs.price;
    };
    std::function<bool(order, order)> pc_std_function = pc_function;

    auto min_order = find_min(orders.begin(), orders.end(), pc_functor);
    if(min_order == orders.end()){
        std::cout << "Not found\n";
    }else{
        std::cout << "Found\n"; // min_order->name << "\n";
    }
    selection_sort(data.begin(), data.end());
    for(auto e:data){
        std::cout << e << ", ";
    }

}
