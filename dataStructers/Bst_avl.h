#ifndef ASD_PS_BST_AVL_H
#define ASD_PS_BST_AVL_H

#include <concepts.h>
#include <memory>

namespace MyDSTRS
{
    template<typename T>
    class TreeNode;

    template<typename T>
    requires ((utils::has_operatorLE<T> && utils::has_operatorEQ<T> && utils::has_operatorHI<T>) || std::is_arithmetic_v<T>)
    class AVLTree
    {
        public:
            AVLTree() = default;

            void insert(T&& value);
            bool find(const T& value) const;
            bool erase(const T& value);

            template<typename U = T>
            requires utils::same_as<T, U> && utils::has_ostream<U>
            void Print() const;

            template<typename U>
            requires utils::same_as<T, U> && utils::is_semblable_startsWith<U>
            uint64_t countAllStartingWith(const U& value) const;

        private:
            static void AdjustWages(TreeNode<T>* newDaddyPtr);
            static void LRotation(std::unique_ptr<TreeNode<T>>* daddyPtrPtr);
            static void RRotation(std::unique_ptr<TreeNode<T>>* daddyPtrPtr);

        private:
            std::unique_ptr<TreeNode<T>> _root{nullptr};
            uint64_t height{0};
    };

    template<typename T>
    struct TreeNode
    {
        friend class AVLTree<T>;

        TreeNode(T&& value) : value(std::forward<T>(value)) { }

        auto wage() const { return lhsLevels - rhsLevels; }

        private:
            T value;

            int32_t lhsLevels{0};
            int32_t rhsLevels{0};

            std::unique_ptr<TreeNode<T>> lhsPtr{nullptr};
            std::unique_ptr<TreeNode<T>> rhsPtr{nullptr};
    };
}

#include "Bst_avl.tpp"

#endif