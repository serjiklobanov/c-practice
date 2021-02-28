#ifndef MEMORY_MANAGER_HEAD_H_2021_02_18
#define MEMORY_MANAGER_HEAD_H_2021_02_18

namespace lab618
{
    template <class T>
    class CMemoryManager
    {
    private:
        struct block
        {
            // Массив данных блока
            T* pdata;
            // Адрес следующего блока
            block *pnext;
            // Первая свободная ячейка
            int firstFreeIndex;
            // Число заполненных ячеек
            int usedCount;
        };
    public:
        class CException
        {
        public:
            CException()
            {
            }
        };

    public:
        CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false) 
            : m_blkSize(_default_block_size), m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct),
            m_pBlocks(nullptr), m_pCurrentBlk(nullptr)
        {
        }

        virtual ~CMemoryManager()
        {
            if (!m_isDeleteElementsOnDestruct)
            {
                while (m_pCurrentBlk)
                {
                    if (m_pCurrentBlk->usedCount != 0)
                    {
                        throw CException();
                    }
                    m_pCurrentBlk = m_pCurrentBlk->pnext;
                }
            }
            else
            {
                clear();
            }
        }

        // Получить адрес нового элемента из менеджера
        T* newObject()
        {
            m_pCurrentBlk = m_pBlocks;
            while (m_pCurrentBlk && m_pCurrentBlk->usedCount == m_blkSize)
            {
                m_pCurrentBlk = m_pCurrentBlk->pnext;
            }
            if (!m_pCurrentBlk) 
            {
                m_pCurrentBlk = newBlock();
            }
            int i = m_pCurrentBlk->firstFreeIndex;
            m_pCurrentBlk->firstFreeIndex = *reinterpret_cast<int*>(&(m_pCurrentBlk->pdata[i]));
            m_pCurrentBlk->usedCount += 1;
            return new(&(m_pCurrentBlk->pdata[i])) T;
        }

        // Освободить элемент в менеджере
        bool deleteObject(T* p)
        {
            m_pCurrentBlk = m_pBlocks;
            while (m_pCurrentBlk && (p - m_pCurrentBlk->pdata >= m_blkSize || p - m_pCurrentBlk->pdata < 0))
            {
                m_pCurrentBlk = m_pCurrentBlk->pnext;
            }
            if (m_pCurrentBlk) 
            {
                int i = p - m_pCurrentBlk->pdata;
                m_pCurrentBlk->pdata[i].~T();
                new(&(m_pCurrentBlk->pdata[i])) int(m_pCurrentBlk->firstFreeIndex);
                m_pCurrentBlk->firstFreeIndex = i;
                m_pCurrentBlk->usedCount -= 1;
                return true;
            }
            else 
            {
                return false;
            }
        }

        // Очистка данных, зависит от m_isDeleteElementsOnDestruct
        void clear()
        {
            m_pCurrentBlk = m_pBlocks;
            while (m_pCurrentBlk)
            {
                block* tmp = m_pCurrentBlk;
                m_pCurrentBlk = m_pCurrentBlk->pnext;
                deleteBlock(tmp);
                delete tmp;
            }
            m_pBlocks = nullptr;
            m_pCurrentBlk = nullptr;
        }
    private:

        // Создать новый блок данных. применяется в newObject
        block* newBlock()
        {
            block* tmp = new block;
            tmp->pdata = reinterpret_cast<T*>(new char[m_blkSize * sizeof(T)]);
            for (int i = 0; i < m_blkSize; ++i) 
            {
                new(&(tmp->pdata[i])) int(i + 1);
            }
            tmp->firstFreeIndex = 0;
            tmp->usedCount = 0;
            tmp->pnext = m_pBlocks;
            m_pBlocks = tmp;
            return m_pBlocks;
        }

        // Освободить память блока данных. Применяется в clear
        void deleteBlock(block *p)
        {
            while (p->usedCount != m_blkSize) 
            {
                int i = p->firstFreeIndex;
                p->firstFreeIndex = *reinterpret_cast<int*>(&(p->pdata[i]));
                p->usedCount += 1;
                new(&(p->pdata[i])) T;
            }
            for (int i = 0; i < m_blkSize; ++i)
            {
                p->pdata[i].~T();
            }


            delete[] reinterpret_cast<char*>(p->pdata);

        }

        // Размер блока
        int m_blkSize;
        // Начало списка блоков
        block* m_pBlocks;
        // Текущий блок
        block *m_pCurrentBlk;
        // Удалять ли элементы при освобождении
        bool m_isDeleteElementsOnDestruct;
    };
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2021_02_18
