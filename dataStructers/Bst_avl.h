#ifndef ASD_PS_BST_AVL_H
#define ASD_PS_BST_AVL_H

#include <concepts.h>

namespace MyDSTRS
{
    template<typename T>
    class TreeNode;


    template<typename T>
    requires ((utils::has_operatorLE<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
    class AVLTree
    {
        public:
            AVLTree() = default;

            void insert(T&& value);
            bool find(const T& value) const;
            bool erase(const T& value);

        private:
            static void LRotation(std::unique_ptr<TreeNode<T>>* daddyPtrPtr, int8_t wage);
            static void RRotation(std::unique_ptr<TreeNode<T>>* daddyPtrPtr, int8_t wage);

        private:
            std::unique_ptr<TreeNode<T>> _root{nullptr};
    };

    template<typename T>
    struct TreeNode
    {
        friend class AVLTree<T>;

        TreeNode(T&& value) : value(std::forward<T>(value)) { }

        private:
            T value;
            int8_t wage{0};
            std::unique_ptr<TreeNode<T>> lhsPtr{nullptr};
            std::unique_ptr<TreeNode<T>> rhsPtr{nullptr};
    };
}

#include "Bst_avl.tpp"

#endif