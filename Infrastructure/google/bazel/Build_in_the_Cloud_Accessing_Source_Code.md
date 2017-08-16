Build in the Cloud: Accessing Source Code

This is the first in a four part series describing how we use the cloud to scale building and testing of software at Google. This series elaborates on a presentation given during the Pre-GTAC 2010 event in Hyderabad. Please see our first post for more details on the types of problems we are solving in Engineering Tools at Google.

Much of our day-to-day activities as software engineers involves source code. When we join a project one of the first things we do is look at the source. We want to build it, run it, experiment with changes, test it, and challenge our assumptions about how it works. For most of us this means we start by “checking out” the source from version control. For small to moderately sized projects almost any reasonable version control system is adequate. But as the number of engineers increases and the code base grows, this can put a strain on the version control system and decrease engineer productivity.

Here at Google, all products are built from head. This approach has advantages: the code is open for anyone to explore and tinker with, it avoids the headaches associated with merging long-lived branches, and building from source ensures there are no binary compatibility issues between libraries. The downside is, with over a hundred million lines of code, it takes a long time to check out. And Google is a global company, which means checkout times are amplified in distributed offices. By computing dependency graphs and using this information to limit the number of files checked out, we have been somewhat successful in reducing checkout time. However, computing dependencies also takes time, and even with this improvement things still took too long.

Engineer time lost to checking out code is the most obvious cost, but the true cost is much higher. Automated build and testing systems also need access to source code. Time spent checking out code in these systems increases the feedback cycle, which decreases their utility. It also increases the complexity of these systems since they are required to maintain state on a file system and interact closely with the version control system for what is essentially read-only access to source code.

In fact, we have found that engineers check out and edit a very small amount code relative to the amount read to perform builds. This is because we always build from source, and changes tend to be localized to a small part of our source tree. So, both engineers and automated systems primarily need quick, read-only access to the large quantity of unedited code required to perform their builds. The unedited code itself is immutable, since it doesn’t change once it’s checked in to the version control system. This means we can use Google infrastructure to mirror all version control information in the cloud as a way to provide fast and scalable read-only access to source code.

In our system, every revision of every file has an associated metadata record. The metadata includes information such as the path location in the repository, the file name, size, version, and such. It also includes a digest of the content associated with this file revision. This digest is the hash of the file content itself, created using a hashing function appropriate for Content Addressable Storage (CAS). There are many areas in our system where we utilize CAS; expect to hear more about it in subsequent posts.

A view of the metadata for version 5 of /some/path/foo.cc and CAS file content:



Our system watches for changes arriving in the version control system. As changes arrive, we hash the file contents to compute digests and insert the content into BigTable. We then construct metadata records for each affected file and insert these into BigTable. At this point we have a complete history of all file versions in the cloud.

Now that we have this data, what do we do with it? We could write a command line tool to checkout code from the cloud to the developer’s workstation. This would be an improvement because it reduces load on the version control system, and replicating the data near distributed offices improves performance by reducing network latency. However it would be extremely useful if, instead of checking out source before it is actually needed, we automatically downloaded code on-demand.

This can be accomplished by writing a custom file system to provide a read-only view of the version history. The File System in Userspace (FUSE) kernel module is a convenient way of implementing a user space daemon that implements such a file system. Users interact with this source file system like any other file system, with the exception that certain path elements are special in that they configure the version information.

For example, accessing foo.cc at global version 1000 from our previous example:



The file system resolves metadata calls such as stat() and readdir() by first interpreting the version number from the path and then querying the version control data in the cloud.

For example, using gcc (or any other tool) to compile foo.cc, where gcc first calls stat() to check file existence:



This allows users and tools to explore the version control using just the version metadata. File content is only downloaded at the point where it is opened. Since file versions are immutable, content can be cached and reused indefinitely. The use of CAS provides de-duplication of file content for free and the same content is never downloaded twice.

By putting our revision history in the cloud we provide engineers with complete access to all the source, and yet almost no time is spent checking out code. Replicating the cloud to multiple geographic regions ensures that performance is similar in all offices around the world. Finally, automated build and test systems can easily access code via a simple file system interface without dealing with the version control system directly. All of this adds up to a fast and efficient system which enables engineers and automated systems to focus on building and testing software instead of the mechanics of downloading source code.

Stay tuned! In this post we mentioned dependency analysis and Content Addressable Storage. Part two in this series describes our build system and how it relates to these topics.

- Nathan York


### link

- http://google-engtools.blogspot.com/2011/06/build-in-cloud-accessing-source-code.html
