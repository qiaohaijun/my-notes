class Widget {
    std::shared_ptr<Widget> GetPtr() {
        return shared_ptr<Widget>(this);     // 错误
    }
};

int main() {
    auto widget = std::make_shared<Widget>();
    widget->GetPtr();
}
