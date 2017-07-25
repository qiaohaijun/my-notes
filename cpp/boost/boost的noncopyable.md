```c++
#ifndef BOOST_NONCOPYABLE_HPP_INCLUDED
#define BOOST_NONCOPYABLE_HPP_INCLUDED

namespace boost {

//  Private copy constructor and copy assignment ensure classes derived from
//  class noncopyable cannot be copied.

//  Contributed by Dave Abrahams

namespace noncopyable_  // protection from unintended ADL
{
  class noncopyable
  {
   protected:
      noncopyable() {}
      ~noncopyable() {}
   private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      const noncopyable& operator=( const noncopyable& );
  };
}

typedef noncopyable_::noncopyable noncopyable;

} // namespace boost

#endif  // BOOST_NONCOPYABLE_HPP_INCLUDED

```
