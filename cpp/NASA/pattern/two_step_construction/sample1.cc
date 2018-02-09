class TwoPhaseCons{
    private:
        // 第一阶段构造函数
        TwoPhaseCons()
        {
        }

        //第二阶段构造函数
        bool construce()
        {
            return true;
        }
    public:

        // 对象创建函数
        static TwoPhaseCons* NewInstance();
};

TwoPhaseCons* TwoPhaseCons:: NewInstance(){

    TwoPhaseCons* ret = new TwoPhaseCons();

    if(!(ret && ret->construct())){

        delete ret;

        ret = NULL;
    }

    return ret;
}
