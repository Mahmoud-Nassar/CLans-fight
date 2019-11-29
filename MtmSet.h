#ifndef MTM4_SET_H
#define MTM4_SET_H

#include "exceptions.h"
#include <iostream>

namespace mtm{
    
    /**
     * A set
     * @tparam Type The type of an element on the group.
     *      Required to implement:
     *                             - operator ==
     *                             - copy constructor
     */
    template<typename Type>
    class MtmSet{

        /**
         * A node in the set
         */
        class Node{
        public:
            Type data;
            Node* next;
            Node(Type element, Node* next) : data(element) ,next(next) {}
            ~Node()= default;
        };
        Node * head;

    public:
        //Forward declaration
        class const_iterator;
        
        /**
         * A iterator for Set
        */
        class iterator{
            Node* current;
        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            iterator() : current(NULL) {}
            
            /**
             * Constructor of Set iterator
             * @param node The node the iterator points to
             */
            explicit iterator(Node *node) : current(node) {}
            
            /**
             * Copy constructor
             * @param it The iterator to copy
             */
            iterator(const iterator& it) : current(it.current) {}

            /**
             * Destructor
             */
            ~iterator() {}

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this iterator.
             */
            iterator& operator=(const iterator& rhs){
                this->current=rhs.current;
                return *this;
            }
            
            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type& operator*() const {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                return current->data;
            }
            
            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the iterator
             *  points to.
             * C++ use the -> operator on the returned pointer,
             * this allows the user to treat the iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                return (&(current->data));
            }
            
            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator& operator++() {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                current=current->next;
                return *this;
            }
            
            /**
             * Postfix increment operator (i++)
             * @return iterator that points to the same node as this before
             * the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator operator++(int) {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                iterator temp=*this;
                ++*this;
                return temp;
            }
            
            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators point to the same node
             */
            bool operator==(const const_iterator& rhs) const {
                return rhs==*this;
            }
            
            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators don't point to the same node
             */
            bool operator!=(const const_iterator& rhs) const {
                return rhs!=*this;
            }

            friend class const_iterator;
        };
        
        /**
         * A const_iterator for Set
        */
        class const_iterator{
            Node* current;

        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            const_iterator() : current(NULL) {}
            
            /**
             * Constructor of Set const_iterator
             * @param node The node the const_iterator points to
             */
            explicit const_iterator(Node *node) : current(node) {}
            
            /**
             * Copy constructor
             * @param it The const_iterator to copy
             */
            const_iterator(const const_iterator& it)  : current(it.current) {}
            
            /**
             * Constructor from iterator (not const_iterator)
             * Allows casting from iterator to const_iterator
             * @param it The iterator to "copy" to a const_iterator
             */
            const_iterator(const iterator& it)  : current(it.current) {}

            /**
             * Destructor
             */
            ~const_iterator() {}

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this const_iterator.
             */
            const_iterator& operator=(const const_iterator& rhs) {
                this->current=rhs.current;
                return *this;
            }
            
            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the const_iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type& operator*() const {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                return current->data;
            }
            
            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the const_iterator
             *  points to.
             *  C++ use the -> operator on the returned pointer,
             *  this allows the user to treat the const_iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                return (&(current->data));
            }
            
            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator& operator++() {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                current=current->next;
                return *this;
            }
            
            /**
             * Postfix increment operator (i++)
             * @return const_iterator that points to the same node as this
             * before the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator operator++(int) {
                if (current==NULL) {
                    throw NodeIsEndException();
                }
                const_iterator temp=*this;
                ++*this;
                return temp;
            }
            
            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators point to the same node
             */
            bool operator==(const const_iterator& rhs) const {
                if (current==NULL && rhs.current==NULL) return true;
                if ((current!=NULL && rhs.current==NULL)|| (current==NULL &&
                        rhs.current!=NULL )) {
                    return false;
                }
                return (current->data==rhs.current->data);
            }
            
            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators don't point to the same
             * node
             */
            bool operator!=(const const_iterator& rhs) const {
                return !(*this==rhs);
            }
        };
        
        /**
         * Empty constructor
         * Creates an empty set
         */
        MtmSet() : head(NULL) {}
        
        /**
         * Copy constructor
         * @param set the Set to copy
         */
        MtmSet(const MtmSet& set) {
            this->head=NULL;
            *this =set;
        }
        
        /**
         * Destructor
         * Free all allocated memory in the set.
         */
        ~MtmSet() {
            this->clear();
        }
        
        /**
         * Insert a new element to the set, doesn't insert if there is already
         *  an equal element in the set.
         * If an element was't inserted, all iterators should stay valid.
         * @param elem The element to insert to the set
         * @return An iterator to the inserted element, or to the equal
         * element if the element wasn't inserted.
         */
        iterator insert(const Type& elem) {
            iterator iterator1 = this->find(elem);
            if (iterator1 != this->end()) {
                return iterator1;
            }
            Node *new_node=new Node(elem,this->head);
            this->head=new_node;
            return this->begin();
        }
        
        /**
         * Remove an element from the set. If there is no element equal to
         *  elem in the set, does nothing.
         * If an element wasn't removed, all iterators should stay valid.
         * @param elem the element to remove.
         */
        void erase(const Type& elem) {
            if (this->empty()) return;
            iterator iterator1=this->find(elem);
            if (iterator1==this->end()) return;
            if (iterator1==this->begin()){
                Node* temp=this->head;
                this->head=temp->next;
                delete temp;
                return;
            }
            Node *node_before=head;
            while (node_before!=NULL) {
                if (node_before->next->data==*iterator1) {
                    break;
                }
                node_before=node_before->next;
            }
            Node* temp=node_before->next;
            node_before->next=temp->next;
            delete temp;
        }
        
        /**
         * Remove the element the iterator points to from the set.
         * Iterator to another set is undefined.
         * @param it The iterator to the element to the set.
         */
        void erase(const iterator& it) {
            if (it==this->end()) return;
            this->erase(*it);
        }
        
        /**
         * Get the amount of elements in the set.
         * @return The amount of elements in the set.
         */
        int size() const {
            if (this->head==NULL) {
                return 0;
            }
            Node* ptr=this->head;
            int counter=0;
            while (ptr!=NULL) {
                counter++;
                ptr=ptr->next;
            }
            return counter;
        }
        
        /**
         * Check if the set is empty.
         * @return true is the set is empty.
         */
        bool empty() const {
            return !this->head;
        }
        
        /**
         * Empty the set, free all allocated memory in the set.
         */
        void clear() {
            while (!this->empty()){
                this->erase(this->begin());
            }
            this->head=NULL;
        }
        
        /**
         * Get an iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        iterator begin() {
            if (head==NULL) {
                return this->end();
            }
            return iterator(head);
        }
        
        /**
         * Get a const_iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        const_iterator begin() const {
            if (head==NULL) {
                return this->end();
            }
            return const_iterator(head);
        }
        
        /**
         * Returns an iterator referring to the past-the-end element in the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return Iterator to past-the-end element.
         */
        iterator end() {
            return iterator(NULL);
        }
        
        /**
         * Returns a const_iterator referring to the past-the-end element in
         * the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return const_iterator to past-the-end element.
         */
        const_iterator end() const {
            return const_iterator(NULL);
        }
        
        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return An iterator that points to the elem.
         */
        iterator find(const Type& elem) {
            for (iterator iterator1=this->begin();
                 iterator1!=this->end();iterator1++) {
                if (*iterator1==elem) {
                    return iterator1;
                }
            }
            return this->end();
        }
        
        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return A const_iterator that points to the elem.
         */
        const_iterator find(const Type& elem) const {
            for (const_iterator iterator1=this->begin();
                 iterator1!=this->end();iterator1++) {
                if (*iterator1==elem) {
                    return iterator1;
                }
            }
            return this->end();
        }
        
        /**
         * Check if an element is in the set.
         * @param elem The element to check if it's in the set.
         * @return True if the element is in the set, false otherwise.
         */
        bool contains(const Type& elem) const {
            if (this->find(elem)==this->end()) return false;
            return true;
        }
        
        /**
         * Check if this set is a superset of a given set.
         * Superset: A superset of B if B is a subset of A, that mean's that
         *  A contains all the elements in B.
         * @param subset The set to check if it's a subset.
         * @return True if the given set is a subset of this set.
         */
        bool isSuperSetOf(const MtmSet& subset) const {
            if (subset.empty()) return true;
            if (this->empty()) return false;
            for (const_iterator iterator1=subset.begin();iterator1!=subset
                    .end();iterator1++){
                if (this->contains(*iterator1)==false) {
                    return false;
                }
            }
            return true;
        }
        
        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the == operator.
         * @return true if thw two set conatain the same elements, false
         *  otherwise.
         */
        bool operator==(const MtmSet& rhs) const  {
            if (rhs.empty()) {
                if (this->empty()) {
                    return true;
                }
                return false;
            }
            return (this->isSuperSetOf(rhs) && rhs.isSuperSetOf(*this));
        }

        /**
         * assignment operator for set
         * this set becomes equal to rhs set (by copy)
         * no changes made on rhs set
         * @param rhs- set to be equal to
         * @return- a refernce to this set (after the assignment)
         */
        MtmSet& operator=(const MtmSet& rhs)  {
            if (&rhs!=this) {
                this->clear();
                for (const_iterator iterator1 = rhs.begin();
                     iterator1 != rhs.end(); iterator1++) {
                    this->insert(*iterator1);
                }
            }
            return *this;
        }

        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the != operator.
         * @return false if thw two set conatain the same elements, true
         *  otherwise.
         */
        bool operator!=(const MtmSet& rhs) const {
            return !(rhs==*this);
        }
        
        /**
         * Insert all the elements in the given set to this set (union).
         * @param set The set to insert all the elements from.
         * @return A reference to this set.
         */
        MtmSet& unite(const MtmSet& set) {
            if (set.empty()) {
                return *this;
            }
            const_iterator iterator1 = set.begin();
            while ( iterator1 != set.end()){
                    if (!this->contains(*iterator1)) {
                        this->insert(*iterator1);
                        iterator1=set.begin();
                        continue;
                    }
                    iterator1++;
                }
            return *this;
        }
        
        /**
         * Returns a new set that is an union of this set, and a given set.
         * @param set The other set (other than this) to be in the union.
         * @return The new set.
         */
        MtmSet unite(const MtmSet& set) const {
            MtmSet set_to_return(*this);
            return set_to_return.unite(set);
        }
        
        /**
         * Remove all the elements from this set, that are in the given set
         * (intersection).
         * @param set The other set in the intersection.
         * @return A reference to this set.
         */
        MtmSet& intersect(const MtmSet& set) {
            if (set.empty()) {
                this->clear();
            }
            else if (!this->empty()) {
                iterator iterator1=this->begin();
                while (iterator1!=this->end()){
                    if (!set.contains(*iterator1)) {
                        this->erase(iterator1);
                        iterator1=this->begin();
                        continue;
                    }
                    iterator1++;
                }
            }
            return *this;
        }
        
        /**
         * Returns a new set that is an intersection of this set,
         *  and a given set.
         * @param set The other set (other than this) to be in the intersection.
         * @return The new set.
         */
        MtmSet intersect(const MtmSet& set) const {
           MtmSet set_to_return(*this);
            return set_to_return.intersect(set);
        }
        
        /**
         * Remove all the elements in the set, that doesn't meet a given
         *  condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A reference to this set.
         */
        template<typename func>
        MtmSet& getSubSet(func condition) {
            if (!this->empty()) {
                iterator iterator1=this->begin();
                while (iterator1!=this->end()){
                    if (!condition(*iterator1)){
                        this->erase(iterator1);
                        iterator1=this->begin();
                        continue;
                    }
                    iterator1++;
                }
            }
            return *this;
        }
        
        /**
         * Get a subset of this set, that contains all the elements in the set,
         * that doesn't meet a given condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A the new set.
         */
        template<typename func>
        MtmSet getSubSet(func condition) const {
            MtmSet set_to_return(*this);
            return set_to_return.getSubSet<func>(condition);
        }
    };
} // namespace mtm

#endif //MTM4_SET_H
