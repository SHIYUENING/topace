#ifndef HGL_TREE_CPP
#define HGL_TREE_CPP

#include<hgl/Tree.H>
namespace hgl
{
    /**
    * 本类构造函数
    */
    template<typename T>
    TreeNode<T>::TreeNode()
    {
    }

    /**
    * 本类析构函数
    */
    template<typename T>
    TreeNode<T>::~TreeNode()
    {
        Node.Clear();
    }
}

#endif//HGL_TREE_CPP>
