#ifndef NW_UT_LINKLIST_H_
#define NW_UT_LINKLIST_H_

#include <nw/types.h>
#include <nw/ut/ut_Inlines.h>
#include <nw/ut/ut_Iterator.h>

namespace nw { namespace ut {

class LinkListNode;

namespace internal {

class LinkListImpl;

} // namespace internal

class LinkListNode
{
private:
    NW_DISALLOW_COPY_AND_ASSIGN(LinkListNode);

public:
    typedef LinkListNode Self;

    explicit LinkListNode()
        : m_pNext(NULL)
        , m_pPrev(NULL)
    {
    }

    Self* GetNext() const
    {
        return m_pNext;
    }

    Self* GetPrev() const
    {
        return m_pPrev;
    }

    friend bool operator==(const Self& r1, const Self& r2)
    {
        return &r1 == &r2;
    }

    friend bool operator!=(const Self& r1, const Self& r2)
    {
        return !(r1 == r2);
    }

private:
    Self* m_pNext;
    Self* m_pPrev;

    friend class internal::LinkListImpl;
};
static_assert(sizeof(LinkListNode) == 8);

namespace internal {

class LinkListImpl
{
private:
    NW_DISALLOW_COPY_AND_ASSIGN(LinkListImpl);

public:
    typedef LinkListImpl        Self;
    typedef u32                 size_type;
    typedef PtrDiff             difference_type;

    typedef LinkListNode        Node;
    typedef Node                value_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    explicit LinkListImpl()
    {
        Initialize_();
    }
    
    ~LinkListImpl()
    {
    }

    size_type size() const { return m_Size; }
    bool empty() const { return m_Size == 0; }

protected:
    Node* GetBaseNode() { return &m_BaseNode; }
    const Node* GetBaseNode() const { return &m_BaseNode; }

private:
    void Initialize_()
    {
        m_Size = 0;
        m_BaseNode.m_pNext = &m_BaseNode;
        m_BaseNode.m_pPrev = &m_BaseNode;
    }

    size_type   m_Size;
    Node        m_BaseNode;
};
static_assert(sizeof(LinkListImpl) == 0xC);

} // namespace internal

template <typename T, PtrDiff TNOffset>
class LinkList : private internal::LinkListImpl
{
private:
    typedef internal::LinkListImpl Base;

public:
    typedef LinkList  Self;
    using Base::Node;

    using Base::size_type;
    using Base::difference_type;

    typedef T                  value_type;
    typedef value_type*        pointer;
    typedef const value_type*  const_pointer;
    typedef value_type&        reference;
    typedef const value_type&  const_reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    LinkList()
    {
    }

    using Base::size;
    using Base::empty;

    pointer GetPrev(pointer p)
    {
        Node* baseNode = GetBaseNode();
        Node* node = p == NULL ? baseNode : GetNodeFromPointer(p);
        node = node->GetPrev();
        return node == baseNode ? NULL : GetPointerFromNode(node);
    }

    const_pointer GetPrev(const_pointer p) const
    {
        const Node* baseNode = GetBaseNode();
        const Node* node = p == NULL ? baseNode : GetNodeFromPointer(p);
        node = node->GetPrev();
        return node == baseNode ? NULL : GetPointerFromNode(node);
    }

    pointer GetNext(pointer p)
    {
        Node* baseNode = GetBaseNode();
        Node* node = p == NULL ? baseNode : GetNodeFromPointer(p);
        node = node->GetNext();
        return node == baseNode ? NULL : GetPointerFromNode(node);
    }

    const_pointer GetNext(const_pointer p) const
    {
        const Node* baseNode = GetBaseNode();
        const Node* node = p == NULL ? baseNode : GetNodeFromPointer(p);
        node = node->GetNext();
        return node == baseNode ? NULL : GetPointerFromNode(node);
    }

    static Node* GetNodeFromPointer(pointer p)
    {
      //NW_ASSERT_NOT_NULL(p);
        return reinterpret_cast<Node*>(reinterpret_cast<IntPtr>(p) + TNOffset);
    }
    static const Node* GetNodeFromPointer(const_pointer p)
    {
      //NW_ASSERT_NOT_NULL(p);
        return reinterpret_cast<const Node*>(reinterpret_cast<IntPtr>(p) + TNOffset);
    }

    static pointer GetPointerFromNode(Node* p)
    {
      //NW_ASSERT_NOT_NULL(p);
        return reinterpret_cast<pointer>(reinterpret_cast<IntPtr>(p) - TNOffset);
    }
    static const_pointer GetPointerFromNode(const Node* p)
    {
      //NW_ASSERT_NOT_NULL(p);
        return reinterpret_cast<const_pointer>( reinterpret_cast<IntPtr>(p) - TNOffset);
    }

    size_type GetSize() const { return this->size(); }
    bool      IsEmpty() const { return this->empty(); }
};

} } // namespace nw::ut

#endif // NW_UT_LINKLIST_H_
