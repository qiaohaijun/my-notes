class Widget : public std::enable_shared_from_this<Widget> {
    std::shared_ptr<Widget> GetPtr() {
        return shared_from_this();
    }
};

int main() {
    auto widget = std::make_shared<Widget>();
    btn->GetPtr();
}
