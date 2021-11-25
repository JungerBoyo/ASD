#include "Bst_avl.h"
#include <stack>

using namespace MyDSTRS;

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::insert(T&& value)
{
    std::stack<std::unique_ptr<TreeNode<T>>*> path;
    path.push(&_root);

    while(path.top()->get())
    {
        auto* top = (*path.top()).get();

        if(value < top->value)
            path.push(&top->lhsPtr);
        else
            path.push(&top->rhsPtr);
    }

    (*path.top()) = std::make_unique<TreeNode<T>>(std::forward<T>(value));

    while(path.size() > 1)
    {
        auto* prevTopPtr = path.top();
        auto* prevTop = prevTopPtr->get();
        path.pop();

        auto* top = path.top()->get();
        if(top->lhsPtr.get() == prevTop)
            ++top->wage;
        else
            --top->wage;

        if(!top->wage)
            break;

        if(top->wage == 2)
        {
            if(prevTop->wage == -1)
                LRotation(prevTopPtr, 1);

            RRotation(path.top(), 0);
            break;
        }
        else if(top->wage == -2)
        {
            if(prevTop->wage == 1)
                RRotation(prevTopPtr, -1);

            LRotation(path.top(), 0);
            break;
        }
    }
}



template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
bool AVLTree<T>::find(const T& value) const
{
    auto* ptr = _root.get();

    while(ptr)
    {
        if(ptr->value < value)
            ptr = ptr->lhsPtr.get();
        else if(ptr->value > value)
            ptr = ptr->rhsPtr.get();
        else
            return true;
    }

    return false;
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
bool AVLTree<T>::erase(const T& value)
{
    std::stack<std::unique_ptr<TreeNode<T>>*> path;
    path.push(&_root);

    bool exists{false};
    while(path.top()->get())
    {
        auto* topPtr = (*path.top()).get();

        if(value < topPtr->value)
            path.push(&topPtr->lhsPtr);
        else if(value > topPtr->value)
            path.push(&topPtr->rhsPtr);
        else
        {
            if(topPtr->lhsPtr)
            {
                auto* rmNodePtrPtr = path.top();

                path.push(&topPtr->lhsPtr);
                std::unique_ptr<TreeNode<T>>** rememberLhs{&path.top()};

                while(path.top()->get())
                    path.push(&path.top()->get()->rhsPtr);
                path.pop();

                auto* predecessorPtrPtr = &path.top()->get()->lhsPtr;
                path.top()->swap(*predecessorPtrPtr);
                auto* predecessorPtr = predecessorPtrPtr->get();

                rmNodePtrPtr->swap(*predecessorPtrPtr);

                auto* rmNodePtr = predecessorPtrPtr->get();
                rmNodePtr->rhsPtr.swap(predecessorPtr->rhsPtr);
                rmNodePtr->lhsPtr.swap(predecessorPtr->lhsPtr);
                predecessorPtr->wage = rmNodePtr->wage;
                rmNodePtr->lhsPtr.release();

                *rememberLhs = &predecessorPtr->lhsPtr;
            }
            else if(topPtr->rhsPtr)
                (*path.top()) = std::move(topPtr->rhsPtr);
            else
                path.top()->release();

            exists = true;
            break;
        }
    }

    if(!exists)
        return false;

    while(path.size() > 1)
    {
        auto* prevTopPtr = path.top();
        auto* prevTop = prevTopPtr->get();
        path.pop();

        auto* top = path.top()->get();
        if(&top->lhsPtr == prevTopPtr)
            --top->wage;
        else
            ++top->wage;

        if((top->wage == 1) || (top->wage == -1))
            break;

        if(top->wage == 2)
        {
            if(prevTop->wage == -1)
                LRotation(prevTopPtr, 1);

            RRotation(path.top(), 0);
        }
        else if(top->wage == -2)
        {
            if(prevTop->wage == 1)
                RRotation(prevTopPtr, -1);

            LRotation(path.top(), 0);
        }
    }

    return exists;
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::LRotation(std::unique_ptr<TreeNode<T>> *daddyPtrPtr, int8_t wage)
{
    auto* rotPassPtr = (*daddyPtrPtr).get();
    auto* newSon = rotPassPtr->rhsPtr.get();

    rotPassPtr->rhsPtr.swap(newSon->lhsPtr);
    newSon->lhsPtr.swap(*daddyPtrPtr);

    newSon->wage = wage;
    rotPassPtr->wage = ((!rotPassPtr->lhsPtr) xor (!rotPassPtr->rhsPtr)) ? 1 : 0;
}

template<typename T>
requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
void AVLTree<T>::RRotation(std::unique_ptr<TreeNode<T>> *daddyPtrPtr, int8_t wage)
{
    auto* rotPassPtr = (*daddyPtrPtr).get();
    auto* newSon = rotPassPtr->lhsPtr.get();

    rotPassPtr->lhsPtr.swap(newSon->rhsPtr);
    newSon->rhsPtr.swap(*daddyPtrPtr);

    newSon->wage = wage;
    rotPassPtr->wage = ((!rotPassPtr->lhsPtr) xor (!rotPassPtr->rhsPtr)) ? -1 : 0;
}
