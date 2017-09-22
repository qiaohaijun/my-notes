Google is starting to contribute a new multi-master implementation,
calling it Git Ketch. Changes are on the Eclipse Gerrit[1].


What is Git Ketch?
------------------
Git Ketch is a multi-master Git repository management system. Writes
(such as git push) can be started on any server, at any time. Writes
are successful only if a majority of participant servers agree.

Acked writes are durable against server failure, due to a majority of
the participants storing all required objects.


Do I need DFS?
--------------
No. We realized not everyone wants to run JGit DFS. Git Ketch is a
higher-level, storage-agnostic service that can use both classical
local file repositories, and DFS type repositories.


Do I need JGit?
---------------
Sort of.

The Ketch Leader process running the consensus algorithm is currently
implemented in Java, relying on JGit. However...

Any Git repository served by Git >= 2.4.0 can act as a voting
participant (the required feature is `git push --atomic`). The
consensus algorithm runs on the Git wire protocol.


Where's the rest?
-----------------
Google's prior multi-master implementation is 4 years old and heavily
intertwined with internal source code. We are rewriting the
multi-master logic and open sourcing as we go. We think this will make
it easier for the JGit project to review and digest.

Unfortunately, major portions are being rewritten from scratch, as
there are segments deeply connected to our internal implementation of
JGit DFS on Google Bigtable, or to our internal authentication and RPC
protocols. None of that makes sense in the open source JGit project.

So, the rest is Coming Soon(TM). We are working on it.
You can help by providing feedback. :)


Why is it called Git Ketch?
---------------------------
Git Ketch is modeled on the Raft Consensus Algorithm[2]. A ketch[3]
sailing vessel is faster and more nimble than a raft[4]. It can also
carry more source codes.

Git Ketch front-loads replication costs, which we think vaguely
resembles a ketch sailing vessel's distinguishing feature of the main
mast on the front of the ship.


Footnotes
---------
- [1] https://git.eclipse.org/r/64206
- [2] https://raft.github.io/
- [3] https://www.google.com/search?q=ketch&tbm=isch
- [4] https://www.google.com/search?q=raft&tbm=isch
