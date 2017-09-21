JGit是git的java版本的API

```java
Git git =Git.cloneRepository()
.setURI("https://github.com/eclipse/jgit.git")
.setDirectory("/path/to/repo")
.call();
```

### link
- http://www.importnew.com/19970.html
