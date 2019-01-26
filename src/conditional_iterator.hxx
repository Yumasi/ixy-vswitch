#pragma once

template<typename Itr, typename F>
struct ConditionalIterator {
    Itr itr;
    Itr end;
    F condition;

    using value_type = typename Itr::value_type;
    using difference_type = typename Itr::difference_type;
    using pointer = typename Itr::pointer;
    using reference = typename Itr::reference;
    using iterator_category = std::forward_iterator_tag;


    ConditionalIterator() = default;
    ConditionalIterator(Itr itr, Itr end, F condition): itr(itr), end(end), condition(condition) {}

    bool operator!=(const ConditionalIterator& other) const { return other.itr != itr; }
    reference operator*() const { return *itr; }
    pointer operator->() const { return &(*itr); }

    ConditionalIterator& operator++() {
        for (; ++itr != end; ) {
            if (condition(*itr))
                break;
        }
        return *this;
    }

    ConditionalIterator operator++(int) {
        ConditionalIterator ret(*this);
        operator++();
        return ret;
    }
}
