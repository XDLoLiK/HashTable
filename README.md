# HashTable
MIPT laboratory work. Hash table acceleration. Comparison between different hash functions' collisions.

## Collisions
hash table size: 2^10 - 5 (prime number)

### Identical one

![one](https://user-images.githubusercontent.com/66733765/163371649-57f4e54f-0a9f-4792-b92c-1e4fb1f90c71.jpg)

### First ascii code

![first_ascii](https://user-images.githubusercontent.com/66733765/163372458-5592036b-1fba-4fe8-82b0-ec3a6e153faa.jpg)

### Sum of all ascii codes

![ascii_sum](https://user-images.githubusercontent.com/66733765/163372649-c3fda432-bdd8-4b95-b56f-4b4fcb2f56dd.jpg)

### Word length

![strlen](https://user-images.githubusercontent.com/66733765/163372839-c4d64b3d-d451-4f88-b6bf-2a2605fdbe19.jpg)

### Rolling hash

![rolling_hash](https://user-images.githubusercontent.com/66733765/163372967-c1b25a69-77bc-4e3c-b151-3de8b5749745.jpg)

### Murmur hash

![murmurhash](https://user-images.githubusercontent.com/66733765/163373933-1c4b4536-43cc-4867-ad77-99a29ba74dc8.jpg)

### crc32

![crc32](https://user-images.githubusercontent.com/66733765/163374045-45c8fd5a-908f-4263-bcb2-1cc76e0c8b08.jpg)

## Acceleration
All tests were made with the following parametres:
* compilation flags: -O0
* hash table size: 2^16 + 1 (prime number)
* inserted from: Hamlet.txt
* searched for from: Dictionary.txt (64 times)
* secondary data structure - linked list

### 0) no optimization <br/>
Time: 2.847207s (average of 5 tests) <br/>

### 1) crc32 optimization <br/>
Profiler view results: hash function takes 83.57% of the time => needs to be accelerated <br/>
Solution: replace murmur3 with crc32 <br/>
Implementation: inline assembly <br/>
Time: 0.684802s (average of 5 tests) <br/>

### 2) strcmp optimization <br/>
Profiler view results: strcmp is called more than 10 000 000 times, pretty slow => needs to be accelerated <br/>
Solution: self-written assembly function <br/>
Implementation: in hash table we only need to check the strings for equality, <br/>
strings are all 32bytes-long, end with zeros => use ymm registers and avx instructions (vpcmpeqb, vpmovmskb) <br/>
Time: 0.626314s (average of 5 tests) <br/>

### 3) strcpy optimization <br/>
Profiler view results: hash_table_find takes pretty much time, but can't be accelerated <br/>
because it just gets called too often => optimize strcpy <br/>
Solution: use avx cpy instruction (\_mm256_store_si256(...)) <br/>
Implementation: intrinsoc functions <br/>
Time: 0.611461s (average of 5 tests) <br/>

### 4) memset optimization <br/>
Profiler view results: memset has overtaken strcmp after its optimization, takes too much time now
Solution: replace memset with some fancy avx instruction (\_mm256_set1_ps(0)) <br/>
Implementation: intrinsoc functions <br/>
Time: 0.598305 (average of 5 tests) <br/>

### 5) "chrome" optimization <br/>
Profiler view results: Why is my laptop so loud? <br/>
Solution: close google-chrome browser <br/>
Implementation: obvious <br/>
Time: -inf (average of 5 tests) <br/>

## Conclusion
acceleration ~ 4.76x <br/>
asm lines ~ 17 <br/>
efficiency factor ~ 279.9 <br/>
time spent ~ 2 days (2 hours excluding debuging) => worthy <br/>
