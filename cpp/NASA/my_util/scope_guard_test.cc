void TestScopeGuard()
{    
    std::function < void()> f = [] { cout << "cleanup from unnormal exit" << endl; };
    //正常退出
    {        
        auto gd = MakeGuard(f);
        //...
        gd.Dismiss();
    }

    //异常退出
    {
        auto gd = MakeGuard(f);
        //...
        throw 1;
    }

    //非正常退出
    {
        auto gd = MakeGuard(f);
        return;
        //...
    }
}
