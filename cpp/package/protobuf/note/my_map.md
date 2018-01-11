```protobuf
message KeyValue{
     required string key = 1;
     required string value = 2;
}
message Map {
     repeated KeyValue items = 1;
}

message Foo {
     required string id = 1;
     optional Map map = 2;
}

```


### link
- https://groups.google.com/forum/#!topic/protobuf/lqXXV1IwcgM
