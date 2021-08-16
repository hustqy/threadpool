#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <cassert>
#include <memory>

using namespace std;

atomic_flag flag = ATOMIC_FLAG_INIT;

void spin_lock()
{

    while (flag.test_and_set(std::memory_order_acquire))
        ;
}

void spin_unlock()
{
    flag.clear(std::memory_order_release);
}

class Animal
{

public:
    Animal(int k) : k(k) { cout << " initalize param" + to_string(k) << endl; };
    Animal() { cout << "Animal" << endl; };
   /*  Animal(const Animal &other) { cout << "copy animal" << endl; };

    Animal &operator=(const Animal &other)
    {
        cout << "copy= animal" << endl;
        return *this;
    };

    Animal(const Animal &&animal)
    {
        cout << "move construct" << endl;
    }

    Animal &operator=(const Animal &&animal)
    {
        cout << "move copy construct" << endl;
        return *this;
    }

    ~Animal()
    {
        cout << "~Animal" << endl;
    }
 */
    string getName() const { return "animal" + std::to_string(k); };

    friend ostream& operator<<(ostream& os, const Animal& dt); 

private:
    int k;
};

class Dog
{
private:
    Animal _animal;

public:
    Dog() { cout << "Dog" << endl; };
    Dog(const Dog &other) { cout << "copy dog" << endl; }
    Dog(const Animal &animal) : _animal(animal)
    {
        cout << "dog constuct initialize list" << endl;
    }
};

ostream& operator<<(ostream& os, const Animal& dt)
{
    os << dt.k;
    return os;
}

void func(int &i)
{

    spin_lock();
    i++;
    cout << "v: " << i << endl;
    spin_unlock();
}

/* atomic<shared_ptr<Animal>> p;

void process_data()
{

    shared_ptr<Animal> local = atomic_load(&p);
    cout << "local " << local->getName() << endl;
}

void update_data()
{
    Animal an(5);
    shared_ptr<Animal> local = make_shared<Animal>(an);

    atomic_store_explicit(&p, local, memory_order_release);
} */

template <typename T>
struct Node
{
    T data;
    Node *next;

    Node(const T &data) : data(data), next(NULL)
    {
    }
    T getData()
    {
        return data;
    }
};

template <typename T>
class Stack
{
private:
    atomic<Node<T> *> head;

public:
    void push(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        newNode->next = head.load(memory_order_acquire);

        while (!atomic_compare_exchange_weak_explicit(&head, &newNode->next, newNode,
                                                      memory_order_release, memory_order_relaxed))
            ;
    }

    void printStack()
    {
        while (head)
        {

            Node<T> *tmp = head.load(memory_order_relaxed);

            cout << tmp->getData() << endl;
            while(!head.compare_exchange_weak(tmp, tmp->next, memory_order_release));
            //atomic_store(&head, tmp-> next);
        }
    }
};

int main(int argc, char **argv)
{

    /* int count = 10;
    int v = 0;
    std::vector<thread> threads;
    for (size_t i = 0; i < count; i++)
    {
        threads.emplace_back (func, std::ref(v));
    }
    for (size_t i = 0; i < count; i++) {

        threads[i].join();
    }
    cout << "res " << v <<endl; */

   /*  Animal animal;

    Dog dog(animal);

    Animal arr[5];
    atomic<Animal *> p(arr);

    Animal *x = p.fetch_add(2);

    assert(x == arr);
    x = p += 1;

    assert(x == &arr[3]);
    assert(p.load() == &arr[3]); */

    Stack<Animal> stack;
    int count = 10;
    int v = 0;
    std::vector<thread> threads;
    for (size_t i = 0; i < count; i++)
    {
        threads.emplace_back([&,i]() {
            Animal t11(i);
            stack.push(t11);
        });
    }
    for (size_t i = 0; i < count; i++)
    {

        threads[i].join();
    }
    stack.printStack();

    return 0;
}