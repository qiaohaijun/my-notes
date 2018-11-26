这个知识点是在今天魔改tf serving的时候学到的.

### 需求背景
将 `rest api` 从同步改为异步. 这个时候`net_http::ServerRequestInterface`这个对象的生命周期就有写问题, 需要处理.
