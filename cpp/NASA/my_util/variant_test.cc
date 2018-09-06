void TestVariant()
{
    typedef Variant<int, char, double> cv;
    int x = 10;

    cv v =x;
    v = 1;
    v = 1.123;
    v = "";//compile error
    v.Get<int>(); //1
    v.Get<double>(); //1.23
    v.Get<short>(); //exception: short is not defined. current type is int
    v.Is<int>();//true
}
