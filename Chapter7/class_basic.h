#pragma once

namespace Chapter7
{
    class SalesData
    {
    //友元函数在类内的声明
    friend SalesData add(const SalesData& _sd1, const SalesData& _sd2);
    private:
        std::string bookNo;
        double revenue;
        unsigned units_sold;
    
    public:
        SalesData(): bookNo(""), revenue(0), units_sold(0) { }
        SalesData(std::string _bookNo, double _revenue, unsigned _units)
        {
            bookNo = _bookNo;
            revenue = _revenue;
            units_sold = _units;
        }
        
        std::string isbn() const { return bookNo; }
        //std::string change_isbn() const { bookNo = "fake"; } // compile error
        void set_isbn(const std::string _bookNo) { bookNo = _bookNo; }

        SalesData& Combine(const SalesData& rhs)
        {
            units_sold += rhs.units_sold;
            revenue += rhs.revenue;

            return *this;
        }
    };

    SalesData add(const SalesData& _sd1, const SalesData& _sd2);

    void Demo1();
    void Demo2();
    void Demo3();
    void Demo4();
    void Demo5();
    void Demo6();
    void Demo7();
    void Demo8();
    void Demo9();
    void Demo10();
}