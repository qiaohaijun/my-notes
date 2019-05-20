Writing Testable Code

Wednesday, August 06, 2008

by Miško Hevery

So you decided to finally give this testing thing a try. 
But somehow you just can't figure out how to write a unit-test for your class. 
Well there are no tricks to writing tests, there are only tricks to writing testable code. 
If I gave you testable code you would have no problems writing a test for it. 
But, somehow you look at your code and you say, "I understand how to write tests for your code, but my code is different ". 
Well your code is different because you violated one or more of the following things. 
(I will go into the details of each in a separate blog posts)


### Mixing object graph construction with application logic: 
In a test the thing you want to do is to instantiate a portion 
(ideally just the class under test) of your application and apply some stimulus to the class and assert that the expected behavior was observed. 
In order to instantiate the a class in isolation we have to make sure that the class itself does not instantiate other objects (and those objects do not instantiate more objects and so on). 
Most developers freely mix the "new" operator with the application logic. 
In order to have a testable code-base your application should have two kinds of classes.
The factories, these are full of the "new" operators and are responsible for building the object graph of your application, but don't do anything.
And the application logic classes which are devoid of the "new" operator and are responsible for doing work.
In test we want to test the application logic. 
And because the application logic is devoid of the "new" operator, 
we can easily construct an object graph useful for testing where we can strategically replace the real classes for test doubles. 
(see: How to Think About the “new” Operator with Respect to Unit Testing)


### Ask for things, Don't look for things (aka Dependency Injection / Law of Demeter): 
OK, you got rid of your new operators in your application code. But how do I get a hold of the dependencies. Simple: Just ask for all of the collaborators you need in your constructor. If you are a House class then in your constructor you will ask for the Kitchen, LivingRoom, and BedRoom, you will not call the "new" operator on those classes (see 1). Only ask for things you directly need, If you are a CarEngine, don't ask for FuelTank, only ask for Fuel. Don't pass in a context/registry/service-locator. So if you are a LoginPage, don't ask for UserContext, instead ask for the User and the Athenticator. Finally don't mix the responsibility of work with configuration, If you are an Authenticator class don't pass in a path of the configuration information which you read inside the constructor to configure yourself, just ask for the configuration object and let some other class worry about reading the object from the disk. In your tests you will not want to write a configuration into a disk just so that your object can read it in again. (see: Breaking the Law of Demeter is Like Looking for a Needle in the Haystack)


### Doing work in constructor: 
A class under tests can have tens of tests. Each test instantiates a slightly different object graph and than applies some stimulus and asserts a response. As you can see the most common operation you will do in tests is instantiation of object graphs, so make it easy on yourself and make the constructors do no work (other than assigning all of the dependencies into the fields). Any work you do in a constructor, you will have to successfully navigate through on every instantiation (read every test). This may be benign, or it may be something really complex like reading configuration information from the disk. But it is not just a direct test for the class which will have to pay this price, it will also be any related test which tries to instantiate your class indirectly as part of some larger object graph which the test is trying to create.

### Global State: 
Global state is bad from theoretical, maintainability, and understandability points of view, but is tolerable at run-time as long as you have one instance of your application. However, each test is a small instantiation of your application in contrast to one instance of application in production. The global state persists from one test to the next and creates mass confusion. Tests run in isolation but not together. Worse yet, tests fail together but problems can not be reproduced in isolation. Order of the tests matters. The APIs are not clear about the order of initialization and object instantiation, and so on. I hope that by now most developers agree that global state should be treated like GOTO.

### Singletons (global state in sheep's clothing): 
It amazes me that many developers will agree that global state is bad yet their code is full of singletons. (Singletons which enforce their own singletoness through private constructor and a global instance variable) The core of the issue is that the global instance variables have a transitive property! All of the internal objects of the singleton are global as well (and the internals of those objects are global as well... recursively). Singletons are by far the most subtle and insidious thing in unit-testing. I will post more blogs on this topic later as I am sure it will create comments from both sides.

### Static methods: (or living in a procedural world): 
The key to testing is the presence of seams (places where you can divert the normal execution flow). Seams are essentially polymorphism (Polymorphism: at compile-time the method you are calling can not be determined). Seams are needed so that you can isolate the unit of test. If you build an application with nothing but static methods you have procedural application. Procedural code has no seams, at compile-time it is clear which method calls which other method. I don't know how to test application without seams. How much a static method will hurt from a testing point of view depends on where it is in you application call graph. A leaf method such as Math.abs() is not a problem since the execution call graph ends there. But if you pick a method in a core of your application logic than everything behind the method becomes hard to test, since there is no way to insert test doubles (and there are no seams). Additionally it is really easy for a leaf method to stop being a leaf and than a method which was OK as static no longer is. I don't know how to unit-test the main method!


### Favor composition over inheritance:
At run-time you can not chose a different inheritance, but you can chose a different composition, this is important for tests as we want to test thing in isolation. Many developers use inheritance as code reuse which is wrong. Whether or not inheritance is appropriate depends on whether polymorphism is going on. Inheriting from AuthenticatedServlet will make your sub-class very hard to test since every test will have to mock out the authentication. This will clutter the focus of the test, with the things we have to do to successfully navigate the super class. But what if AuthenticatedServlet inherits from DbTransactionServlet? (that gets so much harder)

### Favor polymorphism over conditionals: 
If you see a switch statement you should think polymorphisms. If you see the same if condition repeated in many places in your class you should again think polymorphism. Polymorphism will break your complex class into several smaller simpler classes which clearly define which pieces of the code are related and execute together. This helps testing since a simpler/smaller class is easier to test.

### Mixing Service Objects with Value Objects: 
There should be two kinds of objects in your application. (1) Value-objects, these tend to have lots of getters / setters and are very easy to construct are never mocked, and probably don't need an interface. (Example: LinkedList, Map, User, EmailAddress, Email, CreditCard, etc...). (2) Service-objects which do the interesting work, their constructors ask for lots of other objects for colaboration, are good candidates for mocking, tend to have an interface and tend to have multiple implementations (Example: MailServer, CreditCardProcessor, UserAthenticator, AddressValidator). A value-object should never take a service object in its constructor (since than it is not easy to construct). Value-objects are the leafs of your application graph and tend to be created freely with the "new" operator directly in line with your business logic (exception to point 1 since they are leafs). Service-objects are harder to construct and as a result are never constructed with a new operator in-line, (instead use factory / DI-framework) for the object graph construction. Service-objects don't take value-objects in their constructors since DI-frameworks tend to be unaware about the how to create a value-object. From a testing point of view we like value-objects since we can just create them on the fly and assert on their state. Service-objects are harder to test since their state is not clear and they are all about collaboration and as a result we are forced to use mocking, something which we want to minimize. Mixing the two creates a hybrid which has no advantages of value-objects and all the baggage of service-object.


### Mixing of Concerns: 
If summing up what the class does includes the word "and", or the class would be challenging for new team members to read and quickly "get it", or the class has fields that are only used in some methods, or the class has static methods that only operate on parameters than you have a class which mixes concerns. These classes are hard to test since there are multiple objects hiding inside of them and as a result you are testing all of the objects at once.
So here is my top 10 list on testability, the trick is translating these abstract concepts into concrete decisions in your code.
