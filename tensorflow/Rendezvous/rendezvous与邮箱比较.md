1. 邮箱发送的是邮件; rendezvous发送的是tensor
2. 邮件有写信人和收信人; rendezvous的每个tensor都有producer和consumer
3. 信有很多; rendezvous也有很多的tensor在传递
4. 写信人随时写信, 直接发送; rendezvous的producer从不阻塞
5. 收信人需要自己检查; rendezvous可以阻塞, 也可以设置callback.
