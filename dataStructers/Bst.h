#ifndef ASD_PS_BST_H
#define ASD_PS_BST_H

#include <memory>
#include <stack>
#include <fmt/format.h>
#include "concepts.h"

namespace MyDSTRS
{
    template<typename T>
    class TreeNode;

    template<typename T>
    requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>) && utils::has_ostream<T>
    class BST
    {
        public:
            BST() = default;

            auto getRoot() { return _rootPtr; };

            void AddNode(T&& value)
            {
                this->AddNode(std::forward<T>(value), _rootPtr);
                _nodesCount++;
            }


            void PrintAscRec() const { PrintAscRec(_rootPtr); }
            void PrintAscIter() const
            {
                std::stack<std::shared_ptr<TreeNode<T>>> callStack;
                callStack.push(_rootPtr);

                while(callStack.top())
                    callStack.push(callStack.top()->lhsPtr);
                callStack.pop();

                while(!callStack.empty())
                {
                    fmt::print("{}\n", callStack.top()->value);
                    auto tmpRhs = callStack.top()->rhsPtr;
                    callStack.pop();

                    if(tmpRhs)
                    {
                        callStack.push(tmpRhs);

                        while(callStack.top())
                            callStack.push(callStack.top()->lhsPtr);
                        callStack.pop();
                    }
                }
            }

        private:
            void AddNode(T&& value, std::shared_ptr<TreeNode<T>>& tmpPtr)
            {
                if(!tmpPtr)
                {
                    tmpPtr.reset(new TreeNode<T>(std::forward<T>(value)));
                    return;
                }

                if(value > tmpPtr->value)
                    AddNode(std::forward<T>(value), tmpPtr->rhsPtr);
                else
                    AddNode(std::forward<T>(value), tmpPtr->lhsPtr);
            }

            void PrintAscRec(std::shared_ptr<TreeNode<T>> tmpPtr) const
            {
                if(tmpPtr)
                {
                    PrintAscRec(tmpPtr->lhsPtr);
                    fmt::print("{}\n", tmpPtr->value);
                    PrintAscRec(tmpPtr->rhsPtr);
                }
            }

        private:
            std::shared_ptr<TreeNode<T>> _rootPtr{nullptr};
            uint32_t _nodesCount{0};
    };

    template<typename T>
    class TreeNode
    {
        friend class BST<T>;

        TreeNode(T&& value) : value(std::forward<T>(value)) { }

        T value;
        std::shared_ptr<TreeNode<T>> lhsPtr{nullptr};
        std::shared_ptr<TreeNode<T>> rhsPtr{nullptr};
    };

}




#endif