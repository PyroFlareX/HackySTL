#pragma once

#include <new>

#include "Vector.hpp"
#include "Atomic.hpp"


namespace hsd
{
    
    using counter = atomic_usize;

    namespace priv
    {
        template <typename T>
        struct slot
        {
            void destroy()
            {
                storage.~T();
            }

            ~slot()
            {
                destroy();
            }

            slot() requires (std::is_default_constructible_v<T>)
                : storage{}
            {}

            slot(const slot& other)
                : storage{other.storage}
            {
                ticket.store(other.ticket.load());
            }

            slot(slot&& other)
                : storage{move(other.storage)}
            {
                ticket.store(other.ticket.load());
            }

            slot& operator=(const slot& rhs)
            {
                ticket.store(rhs.ticket.load());
                storage = rhs.storage;
                return *this;
            }

            slot& operator=(slot&& rhs)
            {
                ticket.store(rhs.ticket.load());
                storage = move(rhs.storage);
                return *this;
            }

            atomic_usize ticket = {0};
            T storage;
        };
    }

    /**
     * Multiprocessor Multiconsumer Queue [MPMCQueue]
     * Written by PyroFlareX, inspiration from github.com/rigtorp/MPMCQueue for concept.
     * This is a "thread-safe" MPMC queue written for HackySTL, type and max capacity must be known on creation.
     * Probably not the best optimized implementation, but it works well enough.
     * Works as a stack-machine, FIFO
    */
    template<typename T>
    class MPMCQueue
    {
    public:
        MPMCQueue(usize capacity)
            : _capacity(capacity)
        {
            if (_capacity < 1)
            {
                //This is UB
                puts("Capacity is less than 1, this is UB, and an error\n");
                abort();
            }
            _allocation.resize(_capacity + 1);
        }

        MPMCQueue(const MPMCQueue&) = delete;
        MPMCQueue& operator=(const MPMCQueue&) = delete;

        bool try_emplace(T&& value)
        {
            auto head = _head.load();

            while (true)
            {
                auto& slot = _allocation[mod(head)];

                if (turn(head) * 2 == slot.ticket.load(hsd::memory_order_acquire))
                {
                    if (_head.compare_exchange_strong(head, head + 1))
                    {
                        slot.storage = forward<T>(value);
                        slot.ticket.store(turn(head) * 2 + 1, hsd::memory_order_release);
                        return true;
                    }
                }
                else
                {
                    auto const prevHead = head;
                    head = _head.load(hsd::memory_order_acquire);

                    if (head == prevHead)
                    {
                        return false;
                    }
                }
            }

            return false;
        }

        bool try_pop(T& value)
        {
            auto tail = _tail.load();

            while (true)
            {
                auto& slot = _allocation[mod(tail)];

                if (turn(tail) * 2 + 1 ==  slot.ticket.load(hsd::memory_order_acquire))
                {
                    if (_tail.compare_exchange_strong(tail, tail + 1))
                    {
                        value = move(slot.storage);
                        slot.destroy();
                        slot.ticket.store(turn(tail) * 2 + 2, hsd::memory_order_release);
                        return true;
                    }
                }
                else
                {
                    auto const prevTail = tail;
                    tail = _tail.load(hsd::memory_order_acquire);

                    if (tail == prevTail)
                    {
                        return false;
                    }
                }
            }
        }

        void emplace(T&& value)
        {
            auto const head = _head.fetch_add(1);
            auto& slot = _allocation[mod(head)];

            while (turn(head) * 2 != slot.ticket.load(hsd::memory_order_acquire))
                ;
            
            slot.storage = forward<T>(value);
            slot.ticket.store(turn(head) * 2 + 1, hsd::memory_order_release);
        }

        void pop(T& value)
        {
            auto const tail = _tail.fetch_add(1);
            auto& slot = _allocation[mod(tail)];

            while (turn(tail) * 2 + 1 != slot.ticket.load(hsd::memory_order_acquire))
                ;

            value = move(slot.storage);
            slot.destroy();
            slot.ticket.store(turn(tail) * 2 + 2, hsd::memory_order_release);
        }

    private:
        usize _capacity;

        vector<priv::slot<T>> _allocation;

        atomic_usize _head = {0};
        atomic_usize _tail = {0};

        constexpr usize mod(usize number) const
        {
            return number % _capacity; 
        }

        constexpr usize turn(usize number) const
        {
            return number / _capacity;
        }
    };
}