# Huge array
Huge amount of items container for system for fast iterations without overhead of resizing.


## Solutions
1. Allocate one big array, avoid resizing buffer. But overhead may occur when removing item from array.
2. Use handle lookup to find object for safe weak reference to item
3. Allow holes in array, use index lookup for linear iterations
4. Swap hole with last item, index lookup solve the problem of outer index into items. Now array are dense, can be linear iterations without checking hole.
5. If resizing buffer are needed, use virtual memory to avoid defragments, copy memory from old buffer new buffer.


## Reading resources
- [Bitsquid ID Lookup Table](https://bitsquid.blogspot.com/2011/09/managing-decoupling-part-4-id-lookup.html)
- [Our Machinery Virtual Memory Tricks](https://ruby0x1.github.io/machinery_blog_archive/post/virtual-memory-tricks/index.html)