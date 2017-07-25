常规函数每个单词的首字母大写，使用命令式语气, 比如:
1. openFile()
2. checkFileName()

---

而存取函数或者短小的内联函数使用小写加下划线，且与访问变量相吻合。
比如
1. set_num_errors();

```c++
 class Player {
  public:
    void set_player_id(const int player_id) {
      return player_id_ = player_id;
    }
  private:
    int player_id_;
 };
 
 ```
 
 
