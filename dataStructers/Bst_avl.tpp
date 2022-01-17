#include "Bst_avl.h"
#include <vector>
#include <deque>

using namespace MyDSTRS;

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::insert(T&& value)
{
    std::vector<std::unique_ptr<TreeNode<T>>*> path;

    if(height)
        path.reserve(height);

    path.push_back(&_root);

    while(path.back()->get())
    {
        auto* top = (*path.back()).get();

        if(value < top->value)
            path.push_back(&top->lhsPtr);
        else if(value > top->value)
            path.push_back(&top->rhsPtr);
        else
            return;
    }

    (*path.back()) = std::make_unique<TreeNode<T>>(std::forward<T>(value));

    for(int64_t i{static_cast<int64_t>(path.size()) - 1}; i > 0;)
    {
        auto* prevTopPtr = path[i];
        auto* prevTop = prevTopPtr->get();
        --i;

        auto* top = path[i]->get();
        if(top->lhsPtr.get() == prevTop)
            ++top->lhsLevels;
        else
            ++top->rhsLevels;

        auto wage = top->wage();

        if(!wage)
            break;

        if(wage == 2)
        {
            if(prevTop->wage() == -1)
                LRotation(prevTopPtr);

            RRotation(path[i]);
            AdjustWages(path[i]->get());
            break;
        }
        else if(wage == -2)
        {
            if(prevTop->wage() == 1)
                RRotation(prevTopPtr);

            LRotation(path[i]);
            AdjustWages(path[i]->get());
            break;
        }
    }

    if(path.size() > height)
        height = path.size();
}



template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
bool AVLTree<T>::find(const T& value) const
{
    const auto* ptr = _root.get();

    while(ptr)
    {
        if(ptr->value > value)
            ptr = ptr->lhsPtr.get();
        else if(ptr->value < value)
            ptr = ptr->rhsPtr.get();
        else
            return true;
    }

    return false;
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
bool AVLTree<T>::erase(const T& value)
{
    std::vector<std::unique_ptr<TreeNode<T>>*> path;

    if(height)
        path.reserve(height);

    path.push_back(&_root);

    bool exists{false};
    while(path.back()->get())
    {
        auto* topPtr = (*path.back()).get();

        if(value < topPtr->value)
            path.push_back(&topPtr->lhsPtr);
        else if(value > topPtr->value)
            path.push_back(&topPtr->rhsPtr);
        else
        {
            if(topPtr->lhsPtr)
            {
                auto* rmNodePtrPtr = path.back();

                path.push_back(&topPtr->lhsPtr);

                auto rememberLhsIndex = path.size() - 1;

                while(path.back()->get())
                    path.push_back(&path.back()->get()->rhsPtr);
                path.pop_back();

                ///lhs poprzednika moze istniec lub nie, odlacza sie poprzednika
                ///ptr do poprzednika wskazuje potem na lewego a poprzednik na samego siebie
                auto* predecessorPtrPtr = &path.back()->get()->lhsPtr;
                path.back()->swap(*predecessorPtrPtr);
                auto* predecessorPtr = predecessorPtrPtr->get();

                ///zamiana poprzednika z el. do us., poprzednik wskazuje na usuwany
                ///ptr wskazujacy na us. wskazuje na poprz.
                rmNodePtrPtr->swap(*predecessorPtrPtr);

                ///przekazanie synow poprzednikowi, kopia wartosci
                auto* rmNodePtr = predecessorPtrPtr->get();
                rmNodePtr->rhsPtr.swap(predecessorPtr->rhsPtr); /// prawy us. = null, pop.r = syn prawy
                rmNodePtr->lhsPtr.swap(predecessorPtr->lhsPtr); /// prawy us. = us., pop.l = syn l
                predecessorPtr->lhsLevels = rmNodePtr->lhsLevels;
                predecessorPtr->rhsLevels = rmNodePtr->rhsLevels;
                rmNodePtr->lhsPtr.release(); ///lewy wskaznik usuwanego wskazuje na usuwanego

                path[rememberLhsIndex] = &predecessorPtr->lhsPtr;
            }
            else if(topPtr->rhsPtr)
                (*path.back()) = std::move(topPtr->rhsPtr);
            else
                path.back()->release();

            exists = true;
            break;
        }
    }

    if(!exists)
        return false;

    for(int64_t i{static_cast<int64_t>(path.size()) - 1}; i > 0;)
    {
        auto* prevTopPtr = path[i];
        --i;

        auto* top = path[i]->get();
        if(&top->lhsPtr == prevTopPtr)
            --top->lhsLevels;
        else
            --top->rhsLevels;

        auto wage = top->wage();

        if(wage == 1 || wage == -1)
            break;

        if(wage == 2)
        {
            if(top->lhsPtr->wage() == -1)
                LRotation(&top->lhsPtr);

            RRotation(path[i]);
            AdjustWages(path[i]->get());
        }
        else if(wage == -2)
        {
            if(top->rhsPtr->wage() == 1)
                RRotation(&top->rhsPtr);

            LRotation(path[i]);
            AdjustWages(path[i]->get());
        }
    }

    return true;
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::LRotation(std::unique_ptr<TreeNode<T>>* daddyPtrPtr)
{
    auto* daddyPtr = (*daddyPtrPtr).get();
    auto* newDaddy = daddyPtr->rhsPtr.get();

    /// podpiecie lewego podrzewa nowego ojca do ojca->rhs + nowy ojciec->lhs wskazuje na nowy ojciec
    daddyPtr->rhsPtr.swap(newDaddy->lhsPtr);
    /// nowyojciec->lhs = stary ojciec, ptr stary ojciec = nowy ojciec
    newDaddy->lhsPtr.swap(*daddyPtrPtr); ///
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::RRotation(std::unique_ptr<TreeNode<T>> *daddyPtrPtr)
{
    auto* daddyPtr = (*daddyPtrPtr).get();
    auto* newDaddy = daddyPtr->lhsPtr.get();

    /// podpiecie prawego podrzewa nowego ojca do ojca->lhs + nowy ojciec->rhs wskazuje na nowy ojciec
    daddyPtr->lhsPtr.swap(newDaddy->rhsPtr);
    /// nowyojciec->rhs = stary ojciec, ptr stary ojciec = nowy ojciec
    newDaddy->rhsPtr.swap(*daddyPtrPtr);
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::AdjustWages(TreeNode<T>* newDaddyPtr)
{
    auto* lhsSon = newDaddyPtr->lhsPtr.get();
    if(lhsSon)
    {
        auto* lhsSonSon = lhsSon->lhsPtr.get();
        auto* rhsSonSon = lhsSon->rhsPtr.get();

        lhsSon->lhsLevels = lhsSonSon ? std::max(lhsSonSon->lhsLevels, lhsSonSon->rhsLevels) + 1 : 0;
        lhsSon->rhsLevels = rhsSonSon ? std::max(rhsSonSon->lhsLevels, rhsSonSon->rhsLevels) + 1 : 0;
    }

    auto* rhsSon = newDaddyPtr->rhsPtr.get();
    if(rhsSon)
    {
        auto* lhsSonSon = rhsSon->lhsPtr.get();
        auto* rhsSonSon = rhsSon->rhsPtr.get();

        rhsSon->lhsLevels = lhsSonSon ? std::max(lhsSonSon->lhsLevels, lhsSonSon->rhsLevels) + 1 : 0;
        rhsSon->rhsLevels = rhsSonSon ? std::max(rhsSonSon->lhsLevels, rhsSonSon->rhsLevels) + 1 : 0;
    }

    newDaddyPtr->lhsLevels = lhsSon ? std::max(lhsSon->lhsLevels, lhsSon->rhsLevels) + 1 : 0;
    newDaddyPtr->rhsLevels = rhsSon ? std::max(rhsSon->lhsLevels, rhsSon->rhsLevels) + 1 : 0;
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
template<typename U>
requires utils::same_as<T, U> && utils::has_ostream<U>
void AVLTree<T>::Print() const
{
    std::deque<TreeNode<U>*> nodes;
    nodes.push_back(_root.get());

    int32_t level = -1;
    bool onlyNulls = false;
    uint32_t i=1;
    while(!nodes.empty())
    {
        if(static_cast<int32_t>(std::log2(i)) > level)
        {
            if(onlyNulls)
                break;

            level = static_cast<int32_t>(std::log2(i));
            fmt::print("\n");

            onlyNulls = true;
        }

        if(nodes.front())
        {
            onlyNulls = false;
            fmt::print("{}. {}({}) | ", i - 1, nodes.front()->value, nodes.front()->wage());

            nodes.push_back(nodes.front()->lhsPtr.get());
            nodes.push_back(nodes.front()->rhsPtr.get());
        }
        else
        {
            fmt::print("{}. null(-) | ", i - 1);

            nodes.push_back(nullptr);
            nodes.push_back(nullptr);
        }

        nodes.pop_front();
        i++;
    }
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> &&  utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
template<typename U>
requires utils::same_as<T, U> && utils::is_semblable_startsWith<U>
uint64_t AVLTree<T>::countAllStartingWith(const U& value) const
{
    const auto* ptr = _root.get();

    while(ptr)
    {
        if(ptr->value.starts_with(value))
            break;
        else if(ptr->value > value)
            ptr = ptr->lhsPtr.get();
        else if(ptr->value < value)
            ptr = ptr->rhsPtr.get();
    }

    if(!ptr)
        return 0;

    struct recursiveFindLeft
    {
        explicit recursiveFindLeft(const T& value) :
                value(value) {}

        void operator()(const TreeNode<T>* ptr)
        {
            if(!ptr)
                return;

            if(ptr->value.starts_with(value))
            {
                ++count;
                (*this)(ptr->lhsPtr.get());
            }

            (*this)(ptr->rhsPtr.get());
        }

        const T& value;
        uint64_t count{0};
    };


    struct recursiveFindRight
    {
        explicit recursiveFindRight(const T& value) :
                value(value) {}

        void operator()(const TreeNode<T>* ptr)
        {
            if(!ptr)
                return;

            if(ptr->value.starts_with(value))
            {
                ++count;
                (*this)(ptr->rhsPtr.get());
            }

            (*this)(ptr->lhsPtr.get());
        }

        const T& value;
        uint64_t count{0};
    };

    recursiveFindLeft leftCount(value);
    leftCount(ptr->lhsPtr.get());

    recursiveFindRight rightCount(value);
    rightCount(ptr->rhsPtr.get());

    return 1 + leftCount.count + rightCount.count;
}

