#include <iostream>
#include <algorithm>
#include <vector>
namespace DesignPatterns::TemplateMethod // Subclass-Based Comparison
{

class Sorter
{
public: 
    void sort(std::vector<int>& data)
    {
        std::sort(data.begin(), data.end(), [&](int a, int b) 
        {
            return compare(a, b);
        });
    }

private:
    virtual bool compare(int a, int b) = 0;
};

class AscendingSorter: public Sorter
{
private:
    bool compare(int a, int b) override
    {
        return a < b;
    }
};

class DescendingSorter: public Sorter
{
private:
    bool compare(int a, int b) override
    {
        return a > b;
    }
};

}

namespace DesignPatterns::Strategy
{

class Comparator 
{
public:
    virtual bool compare(int a, int b) const = 0;
};

class AscendingComparator : public Comparator 
{
public:
    bool compare(int a, int b) const override 
    {
        return a < b;
    }
};

class DescendingComparator : public Comparator 
{
public:
    bool compare(int a, int b) const override 
    {
        return a > b;
    }
};

class Sorter 
{
public:
    void sort(std::vector<int>& data, const Comparator& comp) 
    {
        std::sort(data.begin(), data.end(), 
            [&comp](int a, int b) 
            {
                return comp.compare(a, b);
            });
    }
};

}

namespace DesignPatterns::Parameterized // C++ templates
{

template<typename Compare>
void sort(std::vector<int>& data, Compare comp) {
    std::sort(data.begin(), data.end(), comp);
}
    
}



int main()
{
    {
        std::vector<int> data = {5, 2, 9, 1};
        DesignPatterns::TemplateMethod::AscendingSorter sorter;
        sorter.sort(data);

        for (int n : data) 
        {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> data = {5, 2, 9, 1};
        DesignPatterns::Strategy::DescendingComparator comp;

        DesignPatterns::Strategy::Sorter sorter;
        sorter.sort(data, comp);


        for (int n : data) 
        {
            std::cout << n << " ";
        } 
        std::cout << std::endl;
    }
    {        
        std::vector<int> data = {5, 2, 9, 1};

        DesignPatterns::Parameterized::sort(data, 
            [](int a, int b) { return a < b; }
        );

        for (int n : data) 
        {
            std::cout << n << " ";
        } 
        std::cout << std::endl;

    }
}