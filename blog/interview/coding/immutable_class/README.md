### Question
1. Define a Color class (red, blue, green, name)
2. Make it thread safe
3. Make it immutable

### Tips
1. add getRGB, add invert, add check
2. check doesn't need to be synchronized; readwrite lock for fine grained lock; both set and get needs tobe synchronized; constructor don't need to be synchronized
3. Remove setters; add finals; invert; what if have a new field: Date? (defensive copy)