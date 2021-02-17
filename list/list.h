#ifndef TEMPLATES_LIST_2021_02_11
#define TEMPLATES_LIST_2021_02_11

namespace lab618
{
    template<class T>
    class CSingleLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf* pnext;
            leaf(T& _data, leaf* _pnext)
                : data(_data), pnext(_pnext) {}
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(nullptr), m_pBegin(nullptr) {}

            CIterator(leaf *p)
                : m_pCurrent(p), m_pBegin(nullptr) {}

            CIterator(const CIterator& src)
                : m_pCurrent(src.m_pCurrent), m_pBegin(src.m_pBegin) {}

            ~CIterator() {}

            CIterator& operator = (const CIterator& src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                return *this;
            }

            bool operator == (const CIterator& it) const
            {
                return (m_pBegin == it.m_pBegin && m_pCurrent == it.m_pCurrent);
            }

            bool operator != (const CIterator&  it) const
            {
                return !(*this == it);
            }

            void operator++()
            {
                if (m_pCurrent)
                {
                    m_pCurrent = m_pCurrent->pnext;
                }
                else
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
                }
            }

            T& getData()
            {
                if (m_pCurrent) 
                {
                    return m_pCurrent->data;
                }
                T tmp;
                return tmp;
            }

            T& operator* () 
            {
                return getData();
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
                m_pBegin = nullptr;
            }

            void setLeafPreBegin(leaf* p)
            {
                m_pCurrent = nullptr;
                m_pBegin = p;
            }

            bool isValid() {
                return m_pCurrent || m_pBegin;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList()
            : m_pBegin(nullptr), m_pEnd(nullptr)
        {
        }

        virtual ~CSingleLinkedList()
        {
            while (m_pBegin)
            {
                popFront();
            }
        }

        void pushBack(T& data)
        {
            leaf* tmp = new leaf(data, nullptr);
            if (!m_pEnd) 
            {
                m_pEnd = tmp;
                m_pBegin = tmp;
            }
            else 
            {
                m_pEnd->pnext = tmp;
                m_pEnd = tmp;
            }
        }

        void pushFront(T& data)
        {
            leaf* tmp = new leaf(data, m_pBegin);
            m_pBegin = tmp;
            if (!m_pEnd)
            {
                m_pEnd = tmp;
            }
        }

        T popFront()
        {
            T tmp;
            if (m_pBegin) 
            {
                if (m_pEnd == m_pBegin) 
                {
                    m_pEnd = nullptr;
                }
                leaf* tmpptr = m_pBegin->pnext;
                tmp = m_pBegin->data;
                delete m_pBegin;
                m_pBegin = tmpptr;

            }
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf* p = it.getLeaf();
            if (p) 
            {
                if (p == m_pBegin) 
                {
                    popFront();
                    it.setLeafPreBegin(m_pBegin);
                }
                else 
                {
                    leaf* tmp = m_pBegin;
                    while (tmp->pnext != p) 
                    {
                        tmp = tmp->pnext;
                    }
                    if (p == m_pEnd) 
                    {
                        m_pEnd = tmp;
                    }
                    tmp->pnext = p->pnext;
                    it.setLeaf(tmp);
                    delete p;
                }
            }
        }

        int getSize()
        {
            int count = 0;
            leaf* tmp = m_pBegin;
            while (tmp) 
            {
                count++;
                tmp = tmp->pnext;
            }
            return count;
        }

        void clear()
        {
            while (m_pBegin)
            {
                popFront();
            }
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };

    template<class T>
    class CDualLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data, leaf * _pprev, leaf * _pnext)
                : data(_data), pprev(_pprev), pnext(_pnext)
            {
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(nullptr), m_pBegin(nullptr), m_pEnd(nullptr)
            {
            }

            CIterator(leaf *p)
                : m_pCurrent(p), m_pBegin(nullptr), m_pEnd(nullptr)
            {
            }

            CIterator(const CIterator &src)
                : m_pCurrent(src.m_pCurrent), m_pBegin(src.m_pBegin), m_pEnd(src.m_pEnd)
            {
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pEnd = src.m_pEnd;
                return *this;
            }

            bool operator == (const CIterator& it) const
            {
                return (m_pBegin == it.m_pBegin && m_pCurrent == it.m_pCurrent && m_pEnd == it.m_pEnd);
            }

            bool operator != (const CIterator&  it) const
            {
                return !(*this == it);
            }

            void operator++()
            {
                if (m_pCurrent)
                {
                    m_pCurrent = m_pCurrent->pnext;
                }
                else if (m_pBegin)
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
                }
            }

            void operator--()
            {
                if (m_pCurrent)
                {
                    m_pCurrent = m_pCurrent->pprev;
                }
                else if (m_pEnd)
                {
                    m_pCurrent = m_pEnd;
                    m_pEnd = nullptr;
                }
            }

            T& getData()
            {
                if (m_pCurrent)
                {
                    return m_pCurrent->data;
                }
                T tmp;
                return tmp;
            }

            T& operator* ()
            {
                return getData();
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
                m_pEnd = nullptr;
                m_pBegin = nullptr;
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
                m_pCurrent = nullptr;
                m_pEnd = nullptr;
                m_pBegin = p;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
                m_pCurrent = nullptr;
                m_pEnd = p;
                m_pBegin = nullptr;
            }

            bool isValid() {
                return m_pCurrent || m_pEnd || m_pBegin;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
            //храним конец списка, если мы находимся после конца
            leaf* m_pEnd;
        };

    public:

        CDualLinkedList()
            : m_pBegin(nullptr), m_pEnd(nullptr)
        {
        };

        virtual ~CDualLinkedList()
        {
            while (m_pBegin)
            {
                popFront();
            }
        };

        void pushBack(T& data)
        {
            leaf* tmp = new leaf(data, m_pEnd, nullptr);
            if (!m_pEnd) 
            {
                m_pEnd = tmp;
                m_pBegin = tmp;
            }
            else 
            {
                m_pEnd->pnext = tmp;
                m_pEnd = tmp;
            }
        }

        T popBack()
        {
            T tmp;
            if (m_pEnd) 
            {
                if (m_pEnd == m_pBegin) 
                {
                    m_pBegin = nullptr;
                }
                leaf* tmpptr = m_pEnd->pprev;
                tmp = m_pEnd->data;
                delete m_pEnd;
                m_pEnd = tmpptr;
                if (m_pEnd) {
                    m_pEnd->pnext = nullptr;
                }
            }
            return tmp;
        }

        void pushFront(T& data)
        {
            leaf* tmp = new leaf(data, nullptr, m_pBegin);
            if (!m_pBegin) 
            {
                m_pEnd = tmp;
                m_pBegin = tmp;
            }
            else 
            {
                m_pBegin->pprev = tmp;
                m_pBegin = tmp;
            }
        }

        T popFront()
        {
            T tmp;
            if (m_pBegin) 
            {
                if (m_pEnd == m_pBegin) 
                {
                    m_pEnd = nullptr;
                }
                leaf* tmpptr = m_pBegin->pnext;
                tmp = m_pBegin->data;
                delete m_pBegin;
                m_pBegin = tmpptr;
                if (m_pBegin)
                {
                    m_pBegin->pprev = nullptr;
                }

            }
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf* p = it.getLeaf();
            if (p) 
            {
                if (p == m_pBegin) 
                {
                    popFront();
                    it.setLeafPreBegin(m_pBegin);
                }
                else if (p == m_pEnd)
                {
                    it.setLeaf(p->pprev);
                    popBack();
                }
                else
                {
                    p->pprev->pnext = p->pnext;
                    p->pnext->pprev = p->pprev;
                    it.setLeaf(p->pprev);
                    delete p;
                }
            }
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
            leaf* p = it.getLeaf();
            if (p) 
            {
                if (p == m_pEnd) 
                {
                    popBack();
                    it.setLeafPostEnd(m_pEnd);
                }
                else if (p == m_pBegin)
                {
                    it.setLeaf(p->pnext);
                    popFront();
                }
                else
                {
                    p->pprev->pnext = p->pnext;
                    p->pnext->pprev = p->pprev;
                    it.setLeaf(p->pnext);
                    delete p;
                }
            }
        }

        int getSize()
        {
            int count = 0;
            leaf* tmp = m_pBegin;
            while (tmp) 
            {
                count++;
                tmp = tmp->pnext;
            }
            return count;
        }

        void clear()
        {
            while (m_pBegin)
            {
                popFront();
            }
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

        CIterator end()
        {
            return CIterator(m_pEnd);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2021_02_11
